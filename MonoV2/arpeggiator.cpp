int arpeggioNotes[maxArpVoices];
bool filled = false;
int nVoices = 0;
bool gateOn = false; // to adress as output at int/ext ck function
bool aLatch = true;
int c = 0;
bool goingUp = true;
/////////////////////////////////////////////////////ARPEGGIATOR/////////////////////
/*
modes:  0- incremental 
        1- U/D
        2- decremental        
*/

void arpeggiatorPlay(int mode, bool enable, int Latching){

	if (gateOn && aLatch && nPressedKeys > 0){
		dac.setVoltage(voltages[arpeggioNotes[c]], false);
       	gateRefresh();
       	aLatch = false;
	}

	if (!gateOn && !aLatch){ 
		switch (mode){
			case 0:	
                c = (c + 1) % maxArpVoices;
                break;
            case 1: 
                if (c >= maxArpVoices - 1 && goingUp) goingUp = false; //transition up to down
                if (c <= 0 && !goingUp) goingUp = true;  //transition down to up
                if (goingUp) c++;
                else    
                    c--;
                break;
            case 2: 
                c = (c - 1) % maxArpVoices;
                break;
		}
        aLatch = true;
	}

}

void arpeggiatorHoldRecord(int nPressedKeys)
{
    if(nPressedKeys > 0)//if any key is pressed
    {
    	int k=0;
	    for (int i = 0; i < Nkeys; i++)//scan through all keys
	    {
	            if(keyboard[i] == 1)// fills arp notes Vector with pressed notes
	            { 
	                arpeggioNotes[k]= i;
	                k++;
	            }
	            if(k == maxArpVoices)break;
	     }
	 }
	 else{
	 	for (int i = 0; i < maxArpVoices; i++){
        arpeggioNotes[i] = -1;
    	}
	 }	 
}
bool arpeggioNotesClean=true;
void arpeggiatorLatchRecord(int nPressedKeys)
{
    if(nPressedKeys > 0)//if any key is pressed
    {
    	if(arpeggioNotesClean){//clear memory when transition to pressed keys

    		arpeggioNotesClean = false;
    		for (int i = 0; i < maxArpVoices; i++){
        		arpeggioNotes[i] = -1;
        	}
    	} 
    	else{
    		arpeggioNotesClean = true; //detect transition
    	}
    	int k=0;
	    for (int i = 0; i < Nkeys; i++)//scan through all keys
	    {
	            if(transient[i] == 1)// fills arp notes Vector with pressed notes
	            { 
	                arpeggioNotes[k]= i;
	                k++;
	            }
	            if(k == maxArpVoices)break;
	    }
	 }
	 
	 		 
}

