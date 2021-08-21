#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

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


namespace Gib {
	struct Rect {
		int16_t x;
		int16_t y;
		uint16_t w;
		uint16_t h;

		Rect() : x{0}, y{0}, w{0}, h{0} {}
		Rect(int16_t vX, int16_t vY, uint16_t vW, uint16_t vH) : x{vX}, y{vY}, w{vW}, h{vH} {}
	};
}


class GameSceneDisplay {
private:
protected:
	Adafruit_SSD1331& oled;
	Localization& loc;

	EventQueue& events;

	const static unsigned short DISPLAY_WIDTH = 96;
	const static unsigned short DISPLAY_HEIGHT = 64;

	const static uint8_t TEXT_HORIZONTAL_MARGIN = 9;
	const static uint8_t TEXT_VERTICAL_MARGIN = 5;

	Gib::Rect calc;
public:
	GameSceneDisplay(Adafruit_SSD1331& o, Localization& l, EventQueue& e) : oled{o}, loc{l}, events{e} {} //make pure virtual?
	//virtual GameScene() = 0;
	virtual ~GameSceneDisplay() {}
	virtual void draw(unsigned long long nowMS) = 0;
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

	GameSceneDisplay* currentScene;

	void leaveTitleScreen(Event& e);

	void mainMenuChangeSelectedButton(Event& e);
	void mainMenuButtonSelected(Event& e);
public:
	Display(EventQueue& e);

	void clear();
	void setup();
	void updateDisplay(unsigned long long nowMS);
};


struct DisplayListener : public Listener {
	Display *activeObject;
	void (Display::*callback)(Event& e);

	DisplayListener() {
		eventType = EVENT_TYPE::EVENT_NONE;
	}

	DisplayListener(Display* a, void (Display::*c)(Event& e), EVENT_TYPE e) {
		activeObject = a;
		callback = c;
		eventType = e;
	}

	void operator()(Event& e) {
		(activeObject->*callback)(e);
	}
};


class TitleScreenDisplay : public GameSceneDisplay {
private:
	DisplayListener startGameListener;

	const char* titleFirstString;
	const char* titleLastString;
	const char* startPromptString;

	unsigned char bottomOfTitleY;

	unsigned long long lastStartTextStateChangeMS = 0;
	static const unsigned short START_TEXT_STATE_CHANGE_THRESHOLD_MS = 1337;
	bool startTextVisible = false;
public:
	TitleScreenDisplay(Display* d, void (Display::*c)(Event& e), Adafruit_SSD1331& o, Localization& l, EventQueue& e);
	void draw(unsigned long long nowMS);
	~TitleScreenDisplay();
};


class MainMenuDisplay : public GameSceneDisplay {
private:
	DisplayListener selectionChangeListener;
	DisplayListener selectedMenuListener;

	const char* titleString;
	const char* playString;
	const char* optionsString;
	const char* quitString;

	Gib::Rect playButtonRect;
	Gib::Rect optionsButtonRect;
	Gib::Rect quitButtonRect;

	unsigned char selectedMenu = 'B';
	unsigned char lastSelectedMenu = 0;
public:
	MainMenuDisplay(Display* d, void (Display::*c1)(Event& e), void (Display::*c2)(Event& e), Adafruit_SSD1331& o, Localization& l, EventQueue& e);
	void draw(unsigned long long nowMS);
	~MainMenuDisplay();
};

#endif