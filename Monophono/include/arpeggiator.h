#ifndef ARPEGGIATOR_H
#define ARPEGGIATOR_H

#include <Arduino.h>

#include "config.h"

enum ArpeggioStates{
    AWAITING_KEYPRESS,
    PLAYING
};
extern ArpeggioStates arpeggioState;

void arpSampler();

void arpElabNote();

uint8_t arpPlayer(bool EN, uint8_t mode, uint8_t octExt);

void arpeggiatorHold();

void arpeggiatorLatch();

uint8_t GATE_arpHold();

uint8_t GATE_arpLatch();


#endif