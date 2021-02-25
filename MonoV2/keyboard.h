#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

const int N =49; //n. tasti
int keyboard[N]; //array contenente gli stati di tutti i pulsanti
uint32_t voltages[N];
int MaxRowIndex=6,RowIndex=0;
int MaxColumnIndex=9,columnIndex=0;
int n=0;
#define PRESSED 1
#define UNPRESSED 0
#define DEBUG_ENABLE true

#include <Wire.h>
#include <Adafruit_MCP4725.h>
Adafruit_MCP4725 dac;
const int maxArpVoices= 7;


bool noteDown(int i, bool* noteScan, bool* noteTrans)

bool noteUp(int i, bool* noteScan, bool* noteTrans)

void gateRefresh();

void gateOn();

void gateOff();

void SerialDebug();

void pinModeInit();
    
void dacInit();

void muxWrite(int val, int* Pins);

void writeColumn(int index);

int getOctave(int pin);

int getMode(int pin);

bool readRow(int index);

#endif