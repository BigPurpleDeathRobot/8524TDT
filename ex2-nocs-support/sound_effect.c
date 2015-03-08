/*
 * sound_effect.c
 *
 *  Created on: Mar 7, 2015
 *      Author: kaptein kuk
 */
#include "sound_effect.h"
//#include "synthesizer.h"

static square_wave_synth_t test_sqr_notes1[] =
{
	{.initialPeriod = NOTE_E, .lastPeriod = NOTE_E, .octave = 3, .initialAmplitide = MAX_AMPLITUDE, .lastAmplitide = MAX_AMPLITUDE, .dutyCycle = 50, .duration = 6615},
	{.initialPeriod = NOTE_C, .lastPeriod = NOTE_C, .octave = 1, .initialAmplitide = MAX_AMPLITUDE, .lastAmplitide = MAX_AMPLITUDE, .dutyCycle = 50, .duration = 6615},
	{.initialPeriod = NOTE_C, .lastPeriod = NOTE_C, .octave = 0, .initialAmplitide = MAX_AMPLITUDE, .lastAmplitide = MAX_AMPLITUDE, .dutyCycle = 50, .duration = 6615},
	{.initialPeriod = NOTE_D, .lastPeriod = NOTE_C, .octave = 1, .initialAmplitide = MAX_AMPLITUDE, .lastAmplitide = MAX_AMPLITUDE, .dutyCycle = 50, .duration = 6615},
	{.initialPeriod = NOTE_A, .lastPeriod = NOTE_C, .octave = 1, .initialAmplitide = MAX_AMPLITUDE, .lastAmplitide = MAX_AMPLITUDE, .dutyCycle = 50, .duration = 6615},
	{.initialPeriod = NOTE_E, .lastPeriod = NOTE_E, .octave = 1, .initialAmplitide = MAX_AMPLITUDE, .lastAmplitide = MAX_AMPLITUDE, .dutyCycle = 50, .duration = 6615},
};

sound_effect_t test = {.notes = 6, .synthesisLength = 39690, .synthesizeData = test_sqr_notes1,};
