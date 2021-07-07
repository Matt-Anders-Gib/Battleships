#include "include/buttons.h"


void Buttons::up() {
	inputStartTime = 0;
}


void Buttons::down(const unsigned short voltageLevel) {
	if((unsigned)(voltageLevel - A_BUTTON_MIN) <= A_BUTTON_RANGE) {
		Serial.println(F("A button"));
		return;
	}

	if((unsigned)(voltageLevel - B_BUTTON_MIN) <= B_BUTTON_RANGE) {
		Serial.println(F("B button"));
		return;
	}

	if((unsigned)(voltageLevel - C_BUTTON_MIN) <= C_BUTTON_RANGE) {
		Serial.println(F("C button"));
		return;
	}

	if((unsigned)(voltageLevel - AB_BUTTON_MIN) <= AB_BUTTON_RANGE) {
		Serial.println(F("A+B buttons"));
		return;
	}

	if((unsigned)(voltageLevel - AC_BUTTON_MIN) <= AC_BUTTON_RANGE) {
		Serial.println(F("A+C buttons"));
		return;
	}

	if((unsigned)(voltageLevel - BC_BUTTON_MIN) <= BC_BUTTON_RANGE) {
		Serial.println(F("B+C buttons"));
		return;
	}

	if((unsigned)(voltageLevel - ABC_BUTTON_MIN) <= ABC_BUTTON_RANGE) {
		Serial.println(F("A+B+C buttons"));
		return;
	}

	Serial.print(F("Unexpected voltage level: "));
	Serial.println(voltageLevel);
}


void Buttons::poll() {
	nowMS = millis();
	inputVoltageLevel = analogRead(INPUT_PIN);
	//Serial.println(inputVoltageLevel);

	if(waitingForInput && nowMS > inputStartTime + INPUT_SEARCH_MS) {
		void = down(highestInputVoltageLevel);
		highestInputVoltageLevel = 0;

		//send(?) button to "logic controller"
		waitingForInput = false;
	}

	if(inputVoltageLevel > GROUND_THRESHOLD_VALUE) { //AT LEAST ONE BUTTON IS CURRENTLY BEING PRESSED
		if(nowMS > inputStartTime + INPUT_SEARCH_MS) { //THIS IS THE FIRST INPUT IN A SEARCH PERIOD
			inputStartTime = nowMS;
			waitingForInput = true;
		} else { //THIS INPUT IS IN THE MIDDLE OF AN INPUT SEARCH PERIOD
			if(inputVoltageLevel > highestInputVoltageLevel) {
				highestInputVoltageLevel = inputVoltageLevel;
			}
		}
	} else {

	}

	//If voltage increase is detected, record highest value as input state

	//poll input pin
	//figure out button configuration based on value
	//set button states
}