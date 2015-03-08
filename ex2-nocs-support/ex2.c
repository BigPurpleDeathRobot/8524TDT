#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "proto.h"

/* Your code will start executing here */
int main(void) 
{
  /* Call the peripheral setup functions */
  setupGPIO();
  
  /* Enable interrupt handling */
  setupNVIC();
  
  /* set sleep mode */
  setupSleepMode(2);
  
  /* use to run in EM1 and EM2
  /* in his house at R'lyeh, dead Cthulhu waits dreaming */
  __asm__("wfi");
  
  /* use to run in EM0: Run Mode
  //while(1);
  
}

/* remember to switch out setupTimer()/disableTimer with setupLEtimer()/disableLEtimer 
 * in gpio.c, player.c and synthesizer.c when running in EM2 */ 

void setupNVIC()
{
  /* TIMER1 does not work in deep sleep mode */
  *ISER0 = 0x1802; /* enable interrupt for TIMER1, GPIO EVEN and ODD */
  /* use for deep sleep, EM2 */
  //*ISER0 = 0x4000802; /* enable interrupt for LETIMER0, GPIO EVEN and ODD */
}

void setupSleepMode(uint8_t foo)
{
  /*
    The SCR controls features of entry to and exit from low power state.
    foo = 0 only sleep 
    foo = 2 enables sleep-on-exit when returning from Handler mode to Thread mode
    foo = 6 enables sleep-on-exit and deep sleep mode
    */
  
  *SCR = foo;
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
