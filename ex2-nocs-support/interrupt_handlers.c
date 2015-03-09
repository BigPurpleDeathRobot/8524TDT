#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "efm32gg.h"
#include "proto.h"

#include "synthesizer.h"
#include "sound_effect.h"

static volatile sfx selectSfx;
static volatile sound_source_t sound_source = sampleplayer;
static volatile uint8_t amplitude = 200;

/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
  switch (sound_source)
	{
		case sampleplayer:
			player(selectSfx, amplitude);
			break;
		case synthesizer:
      synthesize(amplitude);
      break;
	}
  *TIMER1_IFC = 0xff; /* clear interrupt flag */
}

/* LETIMER0 interrupt handler */
void __attribute__ ((interrupt)) LETIMER0_IRQHandler() 
{  
  *LETIMER0_IFC = 1; /* clear interrupt flag */
    switch (sound_source)
	{
		case sampleplayer:
			player(selectSfx, amplitude);
			break;
		case synthesizer:
      synthesize(amplitude);
      break;
	}
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() 
{
    /* TODO handle button pressed event, remember to clear pending interrupt */
    gpioHandler(&selectSfx, &sound_source, &amplitude);
    *GPIO_PA_DOUT = *GPIO_PC_DIN << 8;
    *GPIO_IFC = 0xff; /* clear interrupt flag */
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() 
{
    /* TODO handle button pressed event, remember to clear pending interrupt */
    gpioHandler(&selectSfx, &sound_source, &amplitude);
    *GPIO_PA_DOUT = *GPIO_PC_DIN << 8;
    *GPIO_IFC = 0xff; /* clear interrupt flag */
}
