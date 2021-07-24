#include "include/eventqueue.h"

void EventQueue::registerListener(Listener& listener) {
    listeners.push(&listener);
}


const bool EventQueue::unregisterListener(Listener& listener) {
    
}