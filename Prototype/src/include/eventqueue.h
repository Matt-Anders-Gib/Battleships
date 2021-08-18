#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "ringbuffer.h"
#include "linkedlist.h"


enum class EVENT_TYPE : int {
	EVENT_NONE = 0,

	EVENT_RAW_INPUT_UP = 1,
	EVENT_RAW_INPUT_DOWN = 2,

	EVENT_MENU_SELECTION_CHANGED = 3

	/*EVENT_BUTTON_A_UP = 3,
	EVENT_BUTTON_A_DOWN = 4,
	EVENT_BUTTON_B_UP = 5,
	EVENT_BUTTON_B_DOWN = 6,
	EVENT_BUTTON_S_UP = 7,
	EVENT_BUTTON_S_DOWN = 8*/
};


struct Event {
	EVENT_TYPE type = EVENT_TYPE::EVENT_NONE;
	unsigned char attribute = 0;
	void overwrite(const EVENT_TYPE e, const unsigned char a) {type = e; attribute = a;}
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

	void enqueue(const EVENT_TYPE e, const unsigned char a);
	Event& dequeue(); //WANRING: always check empty() first

	const bool empty();
};


#endif