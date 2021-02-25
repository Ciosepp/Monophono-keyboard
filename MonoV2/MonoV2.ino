//MonoV2.ino
//main file
#include <pin-configuration-board-v2.h>
#include <keyboard.h>

const short int Nkeys=49;
const short int nColumn = 9;
const short int nRow = 6;

bool gate = false;
bool noteDown = false;
bool noteUp = false;


/////////////////////////////////////////////////////ARPEGGIATOR/////////////////////
/*
modes:  0- incremental 
		1- U/D
		2- decremental
		
*/

int arpeggioNotes[maxArpVoices];
bool filled = false;
int nVoices = 0;
bool gateOn = false; // to adress as output at int/ext ck function
bool aLatch = true;
int c = 0;
bool up = true;

void arpeggiator(int mode, bool enable){

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
                if (c >= maxArpVoices - 1 && up) up = false; //up
                if (c <= 0 && !up) up = true;
                if (up) c++;
                else    
                    c--;
                break;
            case 2: 
                c = (c - 1) % maxArpVoices;
                break;
		}
        aLatch = true;
	}

    for (int i = 0; i < maxArpVoices; i++){
        arpeggioNotes[i] = -1;
    }
}



void setup(){
    pinModeInit(); 
    Serial.begin(115200);
    Serial.print("Mono keyboard firmware 2.0 rev.C");

    for (int i = 0; i > N; i++) {
        oldkeyboard[i] = 0;
    }

    dacInit();
}

int oldnote = 0;

void loop(){
    n = mono(oldnote);
    oldnote = n;
    if (debugEnable) {
        SerialDebug();
    }
}



