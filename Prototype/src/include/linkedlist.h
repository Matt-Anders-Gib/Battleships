#ifndef LINKEDLIST_H
#define LINKEDLIST_H


namespace Gib {
    template <class T>
    class LinkedListNode {
    private:
        T& data;
        LinkedListNode<T>* nextNode;
    public:
    };
}

namespace Gib{
    template <class T>
    class LinkedList {
    private:
        LinkedListNode<T>* head;
    public:
    };
}

#endif