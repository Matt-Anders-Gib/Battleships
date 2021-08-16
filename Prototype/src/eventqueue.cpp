#include "include/eventqueue.h"


void EventQueue::registerListener(Listener& addListener) {
	addListener.id = listenerUUID++;

	Serial.print(F("registering listener UUID: "));
	Serial.println(addListener.id);

	listeners.enqueue(addListener);

	Serial.print(F("finished registering listener UUID: "));
	Serial.println(addListener.id);
}


const bool EventQueue::unregisterListener(const Listener& removeListener) {
	Serial.print(F("Attempting to unregister listener UUID: "));
	Serial.println(removeListener.id);

	Serial.print(F("success?: "));
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