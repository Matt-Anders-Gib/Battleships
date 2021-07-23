#include "include/input.h"


void Input::poll(Queue<ButtonEvent>& events, const unsigned long long nowMS) {
	for(Button& b : buttons) {
		if(b.getLastStateChangeTimeMS() + DEBOUNCE_DELAY_MS < nowMS) {
			if(digitalRead(b.getPin()) == LOW) {
				if(b.getState() == BUTTON_UP) {
					continue;
				} else {
					events.enqueue(new ButtonEvent(b, BUTTON_UP));
					b.up();
				}
			} else {
				if(b.getState() == BUTTON_UP) {
					events.enqueue(new ButtonEvent(b, BUTTON_DOWN));
					b.down(nowMS);
				}
			}
		}
	}
}