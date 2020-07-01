#ifndef RING_H
#define RING_H
 
#include <iostream>
 
using namespace std;
 
template <typename key, typename info>
class Ring {
    private:
        struct Node {
            key keyNode;
            info infoNode;
            Node *next;
            Node *prev;
        };
        Node *any;
        int size;
        void copyAll(const Ring<key,info> &other);
        void deleteAll();
    public:
        Ring();
        ~Ring();
        Ring(const Ring<key,info> &other);
        const Ring<key,info> &operator=(const Ring<key,info> &other);
        void insertFirst(const key &keyNew, const info &infoNew);
        void insertLast(const key &keyNew, const info &infoNew);
        bool insertAfter(const key &keyAfter, int occurence, const key &keyNew, const info &infoNew);
        bool insertBefore(const key &keyBefore, int occurence, const key &keyNew, const info &infoNew);
        bool removeFirst();
        bool removeLast();
        bool removeElement(const key &keyRemove, int occurence);
        bool removeAllKeys(const key &keyRemove);
        bool findElement(const key &keyFind, int occurence);
        int getSize();
        bool isEmpty() const;
        void destroyRing();
        void print();
        void reversePrint();
        class ConstIterator {
            private:
                Node *current;
            public:
                ConstIterator();
                ConstIterator(Node *ptr);
                Node& operator*() const;
                bool operator ==(const ConstIterator& right) const;
                bool operator !=(const ConstIterator& right) const;
                ConstIterator& operator++();
                ConstIterator& operator--();
                ConstIterator& operator+=(int n);
                ConstIterator& operator-=(int n);
                ConstIterator(const ConstIterator& other);
        };
        class Iterator {
            private:
                Node *curr;
            public:
                Iterator() {curr = NULL;}
                Node& operator*() {return *curr;}
                bool operator ==(const Iterator& right) {return (curr == right.curr);}
                bool operator !=(const Iterator& right) {return (curr != right.curr);}
                Iterator& operator++() {curr = curr->next; return *this;}
                Iterator& operator--() {curr = curr->prev; return *this;}
                Iterator(const ConstIterator& other);
        };
        ConstIterator begin() const;
        ConstIterator end() const;
 
        Iterator iBegin() {return any;}
        Iterator iEnd() {return any->prev;}
};
 
template <typename key, typename info>
Ring<key,info>::Ring() {
    any = NULL;
    size = 0;
}
 
template <typename key, typename info>
Ring<key, info>::~Ring() {
    deleteAll();
}
 
template <typename key, typename info>
Ring<key,info>::Ring(const Ring<key, info> &other) {
    any = NULL;
    copyAll(other);
}
 
 
template <typename key, typename info>
const Ring<key, info> &Ring<key,info>::operator =(const Ring<key, info> &other) {
    if(this != other) {
        copyAll(other);
    }
    return *this;
}
 
template <typename key, typename info>
void Ring<key,info>::insertFirst(const key& keyNew, const info& infoNew) {
    Node *newNode = new Node;
    newNode->keyNode = keyNew;
    newNode->infoNode = infoNew;
    if((*this).begin() == NULL) {
        any = newNode;
        newNode->next = any;
        newNode->prev = any;
        size++;
        return;
    } 
    Node *temp = any->prev;
    newNode->next = any;
    newNode->prev = temp;
    any->prev = newNode;
    temp->next = newNode;
    any = newNode;
    size++;
}
 
template <typename key, typename info>
void Ring<key,info>::insertLast(const key& keyNew, const info& infoNew) {
    Node *newNode = new Node;
    newNode->keyNode = keyNew;
    newNode->infoNode = infoNew;
    if((*this).begin() == NULL) {
        any = newNode;
        newNode->next = any;
        newNode->prev = any;
    } else {
        any->prev->next = newNode;
        newNode->next = any;
        newNode->prev = any->prev;
        any->prev = newNode;
    }
    size++;
}
 
template <typename key, typename info>
bool Ring<key,info>::insertAfter(const key &keyAfter, int occurence, const key &keyNew, const info &infoNew) {
    bool result = false;
    int count = 0;
    Node *temp = any;
    if(size == 1 && any->keyNode == keyNew && occurence == 1) {
        insertLast(keyNew, infoNew);
    } else {
        if(findElement(temp->keyNode, occurence)) {
            for(int i = 0; i < size; i++) {
                if(temp->keyNode == keyAfter) {
                    count++;
                } 
                if(count == occurence) {
                    result = true;
                    break;
                }
                temp = temp->next;
            } 
            if(temp->next == any) {
               insertLast(keyNew, infoNew);
            } else {
                Node *newNode = new Node;
                newNode->keyNode = keyNew;
                newNode->infoNode = infoNew;
                Node *ptr = temp->next;
                temp->next = newNode;
                newNode->next = ptr;
                newNode->prev = temp;
                ptr->prev = newNode;
                size++;
           }
        } else {
            result = false;
        }
    }
    return result;
}
 
template <typename key, typename info>
bool Ring<key,info>::insertBefore(const key &keyBefore, int occurence, const key &keyNew, const info &infoNew) {

}
 
template <typename key, typename info>
bool Ring<key,info>::removeFirst() {
    bool result; 
    if(isEmpty()) {
        result = false;
    } else if(size == 1){
        delete any;
        any = NULL;
        size = 0;
        result = true;
    } else {
        Node *temp = any;
        any = any->next;
        temp->prev->next = temp->next;
        any->prev = temp->prev;
        delete temp;
        size--;
        result = true;
    }
    return result;
}
 
template <typename key, typename info>
bool Ring<key,info>::removeLast() {
    bool result;
    if(isEmpty()) {
        result = false;
    } else if(size == 1){
        delete any;
        any = NULL;
        size = 0;
        result = true;
    }else {
        Node *temp = any->prev;
        temp->prev->next = temp->next; 
        any->prev = temp->prev;
        delete temp;
        size--;
        result = true;
    }
    return result;
}
 
template <typename key, typename info>
bool Ring<key, info>::removeElement(const key &keyRemove, int occurence) {
    bool result = false;
    int count = 0;
    Ring<key,info>::ConstIterator itr = (*this).begin();
    Node *temp = any;
    if(size == 1 && (*itr).keyNode == keyRemove && occurence == 1) {
        delete any;
        size = 0;
        any = NULL;
        result = true;
    } else {
        if(findElement(keyRemove, occurence)) {
            for(int i = 0; i < size; i++) {
                if(temp->keyNode == keyRemove) {
                    count++;
                } 
                if(count == occurence) {
                    result = true;
                    break;
                }
                ++itr;
                temp = temp->next;
            } 
            if(temp == any) {
                removeFirst();
            } else if(temp->next == any) {
               removeLast();
            } else {
                Node *ptr = temp->next;
                temp->prev->next = ptr;
                ptr->prev = temp->prev;
                delete temp; 
                size--;
           }
        } else {
            result = false;
        }
    }
}
 
template <typename key, typename info>
bool Ring<key, info>::removeAllKeys(const key &keyRemove) {
    bool result;
    int count = 0;
    Ring<key,info>::ConstIterator itr = (*this).begin();
    if(isEmpty()) {
        result = false;
    } else if(size == 1 && (*itr).keyNode == keyRemove) {
        delete any;
        size = 0;
        any = NULL;
        result = true;
    } else {
        for(int i = 0; i < size; i++) {
            if((*itr).keyNode == keyRemove) {
                count++;
            }
            ++itr;
        }
        if(count != 0) {
            for(int j = 0; j < count; j++) {
                removeElement(keyRemove, 1);
            }
            result = true;
        } else {
            result = false;
        }
    } 
    return result;
}
 
template <typename key, typename info>
bool Ring<key, info>::findElement(const key &keyFind, int occurence) {
    int count = 0;
    bool found = false;
    Ring<key,info>::ConstIterator itr = (*this).begin();
    do {
       if((*itr).keyNode == keyFind) {
           count++;
       }
        if(count == occurence) {
            found = true;
            break;
        }
        ++itr;
    } while(itr != (*this).begin() || found != true);
    return found;
}
 
template <typename key, typename info>
int Ring<key,info>::getSize() {
    return size;
}
 
template <typename key, typename info>
bool Ring<key,info>::isEmpty() const {
    bool result = false;
    if(size == 0) {
        result = true;
    }
    return result;
}
 
template <typename key, typename info>
void Ring<key,info>::destroyRing() {
    deleteAll();
}
 
 
template <typename key, typename info>
void Ring<key,info>::deleteAll() {
    int count = size;
    for(int i = 0; i<count; i++) {
        removeFirst();
    }    
    any = NULL;
    size = 0;
}
 
template <typename key, typename info>
void Ring<key,info>::copyAll(const Ring<key,info> &other) {
    Node *newNode;
    Node *current;
    Node *temp;
 
    if(any != NULL) {
        deleteAll();
    }
 
    if(other.any == NULL) {
        any = NULL;
        size = 0;
    } else {
        current = other.any;
 
        size = other.size;
 
        any = new Node;
        any->keyNode = current->keyNode;
        any->infoNode = current->infoNode;
        any->next = NULL;
        any->prev = NULL;
        temp = any;
        current = current->next;
 
        for(int i = 0; i < other.size-1; i++) {
            newNode = new Node;
            newNode->infoNode = current->infoNode;
            newNode->keyOfElement = current->keyOfElement;
            newNode->occurence = current->occurence;
            newNode->next = NULL;
            temp->next = newNode;
            newNode->prev = temp;
            temp = newNode;
            current = current->next;
        }
        temp->next = any;
        any->prev = temp;
    }
 
}
 
template <typename key, typename info>
void Ring<key,info>::print() {
    typename Ring<key,info>::ConstIterator itr = (*this).begin();
    if(this->isEmpty()) {
        cout << "Ring is Empty!" << endl;
    } else {
        for(int i = 0; i < size; i++) {
            cout << (*itr).keyNode << " " << (*itr).infoNode << endl;
            ++itr;
        }
    }
}
 
template <typename key, typename info>
void Ring<key,info>::reversePrint() {
    typename Ring<key,info>::ConstIterator itr = (*this).end();
    if(this->isEmpty()) {
        cout << "Ring is Empty!" << endl;
    } else {
        for(int i = 0; i < size; i++) {
            cout << (*itr).keyNode << " " << (*itr).infoNode << endl;
            --itr;
        }
    }
}
 
 
 
//ConstIterator
template <typename key, typename info>
typename Ring<key,info>::ConstIterator Ring<key,info>::begin() const {
    return any;
}
 
template <typename key, typename info>
typename Ring<key,info>::ConstIterator Ring<key,info>::end() const {
    return any->prev;
}
 
template <typename key, typename info>
Ring<key,info>::ConstIterator::ConstIterator() {
    current = NULL;
}
 
template <typename key, typename info>
Ring<key, info>::ConstIterator::ConstIterator(Node *ptr) {
    current = ptr;
}
 
template <typename key, typename info>
typename Ring<key,info>::Node& Ring<key,info>::ConstIterator::operator*() const {
    return *current;
}
 
template <typename key, typename info>
typename Ring<key,info>::ConstIterator& Ring<key, info>::ConstIterator::operator++() {
    current = current->next;
    return *this;
}
 
template <typename key, typename info>
typename Ring<key,info>::ConstIterator& Ring<key, info>::ConstIterator::operator--() {
    current = current->prev;
    return *this;
}
 
template <typename key, typename info>
bool Ring<key,info>::ConstIterator::operator ==(const ConstIterator& right) const {
    return(current == right.current);
}
 
template <typename key, typename info>
bool Ring<key,info>::ConstIterator::operator !=(const ConstIterator& right) const {
    return(current != right.current);
}
 
template <typename key, typename info>
Ring<key,info>::ConstIterator::ConstIterator(const ConstIterator& other) {
    current = other.current;
}
 
template <typename key, typename info>
typename Ring<key,info>::ConstIterator& Ring<key,info>::ConstIterator::operator+=(int x) {
    for(int i = 0; i < x; i++) {
        current = current->next;
    }
    return *this;
}
 
template <typename key, typename info>
typename Ring<key,info>::ConstIterator& Ring<key,info>::ConstIterator::operator-=(int x) {
    for(int i = 0; i < x; i++) {
        current = current->prev;
    }
    return *this;
}
 
 
 
 
 
 
 

 
#endif

