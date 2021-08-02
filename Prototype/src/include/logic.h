#ifndef LOGIC_H
#define LOGIC_H

#include "Arduino.h" //DELETE ME, YO


#include "global.h"
#include "eventqueue.h"


class Logic {
private:
	GAME_SCREEN lastScreen = GAME_SCREEN::NONE;

	Event currentEvent;
public:
	void update(EventQueue& events);
};

#endif