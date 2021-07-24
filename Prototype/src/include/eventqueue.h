#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "ringbuffer.h"


enum class EVENT_TYPE {BUTTON};


struct Event {
	EVENT_TYPE type;

	Event(EVENT_TYPE t) : type{t} {}
};


class EventQueue {
private:
	Gib::RingBuffer<Event> events = Gib::RingBuffer<ButtonEvent>(16);
public:
};


#endif