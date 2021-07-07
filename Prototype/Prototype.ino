#include "Arduino.h"
#include "src/include/input.h"
#include "src/include/display.h"
#include "src/include/network.h"


Input buttons;
Display oled;
Network net;


void loop() {
	buttons.getInput();
	oled.updateDisplay();
	net.processNetwork();
}


void setup() {
	pinMode(INPUT_PIN, INPUT);

	Serial.begin(9600);
	while(!Serial) {
		delay(250);
	}

	Serial.println(F("Running!"));
}