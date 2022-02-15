#include <iostream>
#include "qstack.h"
#include <vector>
#include <random>
using namespace std;

/*
* Построение 3 - 5 +
* Модификация 1 - 4 +
* Подсчет 3 - 5 +
* 
* Сумма = 14
* 
*/

bool polindrom(string word)
{
    int len = word.length();
    for (int i = 0; i < len / 2; ++i)
    {
        if (word[i] != word[len - i - 1])
        {
            return false;
        }
    }
    return true;
}

int main(){

    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    /*
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
    */

    // Построение 3 - 5
    qstack<string> wstack;
    wstack.push("кабак");
    wstack.push("шалаш");
    wstack.push("дед");
    wstack.push("заказ");
    wstack.push("кбафыв");
    wstack.push("афывцукцу");
    wstack.push("4230942039");
    wstack.push("хахах");
    wstack.push("боб");
    wstack.push("лил");
    wstack.push("зцхкйзех");
    wstack.push("яблоко");

    vector<string> writer;
    for (int i = 0; i < 12; i++) {

        if (polindrom(wstack.head()))
            writer.push_back(wstack.head());
        try {
            wstack.pop();
        }
        catch (EmptyListException& e) {
            cout << "Empty List" << endl;
        }

    }

    for (auto&& e : writer)
        cout << e << endl;

    cout << endl;

    // Модификация - 1 - 4
    qstack<int> S;
    for (int i = 0; i < 10; i++)
        S.push(i);
    
    int y = S.head();
    cout << y << endl;
    S.push(y);
    cout << S.tail() << endl;

    cout << endl;

    // Подсчет 3 - 5
    qstack<int> istack;
    for (int i = 0; i < 20; i++)
        istack.push(-100 + rand() % 200);

    vector<int> iwriter;
    for (int i = 0; i < 20; i++) {

        iwriter.push_back(istack.head());
        try {
            istack.pop();
        }
        catch (EmptyListException& e) {
            cout << "Empty List" << endl;
        }

    }

    for (auto&& e : iwriter)
        cout << e << endl;

    int c = 0;

    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 20; j++)
        {
            if (iwriter[j] - iwriter[i] == 2)
                c += 1;
        }

    cout << c << endl;

    return 0;

}
