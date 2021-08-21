#include "include/logic.h"


//have to pass Logic context in as well
TitleSceneLogic::TitleSceneLogic(Logic* l, void (Logic::*c)(Event& e), EventQueue& e) : GameSceneLogic(e) {
	anyInputListener = LogicListener(l, c, EVENT_TYPE::EVENT_INPUT_DOWN);
	events.registerListener(anyInputListener);
}


Logic::Logic(EventQueue& eventsQueue) : events{eventsQueue} {
	rawButtonListener = LogicListener(this, &Logic::convertRawButtonToInput, EVENT_TYPE::EVENT_RAW_BUTTON_DOWN);
	events.registerListener(rawButtonListener);

	currentScene = new TitleSceneLogic(this, &Logic::titleScreenInput, eventsQueue);
}


void Logic::titleScreenInput(Event& e) {
	events.enqueue(EVENT_TYPE::EVENT_TITLE_SCREEN_INPUT, 0);
}


void Logic::convertRawButtonToInput(Event& e) {
	events.enqueue(EVENT_TYPE::EVENT_INPUT_DOWN, e.attribute);
}


void Logic::processEvents() {
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


void Logic::update() {
	processEvents();
}