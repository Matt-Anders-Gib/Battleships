#include "include/eventqueue.h"

void EventQueue::registerListener(Listener& listener) {
    listeners.enqueue(listener);
}


const bool EventQueue::unregisterListener(Listener& listener) {
    
}


void EventQueue::enqueue(Event* e) {
	events.push(e);
}