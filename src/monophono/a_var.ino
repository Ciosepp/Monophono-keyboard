//////////////////////	variables for monophono firmware	///////
#include "monophonoBoardPinHeader.h"

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

enum monoMode
{
	HIGH 	= 0,
	LOW		= 1
}

arpeggiatorMode arpMode;
arpeggiatorState arpState;
monoMode keyMode;

short NOTE=0;	//0 -> N_KEYS-1
int voltages[N_KEYS];

short nPressedKeys = 0;
bool noteAppend=false;

const short nArpeggiatorVoices = 7;
const short N_OCTAVES_MAX =4;
int arpeggiatorNotes[nArpeggiatorVoices * N_OCTAVES_MAX];
bool arpNoteLatch= false;

