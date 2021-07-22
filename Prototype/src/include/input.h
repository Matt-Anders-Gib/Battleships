#ifndef INPUT_H
#define INPUT_H


#include "Arduino.h"
#include "queue.h"

#define BUTTON_DOWN true
#define BUTTON_UP false


class Button {
private:
	const unsigned short BUTTON_PIN;
	const char name;
	bool state = false;
public:
	Button(const unsigned short p, const char n) : BUTTON_PIN{p}, name{n} {
		pinMode(p, INPUT);
	}

	const unsigned short getPin() {return BUTTON_PIN;}
	const char getName() {return name;}
	const bool getState() {return state;}

	void down() {state = true;}
	void up() {state = false;}
};


struct ButtonEvent {
	Button* button;
	bool pressed;

	ButtonEvent() {
		button = nullptr;
		pressed = false;
	}

	ButtonEvent(Button* b, bool p) {
		button = b;
		pressed = p;
	}

	bool operator==(const ButtonEvent& o) {
		return (button == o.button && pressed == o.pressed);
	}

	bool operator!=(const ButtonEvent& o) {
		return !(*this == o);
	}
};


class Input {
private:
	static const unsigned short BUTTONS_COUNT = 3;

	static const unsigned short A_BUTTON_PIN = 4;
	static const unsigned short B_BUTTON_PIN = 3;
	static const unsigned short SELECT_BUTTON_PIN = 2;

	Button buttons[BUTTONS_COUNT] {Button(A_BUTTON_PIN, 'A'), Button(B_BUTTON_PIN, 'B'), Button(SELECT_BUTTON_PIN, 'S')};
public:
	Input();

	void poll(Queue<ButtonEvent>& events);
};

#endif