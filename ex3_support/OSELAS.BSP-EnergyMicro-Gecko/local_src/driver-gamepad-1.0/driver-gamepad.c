/*
 * gamepad kernel module
 * 
 * todo: interrupts, concurrency, general robustness....
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

#include "efm32gg.h"

//// FUNCTION PROTOTYPES ////
static int gamepad_open(struct inode *inode, struct file *filp);
static int gamepad_release(struct inode *inode, struct file *filp);
static ssize_t gamepad_read(struct file *filp, char __user *buf, size_t len, loff_t *off);
static ssize_t gamepad_write(struct file *filp, const char __user *buf, size_t len, loff_t *off);

//// GLOBALS ////
static dev_t dev_number; // variable for first device number
static struct cdev cdev; // variable for character device structure
static struct class *cl; // variable for the device class
void *gpio_portc_vmem; // pointer for the ioremapped virtual memory
void *gpio_porta_vmem; // pointer for the ioremapped virtual memory

static struct file_operations gamepad_fops = {
	.owner = THIS_MODULE,
	.read = gamepad_read,
	.write = gamepad_write,
	.open = gamepad_open,
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

static ssize_t gamepad_write(struct file *filp,	const char __user *buf, size_t len, loff_t *off){
	printk(KERN_INFO "write()\n");
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
	printk(KERN_DEBUG "...done\n");
	return 0;
}

static void __exit gamepad_cleanup(void)
{
	printk("Cleaning up gamepad module...\n");	
	// call in the cleanup crew...
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

