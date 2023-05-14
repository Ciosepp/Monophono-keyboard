
#ifndef CONFIG_H
#define CONFIG_H 


#define N_ARPEGGIATOR_VOICE 7
#define N_OCTAVES_MAX 4
#define debugEnable 0

#define N_KEYS 49
	
//bolean vect contains key pressure states
extern bool KeyStates[N_KEYS];		

//bolean vect contains old key pressure states
extern bool oldKeyStates[N_KEYS];

//bolean vect contains key pressure changes states
// KeyChanges <= KeyStates XOR oldKeyStates
extern bool KeyChanges[N_KEYS];

extern bool CK_IN;
	//BPMs
extern short CK_AMT;

//ARPEGGIATOR
	//MODE: 0=UP, 1=U/D, 2=DOWN, 3=RAND
extern short ARP_MODE_RAW;
	//STATE: 0=OFF, 1=HOLD, 2=LATCH
extern short ARP_STATE_RAW;
	//OCTAVE: 0, +1, +2, +3
extern short ARP_OCTAVE_RAW;
enum arpeggiatorState
{
	OFF,
	HOLD ,
	LATCH};
enum arpeggiatorMode
{
	UP,
	UD,
	DOWN,
	RAND
};

extern arpeggiatorMode arpMode;
extern arpeggiatorState arpState;


extern short NOTE;	//0 -> N_KEYS-1
extern int voltages[61];


extern short nPressedKeys;

extern int arpeggiatorNotes[N_ARPEGGIATOR_VOICE * N_OCTAVES_MAX];
extern bool arpNoteLatch;


#endif
