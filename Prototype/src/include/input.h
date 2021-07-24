#ifndef INPUT_H
#define INPUT_H


#include "Arduino.h"


#define BUTTON_DOWN true
#define BUTTON_UP false


class Button {
private:
	const unsigned short BUTTON_PIN;
	const char name;
	bool state = false;

	unsigned long long lastStateChangeTimeMS = 0;
public:
	Button(const unsigned short p, const char n) : BUTTON_PIN{p}, name{n} {
		pinMode(p, INPUT);
	}

	const unsigned short getPin() {return BUTTON_PIN;}
	const char getName() {return name;}
	const bool getState() {return state;}

	void up() {state = false;}
	void down(unsigned long long nowMS) {
		state = true;
		lastStateChangeTimeMS = nowMS;
	}

	const unsigned long long getLastStateChangeTimeMS() {return lastStateChangeTimeMS;}
};


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