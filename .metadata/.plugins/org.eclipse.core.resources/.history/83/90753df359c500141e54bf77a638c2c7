/*
 * sound_effect.c
 *
 *  Created on: Mar 7, 2015
 *      Author: kaptein kuk
 */
#include "sound_effect.h"
//#include "synthesizer.h"

static square_note_t test_sqr_notes1[] =
{
	{.period_begin = NOTE_C, .period_end = NOTE_C, .octave = 3, .amp_begin = MAX_AMPLITUDE_PER_CHANNEL/10, .amp_end = MAX_AMPLITUDE_PER_CHANNEL/10, .duty_cycle = 50, .duration = 6615},
	{.period_begin = NOTE_C, .period_end = NOTE_C, .octave = 1, .amp_begin = MAX_AMPLITUDE_PER_CHANNEL/10, .amp_end = MAX_AMPLITUDE_PER_CHANNEL/10, .duty_cycle = 50, .duration = 6615},
	{.period_begin = NOTE_C, .period_end = NOTE_C, .octave = 0, .amp_begin = MAX_AMPLITUDE_PER_CHANNEL/10, .amp_end = MAX_AMPLITUDE_PER_CHANNEL/10, .duty_cycle = 50, .duration = 6615},
	{.period_begin = NOTE_D, .period_end = NOTE_C, .octave = 1, .amp_begin = MAX_AMPLITUDE_PER_CHANNEL/10, .amp_end = MAX_AMPLITUDE_PER_CHANNEL/30, .duty_cycle = 50, .duration = 6615},
	{.period_begin = NOTE_A, .period_end = NOTE_C, .octave = 1, .amp_begin = MAX_AMPLITUDE_PER_CHANNEL/30, .amp_end = MAX_AMPLITUDE_PER_CHANNEL/90, .duty_cycle = 50, .duration = 6615},
	{.period_begin = NOTE_Db, .period_end = NOTE_Db, .octave = 1, .amp_begin = MAX_AMPLITUDE_PER_CHANNEL/90, .amp_end = MAX_AMPLITUDE_PER_CHANNEL/270, .duty_cycle = 50, .duration = 6615},
};

sound_t test =
{
	.note_count = 6,
	.note_duration = 50000,
	.sq1_notes = test_sqr_notes1,
};
