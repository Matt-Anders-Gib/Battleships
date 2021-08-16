#include "include/eventqueue.h"


void EventQueue::registerListener(Listener& l) {
	l.id = listenerUUID++;
	listeners.enqueue(l);
}


const bool EventQueue::unregisterListener(const Listener& oldListener) {
	return listeners.remove(oldListener);
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