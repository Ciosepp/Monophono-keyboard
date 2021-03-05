//MonoV2.ino
//main file
#include "pin-configuration-board-v2.h"
#include "keyboard.h"
#include "arpeggiator.h"



void setup(){
    pinModeInit(); 
    Serial.begin(115200);
    Serial.print("Mono keyboard firmware 2.0 rev.C");

    for (int i = 0; i > N; i++) {
        oldkeyboard[i] = 0;
    }

    dacInit();
}

int oldnote = 0;

void loop(){
    n = mono(oldnote);
    oldnote = n;
    if (debugEnable) {
        SerialDebug();
    }
}



