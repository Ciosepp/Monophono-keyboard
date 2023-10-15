#include "arpeggiator.h"

#include "config.h"
#include "cppQueue.h"
#include "hwFunct.h"

bool BUSY = false;
short nNOTES = 0;

bool isInCycle = false;

bool arpLatch = false;

enum ArpeggiatorStates {
    AWAITING_KEYPRESS,
    PLAYING,
};

// this function scans the keyboard and fills the arp. buffer
// it also returns true if at least one key is pressed, false else.
bool arpRegisterNote() {
    scanKeyboard();
    nPressedKeys = 0;

    for (short i = 0; i < N_KEYS; i++) {
        if (nPressedKeys >= N_ARPEGGIATOR_VOICE) {
            break;  // out if buffer full
        }

        if (KeyStates[i] == PRESSED) {
            arpeggiatorNotes[nPressedKeys] = i;  // save note
            nPressedKeys++;                      // new note
        }
    }
    if (nPressedKeys > 0) {
        return true;
    }
    return false;
}

void arpeggiatorHold() {
    if (nPressedKeys == 0) {
        // TODO: clear the queue and stop playing
        // arpeggiatorClear();
        return;
    }
    if (!isRisingEdge) {
        // awaiting the beat signal
        return;
    }
    
}