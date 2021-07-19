#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

#include "localization.h"


#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF


enum class GAME_SCREEN {NONE, TITLE_SCREEN, MAIN_MENU};


class Display {
private:
	const static unsigned char DISPLAY_PIN_DC = 8;
	const static unsigned char DISPLAY_PIN_RST = 9;
	const static unsigned char DISPLAY_PIN_CS = 10;
	const static unsigned char DISPLAY_PIN_MOSI = 11;
	const static unsigned char DISPLAY_PIN_SCLK = 13;

	Adafruit_SSD1331 display = Adafruit_SSD1331(DISPLAY_PIN_CS, DISPLAY_PIN_DC, DISPLAY_PIN_MOSI, DISPLAY_PIN_SCLK, DISPLAY_PIN_RST);

	const static unsigned short DISPLAY_WIDTH = 96;
	const static unsigned short DISPLAY_HEIGHT = 64;

	int16_t calcX = 0;
	int16_t calcY = 0;
	uint16_t calcW = 0;
	uint16_t calcH = 0;

	const static uint8_t TEXT_HORIZONTAL_MARGIN = 9;
	const static uint8_t TEXT_VERTICAL_MARGIN = 5;

	GAME_SCREEN currentScreen = GAME_SCREEN::TITLE_SCREEN;
	GAME_SCREEN lastScreen = GAME_SCREEN::NONE;

	void titleScreen(unsigned long long nowMS);
	unsigned long long lastStartTextStateChangeMS = 0;
	static const unsigned short START_TEXT_STATE_CHANGE_THRESHOLD_MS = 1337;
	bool startTextVisible = false;

	Localization loc;
public:
	void setup();
	void updateDisplay(unsigned long long nowMS);
};

#endif