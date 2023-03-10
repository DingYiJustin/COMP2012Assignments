//
// Created by ck on 2021/11/5.
//
/*
#include <vector>
#include <string>
#include <iostream>

#include "Manager.h"
#include "BinarySearchTree.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Manager manager = Manager();
    BinarySearchTree *sec1 = new BinarySearchTree(6);
    manager.registerSection("book", sec1);
    manager.printStatus();
    cout << endl;

    for (int i : vector<int>{11, 9, 9, 10, 16, 15, 13, 4, 1, 3})
        sec1->add(i);

    cout << "The height of section #1 is: " << sec1->height() << endl;
    cout << "Section #1 prefix notation: ";
    sec1->printDFSPrefix();
    cout << endl;
    cout << "Section #1 infix notation: ";
    sec1->printDFSInfix();
    cout << endl;
    cout << "11 is " << (sec1->hasId(11) ? "" : "not ") << "in Section #1" << endl;
    
    BinarySearchTree *sec2 = new BinarySearchTree(*sec1);
    manager.registerSection("toy", sec2);
    manager.printStatus();
    cout << endl;
    
    for (int i : vector<int>{5, 13, 19, 17})
        sec2->add(i);

    cout << "The height of section #2 is: " << sec2->height() << endl;
    cout << "Section #2 prefix notation: ";
    sec2->printDFSPrefix();
    cout << endl;
    cout << "Section #2 infix notation: ";
    sec2->printDFSInfix();
    cout << endl;
    cout << "21 is " << (sec2->hasId(21) ? "" : "not ") << "in Section #2" << endl;
    
    cout << "Manager is deleting the book section" << endl;
    manager.deleteSection("book");
    manager.printStatus();
    cout << endl;
    cout << "Manager is deleting the toy section" << endl;
    manager.deleteSection("toy");
    manager.printStatus();

    return 0;
}
*/

#include <iostream>

using namespace std;

int main()
{
    char username1 = '2';
    char username2 = '1';
    cout<<((username1 - '0' + 'a' + 1) * 0x01010000 + (username2 - '0' + 'A' + 2) * 0x0101);
}