#include "include/logic.h"


Logic::Logic(EventQueue& eventsQueue) : events{eventsQueue} {
	rawButtonListener = LogicListener(this, &Logic::convertRawButtonToInput, EVENT_TYPE::EVENT_RAW_BUTTON_DOWN);
	events.registerListener(rawButtonListener);
}


void Logic::convertRawButtonToInput(Event& e) {
	events.enqueue(EVENT_TYPE::EVENT_INPUT_DOWN, e.attribute);
}


void Logic::update() {
	while(!events.empty()) {
		Event& currentEvent = events.dequeue();
		eventUsed = false;

		currentListener = events.firstListener();
		while(currentListener != nullptr) {
			if(currentEvent.type == currentListener->getData().eventType) {
				currentListener->getData()(currentEvent);
				eventUsed = true;
				break;
			}

			currentListener = currentListener->getNextNode();
		}

		if(!eventUsed) {
			Serial.print(F("Event discarded: "));
			Serial.println(static_cast<int>(currentEvent.type));
		}
	}
}