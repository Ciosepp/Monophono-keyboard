#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

const int Nkeys =49; //n. tasti
int keyboard[Nkeys]; //array contenente gli stati di tutti i pulsanti
uint32_t voltages[Nkeys];

const short int Nkeys=49;
const short int nColumn = 9;
const short int nRow = 6;

bool oldkeyboard[Nkeys];
bool transient[Nkeys];

#define PRESSED 1
#define UNPRESSED 0
#define DEBUG_ENABLE true

#include <Wire.h>
#include <Adafruit_MCP4725.h>
Adafruit_MCP4725 dac;
const int maxArpVoices= 7;
const int nMuxAddressPins = 3;


bool noteDown(int i, bool* noteScan, bool* noteTrans)

bool noteUp(int i, bool* noteScan, bool* noteTrans)

void gateRefresh();

void gateOn();

void gateOff();

void SerialDebug();

void PrintKeyScan()

void pinModeInit();
    
void dacInit();

void muxWrite(int val, int* Pins);

void writeColumn(int index);

int getOctave(int pin);

int getMode(int pin);

int getCkRate();

bool readRow(int index);

int keyboardScan();

int mono(int oldNote);

void CvWrite(int note);

bool getGate();

#endif