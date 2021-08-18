#include "Arduino.h"
#include "src/include/input.h"
#include "src/include/network.h"
#include "src/include/logic.h"
#include "src/include/display.h"

#include "src/include/eventqueue.h"

EventQueue events = EventQueue();


Input input;

Logic logicController = Logic(events);
Network net;
Display oled = Display(events);


void loop() {
	input.poll(events, millis());
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

	oled.setup();

	Serial.println(F("Running!"));
}