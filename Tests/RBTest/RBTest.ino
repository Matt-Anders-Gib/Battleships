#include "Arduino.h"
#include "M:\Developer\C++\Sketchbook\Battleships\Prototype\src\include\ringbuffer.h"


struct TestObj {
	char a;
	int id;

	TestObj() {
		a = 'a';
		id = 0;
	}

	void overwrite(char A, char ID) {
		a = A;
		id = ID;
	}
};


void doTests(Gib::RingBuffer<TestObj>& buffer) {
	TestObj& updateObj = buffer.updateTail();
	updateObj.a = 'A';
	updateObj.id = 2;

	Serial.print(F("Object "));
	Serial.print(updateObj.a);
	Serial.print(F(" will have a value of "));
	Serial.println(updateObj.id);

	TestObj& gotObj = buffer.getHead();

	Serial.print(F("Object "));
	Serial.print(gotObj.a);
	Serial.print(F(" has a value of "));
	Serial.println(gotObj.id);

	for(int i = 'B'; i < 'E'; i += 1) {
		buffer.updateTail().overwrite((char)i, i);
	}

	Serial.print(F("There are "));
	Serial.print(buffer.getCount());
	Serial.println(F(" objects in the buffer"));

	int index = 1;
	while(!buffer.empty()) {
		Serial.print(index);
		Serial.print(F(") "));

		gotObj = buffer.getHead();
		Serial.print(gotObj.a);
		Serial.print(F(" : "));
		Serial.println(gotObj.id);

		index += 1;
	}

	Serial.print(F("There are "));
	Serial.print(buffer.getCount());
	Serial.println(F(" objects in the buffer"));
}


void setup() {
	Serial.begin(9600);
	while(!Serial) {
		delay(250);
	}

	Serial.println(F("Running!"));

	Gib::RingBuffer<TestObj> buffer = Gib::RingBuffer<TestObj>();
	doTests(buffer);

	Serial.println(F("Done!"));
}



void loop() {

}