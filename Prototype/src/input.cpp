#include "include/input.h"


void Input::poll(Queue<ButtonEvent>& events) {
	for(Button& b : buttons) {
		if(digitalRead(b.getPin()) == LOW) {
			if(b.getState() == BUTTON_UP) {
				
			} else {
				events.enqueue(new ButtonEvent(&b, BUTTON_UP));
				b.up();
			}
		} else {
			if(b.getState() == BUTTON_UP) {
				events.enqueue(new ButtonEvent(&b, BUTTON_DOWN));
				b.down();
			}
		}
	}
}


Input::Input() {

}