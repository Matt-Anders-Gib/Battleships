#include "include/logic.h"


Logic::Logic() {
	
}


void Logic::update(EventQueue& events) {
	while(!events.empty()) {
		currentEvent = events.dequeue();
		eventUsed = false; 

		currentListener = events.firstListener();
		while(currentListener != nullptr) {

			if(currentEvent.type == currentListener->getData().eventType) {
				currentListener->getData()();
				eventUsed = true;
			}

			currentListener = currentListener->getNextNode();
		}

		if(!eventUsed) {
			Serial.print(F("Event discarded: "));
			Serial.println(static_cast<int>(currentEvent.type));
		}
	}
}