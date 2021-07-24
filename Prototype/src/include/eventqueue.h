#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "ringbuffer.h"


enum class EVENT_TYPE {BUTTON_DOWN, BUTTON_UP};


struct Event {
	const EVENT_TYPE type;
	const char attribute;

	Event(EVENT_TYPE t, const char a) : type{t}, attribute{a} {}
};


struct Listener {
	EVENT_TYPE focus;

};


class EventQueue {
private:
	Gib::RingBuffer<Event> events = Gib::RingBuffer<ButtonEvent>(16);
	Gib::RingBuffer<Listener> listeners = Gib::RingBuffer<Listener>(8);
public:
	void registerListener(Listener& listener);
	const bool unregisterListener(Listener& listener);
};


#endif