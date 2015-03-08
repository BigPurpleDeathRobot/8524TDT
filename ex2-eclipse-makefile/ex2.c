#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "proto.h"


/* Declaration of peripheral setup functions */
static void setupNVIC();
static void setupSleepMode(uint8_t);


/* Your mama will start executing here */
int main(void) 
{
  /* Call the peripheral setup functions */
  setupGPIO();
  setupDAC();
  setupTimer();
  //setupLEtimer();
  
  /* Enable interrupt handling */
  setupNVIC();
  
  /* set sleep mode */
  setupSleepMode(2);
  
  /* in his house at R'lyeh, dead Cthulhu waits dreaming */
  __asm__("wfi");
  
}

void setupNVIC()
{
  *ISER0 = 0x1802;
  //*ISER0 = 0x4000802;
}

void setupSleepMode(uint8_t arg)
{
	/*
	The SCR controls features of entry to and exit from low power state.
	arg = 0 only sleep
	arg = 2 enables sleep-on-exit when returning from Handler mode to Thread mode
	arg = 6 enables sleep-on-exit and deep sleep mode

	*/

	*SCR = arg;
}


/* if other interrupt handlers are needed, use the following names: 
   NMI_Handler
   HardFault_Handler
   MemManage_Handler
   BusFault_Handler
   UsageFault_Handler
   Reserved7_Handler
   Reserved8_Handler
   Reserved9_Handler
   Reserved10_Handler
   SVC_Handler
   DebugMon_Handler
   Reserved13_Handler
   PendSV_Handler
   SysTick_Handler
   DMA_IRQHandler
   GPIO_EVEN_IRQHandler
   TIMER0_IRQHandler
   USART0_RX_IRQHandler
   USART0_TX_IRQHandler
   USB_IRQHandler
   ACMP0_IRQHandler
   ADC0_IRQHandler
   DAC0_IRQHandler
   I2C0_IRQHandler
   I2C1_IRQHandler
   GPIO_ODD_IRQHandler
   TIMER1_IRQHandler
   TIMER2_IRQHandler
   TIMER3_IRQHandler
   USART1_RX_IRQHandler
   USART1_TX_IRQHandler
   LESENSE_IRQHandler
   USART2_RX_IRQHandler
   USART2_TX_IRQHandler
   UART0_RX_IRQHandler
   UART0_TX_IRQHandler
   UART1_RX_IRQHandler
   UART1_TX_IRQHandler
   LEUART0_IRQHandler
   LEUART1_IRQHandler
   LETIMER0_IRQHandler
   PCNT0_IRQHandler
   PCNT1_IRQHandler
   PCNT2_IRQHandler
   RTC_IRQHandler
   BURTC_IRQHandler
   CMU_IRQHandler
   VCMP_IRQHandler
   LCD_IRQHandler
   MSC_IRQHandler
   AES_IRQHandler
   EBI_IRQHandler
   EMU_IRQHandler
*/
