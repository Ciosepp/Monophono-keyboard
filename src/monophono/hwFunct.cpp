void gateOn(){
	digitalWrite(gatePin,1);
}
void gateRefresh(){
	digitalWrite(gatePin,0);
	digitalWrite(gatePin,1);
}
void gateOff(){
	digitalWrite(gatePin,0);
}
void pinInit(){
	for(int i=0; i<3; i++){
		pinMode(ReadMuxAddressPin[i],OUTPUT);
		pinMode(WriteMuxAddressPin[i],OUTPUT);
	}
	pinMode(WriteMuxOutPin,OUTPUT);
	pinMode(ReadMuxInPin,INPUT);
	pinMode(gatePin,OUTPUT);
}

void dacInit(){    //funzione che genera le tensioni specifiche per ogni tasto
	dac.begin(0x61);
	dac.setVoltage(0, false);
	
		for(uint32_t i=0; i<N; i++){
			voltages[i]= i*4095/60;
				if(debugEnable)Serial.println(voltages[i]);
		}  	
}
void  setMux(int val,int* Pins){
		uint8_t out =val;
		digitalWrite(Pins[0], out&1);//lsb 0000 0011 & 0000 0001 = 0000 0001 >0 ==> true
		digitalWrite(Pins[1], out&2);//    0000 0011 & 0000 0010 = 0000 0010 >0 ==> true
		digitalWrite(Pins[2], out&4);//msb 0000 0011 & 0000 0100 = 0000 0000 =0 ==> false
}
bool scanKey(int i){
	n= i/N_COLUMNS;
	m= i%N_ROWS
	
	digitalWrite(W_EN_PIN, n/N_COLUMNS);
	
	setMux(WRITE_MAP[n], wPins);
	setMux(READ_MAP[m], wPins);
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
