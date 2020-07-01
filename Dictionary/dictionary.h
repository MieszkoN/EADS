#include <iostream>

using namespace std;

template <typename key, typename info>
class Dictionary {
    private:
        struct AVLNode {
            key keyAVLNode;
            info infoAVLNode;
            AVLNode *left;
            AVLNode *right;
            int bFactor;
        };
        AVLNode *root;
        void destroy(AVLNode* &ptr);
        void copyDictionary(AVLNode* &copiedDictionaryRoot, AVLNode* otherDictionaryRoot);
        void inorder(AVLNode *ptr) const;
        void preorder(AVLNode *ptr) const;
        void postorder(AVLNode *ptr) const;
        int height(AVLNode *ptr) const;
        int maxx(int x, int y) const;
        int countNode(AVLNode *ptr) const;
        void removeFromDictionary(AVLNode* &ptr);
        void printDictionary(AVLNode* ptr, int space);
        void removeFromAVL(AVLNode* &ptr);
        void rotateToLeft(AVLNode* &root);
        void rotateToRight(AVLNode* &root);
        void balanceFromLeft(AVLNode* &root);
        void balanceFromRight(AVLNode* &root);
        void insertToAVL(AVLNode* &root, AVLNode *newNode, bool &isTaller);
        int getBalance(AVLNode* ptr);
        void setBalance(AVLNode *ptr);
    public:
        Dictionary();
        ~Dictionary();
        Dictionary(const Dictionary<key,info> &other);
        const Dictionary<key, info>& operator=(const Dictionary<key,info>& otherDictionary);
        void remove(const key &keyRemove);
        bool findElement(const key &keyFind);
        void insert(const key &keyNew, const info &infoNew);
        void inorderTraversal();
        void preorderTraversal();
        void postorderTraversal();
        int dictionaryHeight();
        int dictionaryNodeCount();
        int dictionaryLeavesCount();
        void destroyDictionary();
        void print();
        bool isEmpty() const;
};

template <typename key, typename info>
Dictionary<key,info>::Dictionary() {
    root = NULL;
}

template <typename key, typename info>
Dictionary<key,info>::~Dictionary() {
    destroyDictionary();
}

template <typename key, typename info>
void Dictionary<key,info>::destroyDictionary() {
    destroy(root);
}

template <typename key, typename info>
void Dictionary<key,info>::destroy(AVLNode* &ptr) {
    if(ptr != NULL) {
        destroy(ptr->left);
        destroy(ptr->right);
        delete ptr;
        ptr = NULL;
    }
}

template <typename key, typename info>
void Dictionary<key,info>::copyDictionary(AVLNode* &copiedDictionaryRoot, AVLNode* otherDictionaryRoot) {
    if (otherDictionaryRoot == NULL) {
        copiedDictionaryRoot = NULL;
    } else {
        copiedDictionaryRoot = new AVLNode;
        copiedDictionaryRoot->keyAVLNode = otherDictionaryRoot->keyAVLNode;
        copiedDictionaryRoot->infoAVLNode = otherDictionaryRoot->infoAVLNode;
        copiedDictionaryRoot->bFactor = otherDictionaryRoot->bFactor;
        copyDictionary(copiedDictionaryRoot->left, otherDictionaryRoot->left);
        copyDictionary(copiedDictionaryRoot->right, otherDictionaryRoot->right);
    }
}

template <typename key, typename info>
Dictionary<key, info>::Dictionary(const Dictionary<key, info> &otherDictionary) {
    if(otherDictionary.root == NULL) {
        root = NULL;
    } else {
        copyDictionary(root, otherDictionary.root);
    }
}

template <typename key, typename info>
const Dictionary<key,info>& Dictionary<key,info>::operator=(const Dictionary<key,info> &otherDictionary) {
    if (this != &otherDictionary) {
        if (root != NULL) {
            destroy(root);
        }

        if(otherDictionary.root == NULL) {
            root = NULL;
        } else {
            copyDictionary(root, otherDictionary.root);
        }
    }
    return *this;
}

template <typename key,typename info>
void Dictionary<key,info>::rotateToLeft(AVLNode* &root) {
    AVLNode *ptr;

    if(root != NULL && root->right != NULL) {
        ptr = root->right;
        root->right = ptr->left;

        ptr->left = root;
        root = ptr;
    }
}

template <typename key,typename info>
void Dictionary<key,info>::rotateToRight(AVLNode* &root) {
    AVLNode *ptr;
    if(root != NULL && root->left != NULL) {
        ptr = root->left;
        root->left = ptr->right;

        ptr->right = root;
        root = ptr;
    }
}

template <typename key,typename info>
void Dictionary<key,info>::balanceFromLeft(AVLNode* &root) {
    AVLNode *ptr;
    AVLNode *wsk;
    ptr = root->left;
    switch(ptr->bFactor) {
        case -1:
            root->bFactor = 0;
            ptr->bFactor = 0;
            rotateToRight(root);
            break; 

        case 0:
            break;
        case 1:
            wsk = ptr->right;
            switch (wsk->bFactor) {
                case -1:
                    root->bFactor = 1;
                    ptr->bFactor = 0;
                    break;
                case 0:
                    root->bFactor = 0;
                    ptr->bFactor = 0;
                    break;
                case 1:
                    root->bFactor = 0;
                    ptr->bFactor = -1;
            }

            wsk->bFactor = 0;
            rotateToLeft(ptr);
            root->left = ptr;
            rotateToRight(root);
    }
}

template <typename key,typename info>
void Dictionary<key,info>::balanceFromRight(AVLNode* &root) {
    AVLNode *ptr;
    AVLNode *wsk;
    ptr = root->right;
    switch(ptr->bFactor) {
        case -1:
            wsk = ptr->left;
            switch (wsk->bFactor) {
                case -1:
                    root->bFactor = 0;
                    ptr->bFactor = 1;
                    break;
                case 0:
                    root->bFactor = 0;
                    ptr->bFactor = 0;
                    break;
                case 1:
                    root->bFactor = -1;
                    ptr->bFactor = 0;
            }

            wsk->bFactor = 0;
            rotateToRight(ptr);
            root->right = ptr;
            rotateToLeft(root);
            break;
        case 0:
            break;
        case 1:
            root->bFactor = 0;
            ptr->bFactor = 0;
            rotateToLeft(root);
    }    
}

template <typename key, typename info>
void Dictionary<key, info>::insertToAVL(AVLNode* &root, AVLNode *newNode, bool &isTaller) {
    if (root == NULL) {
        root = newNode;
        isTaller = true;
        return;
    } else if (root->keyAVLNode == newNode->keyAVLNode) {
        delete newNode;
        return;
    } else if (root->keyAVLNode > newNode->keyAVLNode) {
        insertToAVL(root->left, newNode, isTaller);

        if(isTaller)
            switch (root->bFactor) {
                case -1:
                    balanceFromLeft(root);
                    isTaller = false;
                    break;
                case 0:
                    root->bFactor = -1;
                    isTaller = true;
                    break;
                case 1:
                    root->bFactor = 0;
                    isTaller = false;
            }
        } else {
            insertToAVL(root->right, newNode, isTaller);

            if (isTaller)
                switch (root->bFactor) {
                    case -1:
                        root->bFactor = 0;
                        isTaller = false;
                        break;
                    
                    case 0:
                        root->bFactor = 1;
                        isTaller = true;
                        break;

                    case 1:
                        balanceFromRight(root);
                        isTaller = false;
                }
        }
}

template <typename key, typename info>
void Dictionary<key, info>::insert(const key &keyNew, const info &infoNew) {
    bool isTaller = false;
    AVLNode *newNode = new AVLNode;
    newNode->keyAVLNode = keyNew;
    newNode->infoAVLNode = infoNew;
    newNode->bFactor = 0;
    newNode->left = NULL;
    newNode->right = NULL;

    insertToAVL(root, newNode, isTaller);
}

template <typename key, typename info>
bool Dictionary<key, info>::findElement(const key &keyFind) {
    AVLNode *ptr = root;
    bool found = false;
    if(root == NULL) {
        return found;
    } else {
        while(ptr != NULL && !found) {
            if(ptr->keyAVLNode == keyFind) {
                found = true;
                break;
            } else {
                if(ptr->keyAVLNode > keyFind) {
                    ptr = ptr->left;
                } else {
                    ptr = ptr->right;
                }
            } 
        }
    }
    return found;
}

template <typename key, typename info>
void Dictionary<key, info>::remove(const key& keyRemove) {
    AVLNode *current;
    AVLNode *trailCurrent;
    bool found = false;
    bool result = false;
    bool isShorter = false;
    if(root == NULL) {
        return;
    } else {
        current = root;
        trailCurrent = root;

        while(current != NULL && !found) {
            if(current->keyAVLNode == keyRemove) {
                found = true;
                break;
            } else {
                trailCurrent = current;

                if(current->keyAVLNode > keyRemove) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
        }

        if(current == NULL) {
            return;
        } else if(found) {
            if(current == root) {
                removeFromAVL(root);
            } else if(trailCurrent->keyAVLNode > keyRemove) {
                removeFromAVL(trailCurrent->left);
            } else {
                removeFromAVL(trailCurrent->right);
            }
            result = true;
        }
        setBalance(root);
        int balance = getBalance(root);

        //Case 1
        if (balance > 1 &&  getBalance(root->right) >= 0)  {
            rotateToLeft(root);
            setBalance(root);
        }
    
        //Case 2
        if (balance > 1 &&  getBalance(root->right) < 0)  
        {  
            rotateToLeft(root->right);
            balanceFromRight(root);
            setBalance(root);
        }  
    
        //Case 3
        if (balance < -1 &&  getBalance(root->left) >= 0) {
            rotateToRight(root);
            setBalance(root);
        }

        //Case 4 
        if (balance < -1 &&  getBalance(root->left) < 0) {  
            balanceFromLeft(root);
        } 
    }
}

template <typename key, typename info>
void Dictionary<key, info>::removeFromAVL(AVLNode* &ptr) {
    AVLNode *current;
    AVLNode *trailCurrent;
    AVLNode *temp;
    if(ptr == NULL) {
        return;
    } else if(ptr->left == NULL && ptr->right == NULL) {
        temp = ptr;
        ptr = NULL;
        delete temp;
    } else if(ptr->left == NULL) {
        temp = ptr;
        ptr = temp->right;
        delete temp;
    } else if(ptr->right == NULL) {
        temp = ptr;
        ptr = temp->left;
        delete temp;
    } else {
        current = ptr->left;
        trailCurrent = NULL;

        while (current->right != NULL) {
            trailCurrent = current;
            current = current->right;
        }
        ptr->keyAVLNode = current->keyAVLNode;
        ptr->infoAVLNode = current->infoAVLNode;
        ptr->bFactor = current->bFactor;

        if(trailCurrent == NULL) {
            ptr->left = current->left;
        } else {
            trailCurrent->right = current->left;
        }

        delete current;
    }   
}

template <typename key, typename info>
int Dictionary<key, info>::getBalance(AVLNode* ptr) {
    if(ptr == NULL) {
        return 0;
    } else {
        return(height(ptr->right) - height(ptr->left));
    }
}


template <typename key, typename info>
void Dictionary<key, info>::inorderTraversal() {
    inorder(root);
}

template <typename key, typename info>
void Dictionary<key, info>::preorderTraversal() {
    preorder(root);
}

template <typename key, typename info>
void Dictionary<key, info>::postorderTraversal() {
    postorder(root);
}

template <typename key, typename info>
void Dictionary<key, info>::inorder(AVLNode *ptr) const {
    if(ptr != NULL) {
        inorder(ptr->left);
        cout << ptr->keyAVLNode << " ";
        inorder(ptr->right);
    }
}

template <typename key, typename info>
void Dictionary<key, info>::preorder(AVLNode *ptr) const {
    if(ptr != NULL) {
        cout << ptr->keyAVLNode << " ";
        preorder(ptr->left);
        preorder(ptr->right);
    }
}

template <typename key, typename info>
void Dictionary<key, info>::postorder(AVLNode *ptr) const {
    if(ptr != NULL) {
        postorder(ptr->left);
        postorder(ptr->right);
        cout << ptr->keyAVLNode << " ";
    }
}

template <typename key, typename info>
int Dictionary<key, info>::countNode(AVLNode *ptr) const {
    int count = 0;
    if(ptr != NULL) {
        count += countNode(ptr->left);
        count += countNode(ptr->right);
        count++;
    }
    return count;
}

template <typename key, typename info>
void Dictionary<key, info>::setBalance(AVLNode *ptr) {
    int count = 0;
    if(ptr != NULL) {
        setBalance(ptr->left);
        setBalance(ptr->right);
        ptr->bFactor = height(ptr->right) - height(ptr->left);
    }
}

template <typename key, typename info>
int Dictionary<key,info>::height(AVLNode *ptr) const{
    if(ptr == NULL) {
        return 0;
    } else {
        return 1 + maxx(height(ptr->left), height(ptr->right));
    }
}

template <typename key, typename info>
int Dictionary<key,info>::maxx(int x, int y) const {
    if (x >= y) {
        return x;
    } else {
        return y;
    }
}

template <typename key, typename info>
int Dictionary<key,info>::dictionaryHeight() {
    return height(root);
}

template <typename key, typename info>
bool Dictionary<key,info>::isEmpty() const{
    return (root == NULL);
}

template <typename key, typename info>
void Dictionary<key, info>::printDictionary(AVLNode* ptr, int space) {
    if(ptr == NULL) {
        return;
    }
    space += 12;

    printDictionary(ptr->right, space);
    cout << endl;

    for(int i = 12; i < space; i++) {
        cout << " ";
    }
    cout << ptr->keyAVLNode << endl;

    printDictionary(ptr->left, space);
}

template <typename key, typename info>
void Dictionary<key, info>::print() {
    printDictionary(root, 0);
}

template <typename key, typename info>
int Dictionary<key, info>::dictionaryNodeCount() {
    return countNode(root);
}