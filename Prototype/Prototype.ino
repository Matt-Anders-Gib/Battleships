#include "Arduino.h"
#include "src/include/input.h"
#include "src/include/display.h"
#include "src/include/network.h"

Input input;
Display oled;
Network net;


void loop() {
	input.getInput();
	oled.updateDisplay(millis());
	net.processNetwork();
}


void setup() {
	Serial.begin(9600);
	while(!Serial) {
		delay(250);
	}

	pinMode(INPUT_PIN, INPUT);
	oled.setup();

	Serial.println(F("Running!"));
}