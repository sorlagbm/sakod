#include <iostream>
#include <ostream>
#include <string>
#include "ConnectedList.h"
using namespace std;

void Or_operation(ConnectedList<int>& a, ConnectedList<int>& b) {

    //a.reset();
    //b.reset();
    for (int i = 0; i < b.size(); i++) {
        a.insertAfter(new Node<int>(b.data()));
        //a._next();
        b._next();
    }

}

void And_operation(ConnectedList<int>& a, ConnectedList<int>& b) {

    int c = 0;
    for (a.reset(); a.curPos() != a.size() - 1; a._next()) {

        for (b.reset(a.curPos() + 1); b.curPos() != b.size(); b._next()) {

            if (a.data() != b.data()) { b.pop(); break; }

        }

        a.pop();

    }

}

int main(){
    ConnectedList<int> a;
    ConnectedList<int> b;
    for (int i = 0; i < 15; i++) {
        a.insertAfter(new Node<int>(i + 1));
        b.insertAfter(new Node<int>(14 - i));
    }

    for (a.reset(); a.curPos() != a.size(); a._next()) {

        cout << a.data() << " " << b.data() << endl;
        b._next();
        
    }

    cout << endl;

    And_operation(a, b);
    b.reset();

    for (a.reset(); a.curPos() != a.size(); a._next()) {

        cout << a.data() << " " << b.data() << endl;
        b._next();

    }

    return 0;
}
