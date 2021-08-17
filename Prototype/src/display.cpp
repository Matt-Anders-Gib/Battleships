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
	oled.getTextBounds(startPromptString, (DISPLAY_WIDTH - calcW)/2, bottomOfTitleY + TEXT_VERTICAL_MARGIN, &calcX, &calcY, &calcW, &calcH);

	startGameListenerA = DisplayListener(d, c, EVENT_TYPE::EVENT_A_BUTTON_DOWN);
	startGameListenerB = DisplayListener(d, c, EVENT_TYPE::EVENT_B_BUTTON_DOWN);
	startGameListenerS = DisplayListener(d, c, EVENT_TYPE::EVENT_S_BUTTON_DOWN);
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
			oled.setCursor(calcX, calcY);
			oled.print(startPromptString);
		} else {
			oled.fillRect(calcX, calcY, calcW, calcH, BLACK);
		}
	}
}


TitleScreen::~TitleScreen() {
	events.unregisterListener(startGameListenerA);
	events.unregisterListener(startGameListenerB);
	events.unregisterListener(startGameListenerS);
}


MainMenu::MainMenu(Adafruit_SSD1331& o, Localization& l, EventQueue& e) : GameScene(o, l, e) {
	titleString = loc.getLocalizedString(LOC_TITLE);
	playString = loc.getLocalizedString(LOC_PLAY);
	optionsString = loc.getLocalizedString(LOC_OPTIONS);
	quitString = loc.getLocalizedString(LOC_QUIT);

	oled.getTextBounds(titleString, 0, 0, &calcX, &calcY, &calcW, &calcH);
	oled.drawLine((DISPLAY_WIDTH - calcW)/2, calcY + calcH, DISPLAY_WIDTH - (DISPLAY_WIDTH - calcW)/2, calcY + calcH, RED);
	oled.setCursor((DISPLAY_WIDTH - calcW)/2, TEXT_VERTICAL_MARGIN);
	oled.print(titleString);

	

	unsigned short lineBottom = calcY + calcH;

	oled.getTextBounds(playString, 0, 0, &calcX, &calcY, &calcW, &calcH);
	oled.setCursor((DISPLAY_WIDTH - calcW)/2, lineBottom + TEXT_VERTICAL_MARGIN + calcH);
	oled.print(playString);
	lineBottom = lineBottom + TEXT_VERTICAL_MARGIN + calcH;

	oled.getTextBounds(optionsString, 0, 0, &calcX, &calcY, &calcW, &calcH);
	oled.setCursor((DISPLAY_WIDTH - calcW)/2, lineBottom + TEXT_VERTICAL_MARGIN + calcH);
	oled.print(optionsString);
	lineBottom = lineBottom + TEXT_VERTICAL_MARGIN + calcH;

	oled.getTextBounds(quitString, 0, 0, &calcX, &calcY, &calcW, &calcH);
	oled.setCursor((DISPLAY_WIDTH - calcW)/2, lineBottom + TEXT_VERTICAL_MARGIN + calcH);
	oled.print(quitString);
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