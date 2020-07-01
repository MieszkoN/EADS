#include <iostream>
#include "ring.h"
#include "split.h"
 
using namespace std;
 
int main() {
    Ring<int,string> *r1 = new Ring<int, string>;
    r1->insertFirst(1,"aaaa");
    r1->insertFirst(2,"bbbb");
    r1->insertFirst(3,"cccc");
    r1->insertFirst(4,"dddd");
    r1->insertFirst(5,"eeee");
    r1->insertFirst(6,"ffff");
    r1->insertFirst(6,"ffff");
    r1->insertFirst(6,"ffff");
    r1->insertFirst(6,"ffff");
    
    r1->insertAfter(6, 4, 1000, "pppp");
 
    r1->print();
 
    r1->removeAllKeys(6);
    cout<<endl;
    cout<<endl;
    Ring<int,string> *r2 = new Ring<int, string>;
    r2 = r1;
    r2->print();
    cout << endl;
    r2->reversePrint();
 
    Ring <int, string> r8;
    r8.insertLast(1, "aaaa");
    r8.insertLast(2, "bbbb");
    r8.insertLast(3, "cccc");
    r8.insertLast(4, "dddd");
    r8.insertLast(5, "eeee");
    r8.insertLast(6, "ffff");
    r8.insertLast(7, "gggg");
    r8.insertLast(8, "hhhh");
    r8.insertLast(9, "iiii");
    r8.insertLast(10, "jjjj");
    r8.insertLast(11, "kkkk");
    r8.insertLast(12, "llll");
    cout << endl <<endl << "Source to split" << endl;
    r8.print();
 
 
 
 
 
 
 
 
   // Ring <int,string> r2;
    Ring <int, string> r11;
    Ring <int, string> r22;
    split(r8,false, r11, 3, 2, r22, 2, 4);
    cout << endl << "Result 1:" << endl;
    r11.print();
    cout << endl << "Result 2:" << endl;
    r22.print();
    cout << endl;
    delete r1;
    delete r2;
}

