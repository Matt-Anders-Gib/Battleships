#ifndef LOGIC_H
#define LOGIC_H

#include "Arduino.h" //DELETE ME, YO

#include "eventqueue.h"


class Logic;
struct LogicListener : public Listener {
	Logic *activeObject;
	void (Logic::*callback)(Event& e);

	LogicListener() {
		eventType = EVENT_TYPE::EVENT_NONE;
	}

	LogicListener(Logic* a, void (Logic::*c)(Event& e), EVENT_TYPE e) {
		activeObject = a;
		callback = c;
		eventType = e;
	}

	void operator()(Event& e) {
		(activeObject->*callback)(e);
	}
};


class GameSceneLogic {
protected:
	EventQueue& events;
public:
	GameSceneLogic(EventQueue& e) : events{e} {}
};


class TitleSceneLogic : public GameSceneLogic {
private:
	LogicListener anyInputListener;
public:
	TitleSceneLogic(Logic* l, void (Logic::*c)(Event& e), EventQueue& e);
};


class Logic {
private:
	EventQueue& events;
	bool eventUsed = false;

	Gib::LinkedListNode<Listener>* currentListener;

	GameSceneLogic* currentScene;

	LogicListener rawButtonListener;
	void convertRawButtonToInput(Event& e);

	void processEvents();

	void titleScreenInput(Event& e);
public:
	Logic(EventQueue& eventsQueue);

	void update();
};

#endif