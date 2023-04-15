#include "hwFunct.h"
#include "Functions.h"
#include "monophonoBoardPinHeader.h"
#include "config.h"
#include "Wire.h"
#include "MCP4725.h"
MCP4725 dac(0x62); 

#define N 60

void gateOn(){
	digitalWrite(GATE_PIN,1);
}
void gateRefresh(){
	digitalWrite(GATE_PIN,0);
	digitalWrite(GATE_PIN,1);
}
void gateOff(){
	digitalWrite(GATE_PIN,0);
}
void pinInit(){
	for(int i=0; i<3; i++){
		pinMode(READ_MUX_ADDRESS_PINS[i],OUTPUT);
		pinMode(WRITE_MUX_ADDRESS_PINS[i],OUTPUT);
	}
	pinMode(W_EN_PIN,OUTPUT);
	pinMode(R_MUX_OUT_PIN,INPUT);
	pinMode(GATE_PIN,OUTPUT);
}

void dacInit(){    //funzione che genera le tensioni specifiche per ogni tasto
	
	dac.writeDAC(0);
	
	for(uint32_t i=0; i<N; i++){
		voltages[i]= i*4095/60;
		if(debugEnable)Serial.println(voltages[i]);
	}  	
}
void setMux(int val,int* Pins){
	uint8_t out =val;
	for (int i = 0; i < 3; i++)
	{
		digitalWrite(Pins[i],1 & (val>>(2-i)));	
	}
}
bool scanKey(int i){
	short n= i/N_COLUMNS;
	short m= i%N_ROWS;

	digitalWrite(W_EN_PIN, n/N_COLUMNS);

	setMux(WRITE_MAP[n], WRITE_MUX_ADDRESS_PINS);
	setMux(READ_MAP[m], READ_MUX_ADDRESS_PINS);

	return digitalRead(R_MUX_OUT_PIN);
}
void scanKeyboard(bool *vect){
		//scan each key
	for(int i=0; i< N_KEYS; i++){
		vect[i] = scanKey(i);
	}
}
//this function read all the control inputs from  
//all potentiometers and GPI

void scanControls(){
		//INPUT CLOCK
	CK_IN = digitalRead(CK_IN_PIN);
		//CK SPEED
	CK_AMT = analogRead(CK_AMT_PIN);
		//ARPEGIATOR
	ARP_MODE_RAW = analogRead(ARP_MODE_PIN);
	ARP_STATE_RAW = analogRead(ARP_ON_PIN);
	ARP_OCT_RAW = analogRead(ARP_OCT_PIN);

}


void CVWrite(int Note)
{
	dac.writeDAC(Note);
}

void GateWrite(bool oldGT, int nK)
{

	if(nK >0)
	{
		if(oldGT == false) gateOn();
		else gateRefresh();
	} 
	else gateOff();

}
