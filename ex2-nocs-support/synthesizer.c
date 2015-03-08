/*
 * synthesizer.c
 *
 *  Created on: Mar 7, 2015
 *      Author: Dr. Satan
 */

#include "synthesizer.h"
#include "sound_effect.h"
#include "proto.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

/*
 * Sine wave generator [work in progress...]
 */
///* create one period at a given freq */
/* create one period at a given freq */
uint16_t generateSineWave(uint16_t freq, uint16_t sample)
{
  uint16_t buffer;

  buffer = (uint16_t) 1024 * (1 + sin((2*3.14159265359*sample*freq)/44100));
  return buffer;

}

/*
 * Square wave generator
 */
static uint16_t initialSquareWavePeriod;
static uint16_t lastSquareWavePeriod;
static uint16_t dutyCycle;
static int32_t squareWavesDuration;
static uint16_t initialSquareWaveAmp;
static uint16_t lastSquareWaveAmp;
static uint16_t squareWavePulseWidth;
static uint16_t squareWaveAmplitude;
static uint16_t squareWaveDirection;
static uint16_t squareWaveSampleIdx;
static int32_t generationProgress;
static uint16_t bias;

static volatile uint16_t synthesizing = 0;
static volatile int16_t noteIndex = -1;
static volatile uint16_t sampleIndex = 0;
static volatile uint16_t sample = 0;
static volatile sound_effect_t currentSoundEffect;
static volatile uint16_t testBoom= 0;

/*private func declarations*/
static uint16_t getGeneratedSquareWaveSample();

void generateSquareWave(square_wave_synth_t note)
{
    uint16_t lastSquareWavePeriod_OLD = lastSquareWavePeriod;

    initialSquareWavePeriod = note.initialPeriod / (1 << note.octave);
    lastSquareWavePeriod = note.lastPeriod / (1 << note.octave);
    dutyCycle = note.dutyCycle;
    squareWavesDuration = (note.duration ? note.duration : 1);
    initialSquareWaveAmp = (note.initialAmplitide>MAX_AMPLITUDE) ? (note.initialAmplitide = MAX_AMPLITUDE) : note.initialAmplitide;
    lastSquareWaveAmp = (note.lastAmplitide>MAX_AMPLITUDE) ? (note.lastAmplitide = MAX_AMPLITUDE) : note.lastAmplitide;


    if (initialSquareWavePeriod != lastSquareWavePeriod_OLD)
    {
        squareWavePulseWidth = (initialSquareWavePeriod * dutyCycle) / 100;
        squareWaveAmplitude = initialSquareWaveAmp;
        squareWaveDirection = !squareWaveDirection;
        squareWaveSampleIdx = 0;
    }
    generationProgress = 0;
}



uint16_t getGeneratedSquareWaveSample()
{

    uint16_t sample = (squareWaveDirection ? squareWaveAmplitude : 0);
    bias -= squareWaveAmplitude / 2;

    squareWaveSampleIdx++;
    generationProgress++;
    if (squareWaveSampleIdx >= squareWavePulseWidth)
    {
        squareWaveSampleIdx = 0;
        squareWaveDirection = !squareWaveDirection;


        uint16_t calcNewPeriod = initialSquareWavePeriod + ((lastSquareWavePeriod - initialSquareWavePeriod) * generationProgress) / squareWavesDuration;
        squareWavePulseWidth = (squareWaveDirection ? (calcNewPeriod * dutyCycle) / 100 : calcNewPeriod - (calcNewPeriod * dutyCycle) / 100);

        squareWaveAmplitude = initialSquareWaveAmp + ((lastSquareWaveAmp - initialSquareWaveAmp) * generationProgress) / squareWavesDuration;
    }

    return sample;
}

uint16_t getSample()
{
	bias = MAX_BIAS;
    uint16_t sample = 0;
    sample += getGeneratedSquareWaveSample();
    sample += bias;

    return sample;
}

void synthesize(uint8_t amplitude)
{
  currentSoundEffect=test;
  synthesizing = 1;
      if (sampleIndex % currentSoundEffect.synthesisLength == 0) // Check if sample is done
			{
				sampleIndex = 0;
				noteIndex++;
				if (noteIndex < currentSoundEffect.notes) // Check if there are more notes to play
				{
					// Prepare next note
					generateSquareWave(currentSoundEffect.synthesizeData[noteIndex]);
        }
				else
				{
					synthesizing = 0;
          disableDAC();
          disableTimer();
          noteIndex = -1;
				}
			}
      // Get next sample and write do DAC
      if (synthesizing == 1)
      {
        sample = getSample();
        sampleIndex++;
        dacData(sample/amplitude);
      }
}
