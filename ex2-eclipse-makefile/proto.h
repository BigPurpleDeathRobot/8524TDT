/*
 * proto.h
 *
 *  Created on: Mar 4, 2015
 *      Author: admin
 *
 *	...given the size of the project, a single interface is deemed sufficient
 *
 */

#ifndef PROTO_H_
#define PROTO_H_

/* From gpio.c */
void setupGPIO();
void clearInterruptGPIO();
void LEDupdateGPIO();

/* From dac.c */
void setupDAC();
void disableDAC();
void dataDAC(uint16_t);

/* From timer.c */
void setupTimer();
void setupLEtimer();
void startTimer();
void stopTimer();
void disableTimer();

/*TODO:From interrupt_handlers.c (if any)*/


/*TODO:From generateSong whatever sound.c*/
void loadSong();
void loadSoundEffect();
void stopSong();

#endif /* PROTO_H_ */
