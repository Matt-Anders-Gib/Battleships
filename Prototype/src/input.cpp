#include "include/input.h"


ButtonEvent Input::up() {
	Serial.print(F("Highest value: "));
	Serial.println(highestInputVoltageLevel);
	highestInputVoltageLevel = 0;

	return BUTTON_EVENT_NONE;
}


ButtonEvent Input::down(const unsigned short voltageLevel) {
	if((unsigned)(voltageLevel - A_BUTTON_MIN) <= A_BUTTON_RANGE) {
		return ButtonEvent(BUTTON::BTN_A, 'A', true);
	}

	if((unsigned)(voltageLevel - B_BUTTON_MIN) <= B_BUTTON_RANGE) {
		return ButtonEvent(BUTTON::BTN_B, 'B', true);
	}

	if((unsigned)(voltageLevel - C_BUTTON_MIN) <= C_BUTTON_RANGE) {
		return ButtonEvent(BUTTON::BTN_C, 'C', true);
	}

	if((unsigned)(voltageLevel - AB_BUTTON_MIN) <= AB_BUTTON_RANGE) {
		return ButtonEvent(BUTTON::BTN_AB, 'X', true);
	}

	if((unsigned)(voltageLevel - AC_BUTTON_MIN) <= AC_BUTTON_RANGE) {
		return ButtonEvent(BUTTON::BTN_AC, 'Y', true);
	}

	if((unsigned)(voltageLevel - BC_BUTTON_MIN) <= BC_BUTTON_RANGE) {
		return ButtonEvent(BUTTON::BTN_BC, 'Z', true);
	}

	if((unsigned)(voltageLevel - ABC_BUTTON_MIN) <= ABC_BUTTON_RANGE) {
		return ButtonEvent(BUTTON::BTN_ABC, '-', true);
	}

	Serial.print(F("Unexpected voltage level: "));
	Serial.println(voltageLevel);
	return BUTTON_EVENT_NONE;
}


ButtonEvent Input::poll() {
	nowMS = millis();
	inputVoltageLevel = analogRead(INPUT_PIN);
	
	event = BUTTON_EVENT_NONE;

	if(inputVoltageLevel > GROUND_THRESHOLD_VALUE) {
		//Serial.println(inputVoltageLevel);

		if(buttonPressedLastFrame == false) {
			inputStartTime = nowMS;
			buttonPressedLastFrame = true;
			inputProcessed = false;
		}

		if(nowMS < inputStartTime + INPUT_SEARCH_MS && inputVoltageLevel > highestInputVoltageLevel) {
			highestInputVoltageLevel = inputVoltageLevel;
		}
	} else {
		if(buttonPressedLastFrame) {
			event = up();
			buttonPressedLastFrame = false;
		}
	}

	if(inputProcessed == false && nowMS > inputStartTime + INPUT_SEARCH_MS) {
		event = down(highestInputVoltageLevel);

		
		inputProcessed = true;
	}

	return event;
}