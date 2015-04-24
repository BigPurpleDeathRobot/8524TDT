/*
 * gamepad kernel module
 * 
 * todo: interrupts, concurrency things...
 */

#include <asm/io.h>
#include <asm/uaccess.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>

#include "efm32gg.h"

// hard coded for platform
#define GPIO_EVEN_IRQ 17
#define GPIO_ODD_IRQ  18

//// FUNCTION PROTOTYPES ////
static int gamepad_open(struct inode *inode, struct file *filp);
static int gamepad_release(struct inode *inode, struct file *filp);
static ssize_t gamepad_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static int gamepad_fasync(int fd, struct file *filp, int mode);
static irqreturn_t intHandlerGPIO(int irq, void *dev_id); 

//// GLOBALS ////
static dev_t dev_number; // variable for first device number
static struct cdev cdev; // struct for character device structure
static struct class *cl; // struct for the device class
void *gpio_portc_vmem; // pointer for the ioremapped virtual memory
void *gpio_int_vmem; // pointer for the ioremapped virtual memory

static struct file_operations gamepad_fops = {
	.owner = THIS_MODULE,
	.open = gamepad_open,	
	.read = gamepad_read,
	.fasync = gamepad_fasync,	
	.release = gamepad_release,
};

//// FUNCTIONS FOR FILE OPERATIONS ////
static int gamepad_open(struct inode *inode, struct file *filp){
	printk(KERN_INFO "open()\n");
	return 0;
}

static int gamepad_release(struct inode *inode, struct file *filp){
	printk(KERN_INFO "close()\n");
	return 0;
}

static ssize_t gamepad_read(struct file *filp, char __user *buf, size_t len, loff_t *off){
	printk(KERN_INFO "read()\n");
	uint8_t data = ~ioread8(gpio_portc_vmem + GPIO_PC_DIN);
	printk(KERN_DEBUG "%u\n", data);
	copy_to_user(buf, &data, 1);
	return 0;
}

static int gamepad_fasync(int fd, struct file *filp, int mode){
	return 0;	
}

//// GPIO SETUP AND CLEANUP ////
static int setupGPIO(void){
	// request mem region for portc
	if(request_mem_region(GPIO_PC_BASE, 0x24, "gamepad") == NULL){
		printk(KERN_ERR "mem region request for PORTC failed\n");
		return -1;
	}
	// remap mem region into virtual memory, cleanup on error
	if((gpio_portc_vmem = ioremap_nocache(GPIO_PC_BASE, 0x24)) == NULL){
		printk(KERN_ERR "mem region remap for PORTC failed\n");
		release_mem_region(GPIO_PC_BASE, 0x24);
		return -1;
	}
	// setup registers
	iowrite32(0x33333333, gpio_portc_vmem + GPIO_PC_MODEL); // set pins 0-7 as inputs
	iowrite32(0x000000ff, gpio_portc_vmem + GPIO_PC_DOUT); // enable internal pull-ups
				
	return 0;
}

static void cleanupGPIO(void){
	// revert changes to registers
	iowrite32(0x00000000, gpio_portc_vmem + GPIO_PC_MODEL);
	iowrite32(0x00000000, gpio_portc_vmem + GPIO_PC_DOUT);
	// cleanup memory	
	iounmap(gpio_portc_vmem);
	release_mem_region(GPIO_PC_BASE, 0x24);
	
}

//// GPIO INTERRUPT SETUP AND CLEANUP
static int setupGPIOint(void){
	// request mem region for gpio interrupts, cleanup on error
	if(request_mem_region(GPIO_INT_BASE, 0x20, "gamepad") == NULL){
		printk(KERN_ERR "mem region request for GPIO INT failed\n");
		return -1;
	}
	// remap mem region into virtual memory, cleanup on error
	if((gpio_int_vmem = ioremap_nocache(GPIO_INT_BASE, 0x20)) == NULL){
		printk(KERN_ERR "mem region remap for GPIO INT failed\n");
		release_mem_region(GPIO_INT_BASE, 0x20);	
		return -1;
	}
	// setup registers
	iowrite32(0x22222222, gpio_int_vmem + GPIO_EXTIPSELL); // portc interrupt source
	iowrite32(0x000000ff, gpio_int_vmem + GPIO_EXTIFALL); // interrupt on falling edge
	iowrite32(0x000000ff, gpio_int_vmem + GPIO_IEN); // enable interrupts
	
	// register interrupt handler, cleanup on error
	if(request_irq(GPIO_EVEN_IRQ, &intHandlerGPIO, 0, "gamepad", NULL)){
		printk(KERN_ERR "irq request for GPIO_EVEN failed\n");
		iounmap(gpio_int_vmem);
		release_mem_region(GPIO_INT_BASE, 0x20);
		return -1;
	}
	if(request_irq(GPIO_ODD_IRQ, &intHandlerGPIO, 0, "gamepad", NULL)){
		printk(KERN_ERR "irq request for GPIO_ODD failed\n");
		free_irq(GPIO_EVEN_IRQ, NULL);
		iounmap(gpio_int_vmem);
		release_mem_region(GPIO_INT_BASE, 0x20);
		return -1;
	}
	
	return 0;		
}

static void cleanupGPIOint(void){
	// free irq
	free_irq(GPIO_ODD_IRQ, NULL);
	free_irq(GPIO_EVEN_IRQ, NULL);
	// revert changes to registers
	iowrite32(0x00000000, gpio_int_vmem + GPIO_EXTIPSELL);
	iowrite32(0x00000000, gpio_int_vmem + GPIO_EXTIFALL);
	iowrite32(0x00000000, gpio_int_vmem + GPIO_IEN);
	// cleanup memory
	iounmap(gpio_int_vmem);
	release_mem_region(GPIO_INT_BASE, 0x20);	
}

//// GPIO INTERRUPT HANDLER ////
static irqreturn_t intHandlerGPIO(int irq, void *dev_id){
	printk(KERN_DEBUG "hello from gpio interrupt handler!\n");
	iowrite32(0xff, gpio_int_vmem + GPIO_IFC);
	return IRQ_HANDLED;
}

//// INIT AND EXIT ////

static int __init gamepad_init(void)
{
	printk("Initializing gamepad module...\n");
	// dynamic allocation of device numbers
	if(alloc_chrdev_region(&dev_number, 0, 1, "gamepad") < 0){
		printk(KERN_ERR "allocation of device numbers failed\n");
		return -1;
	}
	// create device file, cleanup on error
	if((cl = class_create(THIS_MODULE, "gamepad_class")) == NULL){
		printk(KERN_ERR "creation of gamepad class failed\n");	
		unregister_chrdev_region(dev_number, 1);
		return -1;
	}
	if(device_create(cl, NULL, dev_number, NULL, "gamepad") == NULL){
		printk(KERN_ERR "creation of device file failed\n");		
		class_destroy(cl);
		unregister_chrdev_region(dev_number, 1);
		return -1;
	}  
	// initialize cdev structure
	cdev_init(&cdev, &gamepad_fops);
	// register cdev structure with kernel, cleanup on error
	if(cdev_add(&cdev, dev_number, 1) == -1){
		printk(KERN_ERR "registering cdev structure with kernel failed\n");	
		device_destroy(cl, dev_number);
		class_destroy(cl);
		unregister_chrdev_region(dev_number, 1);
		return -1;
	}
	setupGPIO();
	setupGPIOint();
	printk(KERN_DEBUG "...done\n");
	return 0;
}

static void __exit gamepad_cleanup(void)
{
	printk("Cleaning up gamepad module...\n");	
	// call in the cleanup crew...
	cleanupGPIOint();
	cleanupGPIO();
	cdev_del(&cdev);
	device_destroy(cl, dev_number);
	class_destroy(cl);		
	unregister_chrdev_region(dev_number, 1);
	printk(KERN_DEBUG "...done\n");

}

//// MISC ////

// inform kernel of init and exit
module_init(gamepad_init);
module_exit(gamepad_cleanup);

// meta data
MODULE_DESCRIPTION("kernel module for gamepad");
MODULE_LICENSE("GPL");

