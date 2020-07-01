#include <iostream>
#include "sequence.h"
#include "merge.h"
using namespace std;

int main() {
    Sequence<int, string> *s1 = new Sequence<int, string>;
    s1->removeFirst();
    s1->insertFirst(5, "eeeee");                    
    s1->insertFirst(4, "ddddd");
    s1->insertLast(6, "fffff");
    s1->insertLast(7, "ggggg");
    s1->insertLast(8, "hhhhh");
    s1->insertFirst(1, "aaaaa");
    s1->insertFirst(1, "aaaaa");
    s1->insertFirst(1, "aaaaa");
    s1->insertFirst(1, "aaaaa");
    s1->print();
    cout << endl;
    s1->insertAfter(5, "pfaofa", 1, 34, "ok");
    s1->insertBefore(5, "pfaofa", 1, 34, "ok");
    s1->removeElement(10, "jjjjj", 3);
    cout << endl << endl << endl;
    s1->removeElement(1, "aaaaa", 2);
    s1->insertAfter(5, "eeeee", 1, 5, "eeeee");
    s1->insertBefore(4, "ddddd", 1, 5, "eeeee");
    s1->print();
    cout << endl;

    //Assignment operator
    Sequence<int, string> *s2 = new Sequence <int, string>;
    s2 = s1;
    cout << endl;
    s2->print();

    //Copy constructor
    cout << endl;
    Sequence <int, string> s3(*s1);
    s3.print();
    cout << endl;

    //Merge Function

    Sequence <int, string> s5;
    Sequence <int, string> s6;
    Sequence <int, string> s7;
    s7 = merge(s5, 2, 3, s6, 1, 2, 4);
    s7.print();
    s5.insertLast(1, "aa");
    s5.insertLast(2, "bb");
    s5.insertLast(3, "cc");
    s5.insertLast(4, "dd");
    s5.insertLast(5, "ee");
    s5.insertLast(6, "ff");
    s5.insertLast(7, "gg");
    s5.insertLast(8, "hh");
    s5.insertLast(9, "ii");

    s6.insertLast(10, "aaaa");
    s6.insertLast(20, "bbbb");
    s6.insertLast(30, "cccc");
    s6.insertLast(40, "dddd");
    s6.insertLast(50, "eeee");
    s6.insertLast(60, "ffff");
    s6.insertLast(70, "gggg");
    s6.insertLast(80, "hhhh");
    s6.insertLast(90, "iiii");
    s6.insertLast(100, "jjjj");

    s7 = merge(s5, 2, 3, s6, 1, 2, 4);
    cout<< endl << "After merging:" << endl;
    s7.print();
    cout<< endl<< endl;

    delete s1;
    delete s2;
    s3.deleteList();
    s5.deleteList();
    s6.deleteList();
    s7.deleteList();
    s1->print();   // it is deleted
}