

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
#include <MCP4725.h>
Adafruit_MCP4725 dac;
const int maxArpVoices= 7;
const int nMuxAddressPins = 3;

///////////////////////////initialization functions /////////
void pinModeInit();

void dacInit();

///////////////////////////input function //////////////////

bool noteDown(int i, bool* noteScan, bool* noteTrans)

bool noteUp(int i, bool* noteScan, bool* noteTrans)

int getOctave(int pin);

int getMode(int pin);

int getCkRate();

bool readRow(int index);

int keyboardScan();

bool getGate();

///////////////////////////output functions//////////////////

void gateOn();

void gateRefresh();

void gateOff();

void CvWrite(int note);

void muxWrite(int val, int* Pins);

void writeColumn(int index);

int mono(int oldNote);

void PrintKeyScan();

void SerialDebug();

#endif
