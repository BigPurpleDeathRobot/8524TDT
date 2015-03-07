#ifndef PROTO_H
#define PROTO_H

/* Declaration of function prototypes */

// GPIO
void setupGPIO();

// TIMER
void setupTimer(uint32_t period);

// DAC
void setupDAC();
void disableDAC();
void dacData(uint16_t data);

// NVIC
void setupNVIC();

// MISC
void setupSleepMode(uint8_t foo);
void sineWave(uint16_t freq, uint16_t sample);


#endif
