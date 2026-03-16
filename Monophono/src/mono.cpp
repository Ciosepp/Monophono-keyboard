#include "mono.h"
#include "config.h"

// mono states(sequential):
// 1- no key are pressed:   nothing heppens
// 2- one key pressed :     NOTE is updated
// 3- a new key is pressed: NOTE is updated with the lastest
// 4- a new key is pressed: NOTE is updated with the lastest
// 5- the last pressed key is released: NOTE is assigned among pressed keys


//if true a new note has to be assigned
bool noteAppend = false;
void mono(){
    for (short i = 0; i < N_KEYS; i++)
    {
        if (KeyChanges[i] ) //detect 
        {
            if(KeyStates[i]) //key-down
            {
                //nPressedKeys++;//handled by keyboard scan funct
                OLD_NOTE = NOTE;
                NOTE = i;
            }
            else            //key-up
            {
                //nPressedKeys--;//handled by keyboard scan funct
                if(nPressedKeys != 0){//if at least one key pressed
                    if(i == NOTE)   //the last pessed key is released
                    {
                        noteAppend = true;//find new note among already pressed
                    }
                }
            }
        }
        if (noteAppend == true)
        {
            if(KeyStates[i])
            {
                OLD_NOTE = NOTE;
                NOTE = i;
                noteAppend = false;
            }
        }  
    }
   
}

void MONO_GATE(){
    if (nPressedKeys > 0) {
		GATE = 1;
	}
	if(OLD_NOTE != NOTE){
		GATE = 2;
	}
	if(nPressedKeys == 0){
		GATE = 0;
	}
}
