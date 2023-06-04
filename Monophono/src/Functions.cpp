#include "Functions.h"
#include "hwFunct.h"
#include "monophonoBoardPinHeader.h"
#include "config.h"

#include "mono.h"

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


void logic(){
	elabControls();
		//switch between MONO, arpeggiator HOLD or LATCH
	/* switch(arpState){
		case OFF:
		mono();
		break;
		case HOLD:
		arpeggiatorHold();
		break;	
		case LATCH:
		arpeggiatorLatch();
		break;	
	} */

	//dev
	mono();

}


void readInputs()
{
	scanKeyboard(pressedKeys);
	scanControls();
}
