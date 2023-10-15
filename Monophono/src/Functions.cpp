#include "Functions.h"

#include "config.h"
#include "hwFunct.h"
#include "mono.h"
#include "pin_config.h"

void Init() {
    pinInit();
    dacInit();
}

bool noteDown(int i, bool* noteScan, bool* noteTrans) {
    return noteScan[i] && noteTrans[i];
}
bool noteUp(int i, bool* noteScan, bool* noteTrans) {
    return noteScan[i] && !noteTrans[i];
}

void elabControls() {
    ARP_MODE_RAW = map(ARP_MODE_RAW, 0, 1023, 0, 3);

    switch (ARP_MODE_RAW) {
        case 0:
            arpMode = UP;
            break;

        case 1:
            arpMode = UD;
            break;

        case 2:
            arpMode = DOWN;
            break;

        case 3:
            arpMode = RAND;
            break;

        default:
            break;
    }

    ARP_STATE_RAW = map(ARP_STATE_RAW, 0, 1023, 0, 2);

    switch (ARP_STATE_RAW) {
        case 0:
            arpState = OFF;
            break;

        case 1:
            arpState = HOLD;
            break;

        case 2:
            arpState = LATCH;
            break;

        default:
            break;
    }

    ARP_OCTAVE_RAW = map(ARP_OCTAVE_RAW, 0, 1023, 0, 3);

    CK_AMT = map(CK_AMT, 0, 1023, 60, 300);
}

void logic() {
    elabControls();
    // switch between MONO, arpeggiator HOLD or LATCH
    /* switch(arpState){
        case OFF:
        mono();
        break;
        case HOLD:
        arpeggiatorHold();
        break;
        case LATCH:
        arpeggiatorLatch();
        break;
    } */

    // dev
    mono();
}

void readInputs() {
    scanKeyboard();
    scanControls();
    scanClock();
}
