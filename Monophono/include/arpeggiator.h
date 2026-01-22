#ifndef ARPEGGIATOR_H
#define ARPEGGIATOR_H

#include <Arduino.h>

#include "config.h"
void arpSampler();

void arpElabNote();

uint8_t arpPlayer(bool EN, uint8_t mode, uint8_t octExt);

void arpeggiatorHold();

void arpeggiatorLatch();


#endif