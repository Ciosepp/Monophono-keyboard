#include "arpeggiator.h"
#include "config.h"

bool BUSY = false;
short nNOTES=0;

bool arpNoteLatch;

bool arpLatch = false;

void registerNote()
{
    short k=0;
    for (short i = 0; i < N_KEYS; i++)//throughout all the notes
    {
        if(k>=N_ARPEGGIATOR_VOICE) break;//out if buffer full
        if(KeyStates == 1) //if pressed note
        {
            arpeggiatorNotes[k] = i;//save note
            k++;//new note
        }
    }
}

void arpeggiatorHold()
{
    if(CK_IN and !arpLatch){
        
        arpLatch = true;
    }
    if(!CK_IN && arpLatch){
        
        arpLatch = false;
    }
}