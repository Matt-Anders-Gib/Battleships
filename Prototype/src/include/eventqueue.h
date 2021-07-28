#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "ringbuffer.h"
#include "linkedlist.h"


enum class EVENT_TYPE {EVENT_BUTTON_DOWN, EVENT_BUTTON_UP};


struct Event {
	EVENT_TYPE type;
	char attribute;

	Event(const EVENT_TYPE t, const char a) : type{t}, attribute{a} {}
	void overwrite(const EVENT_TYPE t, const char a) {
		type = t;
		attribute = a;
	}
	void overwrite(const Event& e) {
		type = e.type;
		attribute = e.attribute;
	}
};


struct Listener {
	EVENT_TYPE eventType;
	void (*reaction)();
};


class EventQueue {
private:
	Gib::LinkedList<Listener> listeners = Gib::LinkedList<Listener>();
	Gib::RingBuffer<Event> events = Gib::RingBuffer<Event>();
public:
	void registerListener(Listener& listener);
	const bool unregisterListener(Listener& listener);

	void enqueue(const Event& e);
};


#endif