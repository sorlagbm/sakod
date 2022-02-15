#include <iostream>
#include "qstack.h"
using namespace std;

int main(){

    qstack<int> s;
    s.push(10);
    cout << s.head() << endl;

    if (!s.isEmpty())
        s.pop();

    try {
        cout << s.head() << endl;
    }
    catch (EmptyListException& e) {
        cout << "List is empty" << endl;
    }

    return 0;

}
