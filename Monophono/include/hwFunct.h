
#ifndef HWFUNCT_H
#define HWFUNCT_H 

#include <Arduino.h>

#define N 61


void clockSet(short BPM, short division);
bool CLOCK();
void writeClock(bool x);

void gateOn();
void gateRefresh();
void gateOff();
void pinInit();
void dacInit();
void setMux(int val,const short* Pins);
bool scanKey(int i);
void scanKeyboard();
//this function read all the control inputs from  
//all potentiometers and GPI


void scanControls();

void CVWrite(int NOTE);
void GateWrite(bool oldGT, int nK);

//extern const short WRITE_MUX_ADDRESS_PINS[3];

//extern const short READ_MUX_ADDRESS_PINS[3];


#endif
