#include "include/logic.h"


void Logic::update(Queue<ButtonEvent>& events) {
	while(!events.empty()) {
		currentEvent = events.dequeue()->getData();

		
		Serial.print(currentEvent->button.getName());
		Serial.print(": ");
		Serial.println(currentEvent->pressed ? "down" : "up");
	}
}