//pin-configuration-board-v2.h
#ifndef __PIN_CONFIGURATION_BOARD_V2_H__
#define __PIN_CONFIGURATION_BOARD_V2_H__

#define MIDI_OUT_PIN 1
#define CLOCK_OUT_PIN 2
#define GATE_PIN 3

#define MATRIX_WRITE_EXTERNAL_PIN 13
const short int WRITE_MUX_ADDRESS_PINS[] = {10, 11, 12};
#define READ_MUX_OUT_VALUE_PIN 9
const short int READ_MUX_ADDRESS_PINS[] = {6, 7, 8};	

#define ARPEGGIATOR_CLOCK_IN_PIN 4
#define ARPEGGIATOR_MODE_PIN 14
#define ARPEGGIATOR_CLOCK_DIVISION_PIN 15
#define ARPEGGIATOR_CLOCK_RATE_PIN 16
#define ARPEGGIATOR_OCTAVE_EXTENSION_PIN 17
#define SEQUENCER_PIN 20

#endif
