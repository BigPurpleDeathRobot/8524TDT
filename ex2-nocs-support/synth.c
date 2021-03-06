#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "efm32gg.h"
#include "proto.h"


/* create one period at a given freq */
uint16_t sineWave(uint16_t freq, uint16_t sample)
{
  uint16_t buffer;
  
  buffer = (uint16_t) 1024 * (1 + sin((2*3.14159265359*sample*freq)/44100));
  return buffer;

}

