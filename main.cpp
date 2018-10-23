#include "Deku.h"
#include <string>

int main()
{
    string trash;
    GreatDeku<unsigned long> newDeku;
    newDeku.insert(15);
    newDeku.insert(1);
    newDeku.insert(5);
    newDeku.insert(17);
    newDeku.insert(200);
    newDeku.insert(2000);
    newDeku.insert(2);
    newDeku.insert(42);
    newDeku.insert(67);
    newDeku.insert(29);
    newDeku.insert(37);
    newDeku.printInOrder();
    newDeku.prettyPrint();
    cout << "Size: " << newDeku.getSize() << endl;
    cout << endl << endl;
    newDeku.erase(42);
    newDeku.erase(15);
    cout << "newDeku after erasing 42: " << endl;
    newDeku.printInOrder();
    cout << "Size: " << newDeku.getSize() << endl;
    cout << endl << endl;
    return 0;
}