#ifndef PROTO_H
#define PROTO_H

/* Declaration of function prototypes */

// PLAYER
typedef enum {explosion, laser, powerup, jump, song} sfx;
void play(sfx selected);

// GPIO
void setupGPIO();
void gpioHandler(volatile sfx *test);

// TIMER
void setupTimer();
void disableTimer();
void setupLEtimer();
void disableLEtimer();

// DAC
void setupDAC();
void disableDAC();
void dacData(uint16_t data);

// NVIC
void setupNVIC();

// MISC
void setupSleepMode(uint8_t foo);

#endif
