#ifndef PROTO_H
#define PROTO_H

/* Declaration of function prototypes */

// GPIO
void setupGPIO();

// TIMER
void setupTimer();
void setupLEtimer();

// DAC
void setupDAC();
void disableDAC();
void dacData(uint16_t data);

// NVIC
void setupNVIC();

// MISC
void setupSleepMode(uint8_t foo);
uint16_t sineWave(uint16_t freq, uint16_t sample);


// SOME SOUNDS FOR TESTING


#endif
