#include "include/eventqueue.h"


void EventQueue::registerListener(Listener& addListener) {
	addListener.id = listenerUUID++;
	listeners.enqueue(addListener);
}


const bool EventQueue::unregisterListener(const Listener& removeListener) {
	return listeners.remove(removeListener);
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