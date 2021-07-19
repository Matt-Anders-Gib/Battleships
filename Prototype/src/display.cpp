#include "include/display.h"


void Display::titleScreen(unsigned long long nowMS) {
	if(lastStartTextStateChangeMS + START_TEXT_STATE_CHANGE_THRESHOLD_MS < nowMS) {
		startTextVisible = !startTextVisible;
		lastStartTextStateChangeMS = nowMS;

		const char* titleFirstString = loc.getLocalizedString(LOC_TITLE_FIRST);
		const char* titleLastString = loc.getLocalizedString(LOC_TITLE_LAST);
		const char* startPromptString = loc.getLocalizedString(LOC_START_PROMPT);

		display.setTextSize(2);
		display.setTextColor(RED);
		display.setCursor(0, 0);
		display.print(titleFirstString);

		display.getTextBounds(titleFirstString, 0, 0, &calcX, &calcY, &calcW, &calcH); //cache this!
		unsigned short titleFirstHeight = calcH;

		display.getTextBounds(titleLastString, 0, 0, &calcX, &calcY, &calcW, &calcH); //cache this!
		unsigned short titleLastWidth = calcW;
		unsigned short titleLastLowestPoint = titleFirstHeight + TEXT_VERTICAL_MARGIN + calcH;
		display.setCursor(DISPLAY_WIDTH - titleLastWidth, titleFirstHeight + TEXT_VERTICAL_MARGIN);
		display.print(titleLastString);

		display.setTextSize(1);
		display.getTextBounds(startPromptString, 0, 0, &calcX, &calcY, &calcW, &calcH); //cache this!

		if(startTextVisible) {
			display.setTextColor(WHITE);
			display.setCursor((DISPLAY_WIDTH - calcW)/2, titleLastLowestPoint + TEXT_VERTICAL_MARGIN);
			display.print(startPromptString);
		} else {
			display.fillRect((DISPLAY_WIDTH - calcW)/2, titleLastLowestPoint + TEXT_VERTICAL_MARGIN, calcW, calcH, BLACK);
		}
	}
}


void Display::setup() {
	display.begin();
}

void Display::updateDisplay(unsigned long long nowMS) {
	if(lastScreen != currentScreen) {
		display.fillScreen(BLACK);
		lastScreen = currentScreen;
	}

	switch(currentScreen) {
		case GAME_SCREEN::TITLE_SCREEN:
			titleScreen(nowMS);
		break;

		case GAME_SCREEN::MAIN_MENU:
		break;

		default:
		break;
	}
	// function pointer (menus, game screen, etc)

	// redraw game

	// check for changes, update menu/whatever
}