#ifndef DISPLAY_H
#define DISPLAY_H

#include "Arduino.h"

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


class GameScene {
private:
protected:
	Adafruit_SSD1331& display;
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
	GameScene(Adafruit_SSD1331& d, Localization& l, EventQueue& e) : display{d}, loc{l}, events{e} {}
	virtual void draw(unsigned long long nowMS) = 0;
};


struct TitleScreenListener : public Listener {
	TitleScreenListener() {
		eventType = EVENT_TYPE::EVENT_NONE;
	}

	TitleScreenListener(EVENT_TYPE e) {
		eventType = e;
	}

	void operator()() {
		Serial.println(F("Called!"));
	}
};


class TitleScreen : public GameScene {
private:
	TitleScreenListener startGameListenerS;

	const char* titleFirstString;
	const char* titleLastString;
	const char* startPromptString;

	unsigned char bottomOfTitleY;

	unsigned long long lastStartTextStateChangeMS = 0;
	static const unsigned short START_TEXT_STATE_CHANGE_THRESHOLD_MS = 1337;
	bool startTextVisible = false;
public:
	TitleScreen(Adafruit_SSD1331& d, Localization& l, EventQueue& e);
	void draw(unsigned long long nowMS);
	~TitleScreen();
};


class Display {
private:
	const static unsigned char DISPLAY_PIN_DC = 8;
	const static unsigned char DISPLAY_PIN_RST = 9;
	const static unsigned char DISPLAY_PIN_CS = 10;
	const static unsigned char DISPLAY_PIN_MOSI = 11;
	const static unsigned char DISPLAY_PIN_SCLK = 13;

	Adafruit_SSD1331 display = Adafruit_SSD1331(DISPLAY_PIN_CS, DISPLAY_PIN_DC, DISPLAY_PIN_MOSI, DISPLAY_PIN_SCLK, DISPLAY_PIN_RST);
	Localization loc;
	EventQueue& events;

	GameScene* currentScene;
public:
	Display(EventQueue& e);

	void clear();
	void setup();
	void updateDisplay(unsigned long long nowMS);
};

#endif