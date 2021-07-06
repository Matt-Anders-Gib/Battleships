#include "Arduino.h"


void getInput() {
	//poll input pin
	//figure out button configuration based on value
	//set button states
}


void updateDisplay() {
	//function pointer (menus, game screen, etc)

	//redraw game
	
	//check for changes, update menu/whatever
}


void checkNetwork() {
	//send/find heartbeat
	//send game updates
	//receive game updates
}


void loop() {
	getInput();
	updateDisplay();
	checkNetwork();
}


void setup() {
	Serial.begin(9600);
	while(!Serial) {
		delay(250);
	}
}