#include "include/buttons.h"


ButtonEvent Buttons::up() {
	return BUTTON_EVENT_NONE;
}


ButtonEvent Buttons::down(const unsigned short voltageLevel) {
	if((unsigned)(voltageLevel - A_BUTTON_MIN) <= A_BUTTON_RANGE) {
		//Serial.println(F("A button"));
		return ButtonEvent(BUTTON::A, 'A', true);
	}

	if((unsigned)(voltageLevel - B_BUTTON_MIN) <= B_BUTTON_RANGE) {
		//Serial.println(F("B button"));
		return ButtonEvent(BUTTON::B, 'B', true);
	}

	if((unsigned)(voltageLevel - C_BUTTON_MIN) <= C_BUTTON_RANGE) {
		//Serial.println(F("C button"));
		return ButtonEvent(BUTTON::C, 'C', true);
	}

	if((unsigned)(voltageLevel - AB_BUTTON_MIN) <= AB_BUTTON_RANGE) {
		//Serial.println(F("A+B buttons"));
		return ButtonEvent(BUTTON::AB, 'X', true);
	}

	if((unsigned)(voltageLevel - AC_BUTTON_MIN) <= AC_BUTTON_RANGE) {
		//Serial.println(F("A+C buttons"));
		return ButtonEvent(BUTTON::AC, 'Y', true);
	}

	if((unsigned)(voltageLevel - BC_BUTTON_MIN) <= BC_BUTTON_RANGE) {
		//Serial.println(F("B+C buttons"));
		return ButtonEvent(BUTTON::BC, 'Z', true);
	}

	if((unsigned)(voltageLevel - ABC_BUTTON_MIN) <= ABC_BUTTON_RANGE) {
		//Serial.println(F("A+B+C buttons"));
		return ButtonEvent(BUTTON::ABC, '-', true);
	}

	Serial.print(F("Unexpected voltage level: "));
	Serial.println(voltageLevel);
	return BUTTON_EVENT_NONE;
}


ButtonEvent Buttons::poll() {
	nowMS = millis();
	inputVoltageLevel = analogRead(INPUT_PIN);
	event = BUTTON_EVENT_NONE;

	if(inputVoltageLevel > GROUND_THRESHOLD_VALUE) {
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

		highestInputVoltageLevel = 0;
		inputProcessed = true;
	}

	return event;
}