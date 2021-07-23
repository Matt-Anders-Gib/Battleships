#ifndef GLOBAL_H
#define GLOBAL_H

#include "Arduino.h" //this is bad


#define BUTTON_DOWN true
#define BUTTON_UP false


enum class GAME_SCREEN {NONE, TITLE_SCREEN, MAIN_MENU};
static GAME_SCREEN currentScreen = GAME_SCREEN::TITLE_SCREEN;


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


struct ButtonEvent {
	Button& button;
	bool pressed;

	ButtonEvent(Button& b, bool p) : button{b}, pressed{p} {}
};

#endif