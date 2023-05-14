#include "outputCtrl.h"
#include "hwFunct.h"
#include "config.h"

short oldNote=0;

bool isFirstGate = true;

void updateCV(int note,int *volt)
{
    CVWrite(volt[note]);
}


void CV_GATE_CTRL()
{
    if(NOTE != oldNote)
    {
        updateCV(NOTE, voltages);
        GateWrite(isFirstGate, nPressedKeys);
    }
    if(isFirstGate==false && nPressedKeys ==0)
    {
        isFirstGate = true;
    }
}

void ckOutput()
{
    writeClock(CLOCK());
}

void output()
{
    CV_GATE_CTRL();
    ckOutput(); 
}