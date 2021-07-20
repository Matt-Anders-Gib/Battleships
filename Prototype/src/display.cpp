#include "include/display.h"


GameScene::GameScene(Adafruit_SSD1331& d, Localization& l) : display{d}, loc{l} {

}


TitleScreen::TitleScreen(Adafruit_SSD1331& d, Localization& l) : GameScene(d, l) {
	titleFirstString = loc.getLocalizedString(LOC_TITLE_FIRST);
	titleLastString = loc.getLocalizedString(LOC_TITLE_LAST);
	startPromptString = loc.getLocalizedString(LOC_START_PROMPT);
	
	display.setTextSize(2);
	display.setTextColor(RED);
	display.setCursor(0, 0);
	display.print(titleFirstString);

	display.getTextBounds(titleFirstString, 0, 0, &calcX, &calcY, &calcW, &calcH);
	unsigned short titleFirstHeight = calcH;

	display.getTextBounds(titleLastString, 0, 0, &calcX, &calcY, &calcW, &calcH);
	unsigned short titleLastWidth = calcW;
	bottomOfTitleY = titleFirstHeight + TEXT_VERTICAL_MARGIN + calcH;
	display.setCursor(DISPLAY_WIDTH - titleLastWidth, titleFirstHeight + TEXT_VERTICAL_MARGIN);
	display.print(titleLastString);

	display.setTextSize(1);
	display.getTextBounds(startPromptString, 0, 0, &calcX, &calcY, &calcW, &calcH);
}


void TitleScreen::draw(unsigned long long nowMS) {
	if(lastStartTextStateChangeMS + START_TEXT_STATE_CHANGE_THRESHOLD_MS < nowMS) {
		startTextVisible = !startTextVisible;
		lastStartTextStateChangeMS = nowMS;

		if(startTextVisible) {
			display.setTextColor(WHITE);
			display.setCursor((DISPLAY_WIDTH - calcW)/2, bottomOfTitleY + TEXT_VERTICAL_MARGIN); //store this calculation
			display.print(startPromptString);
		} else {
			display.fillRect((DISPLAY_WIDTH - calcW)/2, bottomOfTitleY + TEXT_VERTICAL_MARGIN, calcW, calcH, BLACK); //store this calculation
		}
	}
}


TitleScreen::~TitleScreen() {
	//DELETE CHAR ARRAYS IF THEY ARE DYNAMIC
}


void Display::clear() {
	display.fillScreen(BLACK);
}


void Display::setup() {
	display.begin();
	currentScene = new TitleScreen(display, loc);
}


void Display::updateDisplay(unsigned long long nowMS) {
	currentScene->draw(nowMS);
}