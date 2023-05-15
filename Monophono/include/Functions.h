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
void mono();
void logic();

void readInputs();
void output();
#endif
