#include "Arduino.h"
#include "src/include/input.h"
#include "src/include/network.h"

#include "src/include/gamescene.h"

#include "src/include/eventqueue.h"

EventQueue events = EventQueue();

Input input;
Network net;

GameScene* currentScene;


void loop() {
	input.poll(events, millis());
	net.processIncoming();
	currentScene->processLogic();
	net.processOutgoing();
	currentScene->updateDisplay(millis());
}


void setup() {
	Serial.begin(9600);
	while(!Serial) {
		delay(250);
	}

	oled.setup();

	Serial.println(F("Running!"));
}