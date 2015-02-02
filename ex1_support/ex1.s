        .syntax unified
	
	      .include "efm32gg.s"

	/////////////////////////////////////////////////////////////////////////////
	//
  	// Exception vector table
  	// This table contains addresses for all exception handlers
	//
	/////////////////////////////////////////////////////////////////////////////
	//test for branch
        .section .vectors
	
	      .long   stack_top               /* Top of Stack                 */
	      .long   _reset                  /* Reset Handler                */
	      .long   dummy_handler           /* NMI Handler                  */
	      .long   dummy_handler           /* Hard Fault Handler           */
	      .long   dummy_handler           /* MPU Fault Handler            */
	      .long   dummy_handler           /* Bus Fault Handler            */
	      .long   dummy_handler           /* Usage Fault Handler          */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* SVCall Handler               */
	      .long   dummy_handler           /* Debug Monitor Handler        */
	      .long   dummy_handler           /* Reserved                     */
	      .long   dummy_handler           /* PendSV Handler               */
	      .long   dummy_handler           /* SysTick Handler              */

	      /* External Interrupts */
	      .long   dummy_handler
	      .long   gpio_handler            /* GPIO even handler */
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   gpio_handler            /* GPIO odd handler */
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler
	      .long   dummy_handler

	      .section .text

	/////////////////////////////////////////////////////////////////////////////
	//
	// Reset handler
  	// The CPU will start executing here after a reset
	//
	/////////////////////////////////////////////////////////////////////////////

	      .globl  _reset
	      .type   _reset, %function
        .thumb_func
_reset: 
	      
	      // load CMU base address
	      ldr r1, =CMU_BASE

	      // load current value of HFPERCLK ENABLE
	      ldr r2, [r1, #CMU_HFPERCLKEN0]
	
	      // set bit for GPIO clk
	      mov r3, #1
	      lsl r3, r3, #CMU_HFPERCLKEN0_GPIO
	      orr r2, r2, r3

	      // store new value
	      str r2, [r1, #CMU_HFPERCLKEN0]

	      
	      // set high drive strength for port A
	      ldr r4, =GPIO_PA_BASE
	      mov r2, #0x2
	      str r2, [r4, #GPIO_CTRL]

	      // set pins 8-15 to outputs for port A
	      mov r2, #0x55
	      orr r2, r2, r2, lsl #8
	      orr r2, r2, r2, lsl #16
	      str r2, [r4, #GPIO_MODEH]

	      // turn of all leds, active low
	      mov r2, #0xff
	      lsl r2, r2, #8
	      str r2, [r4, GPIO_DOUT]

	      // set pins 0-7 as inputs for port C
	      ldr r5, =GPIO_PC_BASE
	      mov r2, #0x33
	      orr r2, r2, r2, lsl #8
	      orr r2, r2, r2, lsl #16
	      str r2, [r5, #GPIO_MODEL]

	      // enable internal pull-up for port C
	      mov r2, #0xff
	      str r2, [r5, #GPIO_DOUT]

//_loop:
	      // loop forever and ever
	      //bl _loop
	      //b _loop



	/////////////////////////////////////////////////////////////////////////////
	//
  	// GPIO handler
  	// The CPU will jump here when there is a GPIO interrupt
	//
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
gpio_handler:  

	      // read inputs and set outputs
	      ldr r1, [r5, #GPIO_DIN]
	      lsl r2, r1, #8
	      str r2, [r4, #GPIO_DOUT]
	      b gpio_handler	
	/////////////////////////////////////////////////////////////////////////////
	
        .thumb_func
dummy_handler:  
        b .  // do nothing

