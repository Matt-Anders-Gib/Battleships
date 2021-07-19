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


class Display {
private:
	const static unsigned char DISPLAY_PIN_DC = 8;
	const static unsigned char DISPLAY_PIN_RST = 9;
	const static unsigned char DISPLAY_PIN_CS = 10;
	const static unsigned char DISPLAY_PIN_MOSI = 11;
	const static unsigned char DISPLAY_PIN_SCLK = 13;

	Adafruit_SSD1331 display = Adafruit_SSD1331(DISPLAY_PIN_CS, DISPLAY_PIN_DC, DISPLAY_PIN_MOSI, DISPLAY_PIN_SCLK, DISPLAY_PIN_RST);

	void testlines(uint16_t color);
	void testdrawtext(char *text, uint16_t color);
	void testfastlines(uint16_t color1, uint16_t color2);
	void testdrawrects(uint16_t color);
	void testfillrects(uint16_t color1, uint16_t color2);
	void testfillcircles(uint8_t radius, uint16_t color);
	void testdrawcircles(uint8_t radius, uint16_t color);
	void testtriangles();
	void testroundrects();
	void tftPrintTest();
	void mediabuttons();
	void lcdTestPattern();

	const static unsigned short DISPLAY_WIDTH = 96;
	const static unsigned short DISPLAY_HEIGHT = 64;

	int16_t calcX = 0;
	int16_t calcY = 0;
	uint16_t calcW = 0;
	uint16_t calcH = 0;

	const static uint8_t TEXT_HORIZONTAL_MARGIN = 9;
	const static uint8_t TEXT_VERTICAL_MARGIN = 5;
public:
	void setup();
	void updateDisplay();
};

#endif