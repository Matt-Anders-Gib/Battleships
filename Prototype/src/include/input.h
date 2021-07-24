#ifndef INPUT_H
#define INPUT_H


#include "Arduino.h"
#include "global.h"


class Input {
private:
	static const unsigned short BUTTONS_COUNT = 3;

	static const unsigned short A_BUTTON_PIN = 4;
	static const unsigned short B_BUTTON_PIN = 3;
	static const unsigned short SELECT_BUTTON_PIN = 2;

	Button buttons[BUTTONS_COUNT] {Button(A_BUTTON_PIN, 'A'), Button(B_BUTTON_PIN, 'B'), Button(SELECT_BUTTON_PIN, 'S')};

	static const unsigned short DEBOUNCE_DELAY_MS = 25;
public:
	void poll(Queue<ButtonEvent>& events, const unsigned long long nowMS);
};

#endif