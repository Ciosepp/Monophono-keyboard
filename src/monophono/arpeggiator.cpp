#include "arpeggiator.h"

#include "monophonoBoardPinHeader.h"
#include "config.h"
#include "monophonoBoardPinHeader.h"


void arpeggiatorHold()//vector filler
{
	int nArpeggiatorNotes = nPressedKeys*(1+ARP_OCTAVE_RAW);
	arpFilIndex = 0;
	for(int i = 0; i < N_KEYS; i++){
			//if keys are pressed and arp mem is empty
		if (pressedKeys[i] == PRESSED && arpFilIndex < N_ARPEGGIATOR_VOICE){

			arpeggiatorNotes[arpFilIndex]= i;
			arpFilIndex++;
		}
	}	
	/*	//fill with zeros arpgeggiator memory
	for (int i = 0; i < (arpeggiatorIndex*N_OCTAVES)-arpFilIndex; i++){
		arpeggiatorIndex[i+arpFilIndex] = 0;
	}*/
		//if octaver is greater than 0
	for(int o=1; o <= ARP_OCTAVE_RAW; o++){
			//for each note of the arpeggiator
		for(int j=0; j<arpFilIndex; j++){
				//if octaved note goes out of range
			if((arpeggiatorNotes[j]+(o*12))>(N_ARPEGGIATOR_VOICE * N_OCTAVES))
				break;
				//extend pressed notes for octave(s)
			arpeggiatorNotes[nPressedKeys*o+j]=arpeggiatorNotes[j]+(o*12);
		}		
	}
}
/* In this function the notes are recorded from the state of all keys released;
	after this state is detected all the pressed keys are recorded in <arpeggiatorNotes>
	To delete an unwanted note, is necessary to reset the acquisition by lifting all the
	keys and striking the right notes.
	NOTE that since keys are record at its pressure, ones started the latch arpeggiator
	can be stopped only via the its state selector.
*/

void arpeggiatorLatch()
{

	int nArpeggiatorNotes = nPressedKeys*(1+ARP_OCTAVE_RAW);
	if(!isRecording && nPressedKeys >= 1){
		isRecording = true;
		arpFilIndex =0;
	} 

	if((arpFilIndex < nPressedKeys) && isRecording) isRecording = false;
	if(isRecording){			
			//vector filler

		for(int i = 0; i < N_KEYS; i++){
				//if keys are pressed and arp mem is empty
			if (pressedKeys[i] == PRESSED && nPressedKeys<arpFilIndex){
				arpeggiatorNotes[arpFilIndex]= i;
				arpFilIndex++;
					//break if too many keys are recorded
				if (arpFilIndex > nPressedKeys)break;
			}


		}	
			//if octaver is greater than 0
		for(int o=1; o <= ARP_OCTAVE_RAW; o++){
				//for each note of the arpeggiator
			for(int j=0; j<arpFilIndex; j++){
					//if octaved note goes out of range
				if((arpeggiatorNotes[j]+(o*12))>N_KEYS)
					break;
					//extend pressed notes for octave(s)
				arpeggiatorNotes[nPressedKeys*o+j]=arpeggiatorNotes[j]+(o*12);
			}		
		}
	}
}
void arpeggiatorTiming()
{
			//at clock strike
	if((pressedKeys>0) && CK_IN && !arpNoteLatch){
		switch(arpMode){
			case UP:
			arpeggiatorIndex = (arpeggiatorIndex++)%nArpeggiatorNotes;
			break;
			case UD:
			if(arpeggiatorIndex>=nArpeggiatorNotes){
				UD = true;	
			}
			if(arpeggiatorIndex<=0){
				UD = false;	
			}
			if(!UD)
						//if top
				arpeggiatorIndex++;

			else
				arpeggiatorIndex--;	
			break;	
			case DOWN:
			arpeggiatorIndex = (arpeggiatorIndex+nArpeggiatorNotes-1)%nArpeggiatorNotes;
			break;
		}
		gateRefresh();
		arpNoteLatch = true;
	}	
		//latch reset
	if(!CK_IN && arpNoteLatch) arpNoteLatch== false;
	if(pressedKeys ==0)arpeggiatorIndex =0;
}
