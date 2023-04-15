//hwFunct.h
#ifndef HWFUNCT_H
#define HWFUNCT_H 

#include <Arduino.h>

void gateOn();
void gateRefresh();
void gateOff();
void pinInit();
void dacInit();
void setMux(int val,int* Pins);
bool scanKey(int i);
void scanKeyboard(bool *vect);
//this function read all the control inputs from  
//all potentiometers and GPI


void scanControls();

void CVWrite(int Note);
void GateWrite(bool oldGT, int nK);

#endif
