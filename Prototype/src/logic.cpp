#include "include/logic.h"


Logic::Logic(EventQueue& eventsQueue) : events{eventsQueue} {
	rawButtonListener = LogicListener(this, &Logic::convertRawButtonToInput, EVENT_TYPE::EVENT_RAW_BUTTON_DOWN);
	events.registerListener(rawButtonListener);
}


void Logic::convertRawButtonToInput(Event& e) {
Serial.println(F("Raw button to convert into input"));
	events.enqueue(EVENT_TYPE::EVENT_INPUT_DOWN, e.attribute);
}


void Logic::update() {
	while(!events.empty()) {
		currentEvent = events.dequeue();
		eventUsed = false; 

		currentListener = events.firstListener();
		while(currentListener != nullptr) {
Serial.println(F("top of current listener loop"));
			if(currentEvent.type == currentListener->getData().eventType) { //NOTE: crashing right here!
Serial.println(F("Before call"));
				currentListener->getData()(currentEvent);
Serial.println(F("After call"));
				eventUsed = true;
			}

Serial.println(F("To next node"));
			currentListener = currentListener->getNextNode();
Serial.println(F("currentListener assigned"));
		}
Serial.println(F("Leave listener while loop scope"));

		if(!eventUsed) {
			Serial.print(F("Event discarded: "));
			Serial.println(static_cast<int>(currentEvent.type));
		}
Serial.println(F("Leave event while loop scope"));
	}

Serial.println(F("End of update"));
}