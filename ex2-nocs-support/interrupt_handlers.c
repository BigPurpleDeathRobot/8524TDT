#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "efm32gg.h"
#include "proto.h"

volatile sfx selectSfx;

/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
  *TIMER1_IFC = *TIMER1_IF; /* clear interrupt flag */
  play(selectSfx);
  
}

/* LETIMER0 interrupt handler */
void __attribute__ ((interrupt)) LETIMER0_IRQHandler() 
{  
  *LETIMER0_IFC = *LETIMER0_IF; /* clear interrupt flag */
  *TIMER1_IFC = *TIMER1_IF; /* clear interrupt flag */
  play(selectSfx);
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() 
{
    /* TODO handle button pressed event, remember to clear pending interrupt */
    *GPIO_IFC = *GPIO_IF; /* clear interrupt flag */
    gpioHandler(&selectSfx);
    *GPIO_PA_DOUT = *GPIO_PC_DIN << 8;
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() 
{
    /* TODO handle button pressed event, remember to clear pending interrupt */
    *GPIO_IFC = *GPIO_IF; /* clear interrupt flag */
    gpioHandler(&selectSfx);
    *GPIO_PA_DOUT = *GPIO_PC_DIN << 8;
}
