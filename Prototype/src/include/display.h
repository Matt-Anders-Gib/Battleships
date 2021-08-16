#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

#include "global.h"
#include "localization.h"
#include "eventqueue.h"


#define	BLACK 0x0000
#define	BLUE 0x001F
#define	RED 0xF800
#define	GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF


class Display;


class GameScene {
private:
protected:
	Adafruit_SSD1331& oled;
	Localization& loc;

	EventQueue& events;

	const static unsigned short DISPLAY_WIDTH = 96;
	const static unsigned short DISPLAY_HEIGHT = 64;

	const static uint8_t TEXT_HORIZONTAL_MARGIN = 9;
	const static uint8_t TEXT_VERTICAL_MARGIN = 5;

	int16_t calcX = 0;
	int16_t calcY = 0;
	uint16_t calcW = 0;
	uint16_t calcH = 0;
public:
	GameScene(Adafruit_SSD1331& o, Localization& l, EventQueue& e) : oled{o}, loc{l}, events{e} {}
	//virtual GameScene() = 0;
	virtual ~GameScene() {};
	virtual void draw(unsigned long long nowMS) = 0;
};


struct TitleScreenListener : public Listener {
	Display *displayObject;
	void (Display::*callback)();

	TitleScreenListener() {
		eventType = EVENT_TYPE::EVENT_NONE;
	}

	TitleScreenListener(Display *d, void (Display::*c)(), EVENT_TYPE e) {
		displayObject = d;
		callback = c;
		eventType = e;
	}

	void operator()() {
		(displayObject->*callback)();
	}
};


class TitleScreen : public GameScene {
private:
	TitleScreenListener startGameListenerA;
	TitleScreenListener startGameListenerB;
	TitleScreenListener startGameListenerS;

	const char* titleFirstString;
	const char* titleLastString;
	const char* startPromptString;

	unsigned char bottomOfTitleY;

	unsigned long long lastStartTextStateChangeMS = 0;
	static const unsigned short START_TEXT_STATE_CHANGE_THRESHOLD_MS = 1337;
	bool startTextVisible = false;
public:
	TitleScreen(Display *d, void (Display::*c)(), Adafruit_SSD1331& o, Localization& l, EventQueue& e);
	void draw(unsigned long long nowMS);
	~TitleScreen();
};


class MainMenu : public GameScene {
private:
	const char* titleString;


public:
	MainMenu(Adafruit_SSD1331& o, Localization& l, EventQueue& e);
	void draw(unsigned long long nowMS);
	~MainMenu();
};


class Display {
private:
	const static unsigned char DISPLAY_PIN_DC = 8;
	const static unsigned char DISPLAY_PIN_RST = 9;
	const static unsigned char DISPLAY_PIN_CS = 10;
	const static unsigned char DISPLAY_PIN_MOSI = 11;
	const static unsigned char DISPLAY_PIN_SCLK = 13;

	Adafruit_SSD1331 oled = Adafruit_SSD1331(DISPLAY_PIN_CS, DISPLAY_PIN_DC, DISPLAY_PIN_MOSI, DISPLAY_PIN_SCLK, DISPLAY_PIN_RST);
	Localization loc;
	EventQueue& events;

	GameScene* currentScene;
	void leaveTitleScreen();
public:
	Display(EventQueue& e);

	void clear();
	void setup();
	void updateDisplay(unsigned long long nowMS);
};

#endif