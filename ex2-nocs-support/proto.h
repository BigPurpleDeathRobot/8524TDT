#ifndef PROTO_H
#define PROTO_H

/* Declaration of function prototypes */

// SYNTHESIZER
typedef enum {sampleplayer, synthesizer} sound_source_t;

// PLAYER
typedef enum {explosion, laser, powerup, jump, song} sfx;
void player(sfx selected, uint8_t amplitude);

// GPIO
void setupGPIO();
void gpioHandler(volatile sfx *selectSfx, volatile sound_source_t *selectSource, volatile uint8_t *amplitude);

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
