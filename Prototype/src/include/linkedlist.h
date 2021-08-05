#ifndef LINKEDLIST_H
#define LINKEDLIST_H


namespace Gib {
	template <class T>
	class LinkedListNode {
	private:
		T& data;
		LinkedListNode<T>* nextNode = nullptr;
	public:
		LinkedListNode(T& obj) : data{obj} {};
		~LinkedListNode();

		const unsigned short childCount();

		void enqueue(T& obj);
		LinkedListNode<T>* dequeue();

		T& getData() {return data;}
		LinkedListNode<T>* getNextNode() {return nextNode;}
	};
}


template <class T>
const unsigned short Gib::LinkedListNode<T>::childCount() {
	if(!nextNode) {
		return 1;
	}

	return nextNode->childCount() + 1;
}


template <class T>
void Gib::LinkedListNode<T>::enqueue(T& obj) {
	if(nextNode == nullptr) {
		nextNode = new Gib::LinkedListNode<T>(obj);
	} else {
		nextNode->enqueue(obj);
	}
}


template <class T>
Gib::LinkedListNode<T>::~LinkedListNode() {
	delete nextNode;
}


template <class T>
Gib::LinkedListNode<T>* Gib::LinkedListNode<T>::dequeue() {
	if(!nextNode->getNextNode()) {
		LinkedListNode<T>* tempReturn = nextNode;
		nextNode = nullptr;
		return tempReturn;
	}

	return nextNode->dequeue();
}



namespace Gib {
	template <class T>
	class LinkedList {
	private:
		Gib::LinkedListNode<T>* head;
	public:
		~LinkedList();

		const unsigned short size();

		const Gib::LinkedListNode<T>* getHead() {return head;}

		void enqueue(T& obj);
		T* dequeue();
	};
}


template <class T>
Gib::LinkedList<T>::~LinkedList() {
	delete head;
}


template <class T>
const unsigned short Gib::LinkedList<T>::size() {
	if(head == nullptr) {
		return 0;
	}

	return head->childCount();
}


template <class T>
void Gib::LinkedList<T>::enqueue(T& obj) {
	if(head == nullptr) {
		head = new Gib::LinkedListNode<T>(obj);
	} else {
		head->enqueue(obj);
	}
}


template <class T>
T* Gib::LinkedList<T>::dequeue() {
	if(head == nullptr) {
		return nullptr;
	}

	if(!head->getNextNode()) {
		Gib::LinkedListNode<T>* tempReturn = head;
		head = nullptr;
		return &tempReturn->getData();
	}

	return &head->dequeue()->getData();
}

#endif