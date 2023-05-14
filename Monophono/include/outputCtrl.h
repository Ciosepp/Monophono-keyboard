#ifndef OUTPUTCTRL_H
#define OUTPUTCTRL_H
#include <Arduino.h>

void updateCV(int note,int *volt);

void CV_GATE_CTRL();

void ckOutput();

void output();

#endif