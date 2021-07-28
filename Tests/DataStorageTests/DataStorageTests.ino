#include "Arduino.h"

#include "M:\Developer\C++\Sketchbook\Battleships\Prototype\src\include\ringbuffer.h"
#include "M:\Developer\C++\Sketchbook\Battleships\Prototype\src\include\linkedlist.h"
#include "M:\Developer\C++\Sketchbook\Battleships\Prototype\src\include\freememory.h"


class SampleData {
private:
	int data;
public:
	SampleData(const int d) : data{d} {}
	const int getNum() {return data;}
};


class ParentObject {
private:
public:
	ParentObject() {
		testRB = Gib::RingBuffer<SampleData>();
	}

	Gib::RingBuffer<SampleData> testRB;
};


void printFreeMemory() {
	Serial.print(F("Free memory: "));
	Serial.println(freeMemory());
	Serial.println();
}



void testStackOnlyRingBufferAddInsideNewScope(ParentObject& po) { //fails! out of scope!
	printFreeMemory();

	Serial.println(F("Creating obj"));
	SampleData myS = SampleData(7);
	printFreeMemory();

	Serial.println(F("Adding"));
	po.testRB.push(myS);
	printFreeMemory();

	Serial.println(F("exiting function"));
}


void testRingBuffer() {
	printFreeMemory();

	ParentObject par = ParentObject();
	Serial.println(F("Allocated\n"));
	printFreeMemory();

	Serial.println(F("Create objects"));
	SampleData s1 = SampleData(9001);
	SampleData s2 = SampleData(1337);
	SampleData s3 = SampleData(69);
	printFreeMemory();

	Serial.println(F("Pushing"));
	par.testRB.push(s1);
	par.testRB.push(s2);
	par.testRB.push(s3);
	printFreeMemory();

	Serial.println(F("Popping 1"));
	par.testRB.pop();
	printFreeMemory();

	Serial.println(F("Popping remaining"));
	par.testRB.pop();
	par.testRB.pop();
	printFreeMemory();

	{ //seems to reliably work, but I suspect this could cause problems
		Serial.println(F("allocating inside scope"));
		SampleData s4 = SampleData(42);
		printFreeMemory();

		Serial.println(F("pushing inside scope"));
		par.testRB.push(s4);
		printFreeMemory();

		Serial.println(F("leaving scope"));
	}
	printFreeMemory();

	Serial.println(F("Trying to access object"));
	Serial.println(par.testRB.pop()->getNum());
	printFreeMemory();

	Serial.println(F("Passing into function"));
	testStackOnlyRingBufferAddInsideNewScope(par);
	printFreeMemory();

	Serial.println(F("trying to access obj"));
	Serial.println(par.testRB.pop()->getNum()); //fails
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