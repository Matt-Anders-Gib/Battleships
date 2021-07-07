#include "include/input.h"


void Input::buttonUp() {
	inputStartTime = 0;
}



void Input::buttonDown() {
	if(inputStartTime == 0) {
		inputStartTime = millis();
	}

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

	Serial.print(F("Unexpected voltage level: "));
	Serial.println(inputVoltageLevel);
}


void Input::getInput() {
	inputVoltageLevel = analogRead(INPUT_PIN);
	//Serial.println(inputVoltageLevel);

	if(inputVoltageLevel < GROUND_THRESHOLD_VALUE) {
		if(highestInputVoltageLevel != 0) { //TODO: optimize nested condition out of every frame
			buttonUp();
			highestInputVoltageLevel = 0;
		}

		return;
	} else {
		if(inputVoltageLevel > highestInputVoltageLevel) {
			buttonDown(); //maybe debounce here?
		}
	}

	if(inputStartTime < millis() - INPUT_SEARCH_MS) {
		
	}

	//If voltage increase is detected, record highest value as input state

	//poll input pin
	//figure out button configuration based on value
	//set button states
}