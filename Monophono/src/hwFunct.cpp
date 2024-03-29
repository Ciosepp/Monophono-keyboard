#include "hwFunct.h"

#include "MCP4725.h"
#include "Wire.h"
#include "config.h"
#include "pin_config.h"
MCP4725 dac(0x60);

#include "Timer.h"
Timer BPM32;

void clockSet(short BPM, short division) {
    unsigned long t = (60000 / BPM) / division;
    BPM32.setClock(t, 50);
}
bool CLOCK() {
    return BPM32.getClock();
}

void writeClock(bool x) {
    digitalWrite(CLOCK_OUT_PIN, x);
}

void gateOn() {
    digitalWrite(GATE_PIN, 1);
}
void gateRefresh() {
    digitalWrite(GATE_PIN, 0);
    digitalWrite(GATE_PIN, 1);
}
void gateOff() {
    digitalWrite(GATE_PIN, 0);
}

void pinInit() {
    for (int i = 0; i < 3; i++) {
        pinMode(READ_MUX_ADDRESS_PINS[i], OUTPUT);
        pinMode(WRITE_MUX_ADDRESS_PINS[i], OUTPUT);
    }
    pinMode(W_EN_PIN, OUTPUT);
    pinMode(R_MUX_OUT_PIN, INPUT);

    pinMode(GATE_PIN, OUTPUT);

    pinMode(CLOCK_OUT_PIN, OUTPUT);
    pinMode(CK_IN_PIN, INPUT);
}

void dacInit() {  // funzione che genera le tensioni specifiche per ogni tasto
    dac.begin();
    dac.writeDAC(0);

    for (uint32_t i = 0; i < N; i++) {
        double x = 4095.0 / 60.0;
        voltages[i] = i * x;
        Serial.println(voltages[i]);
    }
}

void setMux(int val, const short* Pins) {
    for (int i = 0; i < 3; i++) {
        digitalWrite(Pins[i], 1 & (val >> i));
    }
}

bool scanKey(int i) {
    bool x = 0;
    // hardware port mapping
    // write(rows) multiplexer
    int WRITE_MAP[N_ROWS - 1] = {3, 0, 1, 2, 6, 7, 4, 5};
    // read(colmns) multiplexer
    int READ_MAP[N_COLUMNS] = {6, 4, 1, 2, 0, 3};

    short w = i / N_COLUMNS;
    short r = i % N_COLUMNS;

    digitalWrite(W_EN_PIN, w == 0);

    setMux(WRITE_MAP[(w - 1) % (N_ROWS - 1)], WRITE_MUX_ADDRESS_PINS);

    setMux(READ_MAP[r], READ_MUX_ADDRESS_PINS);

    // delayMicroseconds(50);
    x = digitalRead(R_MUX_OUT_PIN);
    return x;
}

void scanKeyboard() {
    for (int i = 0; i < N_KEYS; i++) {
        bool oldKeyState = KeyStates[i];
        KeyStates[i] = scanKey(i);
        KeyChanges[i] = oldKeyState ^ KeyStates[i];
        nPressedKeys += (int)KeyStates[i];
        nChangedKeys += (int)KeyChanges[i];
    }
    setMux(0, WRITE_MUX_ADDRESS_PINS);  // non sicuro sia necessario
    setMux(0, READ_MUX_ADDRESS_PINS);
}
// this function read all the control inputs from
// all potentiometers and GPI

void scanControls() {
    // CK SPEED
    CK_AMT = analogRead(CK_AMT_PIN);
    // ARPEGIATOR
    ARP_MODE_RAW = analogRead(ARP_MODE_PIN);
    ARP_STATE_RAW = analogRead(ARP_ON_PIN);
    ARP_OCTAVE_RAW = analogRead(ARP_OCT_PIN);
}

void scanClock() {
    oldClockRaw = clockRaw;
    // INPUT CLOCK
    clockRaw = digitalRead(CK_IN_PIN);
    if (oldClockRaw == LOW and clockRaw == HIGH) {
        isRisingEdge = true;
    }
}

void CVWrite(int ADC_VAL) {
    dac.writeDAC(ADC_VAL);
}

void GateWrite(bool isFirst, int nK) {
    if (nK > 0) {
        if (isFirst == true)
            gateOn();
        else
            gateRefresh();
    } else
        gateOff();
}
