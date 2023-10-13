#include "arpeggiator.h"
#include "config.h"

bool BUSY = false;
short nNOTES=0;

short arpeggiatorNotes[N_ARPEGGIATOR_VOICE * N_OCTAVES_MAX];
bool arpNoteLatch;

bool arpLatch = false;
void arpeggiatorHold()
{
    if(CK_IN && !arpLatch){
        
        arpLatch = true;
    }
    if(!CK_IN && arpLatch){
        
        arpLatch = false;
    }
}