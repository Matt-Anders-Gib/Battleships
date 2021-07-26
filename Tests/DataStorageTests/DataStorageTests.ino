#include "Arduino.h"

#include "M:\Developer\C++\Sketchbook\Battleships\Prototype\src\include\ringbuffer.h"
#include "M:\Developer\C++\Sketchbook\Battleships\Prototype\src\include\linkedlist.h"


#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__

int freeMemory() {
  char top;
#ifdef __arm__
  return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
  return &top - __brkval;
#else  // __arm__
  return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
}


struct SampleData {
private:
	int data;
public:
	const int getData() {return data;}
};


void testRingBuffer() {
	//Gib::RingBuffer<SampleData> testRB = Gib::RingBuffer<SampleData>(16);
	SampleData testD = SampleData();
}


void testLinkedList() {

}


void setup() {
	Serial.begin(9600);
	while(!Serial) {
		delay(250);
	}

	Serial.println(F("Start"));
	Serial.print(F("Free memory: "));
	Serial.println(freeMemory());
	Serial.println();

	Serial.println(F("Test Ring Buffer"));
	testRingBuffer();
	Serial.println(F("Complete"));

	Serial.print(F("Free memory: "));
	Serial.println(freeMemory());
	Serial.println();

	Serial.println(F("Test Linked List"));
	testLinkedList();
	Serial.println(F("Complete"));

	Serial.print(F("Free memory: "));
	Serial.println(freeMemory());
	Serial.println();

	Serial.println(F("Done"));
}


void loop() {}