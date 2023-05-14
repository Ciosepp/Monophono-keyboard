#include <Arduino.h>

#include "config.h"
#include "pin_config.h"
#include "hwFunct.h"

#include "outputCtrl.h"

String str;
void setup() {
	pinInit();
	Serial.begin(9600);
	Serial.print("Monophono debug \n");
	gateOn();
	delay(2000);
	clockSet(120, 1);

}
bool flag=false;

void loop() {
	digitalWrite(GATE_PIN,CLOCK() );
	scanControls();
	ckOutput();
	if(!flag && CLOCK())
	{
		Serial.print( "ARP_EN:");
		Serial.print(map(ARP_STATE_RAW,1023,0,0,2));
		Serial.print(" CKamt: ");
		Serial.print(map(CK_AMT,0,1023,60,300));
		clockSet(map(CK_AMT,0,1023,60,300), map(ARP_OCTAVE_RAW,1023,0,1,4));
		Serial.print(" ARP_MODE:");
		Serial.print(map(ARP_MODE_RAW,1023,0,0,3));
		Serial.print(" OCT:");
		Serial.print(map(ARP_OCTAVE_RAW,1023,0,0,3));
		Serial.println("");
		flag=true;
	}
	if(flag && !CLOCK())flag=false;
	
}