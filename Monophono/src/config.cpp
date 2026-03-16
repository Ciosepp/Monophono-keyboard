#include "config.h"
#include "cppQueue.h"

//bolean vect contains key pressure states
bool KeyStates[N_KEYS];		
int8_t pressedNotes[N_KEYS];
short nPressedKeys = 0;

bool KEYDOWN;
bool KEYEVENT;

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
uint8_t ARP_OCTAVE;
//cppQueue arpeggiatorNotes(sizeof(byte), MAX_ARP_SEQUENCE_LENGTH);	

bool arpNotes[N_ARPEGGIATOR_VOICE *N_OCTAVES_MAX];

int arpeggiatorNotes[MAX_ARP_SEQUENCE_LENGTH];

arpeggiatorMode arpMode;
arpeggiatorState arpState;

bool isFirstArpegio = true;


short NOTE;	//0 -> N_KEYS-1
short OLD_NOTE;	//0 -> N_KEYS-1
int voltages[61];

uint8_t GATE;
bool GATE_STACCATO = true;



