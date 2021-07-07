#include "Arduino.h"
#include "src/include/input.h"
#include "src/include/display.h"
#include "src/include/network.h"


Input input;
Display display;
Network network;


void loop() {
	input.getInput();
	display.updateDisplay();
	network.processNetwork();
}


void setup() {
	pinMode(INPUT_PIN, INPUT);

	Serial.begin(9600);
	while(!Serial) {
		delay(250);
	}

	Serial.println(F("Running!"));
}