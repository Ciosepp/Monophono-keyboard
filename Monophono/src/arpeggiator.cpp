#include "arpeggiator.h"

#include "config.h"
//#include "cppQueue.h"
#include "hwFunct.h"

bool BUSY = false;
short nNOTES = 0;

bool isInCycle = false;

bool arpLatch = false;

enum ArpeggiatorStates {
    AWAITING_KEYPRESS,
    PLAYING,
};

uint8_t arpSavedNotes[N_ARPEGGIATOR_VOICE];
uint8_t nArpNotes=0;

void arpSampler(){`
	nArpNotes = nPressedKeys;
	if (nArpNotes > N_ARPEGGIATOR_VOICE) nArpNotes = N_ARPEGGIATOR_VOICE;

	for (int i = 0; i < nArpNotes; i++)
	{
		arpeggiatorNotes[i]  = pressedNotes[i];
		//nArpNotes = (nArpNotes>N_ARPEGGIATOR_VOICE) ?N_ARPEGGIATOR_VOICE: nPressedKeys;
	}	
}

//fills the arp. buffer up to the maximun arp. notes 
void arpElabNote() {
    
    if (nArpNotes > 0)
    {
        
        //extend notes to max octaves playable 
        for (uint8_t i = 1; i < N_OCTAVES_MAX; i++)
        {
            for (uint8_t j = 0; j < nArpNotes; j++)
            {
                arpeggiatorNotes[j+(i*nArpNotes)] = arpeggiatorNotes[j]+(i*12);

				if(arpeggiatorNotes[j]+(i*12) > 60){ //constraining to octave limit 
					arpeggiatorNotes[j+(i*nArpNotes)] = arpeggiatorNotes[j]+((i-1)*12);
				} 
            }   
        }
    }
}
//index of the note currently being played fromthe arpeggiator
int8_t currentArpNoteIndex = 0; 
//calculates the index after each clock 
// mode: 0-up, 1-down, 2-UD
//octExt: 0, 1=+1, 2=+2
bool IS_FIRST_NOTE =true;
bool isUPverse=true;

uint8_t arpPlayer(bool EN, uint8_t mode, uint8_t octExt){
	int limit = nArpNotes*(octExt+1);

	if (!EN){
		if(!IS_FIRST_NOTE) IS_FIRST_NOTE =true;
		if(!isUPverse)isUPverse=true;
	} 


	if (EN && isRisingEdge)
	{
		switch (mode)
		{
			case 0://UP
				if(!IS_FIRST_NOTE){
					currentArpNoteIndex = (currentArpNoteIndex +1)%limit;       
				}
			break;
			
			case 1://DOWN
			currentArpNoteIndex = (currentArpNoteIndex -1)%limit;
			break;
			
			case 2://UP-DOWN
			if (isUPverse==true && !IS_FIRST_NOTE)
			{
				currentArpNoteIndex ++;
				if (currentArpNoteIndex>=limit)
				{
					isUPverse=false;
					break;
				}
			}
			if (isUPverse==false)
			{
				currentArpNoteIndex --;
				if (currentArpNoteIndex<=0)
				{
					isUPverse=true;
					break;
				}
			}
			
			break;
			default:
			break;
		}
		IS_FIRST_NOTE = false;
		isRisingEdge = false;
	}
	return currentArpNoteIndex;
}

void arpeggiatorHold() {
	arpSampler(); //countinuos sampling
	arpElabNote();//process arp notes
	NOTE = arpPlayer(nArpNotes >0 , ARP_MODE_RAW, ARP_OCTAVE);

}

void arpeggiatorLatch(){
    
}