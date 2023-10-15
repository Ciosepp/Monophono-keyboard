#include "arpeggiator.h"
#include "config.h"
#include "hwFunct.h"

bool BUSY = false;
short nNOTES=0;

bool isInCycle = false;

bool arpLatch = false;

enum {
		
}

//this function scans the keyboard and fills the arp. buffer
//it also returns true if at least one key is pressed, false else.
bool arpRegisterNote()
{
    scanKeyboard();
    nPressedKeys = 0;

    for (short i = 0; i < N_KEYS; i++)//throughout all the notes
    {
        if(nPressedKeys >= N_ARPEGGIATOR_VOICE) break;//out if buffer full

        if(KeyStates == PRESSED) //if pressed note
        {
            arpeggiatorNotes[nPressedKeys] = i;//save note
            nPressedKeys++;//new note
        }
    }
    if (nPressedKeys > 0) return true;
    else
        return false;
    
}

void arpeggiatorHold()
{
	// se nTastiPremuti == 0
		// stop
	// s


    if(arpRegisterNote() == true) //some key are pressed
    {   
        
        if(CK_IN and !arpLatch){
            
            arpLatch = true;
        }
        if(!CK_IN && arpLatch){
            
            arpLatch = false;
        }
    }
    else 
    {
        isInCycle = false;
    }

}