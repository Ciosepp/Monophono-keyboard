
bool noteDown(int i, bool* noteScan, bool* noteTrans){
	return noteScan[i]&&noteTrans[i];
}
bool noteUp(int i, bool* noteScan, bool* noteTrans){
	return noteScan[i]&& !noteTrans[i];
}
void SerialDebug(){
	for (int i = 0; i < 49; i++){
		Serial.print(transient[i]);
	}
	Serial.println("");
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

int mono(int oldNote){
	int note = oldNote;
	for(int i = 0; i < N_KEYS; i++){

			//key-change detection (XOR)
		if(pressedKeys[i] ^^ oldPressedKeys[i]){

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
	return note;
}

void logic(){
	elabControls();
		//switch between MONO, arpeggiator HOLD or LATCH
	switch(arpState){
		case OFF:
			NOTE = mono();
			break;
		case HOLD:
			NOTE = arpeggiatorHold();
			break;	
		case LATCH:
			NOTE = arpeggiatorLatch();
			break;	
	}

}
int arpFilIndex=0;
void arpeggiatorHold(){
		//vector filler
	int nArpeggiatorNotes = nPressedKeys*(1+ARP_OCTAVE);
	arpFilIndex = 0;
	for(int i = 0; i < N_KEYS; i++){
			//if keys are pressed and arp mem is empty
		if (pressedKeys[i] == PRESSED && arpFilIndex < nArpeggiatorVoices){

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
			if((arpeggiatorNotes[j]+(o*12))>(nArpeggiatorVoices * N_OCTAVES))
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
	Note that since keys are record at its pressure, ones started the latch arpeggiator
	can be stopped only via the its state selector.
*/

bool isRecording = true;
void arpeggiatorLatch(){

	int nArpeggiatorNotes = nPressedKeys*(1+ARP_OCTAVE);
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
void arpeggiatorTiming(){
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

void arpeggiatorLatch(){
	for(int i = 0; i < N_KEYS; i++){
	}
}
void readInputs(){
	scanKeyboard(pressedKeys);
	scanControls();
	elabControls();
}
