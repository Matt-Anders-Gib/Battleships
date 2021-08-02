#include "include/eventqueue.h"


unsigned short EventQueue::registerListener(Listener& l) {
	listeners.enqueue(l);
	return listenerUUID++;
}


const bool EventQueue::unregisterListener(const unsigned short id) {
	
}


void EventQueue::enqueue(const EVENT_TYPE e) {
	events.updateTail().overwrite(e);
}


const bool EventQueue::empty() {
	return events.empty();
}


const Event& EventQueue::dequeue() { //WANRING: always check empty() first
	return events.getHead();
}