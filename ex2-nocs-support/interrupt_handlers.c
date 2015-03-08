#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "efm32gg.h"
#include "proto.h"
#include "sound/sineTones.h"

uint16_t test = 0;

/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
  *TIMER1_IFC = *TIMER1_IF; /* clear interrupt flag */
  dacData(boom[test]);
  test++;
  if (test == boomLen)
    //test = 0;
    disableDAC();
}

/* LETIMER0 interrupt handler */
void __attribute__ ((interrupt)) LETIMER0_IRQHandler() 
{  
  *LETIMER0_IFC = *LETIMER0_IF; /* clear interrupt flag */
  /* TODO IF TIME */
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
