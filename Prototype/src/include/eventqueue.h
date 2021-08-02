#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "ringbuffer.h"
#include "linkedlist.h"


enum class EVENT_TYPE {EVENT_NONE, EVENT_A_BUTTON_DOWN, EVENT_A_BUTTON_UP, EVENT_B_BUTTON_DOWN, EVENT_B_BUTTON_UP, EVENT_S_BUTTON_DOWN, EVENT_S_BUTTON_UP};


struct Event {
	EVENT_TYPE type = EVENT_TYPE::EVENT_NONE;
	void overwrite(const EVENT_TYPE e) {type = e;}
};


struct Listener {
	EVENT_TYPE eventType;
	void (*reaction)();
};


class EventQueue {
private:
	unsigned short listenerUUID = 0;
	Gib::LinkedList<Listener> listeners = Gib::LinkedList<Listener>();
	Gib::RingBuffer<Event> events = Gib::RingBuffer<Event>();
public:
	unsigned short registerListener(Listener& l);
	const bool unregisterListener(const unsigned short id);

	void enqueue(const EVENT_TYPE e);
	const Event& dequeue(); //WANRING: always check empty() first

	const bool empty();
};


#endif