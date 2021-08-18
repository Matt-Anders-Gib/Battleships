#ifndef LOGIC_H
#define LOGIC_H

#include "Arduino.h" //DELETE ME, YO


#include "global.h"
#include "eventqueue.h"


class Logic;

struct LogicListener : public Listener {
	Logic *activeObject;
	void (Logic::*callback)(Event& e);

	LogicListener() {
		eventType = EVENT_TYPE::EVENT_NONE;
	}

	LogicListener(Logic *a, void (Logic::*c)(Event& e), EVENT_TYPE e) {
		activeObject = a;
		callback = c;
		eventType = e;
	}

	void operator()(Event& e) {
		(activeObject->*callback)(e);
	}
};


class Logic {
private:
	GAME_SCREEN lastScreen = GAME_SCREEN::NONE;

	EventQueue& events;

	Event eventNone = Event();
	Event& currentEvent = eventNone;
	bool eventUsed = false;

	Gib::LinkedListNode<Listener>* currentListener;

	LogicListener rawButtonListener;
	void convertRawButtonToInput(Event& e);
public:
	Logic(EventQueue& eventsQueue);

	void update();
};

#endif