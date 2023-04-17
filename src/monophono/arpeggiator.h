#ifndef ARPEGGIATOR_H
#define ARPEGGIATOR_H

#include <Arduino.h>

int arpFilIndex=0;
void arpeggiatorHold();
bool isRecording = true;
void arpeggiatorLatch();
void arpeggiatorTiming();
short arpeggiatorIndex;

#endif  