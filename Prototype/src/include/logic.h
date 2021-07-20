#ifndef LOGIC_H
#define LOGIC_H

#include "global.h"


class Logic {
private:
	GAME_SCREEN lastScreen = GAME_SCREEN::NONE;
public:
	void update();
};

#endif