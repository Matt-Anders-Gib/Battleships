#include "Arduino.h"

#include "Source/Include/GameScene.hpp"


GameScene* currentScene;


void loop() {

}


void setup() {
	Serial.begin(9600);
	while(!Serial) {
		delay(100);
	}

	currentScene = new TitleScene();
}