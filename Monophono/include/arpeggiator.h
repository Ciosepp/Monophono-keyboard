#ifndef ARPEGGIATOR_H
#define ARPEGGIATOR_H

#include <Arduino.h>


void arpSampler();

void arpElabNote();

uint8_t arpPlayer(bool EN, int mode, int octExt, int nPKeys);

#endif