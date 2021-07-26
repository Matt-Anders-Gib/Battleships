#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "ringbuffer.h"
#include "linkedlist.h"


enum class EVENT_TYPE {BUTTON_DOWN, BUTTON_UP};


struct Event {
	const EVENT_TYPE type;
	const char attribute;

	Event(EVENT_TYPE t, const char a) : type{t}, attribute{a} {}
};


struct Listener {
	EVENT_TYPE eventType;
	void (*reaction)();
};


class EventQueue {
private:
	Gib::RingBuffer<Event> events = Gib::RingBuffer<Event>(16);
	Gib::LinkedList<Listener> listeners = Gib::LinkedList<Listener>();
public:
	void registerListener(Listener& listener);
	const bool unregisterListener(Listener& listener);
};


#endif