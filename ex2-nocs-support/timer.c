#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

#define SAMPLE_PERIOD 317 /* ~44100 samples per second */

/* function to setup the timer */
void setupTimer()
{
  *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_TIMER1; /* enable TIMER1 clock */
  *TIMER1_TOP = SAMPLE_PERIOD; /* set counter top value */
  *TIMER1_IEN = 1; /* enable overflow interrupt */
  *TIMER1_CMD = 1; /* start timer */
}

void disableTimer()
{
  *CMU_HFPERCLKEN0 &= ~CMU2_HFPERCLKEN0_TIMER1; /* disable TIMER1 clock */
  *TIMER1_CMD = 0; /* stop timer */
}

void setupLEtimer()
{
  *CMU_HFCORECLKEN0 |= (1 << 4); /* enable the clock for Low Energy Peripherals */
  *CMU_LFACLKEN0 |= CMU2_LFACLKEN0_LETIMER0; /* enable LFACLK for LETIMER0 */
  *CMU_OSCENCMD = (1 << 6); /* enables LFRCO, default osc for LFACLK */
  *LETIMER0_CTRL |= (1 << 9); /* set COMP0 as top value */
  *LETIMER0_COMP0 = 32768/44100; /* set top value */
  *LETIMER0_IEN = 1; /* enable interrupt on the COMP0 interrupt flag */
  *LETIMER0_CMD = 1; /* start timer */
}


