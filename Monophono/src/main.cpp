#include <Arduino.h>

#include "config.h"
#include "pin_config.h"
#include "hwFunct.h"

void setup() {
	pinInit();
	Serial.begin(9600);
	gateOn();

}

void loop() {
	scanKeyboard(KeyStates);
	for (int i = 0; i < N_KEYS; i++)
	{
		Serial.print(KeyStates[i]);
	}
	Serial.print("\n");
	delay(1000);
}