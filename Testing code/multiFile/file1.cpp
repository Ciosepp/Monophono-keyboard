#include "file1.h"
#include "a.h"

short pin=13, timer = 300;
bool state = true;
int var =10;




void inito(int q){
    pinMode(pin, OUTPUT);
    
}
void bl()
{
    digitalWrite(pin,state);
    delay(timer );
    digitalWrite(pin,!state);
    delay(timer);
    
}
