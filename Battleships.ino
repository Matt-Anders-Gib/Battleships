#include "Arduino.h"


void loop() {

}


void setup() {
	Serial.begin(9600);
	while(!Serial) {
		delay(250);
	}
}