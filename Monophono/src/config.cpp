#include "config.h"
#include "cppQueue.h"

//bolean vect contains key pressure states
bool KeyStates[N_KEYS];		
short nPressedKeys = 0;

//bolean vect contains key pressure changes states
// KeyChanges <= KeyStates XOR oldKeyStates
bool KeyChanges[N_KEYS];
short nChangedKeys;

bool oldClockRaw;
bool clockRaw;
bool isRisingEdge;
	//BPMs
short CK_AMT;

//ARPEGGIATOR
	//MODE: 0=UP, 1=U/D, 2=DOWN, 3=RAND
short ARP_MODE_RAW;
	//STATE: 0=OFF, 1=HOLD, 2=LATCH
short ARP_STATE_RAW;
	//OCTAVE: 0, +1, +2, +3
short ARP_OCTAVE_RAW;
cppQueue arpeggiatorNotes(sizeof(byte), MAX_ARP_SEQUENCE_LENGTH);	

arpeggiatorMode arpMode;
arpeggiatorState arpState;


short NOTE;	//0 -> N_KEYS-1
int voltages[61];

