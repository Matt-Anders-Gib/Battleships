#include "include/display.h"


void Display::testlines(uint16_t color) {
	display.fillScreen(BLACK);
	for (int16_t x = 0; x < display.width() - 1; x += 6) {
		display.drawLine(0, 0, x, display.height() - 1, color);
	}
	for (int16_t y = 0; y < display.height() - 1; y += 6) {
		display.drawLine(0, 0, display.width() - 1, y, color);
	}

	display.fillScreen(BLACK);
	for (int16_t x = 0; x < display.width() - 1; x += 6) {
		display.drawLine(display.width() - 1, 0, x, display.height() - 1,
						 color);
	}
	for (int16_t y = 0; y < display.height() - 1; y += 6) {
		display.drawLine(display.width() - 1, 0, 0, y, color);
	}

	// To avoid ESP8266 watchdog timer resets when not using the hardware SPI
	// pins
	delay(0);

	display.fillScreen(BLACK);
	for (int16_t x = 0; x < display.width() - 1; x += 6) {
		display.drawLine(0, display.height() - 1, x, 0, color);
	}
	for (int16_t y = 0; y < display.height() - 1; y += 6) {
		display.drawLine(0, display.height() - 1, display.width() - 1, y,
						 color);
	}

	display.fillScreen(BLACK);
	for (int16_t x = 0; x < display.width() - 1; x += 6) {
		display.drawLine(display.width() - 1, display.height() - 1, x, 0,
						 color);
	}
	for (int16_t y = 0; y < display.height() - 1; y += 6) {
		display.drawLine(display.width() - 1, display.height() - 1, 0, y,
						 color);
	}
}


void Display::testdrawtext(char *text, uint16_t color) {
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0, 0);

	for (uint8_t i = 0; i < 168; i++) {
		if (i == '\n') continue;
		display.write(i);
		if ((i > 0) && (i % 21 == 0)) display.println();
	}
}


void Display::testfastlines(uint16_t color1, uint16_t color2) {
	display.fillScreen(BLACK);
	for (int16_t y = 0; y < display.height() - 1; y += 5) {
		display.drawFastHLine(0, y, display.width() - 1, color1);
	}
	for (int16_t x = 0; x < display.width() - 1; x += 5) {
		display.drawFastVLine(x, 0, display.height() - 1, color2);
	}
}


void Display::testdrawrects(uint16_t color) {
	display.fillScreen(BLACK);
	for (int16_t x = 0; x < display.height() - 1; x += 6) {
		display.drawRect((display.width() - 1) / 2 - x / 2,
						 (display.height() - 1) / 2 - x / 2, x, x, color);
	}
}


void Display::testfillrects(uint16_t color1, uint16_t color2) {
	display.fillScreen(BLACK);
	for (int16_t x = display.height() - 1; x > 6; x -= 6) {
		display.fillRect((display.width() - 1) / 2 - x / 2,
						 (display.height() - 1) / 2 - x / 2, x, x, color1);
		display.drawRect((display.width() - 1) / 2 - x / 2,
						 (display.height() - 1) / 2 - x / 2, x, x, color2);
	}
}


void Display::testfillcircles(uint8_t radius, uint16_t color) {
	for (uint8_t x = radius; x < display.width() - 1; x += radius * 2) {
		for (uint8_t y = radius; y < display.height() - 1; y += radius * 2) {
			display.fillCircle(x, y, radius, color);
		}
	}
}


void Display::testdrawcircles(uint8_t radius, uint16_t color) {
	for (int16_t x = 0; x < display.width() - 1 + radius; x += radius * 2) {
		for (int16_t y = 0; y < display.height() - 1 + radius;
			 y += radius * 2) {
			display.drawCircle(x, y, radius, color);
		}
	}
}


void Display::testtriangles() {
	display.fillScreen(BLACK);
	int color = 0xF800;
	int t;
	int w = display.width() / 2;
	int x = display.height();
	int y = 0;
	int z = display.width();
	for (t = 0; t <= 15; t += 1) {
		display.drawTriangle(w, y, y, x, z, x, color);
		x -= 4;
		y += 4;
		z -= 4;
		color += 100;
	}
}


void Display::testroundrects() {
	display.fillScreen(BLACK);
	int color = 100;
	int i;
	int t;
	for (t = 0; t <= 4; t += 1) {
		int x = 0;
		int y = 0;
		int w = display.width();
		int h = display.height();
		for (i = 0; i <= 8; i += 1) {
			display.drawRoundRect(x, y, w, h, 5, color);
			x += 2;
			y += 3;
			w -= 4;
			h -= 6;
			color += 1100;
		}
		color += 100;
	}
}


void Display::tftPrintTest() {
	display.fillScreen(BLACK);
	display.setCursor(0, 5);
	display.setTextColor(RED);
	display.setTextSize(1);
	display.println("Hello World!");
	display.setTextColor(YELLOW, GREEN);
	display.setTextSize(2);
	display.print("Hello Wo");
	display.setTextColor(BLUE);
	display.setTextSize(3);
	display.print(1234.567);
	delay(1500);
	display.setCursor(0, 5);
	display.fillScreen(BLACK);
	display.setTextColor(WHITE);
	display.setTextSize(0);
	display.println("Hello World!");
	display.setTextSize(1);
	display.setTextColor(GREEN);
	float p = 3.1415926;
	display.print(p, 5);
	display.println(" Want pi?");
	display.print(8675309, HEX);  // print 8,675,309 out in HEX!
	display.print(" Print HEX");
	display.setTextColor(WHITE);
	display.println("Sketch has been");
	display.println("running for: ");
	display.setTextColor(MAGENTA);
	display.print(millis() / 1000);
	display.setTextColor(WHITE);
	display.print(" seconds.");
}


void Display::mediabuttons() {
	// play
	display.fillScreen(BLACK);
	display.fillRoundRect(25, 10, 78, 60, 8, WHITE);
	display.fillTriangle(42, 20, 42, 60, 90, 40, RED);
	delay(500);
	// pause
	display.fillRoundRect(25, 90, 78, 60, 8, WHITE);
	display.fillRoundRect(39, 98, 20, 45, 5, GREEN);
	display.fillRoundRect(69, 98, 20, 45, 5, GREEN);
	delay(500);
	// play color
	display.fillTriangle(42, 20, 42, 60, 90, 40, BLUE);
	delay(50);
	// pause color
	display.fillRoundRect(39, 98, 20, 45, 5, RED);
	display.fillRoundRect(69, 98, 20, 45, 5, RED);
	// play color
	display.fillTriangle(42, 20, 42, 60, 90, 40, GREEN);
}


void Display::lcdTestPattern(void) {
	uint8_t w, h;
	display.setAddrWindow(0, 0, 96, 64);

	for (h = 0; h < 64; h++) {
		for (w = 0; w < 96; w++) {
			if (w > 83) {
				display.writePixel(w, h, WHITE);
			} else if (w > 71) {
				display.writePixel(w, h, BLUE);
			} else if (w > 59) {
				display.writePixel(w, h, GREEN);
			} else if (w > 47) {
				display.writePixel(w, h, CYAN);
			} else if (w > 35) {
				display.writePixel(w, h, RED);
			} else if (w > 23) {
				display.writePixel(w, h, MAGENTA);
			} else if (w > 11) {
				display.writePixel(w, h, YELLOW);
			} else {
				display.writePixel(w, h, BLACK);
			}
		}
	}
	display.endWrite();
}



void Display::setup() {
	display.begin();

	display.fillScreen(BLACK);

	Localization loc;
	const char* titleFirstString = loc.getLocalizedString(LOC_TITLE_FIRST);
	const char* titleLastString = loc.getLocalizedString(LOC_TITLE_LAST);
	const char* startPromptString = loc.getLocalizedString(LOC_START_PROMPT);

	display.setTextSize(2);
	display.setTextColor(RED);
	display.setCursor(0, 0);
	display.print(titleFirstString);

	display.getTextBounds(titleFirstString, 0, 0, &calcX, &calcY, &calcW, &calcH);
	unsigned short titleFirstHeight = calcH;

	display.getTextBounds(titleLastString, 0, 0, &calcX, &calcY, &calcW, &calcH);
	unsigned short titleLastWidth = calcW;
	unsigned short titleLastLowestPoint = titleFirstHeight + TEXT_VERTICAL_MARGIN + calcH;
	display.setCursor(DISPLAY_WIDTH - titleLastWidth, titleFirstHeight + TEXT_VERTICAL_MARGIN);
	display.print(titleLastString);

	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.getTextBounds(startPromptString, 0, 0, &calcX, &calcY, &calcW, &calcH);
	display.setCursor((DISPLAY_WIDTH - calcW)/2, titleLastLowestPoint + TEXT_VERTICAL_MARGIN);
	display.print(startPromptString);
}

void Display::updateDisplay() {
	// function pointer (menus, game screen, etc)

	// redraw game

	// check for changes, update menu/whatever
}