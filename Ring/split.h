#ifndef SPLIT_H
#define SLPIT_H
#include <iostream>
#include "ring.h"

using namespace std;

template <typename key, typename info>
void split(const Ring <key, info> &source, bool direction, 
            Ring <key, info> &result1, int sequence1, int rep1, 
            Ring <key, info> &result2, int sequence2, int rep2) {
   
   typename Ring <key,info>::ConstIterator it = source.begin();

    if(source.isEmpty()) {
        cout << "Ring is empty!" << endl;
    } else if(sequence1 < 0 || sequence2 < 0){
        cout << "Length must be greater than 0!" << endl;
    } else if(direction){
        if(rep1 > rep2) {
            for(int k = 0; k < rep2; k++) {
                for(int i = 0; i < sequence1; i++) {
                    result1.insertLast((*it).keyNode, (*it).infoNode);
                    ++it;
                }

                for(int j = 0; j < sequence2; j++) {
                    result2.insertLast((*it).keyNode, (*it).infoNode);
                    ++it;
                }
            }

            for (int l = 0; l < rep1-rep2; l++) {
                for(int i = 0; i < sequence1; i++) {
                    result1.insertLast((*it).keyNode, (*it).infoNode);
                    ++it;
                }
            }

        } else if(rep1 < rep2) {
            for(int k = 0; k < rep1; k++) {
                for(int i = 0; i < sequence1; i++) {
                    result1.insertLast((*it).keyNode, (*it).infoNode);
                    ++it;
                }

                for(int j = 0; j < sequence2; j++) {
                    result2.insertLast((*it).keyNode, (*it).infoNode);
                    ++it;
                }
            }

            for (int l = 0; l < rep2-rep1; l++) {
                for(int j = 0; j < sequence2; j++) {
                    result2.insertLast((*it).keyNode, (*it).infoNode);
                    ++it;
                }
            }
        } else {
            for(int k = 0; k < rep1; k++) {
                for(int i = 0; i < sequence1; i++) {
                    result1.insertLast((*it).keyNode, (*it).infoNode);
                    ++it;
                }

                for(int j = 0; j < sequence2; j++) {
                    result2.insertLast((*it).keyNode, (*it).infoNode);
                    ++it;
                }
            }
        }
    } else {
        if(rep1 > rep2) {
            for(int k = 0; k < rep2; k++) {
                for(int i = 0; i < sequence1; i++) {
                    result1.insertLast((*it).keyNode, (*it).infoNode);
                    --it;
                }

                for(int j = 0; j < sequence2; j++) {
                    result2.insertLast((*it).keyNode, (*it).infoNode);
                    --it;
                }
            }

            for (int l = 0; l < rep1-rep2; l++) {
                for(int i = 0; i < sequence1; i++) {
                    result1.insertLast((*it).keyNode, (*it).infoNode);
                    --it;
                }
            }

        } else if(rep1 < rep2) {
            for(int k = 0; k < rep1; k++) {
                for(int i = 0; i < sequence1; i++) {
                    result1.insertLast((*it).keyNode, (*it).infoNode);
                    --it;
                }

                for(int j = 0; j < sequence2; j++) {
                    result2.insertLast((*it).keyNode, (*it).infoNode);
                    --it;
                }
            }
            for (int l = 0; l < rep2-rep1; l++) {
                for(int j = 0; j < sequence2; j++) {
                    result2.insertLast((*it).keyNode, (*it).infoNode);
                    --it;
                }
            }
        } else {
            for(int k = 0; k < rep1; k++) {
                for(int i = 0; i < sequence1; i++) {
                    result1.insertLast((*it).keyNode, (*it).infoNode);
                    --it;
                }

                for(int j = 0; j < sequence2; j++) {
                    result2.insertLast((*it).keyNode, (*it).infoNode);
                    --it;
                }
            }
        }
        
    }       

}
#endif