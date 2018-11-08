#include "Deku.h"
#include <string>

int main()
{
    string trash;
    GreatDeku<unsigned long, string> newDeku;
    newDeku.insert(3,"three");
    newDeku.insert(5,"five");
    newDeku.insert(1,"one");
    newDeku.insert(4,"four");
    newDeku.insert(2,"two");
    newDeku.insert(5, "fivve");
    for (int i = 1; i < 6; ++i)
        cout << newDeku.find(i)->value_ << endl;
    cout << "Print:\n";
    newDeku.printInOrder();

    if (newDeku.find(6) == nullptr)
        cout << "Key 6 not found" << endl;

    cout << "Erase newDeku at 3:\n";
    newDeku.erase(3);
    newDeku.printInOrder();

    cout << "Erase newDeku at 4:\n";
    newDeku.erase(4);
    newDeku.printInOrder();

    cout << "Erase newDeku at 5:\n";
    newDeku.erase(5);
    newDeku.printInOrder();

    cout << "Erase newDeku at 1:\n";
    newDeku.erase(1);
    newDeku.printInOrder();

    cout << "Erase newDeku at 2:\n";
    newDeku.erase(2);
    newDeku.printInOrder();
    return 0;
}