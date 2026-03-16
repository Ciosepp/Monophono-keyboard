#include "outputCtrl.h"
#include "hwFunct.h"
#include "config.h"

short oldNote=0;

bool isFirstGate = true;

void updateCV(int note){
    CVWrite(voltages[note]);
}

//input GATE{GLO}
//0 - gate off
//1 - gate on
//2 - gate refresh 
void GATE_WRITE(){
	if (GATE == 0){
		gateOff();
	}
	if (GATE == 1){
		gateOn();
	}
	if (GATE == 2){
		gateRefresh();
		GATE = 1;
	}
}

void CV_WRITE(){

    updateCV(NOTE);
 
}

void ckOutput()
{
    writeClock(CLOCK());
}

void output(){
    CV_WRITE(); //drive DAC
	GATE_WRITE(); //wirte Gate
    ckOutput(); //generate CK_OUT
}


void ARP_LATCH_GATE(bool isInArp){
	 if (!isInArp) {
		gateOff();
	}
	else{
		if(OLD_NOTE != NOTE){
			gateRefresh();
			//
		}
	}
}