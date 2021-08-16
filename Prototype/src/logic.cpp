#include "include/logic.h"


Logic::Logic() {
	
}


void Logic::update(EventQueue& events) {
	while(!events.empty()) {
		Event& currentEvent = events.dequeue(); //do not declare every cycle!
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
			Serial.println(F("Event wasted"));
		}
	}
}