#ifndef CONFIG_H
#define CONFIG_H 

#include <stdint.h>

#define N_ARPEGGIATOR_VOICE 7

#define N_OCTAVES_MAX 3

#define debugEnable 0

#define N_KEYS 49

#define PRESSED true
#define RELEASED false

#define MAX_ARP_SEQUENCE_LENGTH (N_ARPEGGIATOR_VOICE * N_OCTAVES_MAX)
	
//bolean vect contains key pressure states
extern bool KeyStates[N_KEYS];		
extern short nPressedKeys;

//true if a key is pressed
extern bool KEYDOWN;

//true if a key event (press or release) is detected
extern bool KEYEVENT;

//contains all the pressed notes
extern int8_t pressedNotes[N_KEYS];

//bolean vect contains key pressure changes states
// KeyChanges <= KeyStates XOR oldKeyStates
extern bool KeyChanges[N_KEYS];
extern short nChangedKeys;

extern bool oldClockRaw;
extern bool clockRaw;
extern bool isRisingEdge;
	//BPMs
extern short CK_AMT;

//ARPEGGIATOR
	//MODE: 0=UP, 1=U/D, 2=DOWN, 3=RAND
extern short ARP_MODE_RAW;
	//STATE: 0=OFF, 1=HOLD, 2=LATCH
extern short ARP_STATE_RAW;
	//OCTAVE: 0, +1, +2, +3
extern short ARP_OCTAVE_RAW;
extern uint8_t ARP_OCTAVE;
enum arpeggiatorState
{
	OFF,
	HOLD ,
	LATCH
};

enum arpeggiatorMode
{
	UP,
	UD,
	DOWN,
	RAND
};

extern arpeggiatorMode arpMode;
extern arpeggiatorState arpState;

extern bool arpNotes[MAX_ARP_SEQUENCE_LENGTH];


extern short NOTE;	//0 -> N_KEYS-1
extern int voltages[61];

extern int arpeggiatorNotes[MAX_ARP_SEQUENCE_LENGTH];
extern bool arpNoteLatch;


#endif
