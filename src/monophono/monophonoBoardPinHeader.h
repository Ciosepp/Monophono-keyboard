////////////////// MONOPHONO PIN CONFIGURATOR	///////////////////////
//#define version 2.5
#define version 25

#if version == 3
	#define __V3_BOARD__
#elif version == 25
	#define __V2_5_BOARD__
#endif
////				BOARD: V3

#ifdef __V2_5_BOARD__
	#define MIDI_OUT_PIN 1
    #define CLOCK_OUT_PIN 2
    #define GATE_PIN 3

    #define W_EN_PIN        13
    #define W_MUX_C_PIN     12
    #define W_MUX_B_PIN     11
    #define W_MUX_A_PIN     10
    #define R_MUX_OUT_PIN   9
    #define R_MUX_C_PIN     8
    #define R_MUX_B_PIN     7
    #define R_MUX_A_PIN     6
    //#define MATRIX_WRITE_EXTERNAL_PIN 13
    //const short int WRITE_MUX_ADDRESS_PINS[] = {10, 11, 12};
    //#define READ_MUX_OUT_VALUE_PIN 9
    //const short int READ_MUX_ADDRESS_PINS[] = {6, 7, 8};    
    
    #define ARPEGGIATOR_CLOCK_IN_PIN 4
    #define ARPEGGIATOR_MODE_PIN 14
    #define ARPEGGIATOR_CLOCK_DIVISION_PIN 15
    #define ARPEGGIATOR_CLOCK_RATE_PIN 16
    #define ARPEGGIATOR_OCTAVE_EXTENSION_PIN 17
    #define SEQUENCER_PIN 20

#endif

#ifdef __V3_BOARD__
    #define W_EN_PIN        2
    #define W_MUX_C_PIN     3
    #define W_MUX_B_PIN     4
    #define W_MUX_A_PIN     5
    #define R_MUX_OUT_PIN   6
    #define R_MUX_C_PIN     7
    #define R_MUX_B_PIN     8
    #define R_MUX_A_PIN     9

    #define MIDI_OUT_PIN    10
    #define NC_PIN          11
    #define CK_IN_PIN       12
    #define CK_OUT_PIN      13
    #define CK_AMT_PIN      14
    #define ARP_OCT_PIN     15
    #define ARP_MODE_PIN    16
    #define ARP_ON_PIN      17

    #define I2C_SDA_PIN     18
    #define I2C_SCL_PIN     19
        
    #define AUX1_PIN        20
    #define AUX2_PIN        21
#endif

const short WRITE_MUX_ADDRESS_PINS[3] = {W_MUX_A_PIN,
						W_MUX_B_PIN,
						W_MUX_C_PIN};

const short READ_MUX_ADDRESS_PINS[3] = {R_MUX_A_PIN,
						R_MUX_B_PIN,
						R_MUX_C_PIN};

const short N_ROWS = 9;
const short N_COLUMNS = 6;

#define N_KEYS 49
#define PRESSED true
#define N_OCTAVES 4

//hardware port mapping
	//write(rows) multiplexer
int WRITE_MAP[N_ROWS-1]={3,0,1,2,4,6,7,5};
	//read(colmns) multiplexer
int READ_MAP[N_COLUMNS]={5,6,4,2,1,0};
