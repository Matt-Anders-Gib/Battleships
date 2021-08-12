#include "include/display.h"


TitleScreen::TitleScreen(Display *d, void (Display::*c)(), Adafruit_SSD1331& o, Localization& l, EventQueue& e) : GameScene(o, l, e) {
	titleFirstString = loc.getLocalizedString(LOC_TITLE_FIRST);
	titleLastString = loc.getLocalizedString(LOC_TITLE_LAST);
	startPromptString = loc.getLocalizedString(LOC_START_PROMPT);
	
	oled.setTextSize(2);
	oled.setTextColor(RED);
	oled.setCursor(0, 0);
	oled.print(titleFirstString);

	oled.getTextBounds(titleFirstString, 0, 0, &calcX, &calcY, &calcW, &calcH);
	unsigned short titleFirstHeight = calcH;

	oled.getTextBounds(titleLastString, 0, 0, &calcX, &calcY, &calcW, &calcH);
	unsigned short titleLastWidth = calcW;
	bottomOfTitleY = titleFirstHeight + TEXT_VERTICAL_MARGIN + calcH;
	oled.setCursor(DISPLAY_WIDTH - titleLastWidth, titleFirstHeight + TEXT_VERTICAL_MARGIN);
	oled.print(titleLastString);

	oled.setTextSize(1);
	oled.getTextBounds(startPromptString, 0, 0, &calcX, &calcY, &calcW, &calcH);

	startGameListenerA = TitleScreenListener(d, c, EVENT_TYPE::EVENT_A_BUTTON_DOWN);
	startGameListenerB = TitleScreenListener(d, c, EVENT_TYPE::EVENT_B_BUTTON_DOWN);
	startGameListenerS = TitleScreenListener(d, c, EVENT_TYPE::EVENT_S_BUTTON_DOWN);
	e.registerListener(startGameListenerA);
	e.registerListener(startGameListenerB);
	e.registerListener(startGameListenerS);
}


void TitleScreen::draw(unsigned long long nowMS) {
	if(lastStartTextStateChangeMS + START_TEXT_STATE_CHANGE_THRESHOLD_MS < nowMS) {
		startTextVisible = !startTextVisible;
		lastStartTextStateChangeMS = nowMS;

		if(startTextVisible) {
			oled.setTextColor(WHITE);
			oled.setCursor((DISPLAY_WIDTH - calcW)/2, bottomOfTitleY + TEXT_VERTICAL_MARGIN); //store this calculation
			oled.print(startPromptString);
		} else {
			oled.fillRect((DISPLAY_WIDTH - calcW)/2, bottomOfTitleY + TEXT_VERTICAL_MARGIN, calcW, calcH, BLACK); //store this calculation
		}
	}
}


TitleScreen::~TitleScreen() {
	//DELETE CHAR ARRAYS IF THEY ARE DYNAMIC
	//unregister listener
}


MainMenu::MainMenu(Adafruit_SSD1331& o, Localization& l, EventQueue& e) : GameScene(o, l, e) {
	titleString = loc.getLocalizedString(LOC_TITLE);

	oled.getTextBounds(titleString, 0, 0, &calcX, &calcY, &calcW, &calcH);
	oled.setCursor((DISPLAY_WIDTH - calcW)/2, TEXT_VERTICAL_MARGIN);
	oled.print(titleString);
}


void MainMenu::draw(unsigned long long nowMS) {

}


MainMenu::~MainMenu() {

}


void Display::leaveTitleScreen() {
	clear();

	delete currentScene;
	currentScene = new MainMenu(oled, loc, events);
}


void Display::clear() {
	oled.fillScreen(BLACK);
	oled.setTextSize(1);
	oled.setTextColor(WHITE);
}


void Display::setup() {
	oled.begin();
	clear();
	currentScene = new TitleScreen(this, &Display::leaveTitleScreen, oled, loc, events);
}


void Display::updateDisplay(unsigned long long nowMS) {
	currentScene->draw(nowMS);
}


Display::Display(EventQueue& e) : events{e} {

}