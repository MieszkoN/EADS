#include <iostream>
#include "sequence.h"
using namespace std;

template <typename key, typename info>

Sequence <key, info> merge(const Sequence<key, info> &s1, int start1, int len1, const Sequence<key, info> &s2, int start2, int len2, int count) {
    Sequence <key, info> *s3 = new Sequence<key, info>;
    if(s1.isEmpty() && s2.isEmpty())
        return *s3;

    for(int i = 0; i < count; i++) {
        for(int j = start1; j < start1+len1; j++) {
            if(j < s1.getNumberOfElements()) {
                s3->insertLast(s1.getKeyAtPosition(j), s1.getInfoAtPosition(j));
            } else {
                break;
            }
        }
        start1 += len1;

        for(int k = start2; k < len2+start2; k++) {
            if(k < s2.getNumberOfElements()) {
                s3->insertLast(s2.getKeyAtPosition(k), s2.getInfoAtPosition(k));
            }
        }
        start2 += len2;
    }
    return *s3;
    delete s3;
}