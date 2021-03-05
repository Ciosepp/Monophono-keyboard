int arpeggioNotes[maxArpVoices];
bool filled = false;
int nVoices = 0;
bool aLatch = true;
int arpeggioNoteIndex = 0;
int arpeggioOctaveIndex=1; //1->4
short int octJumpInterval = 12;//semitones
bool goingUp = true;
/////////////////////////////////////////////////////ARPEGGIATOR/////////////////////
/*
modes:  0- incremental 
        1- U/D
        2- decremental        
*/

void arpeggiatorPlay(bool gateOn, int mode, bool enable, bool Latching, int octaveExtension){
	
	int note = arpeggioNoteIndex + (octJumpInterval*arpeggioOctaveIndex);

	if (gateOn && aLatch && nPressedKeys > 0){
		CvWrite(arpeggioNotes[note]);
       	gateRefresh();
       	aLatch = false;// detect ck transition
	}

	if (!gateOn && !aLatch){ 
		switch (mode){
			case 0:	
                arpeggioNoteIndex = (arpeggioNoteIndex + 1) % maxArpVoices;
                
                arpeggioOctaveIndex= (arpeggioOctaveIndex + 1) % octaveExtension;
                if((arpeggioNoteIndex + (octJumpInterval*arpeggioOctaveIndex)) >= 60){
                	arpeggioOctaveIndex = 1;
                }
                break;
            case 1: 
                if (arpeggioNoteIndex >= maxArpVoices - 1 && goingUp) goingUp = false; //transition up to down
                if (arpeggioNoteIndex <= 0 && !goingUp) goingUp = true;  //transition down to up
                if (goingUp) arpeggioNoteIndex++;
                else    
                    arpeggioNoteIndex--;
                break;
            case 2: 
                arpeggioNoteIndex = (arpeggioNoteIndex - 1) % maxArpVoices;
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

    		memoryClean();
    		arpeggioNotesClean = false;
    	} 
    	
    	int k=0;
	    for (int i = 0; i < Nkeys; i++)//scan through all keys
	    {
			if(transient[i] == 1)// fills arp notes Vector with pressed notes
			{ 
			    arpeggioNotes[k] = i;
			    k++;
			}
			if(k == maxArpVoices || k == nPressedKeys)break;
	    }
	}
	else{ // no pressed keys
		arpeggioNotesClean = true; //detect transition
	}	 		 
}
void memoryClean(){
	for (int i = 0; i < maxArpVoices; i++){
        arpeggioNotes[i] = -1;
    }
}
void memoryCleanFromIndex(int index){
	for (int i = index; i < maxArpVoices; i++){ // fill the rest of the array w -1
    	arpeggioNotes[i] = -1;
    }
}