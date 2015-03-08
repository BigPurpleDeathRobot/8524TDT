#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "proto.h"

/* function to set up GPIO mode and interrupts*/
void setupGPIO()
{
  /* TODO set input and output pins for the joystick */
    
  *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO; /* enable GPIO clock*/
  //*GPIO_PA_CTRL = 2;  /* set high drive strength */
  *GPIO_PA_CTRL = 1;  /* set lowest drive strength to preserve eyes*/
  *GPIO_PA_MODEH = 0x55555555; /* set pins A8-15 as output */
  *GPIO_PA_DOUT = 0xff00; /* turn off LEDs D1-D8 (LEDs are active low) */
  
  *GPIO_PC_MODEL = 0x33333333; /* set pins C0-7 as input */
  *GPIO_PC_DOUT = 0x00ff; /* enable internal pull-up on pins C0-7 */
  *GPIO_EXTIPSELL = 0x22222222; /* enable interrupt on  pins C0-7 */
  *GPIO_EXTIRISE = 0xff; /* rising edge trigger enabled */
  *GPIO_EXTIFALL = 0xff; /* falling edge trigger enabled */
  *GPIO_IEN = 0xff; /* pin in external interrupt enabled */
}

void gpioHandler(volatile sfx *selectSfx)
{
  switch(*GPIO_PC_DIN)
  {
    case 0xfe:
      setupDAC();
      setupTimer();
      *selectSfx = explosion;
      break;
    case 0xfd:
      setupDAC();
      setupTimer();
      *selectSfx = laser;
      break;
    case 0xfb:
      setupDAC();
      setupTimer();
      *selectSfx = powerup;
      break;
    case 0xf7:
      setupDAC();
      setupTimer();
      *selectSfx = jump;
      break;
    case 0xef:
      setupDAC();
      setupTimer();
      *selectSfx = song;
      break;
  }
}

