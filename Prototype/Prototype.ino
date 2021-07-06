#include "Arduino.h"


//TIE-DOWN_RESISTANCE = 10000 Ohms

//NOTE: +-1 Margin Added

//A_BUTTON_RESISTANCE = 1000 Ohms
const static unsigned short A_BUTTON_MIN = 617;
const static unsigned short A_BUTTON_MAX = 621;

//B_BUTTON_RESISTANCE = 2000 Ohms
const static unsigned short B_BUTTON_MIN = 565;
const static unsigned short B_BUTTON_MAX = 569;

//C_BUTTON_RESISTANCE = 3000 Ohms
const static unsigned short C_BUTTON_MIN = 523;
const static unsigned short C_BUTTON_MAX = 527;

const static unsigned short AB_BUTTON_MIN = 637;
const static unsigned short AB_BUTTON_MAX = 641;

const static unsigned short AC_BUTTON_MIN = 632;
const static unsigned short AC_BUTTON_MAX = 636;

const static unsigned short BC_BUTTON_MIN = 607;
const static unsigned short BC_BUTTON_MAX = 611;

const static unsigned short ABC_BUTTON_MIN = 644;
const static unsigned short ABC_BUTTON_MAX = 648;




static const constexpr unsigned short inputValueMargin = 6;
static const constexpr unsigned short inputPin = 14;
unsigned short inputVoltageLevel;


void getInput() {
	inputVoltageLevel = analogRead(inputPin);

	//If voltage increase is detected, record highest value as input state

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