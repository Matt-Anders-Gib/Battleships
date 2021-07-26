#ifndef LINKEDLIST_H
#define LINKEDLIST_H


namespace Gib {
	template <class T>
	class LinkedListNode {
	private:
		T& data;
		LinkedListNode<T>* nextNode;
	public:
		LinkedListNode(T& obj);

		void enqueue(T& obj);
		LinkedListNode<T>* dequeue();

		LinkedListNode<T>* getNextNode() {return nextNode;}
	};
}


template <class T>
Gib::LinkedListNode<T>::LinkedListNode(T& obj) {
	data = obj;
	nextNode = nullptr;
}


template <class T>
void Gib::LinkedListNode<T>::enqueue(T& obj) {
	if(nextNode == nullptr) {
		nextNode = Gib::LinkedListNode<T>(obj);
	} else {
		nextNode->enqueue(obj);
	}
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
		Gib::LinkedListNode<T>* tempReturn;
	public:
		void enqueue(T& obj);
		T* dequeue();
	};
}


template <class T>
void Gib::LinkedList<T>::enqueue(T& obj) {
	if(head == nullptr) {
		head = Gib::LinkedListNode<T>(obj);
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
		tempReturn = head;
		head = nullptr;
		return tempReturn;
	}

	return head->dequeue();
}

#endif