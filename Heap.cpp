#include <iostream>
#include "CircularDynamicArray.cpp"
using namespace std;

template <typename keytype>
class Heap {
    private:
        CircularDynamicArray<keytype> *heap;
        void buildHeap(CircularDynamicArray<keytype> *heap, int s) {
            int v = (s / 2) - 1;
            for (int i = v; i >= 0; i--) {
                heapify(heap, s, i);
            }
        }
        void heapify(CircularDynamicArray<keytype> *heap, int s, int index) {
            int l = left(index);
            int r = right(index);

            int smallest = index;

            if (l < s && heap->operator[](l) < heap->operator[](smallest)) {
                smallest = l;
            }

            if (r < s && heap->operator[](r) < heap->operator[](smallest)) {
                smallest = r;
            }

            if (smallest != index) { 
                keytype temp = heap->operator[](index);
                heap->operator[](index) = heap->operator[](smallest);
                heap->operator[](smallest) = temp;
                heapify(heap, s, smallest); 
            }
        }
        int parent(int p) {
            return (p - 1) / 2;

        }
        int left(int l) {
            return (2*l + 1); 
        }
        int right(int r) {
            return (2*r + 2);
        }
    public:
        Heap() {
            this->heap = new CircularDynamicArray<keytype>();
        }
        Heap(keytype k[], int s) {
            this->heap = new CircularDynamicArray<keytype>();
            for (int i = 0; i < s; i++) {
                this->heap->addEnd(k[i]);
            } 
            buildHeap(this->heap, s);
        }
        ~Heap() {
            delete this->heap;
        }

        Heap<keytype> operator=(Heap<keytype>& x) {
           this->heap = x.heap; 
           return *this;
        }
        Heap(Heap<keytype> &x) {
            this->heap = x.heap; 
        }

        keytype peekKey() {
            return this->heap->operator[](0);
        }
        keytype extractMin() {
            keytype smallest = this->heap->operator[](0);
            heap->operator[](0) = heap->operator[](heap->length()-1);
            this->heap->delEnd();
            heapify(this->heap, this->heap->length(), 0);
            return smallest;
        }

        void insert(keytype k) {
            heap->addEnd(k);
            int curr = heap->length() - 1;
            while (curr > 0 && heap->operator[](parent(curr)) > heap->operator[](curr)) {
                keytype temp = heap->operator[](parent(curr));
                heap->operator[](parent(curr)) = heap->operator[](curr);
                heap->operator[](curr) = temp;
                curr = parent(curr);
            }
        }
        void printKey() {
            if (this->heap->length() > 0) {
                for (int i = 0; i < this->heap->length(); i++) {
                    cout << this->heap->operator[](i) << " ";
                }
                cout << endl;
            }        
        }
};