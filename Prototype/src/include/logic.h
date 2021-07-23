#ifndef LOGIC_H
#define LOGIC_H

#include "global.h"
#include "queue.h"


class Logic {
private:
	GAME_SCREEN lastScreen = GAME_SCREEN::NONE;
	ButtonEvent* currentEvent = nullptr;
public:
	void update(Queue<ButtonEvent>& events);
};

#endif