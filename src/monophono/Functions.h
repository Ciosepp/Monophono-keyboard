//Functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H 

#include <Arduino.h>

extern short ARP_MODE_RAW;
extern short ARP_STATE_RAW;
extern short ARP_OCTAVE_RAW;
extern short CK_AMT;

extern short NOTE;

void Init();
bool noteDown(int i, bool* noteScan, bool* noteTrans);
bool noteUp(int i, bool* noteScan, bool* noteTrans);
void elabControls();
int mono(int oldNote);
void logic();
int arpFilIndex=0;
void arpeggiatorHold();
bool isRecording = true;
void arpeggiatorLatch();
void arpeggiatorTiming();
void readInputs();
void output();
#endif
