#ifndef PROTO_H_INCLUDE
#define PROTO_H_INCLUDE

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


// SOME SOUNDS FOR TESTING
const uint32_t sinLen = 100;
const uint16_t sinSound[] = {1024,1088,1152,1216,1279,1340,1401,1460,1517,1573,1626,1677,1725,1770,1813,1852,1889,1921,1951,1976,1998,2016,2030,2040,2046,2048,2046,2040,2030,2016,1998,1976,1951,1921,1889,1852,1813,1770,1725,1677,1626,1573,1517,1460,1401,1340,1279,1216,1152,1088,1024,960,896,832,769,708,647,588,531,475,422,371,323,278,235,196,159,127,97,72,50,32,18,8,2,0,2,8,18,32,50,72,97,127,159,196,235,278,323,371,422,475,531,588,647,708,769,832,896,960};

#endif
