#include "include/eventqueue.h"

void EventQueue::registerListener(Listener& listener) {
    listeners.enqueue(listener);
}


const bool EventQueue::unregisterListener(Listener& listener) {
    
}


void EventQueue::enqueue(const Event& e) {
	events.updateTail().overwrite(e);
}