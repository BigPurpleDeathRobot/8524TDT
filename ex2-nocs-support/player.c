#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include "efm32gg.h"
#include "proto.h"

#include "sound/sineTones.h"
#include "sound/sfx.h"

static volatile uint32_t sample = 0;
static volatile sfx current;

void player(sfx selected, uint8_t amplitude)
{
  const uint32_t *sampleNum;
  const uint16_t *selectedSfx;
  
  /* check for sfx change and reset sample counter */
  if (selected != current)
  {
    current = selected;
    sample = 0;
  }
  
  /* point to selected sfx */
  switch(selected)
  {
    case explosion:
      sampleNum = &explosionLen;
      selectedSfx = explosion0;
      break;
    case laser:
      sampleNum = &laserLen;
      selectedSfx = laser0;
      break;
    case powerup:
      sampleNum = &powerupLen;
      selectedSfx = powerup0;
      break;
    case jump:
      sampleNum = &jumpLen;
      selectedSfx = jump0;
      break;
    case song:
      sampleNum = &songLen;
      selectedSfx = song0;
      break;
  }
  
  /* feed data to dac */
  if (sample < *sampleNum)
  {
    dacData(selectedSfx[sample]/amplitude);
    sample++;
  }
  else
  {
    if (selected == song)
    {
      sample = 0;
    }
    else
    {
      sample = 0;
      disableDAC();
      disableLEtimer();
    }
  }
}
