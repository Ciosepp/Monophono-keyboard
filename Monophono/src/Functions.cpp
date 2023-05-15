#include "Functions.h"
#include "hwFunct.h"
#include "monophonoBoardPinHeader.h"
#include "config.h"
void Init(){
	pinInit();
	dacInit();
}

bool noteDown(int i, bool* noteScan, bool* noteTrans){
	return noteScan[i]&&noteTrans[i];
}
bool noteUp(int i, bool* noteScan, bool* noteTrans){
	return noteScan[i]&& !noteTrans[i];
}

void elabControls(){

	ARP_MODE_RAW = 	map(ARP_MODE_RAW,0,1023,0,3);
	arpMode = ARP_MODE_RAW;

	ARP_STATE_RAW =	map(ARP_STATE_RAW,0,1023,0,2);
	arpState = ARP_STATE_RAW;

	ARP_OCTAVE_RAW= map(ARP_OCTAVE_RAW,0,1023,0,3);

	CK_AMT =		map(CK_AMT,0, 1023,60,300);

}
/*	Mono algorithm returns an integer corresponding 
	to the last pressed note pressed, the highest, lowest,
	or one of the last ones after the last key is pressed;
	it also calls functions as gateOn(), gateOff() 
	or gateOn() gateRefresh() if events are detected.
	All the states can be summarized in:
	1-		first key donw
	2-..- 	n-keys pressed in addiction
	...3-	1 key released
	4- 		last key released
	At each pression the gate is updated like for the CV
	When more keys are pressed and one is released, the CV is 
	associated to the closest pressed note, with high or low pririty.

*/

void mono(){

	for(int i = 0; i < N_KEYS; i++){

			//key-change detection (XOR)
		if(pressedKeys[i] ^ oldPressedKeys[i]){

				//key down
			if(pressedKeys[i] == PRESSED){
				NOTE = i;
				gateRefresh();
				nPressedKeys++;
			}
				//key up
			if(pressedKeys[i] == !PRESSED){
				nPressedKeys--;

				if(nPressedKeys== 0){
					gateOff();
				}
				else {
					noteAppend = true;
				}
			}
			if(noteAppend && pressedKeys[i]){
				NOTE = i;
				noteAppend = false;
			}
		}
			//update edge-detection memory
		oldPressedKeys[i] = pressedKeys[i];
	}

}


void logic(){
	elabControls();
		//switch between MONO, arpeggiator HOLD or LATCH
	switch(arpState){
		case OFF:
		mono();
		break;
		case HOLD:
		arpeggiatorHold();
		break;	
		case LATCH:
		arpeggiatorLatch();
		break;	
	}

}


void readInputs()
{
	scanKeyboard(pressedKeys);
	scanControls();
}

int oldNote =0;
bool oldGateState = false;

void output()
{
	if(NOTE != oldNote)
	{
		NOTE = oldNote;
		CVWrite(voltages[NOTE]);
		GateWrite(oldGateState, nPressedKeys);
	}
}
