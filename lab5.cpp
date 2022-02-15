#include <iostream>
#include <ostream>
#include <string>
#include <fstream>
#include <vector>
#include "ConnectedList.h"
using namespace std;

class EmptyList_exception : public exception {
private:
    string message;
public:
    EmptyList_exception(string error = "") {
        message = error;
    }
    const char* what() const noexcept { return message.c_str(); }
};

class Overflow_exception : public exception {
private:
    string message;
public:
    Overflow_exception(string error = "") {
        message = error;
    }
    const char* what() const noexcept { return message.c_str(); }
};

bool perfect(int n)
{
    if (n <= 1) return false;
    int sum = 1;
    for (int i = 2; i <= n / 2; ++i)
        if (!(n % i))
            sum += i;
    if (sum == n)
        return true;
    return false;
}

template<class T>
class Queue {

public:

    static constexpr unsigned K = 25;

    bool find(const T& data);

    T& get_head() { return list._head(); }
    T& get_tail() { return list._tail(); }

    Queue() {
        list = ConnectedList<T>();
    }

    void push_back(const T& item) {

        if (list.size() > K) throw Overflow_exception();
        list.insertAfter(new Node<T>(item));
    }
    void pop() {
        if (list.isEmpty() == true) throw EmptyList_exception();
        else list.pop();
    }

    size_t size() const { return list.lenght; }
    bool isEmpty() const { return list.isEmpty(); }
    void clear() {
        list.clear();
    }

    template< typename T>
    friend ostream& operator<<(ostream& file, Queue<T>& queue);

private:

    ConnectedList<T> list;

};

template<class T>
ostream& operator<<(ostream& file, Queue<T>& queue) {

    queue.list.reset();
    for (int i = 0; i < queue.list.size(); i++) {
        file << queue.list.data() << " ";
        queue.list._next();
    }
    return file;

}

template<class T>
bool Queue<T>::find(const T& data) {

    return Find(data, list);

}

int main() {

    ifstream* F = new ifstream("F.txt", ios_base::app);
    
    Queue<int> q;

    vector<int> reader;
    for(int i = 0; i < 15; i++) {

        int temp;
        *F >> temp;
        reader.push_back(temp);

    }

    for (auto&& e : reader)
        cout << e << " ";
    cout << endl;

    for (int i = 0; i < 15; i++) {

        try {
            q.push_back(reader[i]);
        }
        catch (Overflow_exception& ex) {
            cout << "Overflow (K = 25)" << endl;
        }

    }

    vector<int> writer;
    for (int i = 0; i < 15; i++) {

        writer.push_back(q.get_head());
        try {
            q.pop();
        }
        catch (EmptyList_exception& ex) {
            cout << "Empty List!" << endl;
        }

    }

    for (auto&& e : writer)
        cout << e << " ";
    cout << endl;

    ofstream* G = new ofstream("G.txt", ios_base::app);

    for (int i = 0; i < 15; i++)
        *G << writer[i] << " ";

    cout << q.find(2) << endl;

    Queue<int> r;
    vector<int> t;
    for (int i = 0; i < 15; i++)
        r.push_back(i);

    int c = 0;
    for (int i = 0; i < 15; i++) {
        t.push_back(q.get_head());
        try {
            q.pop();
        }
        catch (EmptyList_exception& ex) {
            cout << "Empty List!" << endl;
        }
        if (perfect(t[i])) c += 1;
    }
    cout << c << endl;

    return 0;
}
