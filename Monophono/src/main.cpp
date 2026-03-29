#include <Arduino.h>

#include "config.h"
#include "pin_config.h"
#include "hwFunct.h"
#include "Functions.h"

#include "outputCtrl.h"

bool flag=false;
String str;

void setup() {

	Serial.begin(115200);
	Serial.print("Monophono debug \n");

	Init();

	clockSet(120, 2);

	
}

void loop() {
	
	readInputs();
	
	logic();

	output();
	

	if(!printFlag && CLOCK()) {

		// Serial.print("ARP_OCTAVE: ");
		// Serial.print(ARP_OCTAVE);
		// //Serial.println("");
		// Serial.print("  A_state: ");
		// Serial.print(arpState);
		// //Serial.println("");
		// Serial.print("  A_mode: ");
		// Serial.print(arpMode);
		// Serial.println("");

		// Serial.print("Pressed NOTES:");
		// Serial.println("");
		// for (int i = 0; i < N_KEYS; i++) {
		// Serial.print(KeyStates[i]);
		// }
	// 	Serial.println("");
	// 	Serial.print("ARP NOTES: ");

		// for (int i = 0; i < 21; i++){
		// 	Serial.print(arpeggiatorNotes[i]);
		// 	Serial.print(" ");
		// }	
	// 	Serial.println("");
	// 	Serial.print("current Note: ");
	// 	Serial.print(NOTE);
	// 	Serial.println("");
	// 	Serial.println("");
		printFlag = true;
	 }
	if(printFlag && !CLOCK()) printFlag=false;
	//Serial.println(voltages[NOTE]);
	//Serial.println(nPressedKeys);
}