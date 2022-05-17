#include "connectedlist\Node.h"
template<class T>
class ConnectedList {

#define NEW(T, VALUE) new Node<T>(VALUE)

    /*
    Node<int>* head = new Node<int>(15);
    Node<int>* cur = new Node<int>(54, head);
    cout << cur->getData() << endl;
    cur = cur->nextNode();
    cout << cur->getData() << endl;
    cur->insertAfter(new Node<int>(345));
    cur = cur->nextNode();
    cout << cur->getData() << endl;
    cur = cur->prevNode();
    cout << cur->getData() << endl;
    cout << endl;
    Node<int>* a = new Node<int>(4);
    cout << a->getData() << endl;
    a->insertAfter(new Node<int>(23423));
    a = a->nextNode();
    cout << a->getData() << endl;
    */

private:
    Node<T>* head, * tail, * cur;

    unsigned long long lenght;
    unsigned long long pos;

public:

    ConnectedList(T value_of_head = T()) : head(NODE_NULL), cur(head), tail(NODE_NULL)
        , lenght(0), pos(-1) {}

    void _next() {
        cur = cur->nextNode();
        pos += 1;
    }
    void _prev() {
        if (cur != NODE_NULL && cur->prevNode() != NODE_NULL) {
            cur = cur->prevNode();
            pos -= 1;
        }
    }

    unsigned long long size() const { return lenght; }
    unsigned long long curPos() const { return pos; }
    bool isEmpty() const { return head == NODE_NULL ? true : false; }
    T& data() { return cur->getData(); }

    void insertAfter(Node<T>* item);
    void insertAt(Node<T>* item) {
        Node<T>* newNode;

        if (cur->prevNode() == NODE_NULL) {
            newNode = new Node<T>(item, head);
            head = newNode;
        }
        else {
            newNode = new Node<T>(item);
            cur->prevNode()->insertAfter(newNode);
        }
        if (cur->prevNode() == this->tail) {
            this->tail = newNode;
            this->pos = this->lenght;
        }
        cur = newNode;
        lenght += 1;
    }

    void pop() {
        Node<T>* temp = head;
        temp->deleteNode();
        head = head->nextNode();
        //head = head->nextNode();

        lenght -= 1;
        //e->deleteNode();
    }

    void deleteAt() {
        cur->deleteNode();
        lenght -= 1;
        pos -= 1;
    }

    void reset(int pos = 0) {
        if (pos == 0) {
            cur = head;
            //tail = head;
            this->pos = 0;
        }
        else {
            cur = head->nextNode();
            this->pos = 1;
            for (; this->pos != pos; this->pos++) {
                cur = cur->nextNode();
            }
        }
    }

    void clear() {
        Node<T>* _Cur, * _Next;
        _Cur = head;
        while (_Cur != NODE_NULL) {

            _Next = _Cur->nextNode();
            delete _Cur;

            _Cur = _Next;
        }
        head = NODE_NULL;
        lenght = 0;
        pos = -1;
    }
};

template<class T>
void ConnectedList<T>::insertAfter(Node<T>* item) {

    if (head != NODE_NULL) {
        tail->insertAfter(item);
        tail = tail->nextNode();
        lenght += 1;
    }
    else {
        head = item;
        lenght += 1;
        pos += 1;
        cur = head;
        tail = head->nextNode();
    }

}

