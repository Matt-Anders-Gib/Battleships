#include "Arduino.h"
#include "src/include/input.h"
#include "src/include/network.h"
#include "src/include/logic.h"
#include "src/include/display.h"


Input input;
ButtonEvent currentInput;

Logic logicController;
Network net;
Display oled;


void loop() {
	currentInput = input.getInput();
	net.processIncoming();

	logicController.update();
	net.processOutgoing();
	oled.updateDisplay(millis());
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