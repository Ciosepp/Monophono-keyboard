#ifndef OUTPUTCTRL_H
#define OUTPUTCTRL_H
#include <Arduino.h>

void updateCV(int note,int *volt);

void GATE_WRITE();

void CV_WRITE();

void ARP_GATE();

void ckOutput();

void output();

#endif