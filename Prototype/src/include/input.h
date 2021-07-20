#ifndef INPUT_H
#define INPUT_H

#include "Arduino.h"
#include "buttons.h"


class Input {
private:
	Buttons buttons;
	ButtonEvent buttonEvent;
public:
	ButtonEvent getInput();
};

#endif