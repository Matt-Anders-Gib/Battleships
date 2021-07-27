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


void printFreeMemory() {
	Serial.print(F("Free memory: "));
	Serial.println(freeMemory());
	Serial.println();
}


class SampleData {
private:
	int data;
public:
	SampleData(const int d) : data{d} {}
	const int getNum() {return data;}
};


class ParentObject {
private:
	Gib::RingBuffer<SampleData> testRB;
public:
	ParentObject() {
		testRB = Gib::RingBuffer<SampleData>()
	}
};


void testStackOnlyRingBufferAddInsideNewScope(Gib::RingBuffer<SampleData>& rb) {
	//Gib::RingBuffer<SampleData> rb = Gib::RingBuffer<SampleData>();
	printFreeMemory();

	Serial.println(F("Creating obj"));
	SampleData myS = SampleData(7);
	printFreeMemory();

	Serial.println(F("Adding"));
	rb.push(myS);
	printFreeMemory();

	Serial.println(F("exiting function"));
}


void testRingBuffer() {
	printFreeMemory();

	;
	Serial.println(F("Allocated\n"));
	printFreeMemory();

	Serial.println(F("Create objects"));
	SampleData s1 = SampleData(9001);
	SampleData s2 = SampleData(1337);
	SampleData s3 = SampleData(69);
	printFreeMemory();

	Serial.println(F("Pushing"));
	testRB.push(s1);
	testRB.push(s2);
	testRB.push(s3);
	printFreeMemory();

	Serial.println(F("Popping 1"));
	testRB.pop();
	printFreeMemory();

	Serial.println(F("Popping remaining"));
	testRB.pop();
	testRB.pop();
	printFreeMemory();

	{
		Serial.println(F("allocating inside scope"));
		SampleData s4 = SampleData(42);
		printFreeMemory();

		Serial.println(F("pushing inside scope"));
		testRB.push(s4);
		printFreeMemory();

		Serial.println(F("leaving scope"));
	}
	printFreeMemory();

	Serial.println(F("Trying to access object"));
	Serial.println(testRB.pop()->getNum());
	printFreeMemory();

	Serial.println(F("Passing into function"));
	testStackOnlyRingBufferAddInsideNewScope(testRB);
	printFreeMemory();

	Serial.println(F("trying to access obj"));
	Serial.println(testRB.pop()->getNum());
	printFreeMemory();
}


void testLinkedList() {
	printFreeMemory();

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

	printFreeMemory();
}


void setup() {
	Serial.begin(9600);
	while(!Serial) {
		delay(250);
	}

	Serial.println(F("Start"));

	printFreeMemory();

	Serial.println(F("Test Ring Buffer"));
	testRingBuffer();
	Serial.println(F("Complete"));

	printFreeMemory();

	Serial.println(F("Test Linked List"));
	testLinkedList();
	Serial.println(F("Complete"));

	printFreeMemory();

	Serial.println(F("Done"));
}


void loop() {}