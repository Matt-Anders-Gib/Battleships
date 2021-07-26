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
	SampleData(const int d) : data{d} {}
	const int getNum() {return data;}
};


void testRingBuffer() {
	Serial.print(F("Free memory: "));
	Serial.println(freeMemory());
	Serial.println();

	Gib::RingBuffer<SampleData> testRB = Gib::RingBuffer<SampleData>(14);
	Serial.println(F("Allocated\n"));

	Serial.print(F("Free memory: "));
	Serial.println(freeMemory());
	Serial.println();
}


void testLinkedList() {
	Serial.print(F("Free memory: "));
	Serial.println(freeMemory());
	Serial.println();

	Gib::LinkedList<SampleData> testLL = Gib::LinkedList<SampleData>();
	Serial.println(F("Allocated"));

	SampleData testDataOne = SampleData(69);
	SampleData testDataTwo = SampleData(1337);
	SampleData testDataThree = SampleData(9001);

	Serial.print(F("Linked List size: "));
	Serial.println(testLL.size());

	Serial.println(F("Enqueue 3"));
	testLL.enqueue(testDataOne);
	testLL.enqueue(testDataTwo);
	testLL.enqueue(testDataThree);

	Serial.print(F("Linked List size: "));
	Serial.println(testLL.size());

	Serial.print(F("Dequeue: "));
	Serial.println(testLL.dequeue()->getNum());

	Serial.print(F("Linked List size: "));
	Serial.println(testLL.size());

	Serial.print(F("Free memory: "));
	Serial.println(freeMemory());
	Serial.println();
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

	/*Serial.println(F("Test Linked List"));
	testLinkedList();
	Serial.println(F("Complete"));

	Serial.print(F("Free memory: "));
	Serial.println(freeMemory());
	Serial.println();*/

	Serial.println(F("Done"));
}


void loop() {}