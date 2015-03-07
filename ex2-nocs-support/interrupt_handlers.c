#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "efm32gg.h"
#include "proto.h"
uint16_t test = 0;
/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
  /*
    TODO feed new samples to the DAC
    remember to clear the pending interrupt by writing 1 to TIMER1_IFC
  */
  *TIMER1_IFC = *TIMER1_IF; /* clear interrupt flag */
  sineWave(440, test);
  test++;
  if (test == 100)
    test = 0;
 
  
  //disableDAC();
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() 
{
    /* TODO handle button pressed event, remember to clear pending interrupt */
    *GPIO_IFC = *GPIO_IF; /* clear interrupt flag */
    *GPIO_PA_DOUT = *GPIO_PC_DIN << 8;
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() 
{
    /* TODO handle button pressed event, remember to clear pending interrupt */
    *GPIO_IFC = *GPIO_IF; /* clear interrupt flag */
    *GPIO_PA_DOUT = *GPIO_PC_DIN << 8;
}
