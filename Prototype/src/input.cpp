#include "include/input.h"


void Input::getInput() {
	buttonEvent = buttons.poll();

	if(buttonEvent != BUTTON_EVENT_NONE) { //TODO: Think of some way to do this branchlessly
		Serial.print(buttonEvent.identifier);
		Serial.print(F(" "));
		Serial.println(buttonEvent.pressed);
	}
}