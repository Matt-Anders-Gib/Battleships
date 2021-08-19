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
		Serial.print(F("There are # pending events, "));
		Serial.println(events.count());

		Event& currentEvent = events.dequeue();
		eventUsed = false;

		Serial.print(F("Event: "));
		Serial.println(static_cast<int>(currentEvent.type));

		Serial.print(F("There are # registered listeners, "));
		Serial.println(events.listenersSize());

		currentListener = events.firstListener();
		while(currentListener != nullptr) {
			Serial.print(F("listener wants "));
			Serial.flush();
			Serial.println(static_cast<int>(currentListener->getData().eventType));

			if(currentEvent.type == currentListener->getData().eventType) {
				Serial.println(F("Event type and Listener match"));
				currentListener->getData()(currentEvent);
				eventUsed = true;
			} else {
				Serial.println(F("Event type and Listener do not match"));
			}

			currentListener = currentListener->getNextNode();
		}

		if(!eventUsed) {
			Serial.print(F("Event discarded: "));
			Serial.println(static_cast<int>(currentEvent.type));
		}
	}
}