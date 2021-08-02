#include "include/input.h"


void Input::poll(EventQueue& events, const unsigned long long nowMS) {
	for(Button& b : buttons) {
		if(b.getLastStateChangeTimeMS() + DEBOUNCE_DELAY_MS < nowMS) {
			if(digitalRead(b.getPin()) == LOW) {
				if(b.getState() == BUTTON_UP) {
					continue;
				} else {
					switch(b.getName()) {
					case 'A':
						events.enqueue(EVENT_TYPE::EVENT_A_BUTTON_UP);
					break;

					case 'B':
						events.enqueue(EVENT_TYPE::EVENT_B_BUTTON_UP);
					break;

					case 'S':
						events.enqueue(EVENT_TYPE::EVENT_S_BUTTON_UP);
					break;

					default:
						//log error: unknown button
					break;
					}

					b.up();
				}
			} else {
				if(b.getState() == BUTTON_UP) {
					switch(b.getName()) {
					case 'A':
						events.enqueue(EVENT_TYPE::EVENT_A_BUTTON_DOWN);
					break;

					case 'B':
						events.enqueue(EVENT_TYPE::EVENT_B_BUTTON_DOWN);
					break;

					case 'S':
						events.enqueue(EVENT_TYPE::EVENT_S_BUTTON_DOWN);
					break;

					default:
						//log error: unknown button
					break;
					}

					b.down(nowMS);
				}
			}
		}
	}
}