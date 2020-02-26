#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
using namespace std;

template <typename key, typename info>
class Sequence {
    private:
        struct Element {
            key keyOfElement;
            info infoOfElement;
            int occurence;
            Element *next;
        };
        int numberOfElements;
        void copySequence(const Sequence<key, info>& s1);
        void destroyList();  
        Element *head;
        Element *last;
    public:
        Sequence();   
        ~Sequence();  
        Sequence(const Sequence<key, info>& s1);  
        const Sequence<key,info>& operator= (const Sequence<key, info>& otherSequence); 
        void insertFirst(const key& keyOfNewElement, const info& infoOfNewElement);  
        void insertAfter(const key& keyAfter, const info& infoAfter, int which, const key& keyNew, const info& infoNew);
        void insertBefore(const key& keyBefore, const info& infoBefore, int which, const key& keyNew, const info& infoNew);
        void removeFirst();
        void removeLast(); 
        void insertLast(const key& keyOfNewElement, const info& infoOfNewElement);  
        void removeElement(const key& keyOfRemove, const info& infoOfRemove, int which);  
        bool findElement(const key& keyFind, const info& infoFind, int which);    
        int count(const key& keyOfCount, const info& infoOfCount);  
        int getNumberOfElements() const;    
        bool operator ==(const Sequence<key,info> &otherSequence);
      //  Element *getHead();
        key getKeyAtPosition(int position) const;
        info getInfoAtPosition(int position) const;   
        void deleteList();
        bool isEmpty() const;  
        void print(); 
};


template <typename key, typename info>
Sequence<key, info>::Sequence() {
    head = NULL;
    last = NULL;
    numberOfElements = 0;
}

template <typename key, typename info>
Sequence<key, info>::~Sequence() {
    destroyList();
}

template <typename key, typename info>
void Sequence<key, info>::copySequence(const Sequence<key,info>& s1) {
    Element *newElement;
    Element *current;

    if(head != NULL) {
        destroyList();
    }

    if(s1.head == NULL) {
        head = NULL;
        numberOfElements = 0;
    } else {
        current = s1.head;

        numberOfElements = s1.numberOfElements;

        head = new Element;
        head->keyOfElement = current->keyOfElement;
        head->infoOfElement = current->infoOfElement;
        head->occurence = current->occurence;
        head->next = NULL;
        last = head;
        current = current->next;

        while (current != NULL) {
            newElement = new Element;
            newElement->infoOfElement = current->infoOfElement;
            newElement->keyOfElement = current->keyOfElement;
            newElement->occurence = current->occurence;
            newElement->next = NULL;
            last->next = newElement;
            last = newElement;
            current = current->next;
        }
    }
}

template <typename key, typename info>
bool Sequence<key, info>::operator == (const Sequence<key, info> &otherSequence) {
    if (numberOfElements != otherSequence.numberOfElements) {
        return false;
    }
    Element *current = this->head;
    Element *temp = otherSequence.head;
    while(current != NULL) {
        if((current->keyOfElement != temp->keyOfElement) || (current->infoOfElement != temp->infoOfElement) || (current->occurence != temp->occurence)) {
            return false;
        }
        current = current->next;
        temp = temp->next;
    }
}

template <typename key, typename info>
const Sequence<key,info>& Sequence<key,info>::operator =(const Sequence<key,info>& otherSequence) {
    copySequence(otherSequence);
    return *this;
}


template <typename key, typename info>
Sequence<key, info>::Sequence(const Sequence<key, info>& s1) {
    head = NULL;
    copySequence(s1);
}

template <typename key, typename info>
void Sequence<key, info>::insertFirst(const key &keyOfNewElement, const info& infoOfNewElement) {
    Element *newNode;
    newNode = new Element;
    newNode->keyOfElement = keyOfNewElement;
    newNode->infoOfElement = infoOfNewElement;
    newNode->next = head;
    head = newNode;
    numberOfElements++;
    newNode->occurence = 1;
    Element *temp = head->next;
    while(temp != NULL) {
        if(temp->keyOfElement == keyOfNewElement && temp->infoOfElement == infoOfNewElement) {
            temp->occurence++;
        }
        temp = temp->next;
    }
    if(head->next == NULL)
    {
        last = head;
    }
    numberOfElements++;
}

template <typename key, typename info>
void Sequence<key, info>::insertLast(const key& keyOfNewElement, const info& infoOfNewElement) {
    Element *newNode = new Element;
    newNode->keyOfElement = keyOfNewElement;
    newNode->infoOfElement = infoOfNewElement;
    newNode->next = NULL;
    if(head == NULL) {
        head = newNode;
    } else {
        Element *temp = head;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        last = newNode;
    }
    newNode->occurence = count(keyOfNewElement, infoOfNewElement);
    numberOfElements++;
}

template <typename key, typename info>
void Sequence<key, info>::insertAfter(const key& keyAfter, const info& infoAfter, int which, const key& keyNew, const info& infoNew) {
    Element *current = head;
    int counter = 0;
    if(head == NULL) {
        cout << "Sequence is empty, so there is no element to insert after this!" << endl;
    } else if(!findElement(keyAfter, infoAfter, which)) {
        cout << "There is no such element in the sequence!" << endl;
    } else {   
        while(current != NULL) {
            if((current->keyOfElement == keyAfter) && (current->infoOfElement == infoAfter) && (current->occurence == which)) {
                break;
            }
            current = current->next;
        }
        Element *newNode = new Element;
        newNode->keyOfElement = keyNew;
        newNode->infoOfElement = infoNew;
        newNode->occurence = 0;
        newNode->next = current->next;
        current->next = newNode;
        Element *temp = head;
        while(temp->occurence != 0) {
            if(temp->keyOfElement == keyNew && temp->infoOfElement == infoNew) {
                counter++;
            }
            temp = temp->next;
        }
        while(temp != NULL) {
            if(temp->keyOfElement == keyNew && temp->infoOfElement == infoNew) {
                temp->occurence++;
            }
            temp = temp->next;
        }

        if(counter == 0) {
            newNode->occurence = 1;
        } else {
            newNode->occurence = counter+1;
        }

        if(newNode->next == NULL) {
            last = newNode;
        }
    }
}

template <typename key, typename info>
void Sequence <key, info>::insertBefore(const key& keyBefore, const info& infoBefore, int which, const key& keyNew, const info& infoNew) {
    Element *prev;
    Element *current = head;
    int counter = 0;
    if(head == NULL) {
        cout << "Sequence is empty, so there is no such element to insert before this!" << endl;
    } else if(!findElement(keyBefore, infoBefore, which)) {
        cout << "There is no such element in the sequence" << endl;
    } else {
        while (current != NULL) {
            if(current->keyOfElement == keyBefore && current->infoOfElement == infoBefore && current->occurence == which) {
                break;
            }
            prev = current;
            current = current->next;
        }
        Element *newNode = new Element;
        newNode->keyOfElement = keyNew;
        newNode->infoOfElement = infoNew;
        newNode->occurence = 0;
        newNode->next = current;
        if(current == head) {
            newNode->occurence = 1;
            head = newNode;
            numberOfElements++;
            Element *temp = head;
            temp = temp->next;
            while(temp != NULL) {
                if(temp->keyOfElement == keyNew && temp->infoOfElement == infoNew) {
                    temp->occurence++;
                }
                temp = temp->next;
            }
        } else {
            prev->next = newNode;
            numberOfElements++;
            Element *temp = head;
            while(temp->occurence != 0) {
                if (temp->keyOfElement == keyNew && temp->infoOfElement == infoNew) {
                    counter++;
                }
                temp = temp->next;
            }
            if(counter == 0) {
                newNode->occurence = 1;
            } else {
                newNode->occurence = counter;
            }
            temp = temp->next;
            while(temp != NULL) {
                if (temp->keyOfElement == keyNew && temp->infoOfElement == infoNew) {
                    temp->occurence++;
                }
                temp = temp->next;
            }
        }
    }
}

template <typename key, typename info>
void Sequence<key, info>::removeElement(const key& keyOfRemove, const info& infoOfRemove, int which) {
    Element *temp = head;
    Element *prev = temp;
    if(head == NULL) {
        cout << "There is no element in the sequence";
    } else if(!findElement(keyOfRemove, infoOfRemove, which)) {
        cout << "There is no such element in the sequence!" << endl;
    } else {
        Element *current = head;
        while(current != NULL) {
            if((current->keyOfElement == keyOfRemove) && (current->infoOfElement == infoOfRemove) && (current->occurence > which)) {
                current->occurence--;
            }
            current = current->next;
        }

        while (temp != NULL) {
			if (temp->keyOfElement == keyOfRemove && temp->infoOfElement == infoOfRemove && temp->occurence == which) {
				if (temp->next == NULL)  {
					prev->next = NULL;
					delete temp;
					return;
				} else {
					prev->next = temp->next;
					delete temp;
					return;
				}
			}
			prev = temp;
			temp = temp->next;
		}
    }
}

template <typename key, typename info>
void Sequence<key, info>::removeFirst() {
    if(head == NULL) {
        cout << "Sequence is empty" << endl;
    } else {
        Element *temp = head;
        while(temp != NULL) {
            if(temp->keyOfElement == head->keyOfElement && temp->infoOfElement == head->infoOfElement) {
                temp->occurence--;
            }
            temp = temp->next;
        }
        Element *current = head;
        head = head->next;
        numberOfElements--;
        delete current;
    }
}

template <typename key, typename info>
void Sequence<key, info>::removeLast() {
    Element *prev;
    Element *current;
    if(head == NULL) {
        cout << "Sequence is empty" << endl;
    } else if(head->next == NULL) {
        current = head;
        head = NULL;
        delete current;
    } else {
        current = head;
        while(current->next) {
            prev = current;
            current = current->next;
        }
        prev->next = NULL;
        numberOfElements--;
        delete current;
    }
}

template <typename key, typename info>
bool Sequence<key, info>::findElement(const key& keyFind, const info& infoFind, int which) {
    bool found = false;
    Element *current = head;

    while(current != NULL) {
        if(current->keyOfElement == keyFind && current->infoOfElement == infoFind && current->occurence == which) {
            found = true;
            break;
        }
        current = current->next;
    }
    return found;
}

template <typename key, typename info>
int Sequence<key, info>::getNumberOfElements() const {
    return numberOfElements;
}

template <typename key, typename info>
bool Sequence<key, info>::isEmpty() const {
    bool status = false;
    if(numberOfElements == 0) {
        status = true;
    }
    return status;
}

template <typename key, typename info>
int Sequence<key, info>::count(const key& keyOfCount, const info& infoOfCount) {
    Element *current = head;
    int count = 0;
    while (current != NULL) {
        if (current->keyOfElement == keyOfCount && current->infoOfElement == infoOfCount) {
            count++;
        }
        current = current->next;
    }

    return count;
}

template <typename key, typename info>
void Sequence<key, info>::print() {
    Element *current;
    current = head;
    if(head == NULL) {
        cout << "Sequence is empty" << endl;
    }
    
    while(current != NULL) {
        cout << current->keyOfElement << " " << current->infoOfElement << " " << current->occurence << endl;
        current = current->next;
    }
}

template <typename key, typename info>
void Sequence<key, info>::destroyList() {
    Element *temp;

    while(head != NULL) {
        temp = head;
        head = head->next;
        delete temp;
    }
    numberOfElements = 0;
}

template <typename key, typename info>
key Sequence <key, info>::getKeyAtPosition(int position) const {
    Element *current = head;
    int i = 0;
    if(head == NULL) {
        cout << "Sequence is empty" << endl;
    } else {
        while (i < position && current != NULL) {
            current = current->next;
            i++;
        }
        return current->keyOfElement;
    }
}

template <typename key, typename info>
info Sequence <key, info>::getInfoAtPosition(int position) const {
    Element *current = head;
    int i = 0;
    if(head == NULL) {
        cout << "Sequence is empty" << endl;
    } else {
        while (i < position && current != NULL) {
            current = current->next;
            i++;
        }
        return current->infoOfElement;
    }
}

template <typename key, typename info>
void Sequence <key, info>::deleteList() {
    destroyList();
}

#endif