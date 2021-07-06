#include "Arduino.h"
#include "display.h"


//TIE-DOWN_RESISTANCE = 10000 Ohms

//NOTE: +-1 Margin Added

//A_BUTTON_RESISTANCE = 1000 Ohms
const static constexpr unsigned short A_BUTTON_MIN = 617;
const static constexpr unsigned short A_BUTTON_MAX = 621;
const static constexpr unsigned short A_BUTTON_RANGE = A_BUTTON_MAX - A_BUTTON_MIN;

//B_BUTTON_RESISTANCE = 2000 Ohms
const static constexpr unsigned short B_BUTTON_MIN = 565;
const static constexpr unsigned short B_BUTTON_MAX = 569;
const static constexpr unsigned short B_BUTTON_RANGE = B_BUTTON_MAX - B_BUTTON_MIN;

//C_BUTTON_RESISTANCE = 3000 Ohms
const static constexpr unsigned short C_BUTTON_MIN = 523;
const static constexpr unsigned short C_BUTTON_MAX = 527;
const static constexpr unsigned short C_BUTTON_RANGE = C_BUTTON_MAX - C_BUTTON_MIN;

const static constexpr unsigned short AB_BUTTON_MIN = 637;
const static constexpr unsigned short AB_BUTTON_MAX = 641;
const static constexpr unsigned short AB_BUTTON_RANGE = AB_BUTTON_MAX - AB_BUTTON_MIN;

const static constexpr unsigned short AC_BUTTON_MIN = 632;
const static constexpr unsigned short AC_BUTTON_MAX = 636;
const static constexpr unsigned short AC_BUTTON_RANGE = AC_BUTTON_MAX - AC_BUTTON_MIN;

const static constexpr unsigned short BC_BUTTON_MIN = 607;
const static constexpr unsigned short BC_BUTTON_MAX = 611;
const static constexpr unsigned short BC_BUTTON_RANGE = BC_BUTTON_MAX - BC_BUTTON_MIN;

const static constexpr unsigned short ABC_BUTTON_MIN = 644;
const static constexpr unsigned short ABC_BUTTON_MAX = 648;
const static constexpr unsigned short ABC_BUTTON_RANGE = ABC_BUTTON_MAX - ABC_BUTTON_MIN;



static const constexpr unsigned short GROUND_THRESHOLD_VALUE = 3;
static const constexpr unsigned short INPUT_PIN = A0; //IMPORTANT NOTE: this pin value will change based on your board

unsigned short inputVoltageLevel = 0;
unsigned short highestInputVoltageLevel = 0;


void buttonUp() {

}



void buttonDown() {
	if((unsigned)(inputVoltageLevel - A_BUTTON_MIN) <= A_BUTTON_RANGE) {
		Serial.println(F("A button"));
		return;
	}

	if((unsigned)(inputVoltageLevel - B_BUTTON_MIN) <= B_BUTTON_RANGE) {
		Serial.println(F("B button"));
		return;
	}

	if((unsigned)(inputVoltageLevel - C_BUTTON_MIN) <= C_BUTTON_RANGE) {
		Serial.println(F("C button"));
		return;
	}

	if((unsigned)(inputVoltageLevel - AB_BUTTON_MIN) <= AB_BUTTON_RANGE) {
		Serial.println(F("A+B buttons"));
		return;
	}

	if((unsigned)(inputVoltageLevel - AC_BUTTON_MIN) <= AC_BUTTON_RANGE) {
		Serial.println(F("A+C buttons"));
		return;
	}

	if((unsigned)(inputVoltageLevel - BC_BUTTON_MIN) <= BC_BUTTON_RANGE) {
		Serial.println(F("B+C buttons"));
		return;
	}

	if((unsigned)(inputVoltageLevel - ABC_BUTTON_MIN) <= ABC_BUTTON_RANGE) {
		Serial.println(F("A+B+C buttons"));
		return;
	}
}


void getInput() {
	inputVoltageLevel = analogRead(INPUT_PIN);
	//Serial.println(inputVoltageLevel);

	if(inputVoltageLevel < GROUND_THRESHOLD_VALUE) {
		if(highestInputVoltageLevel != 0) { //optimize nested loop out of every frame
			buttonUp();
			highestInputVoltageLevel = 0;
		}

		return;
	} else {
		if(inputVoltageLevel > highestInputVoltageLevel) {
			buttonDown(); //maybe debounce here?
		}
	}

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
	pinMode(INPUT_PIN, INPUT);

	Serial.begin(9600);
	while(!Serial) {
		delay(250);
	}

	Serial.println(F("Running!"));
}