#ifndef INPUT_H
#define INPUT_H

#include "Arduino.h"


class Input {
private:
	Buttons buttons;
public:
	void getInput();
};

#endif