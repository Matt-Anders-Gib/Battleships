#ifndef RINGBUFFER_H
#define RINGBUFFER_H


namespace Gib {

	template <class T>
	class RingBuffer {
	private:
		const unsigned short BUFFER_SIZE;
		T** buffer;
		T* held;

		unsigned short headIndex = 0;
		unsigned short tailIndex = 0;
	public:
		RingBuffer(const unsigned short s);

		const bool empty() const {return headIndex == tailIndex;}

		void push(const T* obj);
		T* pop();
	};
}

template <class T>
Gib::RingBuffer<T>::RingBuffer(const unsigned short s) : BUFFER_SIZE{s} {
	buffer = new T*[BUFFER_SIZE]();
}


template <class T>
void Gib::RingBuffer<T>::push(const T* obj) {
	buffer[tailIndex] = obj;
	tailIndex += 1;

	if(tailIndex == BUFFER_SIZE) {
		tailIndex = 0;
	}

	if(tailIndex + 1 == headIndex) {
		//log an error that next last available queue index was taken. Next enqueue may overwrite unprocessed objects
	}
}


template <class T>
T* Gib::RingBuffer<T>::pop() {
	if(empty()) {
		return nullptr;
	}

	held = buffer[headIndex];

	headIndex += 1;
	if(headIndex == BUFFER_SIZE) {
		headIndex = 0;
	}

	return held;
}

#endif