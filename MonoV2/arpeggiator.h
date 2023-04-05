#ifndef ARPEGGIATOR_H
#define ARPEGGIATOR_H 

#include "pin-configuration-board-v2.h"
#include "keyboard.h"
#include <Arduino.h>

void arpeggiatorPlay(bool gateOn, int mode, bool enable, bool Latching, int octaveExtension);

void arpeggiatorHoldRecord(int nPressedKeys);

void arpeggiatorLatchRecord(int nPressedKeys);

void memoryClean();

void arpeggiatorRecord(int nPressedKeys);

#endif

