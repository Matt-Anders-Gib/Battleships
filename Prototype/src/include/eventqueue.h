#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "ringbuffer.h"
#include "linkedlist.h"


enum class EVENT_TYPE : int {
	EVENT_NONE = 0,
	
	EVENT_A_BUTTON_DOWN = 1,
	EVENT_A_BUTTON_UP = 2,
	EVENT_B_BUTTON_DOWN = 3,
	EVENT_B_BUTTON_UP = 4,
	EVENT_S_BUTTON_DOWN = 5,
	EVENT_S_BUTTON_UP = 6
};


struct Event {
	EVENT_TYPE type = EVENT_TYPE::EVENT_NONE;
	void overwrite(const EVENT_TYPE e) {type = e;}
};


struct Listener {
	unsigned short id;
	EVENT_TYPE eventType;
	virtual void operator()() = 0;

	const bool operator==(const Listener& o) const {return id == o.id;}
};


class EventQueue {
private:
	unsigned short listenerUUID = 0;
	Gib::LinkedList<Listener> listeners = Gib::LinkedList<Listener>();
	Gib::RingBuffer<Event> events = Gib::RingBuffer<Event>();
public:
	void registerListener(Listener& addListener);
	const bool unregisterListener(const Listener& removeListener);
	Gib::LinkedListNode<Listener>* firstListener() {return listeners.getHead();}

	void enqueue(const EVENT_TYPE e);
	Event& dequeue(); //WANRING: always check empty() first

	const bool empty();
};


#endif