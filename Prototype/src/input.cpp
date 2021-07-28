#include "include/input.h"


void Input::poll(EventQueue& events, const unsigned long long nowMS) {
	for(Button& b : buttons) {
		if(b.getLastStateChangeTimeMS() + DEBOUNCE_DELAY_MS < nowMS) {
			if(digitalRead(b.getPin()) == LOW) {
				if(b.getState() == BUTTON_UP) {
					continue;
				} else {
					//events.enqueue(new ButtonEvent(b, BUTTON_UP));
					events.enqueue(Event(EVENT_TYPE::EVENT_BUTTON_UP, b.getName()));
					b.up();
				}
			} else {
				if(b.getState() == BUTTON_UP) {
					events.enqueue(Event(EVENT_TYPE::EVENT_BUTTON_DOWN, b.getName()));
					//events.enqueue(new ButtonEvent(b, BUTTON_DOWN));
					b.down(nowMS);
				}
			}
		}
	}
}