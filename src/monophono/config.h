#ifndef CONFIG_H
#define CONFIG_H 


#define N_ARPEGGIATOR_VOICE 7
#define N_OCTAVES_MAX 4
#define debugEnable 0

	
//bolean vect contains key pressure states
bool pressedKeys[N_KEYS];		

//bolean vect contains old key pressure states
bool oldPressedKeys[N_KEYS];

bool CK_IN;
	//BPMs
short CK_AMT;

//ARPEGGIATOR
	//MODE: 0=UP, 1=U/D, 2=DOWN, 3=RAND
short ARP_MODE_RAW;
	//STATE: 0=OFF, 1=HOLD, 2=LATCH
short ARP_STATE_RAW;
	//OCTAVE: 0, +1, +2, +3
short ARP_OCTAVE_RAW;

enum arpeggiatorState
{
	OFF=	0,
	HOLD =	1,
	LATCH=	2};
enum arpeggiatorMode
{
	UP=		0,
	UD=		1,
	DOWN=	2,
	RAND=	3
};	

arpeggiatorMode arpMode;
arpeggiatorState arpState;


short NOTE=0;	//0 -> N_KEYS-1
int voltages[N_KEYS];


short nPressedKeys = 0;

//flag per indicare se ci sono ancora altre note premute
bool noteAppend = false;


int arpeggiatorNotes[N_ARPEGGIATOR_VOICE * N_OCTAVES_MAX];
bool arpNoteLatch= false;


#endif
