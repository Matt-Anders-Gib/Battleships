#include "include/eventqueue.h"


void EventQueue::registerListener(Listener& l) {
	l.id = listenerUUID++;
	listeners.enqueue(l);
}


const bool EventQueue::unregisterListener(const unsigned short id) {
	Listener *l = firstListener();
	Listener *parent = 

	while(l) {
		if(l == id) {
			//remove from linked list
			return true;
		}
	}

	return false;
}


void EventQueue::enqueue(const EVENT_TYPE e) {
	events.updateTail().overwrite(e);
}


const bool EventQueue::empty() {
	return events.empty();
}


Event& EventQueue::dequeue() { //WANRING: always check empty() first
	return events.getHead();
}