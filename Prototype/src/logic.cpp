#include "include/logic.h"


void Logic::update(EventQueue& events) {
	while(!events.empty()) {
		currentEvent = events.dequeue();
		
		switch(currentEvent.type) {
		case EVENT_TYPE::EVENT_A_BUTTON_DOWN:
			Serial.println(F("A Button Down"));
		break;

		case EVENT_TYPE::EVENT_A_BUTTON_UP:
			Serial.println(F("A Button Up"));
		break;

		case EVENT_TYPE::EVENT_B_BUTTON_DOWN:
			Serial.println(F("B Button Down"));
		break;

		case EVENT_TYPE::EVENT_B_BUTTON_UP:
			Serial.println(F("B Button Up"));
		break;

		case EVENT_TYPE::EVENT_S_BUTTON_DOWN:
			Serial.println(F("S Button Down"));
		break;

		case EVENT_TYPE::EVENT_S_BUTTON_UP:
			Serial.println(F("S Button Up"));
		break;

		case EVENT_TYPE::EVENT_NONE:
			Serial.println(F("EVENT_NONE"));
		break;

		default:
			Serial.println(F("Unknown event"));
		break;
		}
	}
}