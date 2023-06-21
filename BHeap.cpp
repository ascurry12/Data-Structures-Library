#include <iostream>
#include "CircularDynamicArray.cpp"
using namespace std;

template <typename keytype>
struct Node {
    Node *parent, *sibling, *child;
    keytype key;
    int degree;

    Node() {
        parent = nullptr;
        sibling = nullptr;
        child = nullptr;
        degree = -1;
    }
    Node(keytype k) {
        parent = nullptr;
        sibling = nullptr;
        child = nullptr;
        key = k;
        degree = 0;
    }
    ~Node() {

    }
};

template <typename keytype>
class BHeap {
    private:
        Node<keytype> *bHeap;
        int rootCount;
        keytype minKey;

        bool isEmpty() {
            if (rootCount > 0) {
                return false;
            }
            return true;
        }
        void insertHelper(Node<keytype> *heap, Node<keytype> *newNode) {
            Node<keytype> *temp = heap;
            if (isEmpty()) {
                temp->sibling = newNode;
                rootCount++;
                minKey = newNode->key;
                return;
            }
            else {
                newNode->sibling = temp->sibling;
                temp->sibling = newNode;
                rootCount++;
            }
            return;
        }
        void insertMerge(Node<keytype> *firstNode, Node<keytype> *secondNode) {
            secondNode->sibling = firstNode->child;
            firstNode->child = secondNode;
            firstNode->degree++;
            rootCount--;
        }
        void findMin(Node<keytype> *node) {
            if (node != nullptr) {
                Node<keytype> *temp = node;
                keytype min = node->key;
                while (temp->sibling != nullptr) {
                    if (min >= temp->sibling->key) {
                    min = temp->sibling->key;

                }
                temp = temp->sibling;
                }
                minKey = min;
            }

        }
        void mergeHelper(Node<keytype> *node) {
            Node<keytype> *curr = bHeap->sibling;
            Node<keytype> *curr2 = node;
            Node<keytype> *temp = nullptr;
            Node<keytype> *temp2 = nullptr;

            if (curr->degree <= curr2->degree) {
                temp = curr;
                curr = curr->sibling;
            }
            else {
                temp = curr2;
                curr2 = curr2->sibling;
            }

            temp2 = temp;

            while (curr != nullptr && curr2 != nullptr) {
                if (curr->degree <= curr2->degree) {
                    temp->sibling = curr;
                    curr = curr->sibling;
                }
                else {
                    temp->sibling = curr2;
                    curr2 = curr2->sibling;
                }

                temp = temp->sibling;
            }

            if (curr != nullptr) {
                while (curr != nullptr) {
                    temp->sibling = curr;
                    curr = curr->sibling;
                    temp = temp->sibling; 
                }
            }

            if (curr2 != nullptr) {
                while (curr2 != nullptr) {
                    temp->sibling = curr2;
                    curr2 = curr2->sibling;
                    temp = temp->sibling; 
                }
            }

            if (rootCount > 1) {
                updateDegree(this->bHeap);
            }
        }
        void updateDegree(Node<keytype> *node) {
            Node<keytype> *temp2 = node;
            Node<keytype> *prev = nullptr;
            Node<keytype> *sib = node->sibling;

            while (sib != nullptr) {
                if ((temp2->degree != sib->degree) || (sib->sibling != nullptr && temp2->degree == sib->sibling->degree)) {
                    prev = temp2;
                    temp2 = sib;
                }
                else {
                    if (temp2->key <= sib->key) {
                        temp2->sibling = sib->sibling;
                        insertMerge(temp2, sib);
                    }
                    else {
                        if (prev == nullptr) {
                            node = sib;
                        }
                        else {
                            prev->sibling = sib;
                        }
                        insertMerge(sib, temp2);
                        temp2 = sib;
                    }
                    
                }
            }
        }    
        void printHelper(Node<keytype> *heap) {
            Node<keytype> *temp = heap->sibling;
            while (temp != nullptr) {
                if (temp == nullptr) {
                    break;
                }
                // store sibling 
                Node<keytype> *tempSib = temp->sibling;
                // "cut off" rest of tree (rest of tree stored in tempSib)
                temp->sibling = nullptr;
                cout << "B" << temp->degree << endl;
                printHeap(temp);   
                cout << endl << endl;  
                // replace rest of tree after traversal, move on to next node
                temp->sibling = tempSib;
                temp = tempSib;
            }
        }
        void printHeap(Node<keytype> *heap) {
            Node<keytype> *temp = heap;
            if (temp != nullptr) {
                cout << temp->key << " ";
                printHeap(temp->child);
                printHeap(temp->sibling); 
            }
        }
    public:
        BHeap() {
            this->bHeap = new Node<keytype>();
            rootCount = 0;
        }
        BHeap(keytype k[], int s) {
            this->bHeap = new Node<keytype>();
            rootCount = 0;
            for (int i = 0; i < s; i++) {
                this->insert(k[i]);
            }
        }
        ~BHeap() {

        }

        BHeap<keytype> operator=(BHeap<keytype>& x) {
            this->bHeap = x.bHeap;
            this->rootCount = x.rootCount;
            this->minKey = x.minKey;

            return *this;
        }
        BHeap(BHeap<keytype> &x) {
            this->bHeap = x.bHeap;
            this->rootCount = x.rootCount;
            this->minKey = x.minKey;
        }

        keytype peekKey() {
            return this->minKey;
        }
        keytype extractMin() {
            if (this->bHeap->sibling != nullptr) {
                Node<keytype> *temp = this->bHeap->sibling;
                Node<keytype> *prev = nullptr;
                Node<keytype> *prevNode = nullptr;
                Node<keytype> *delNode = nullptr;
                keytype currMin = temp->key;
                while (temp != nullptr) {
                    if (currMin >= temp->key) {
                        currMin = temp->key;
                        prev = prevNode;
                        delNode = temp;
                    }
                    prevNode = temp;
                    temp = temp->sibling;
                }

                if (prev != nullptr && delNode->sibling != nullptr) {
                    prev->sibling = delNode->sibling;
                }
                else if (prev != nullptr && delNode->sibling == nullptr) {
                    prev->sibling = nullptr;
                }
                else if (prev == nullptr && delNode->sibling != nullptr) {
                    this->bHeap->sibling = delNode->sibling;
                }
                else if (prev == nullptr && delNode->sibling == nullptr) {
                    this->bHeap->sibling = nullptr;
                }

                keytype min = delNode->key;

                if (delNode->child != nullptr) {
                    BHeap<keytype> H;
                    H.bHeap->sibling = delNode->child;

                    Node<keytype> *n = nullptr;
                    Node<keytype> *p = nullptr;
                    Node<keytype> *c = H.bHeap->sibling;
                    
                    while (c != nullptr) {
                        n = c->sibling;
                        c->sibling = p;
                        p = c;
                        c = n;
                    }
                    H.bHeap->sibling = p;
                    H.rootCount = delNode->degree;
                    merge(H);
                    delNode->child = nullptr;
                }
                findMin(this->bHeap->sibling);

                return min;
            }
            return 0;    
        }
        void insert(keytype k) {
            BHeap<keytype> newHeap;
            Node<keytype> *heapNode = new Node<keytype>(k);
            newHeap.bHeap->sibling = heapNode;
            merge(newHeap);
            findMin(this->bHeap->sibling);
        }
        void merge(BHeap<keytype> &H2) {
            Node<keytype> *curr = this->bHeap->sibling;
            Node<keytype> *curr2 = H2.bHeap->sibling;
            Node<keytype> *temp = nullptr;
            Node<keytype> *temp2 = nullptr;

            if (this->bHeap->sibling == nullptr) {
                this->bHeap->sibling = H2.bHeap->sibling;
                this->rootCount++;
            }
            else {
                if ((curr != nullptr && curr2 != nullptr) && (curr->degree <= curr2->degree)) {
                    temp = curr;
                    curr = curr->sibling;
                }
                else {
                    temp = curr2;
                    if (curr2 != nullptr) {
                        curr2 = curr2->sibling;
                    }
                }

                temp2 = temp;

                while (curr != nullptr && curr2 != nullptr) {
                    if (curr->degree <= curr2->degree) {
                        temp->sibling = curr;
                        curr = curr->sibling;
                    }
                    else {
                        temp->sibling = curr2;
                        curr2 = curr2->sibling;
                    }
                    temp = temp->sibling;
                }

                if (curr != nullptr && temp != nullptr) {
                    while (curr != nullptr) {
                        temp->sibling = curr;
                        curr = curr->sibling;
                        temp = temp->sibling; 
                    }
                }

                if (curr2 != nullptr) {
                    while (curr2 != nullptr) {
                        temp->sibling = curr2;
                        curr2 = curr2->sibling;
                        temp = temp->sibling; 
                    }
                }
                temp = temp2;

                Node<keytype> *prev  = nullptr;
                Node<keytype> *sib = temp->sibling;
                while (sib != nullptr) {
                    if ((temp->degree != sib->degree) || (sib->sibling != nullptr && temp->degree == sib->sibling->degree)) {
                        prev = temp;
                        temp = sib;
                    }
                    else {
                        if (temp->key <= sib->key) {
                            temp->sibling = sib->sibling;
                            insertMerge(temp, sib);
                        }
                        else {
                            if (prev == nullptr) {
                                temp2 = sib;
                            }
                            else {
                                prev->sibling = sib;
                            }
                            insertMerge(sib, temp);
                            temp = sib;
                        }
                        
                    }
                    sib = temp->sibling;
                }
                this->bHeap->sibling = temp2;
            }

            findMin(this->bHeap->sibling);
            
        }
        void printKey() {
            printHelper(this->bHeap);
        }

};