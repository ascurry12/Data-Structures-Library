#include <iostream>
using namespace std;

template <typename arraytype>
class CircularDynamicArray {
    private:
    bool reversed;
    arraytype outOfBounds; 

    int partition(arraytype arr[], int left, int right) {
        int i = left;
        int x = arr[(right + this->front + this->cap) % this->cap];
        for (int j = left; j <= right - 1; j++) {
            if (arr[(j + this->front + this->cap) % this->cap] <= x) {
                arraytype temp = arr[(i + this->front + this->cap) % this->cap]; // i
                arr[(i + this->front + this->cap) % this->cap] = arr[(j + this->front + this->cap) % this->cap]; // i, j
                arr[(j + this->front + this->cap) % this->cap] = temp; // j
                i++;
            }
        }
        arraytype temp2 = arr[(i + this->front + this->cap) % this->cap]; // i
        arr[(i + this->front + this->cap) % this->cap] = arr[(right + this->front + this->cap) % this->cap]; // i , right
        arr[(right + this->front + this->cap) % this->cap] = temp2; // right
        return i;
    }
    arraytype quickSelectHelper(arraytype arr[], int left, int right, int k) {
        if (k > 0 && k <= right - left + 1) {
            int index = partition(arr, left, right);

            if (index - left == k - 1) {
                return arr[(index + this->front + this->cap) % this->cap];
            }
            if (index - left > k - 1) {
                return quickSelectHelper(arr, left, index - 1, k);
            }
            return quickSelectHelper(arr, index + 1, right, k - index + left - 1);
        }
    }
    void merge (arraytype arr[], int left, int mid, int right) {
        int subArrayOne = mid - left + 1;
        int subArrayTwo = right - mid;
    
        arraytype *leftArray = new arraytype[subArrayOne];
        arraytype *rightArray = new arraytype[subArrayTwo];
    
        for (int i = 0; i < subArrayOne; i++) {
            leftArray[i] = arr[(left + i + this->front + this->cap) % this->cap];
        }
        for (int j = 0; j < subArrayTwo; j++) {
            rightArray[j] = arr[(mid + 1 + j + this->front + this->cap) % this->cap];
        }
        int s1Index = 0;
        int s2Index = 0;
        int mergedIndex = left;
    
        while (s1Index < subArrayOne && s2Index < subArrayTwo) {
            if (leftArray[s1Index] <= rightArray[s2Index]) {
                arr[(mergedIndex + this->front + this->cap) % this->cap] = leftArray[s1Index];
                s1Index++;
            }
            else {
                arr[(mergedIndex + this->front + this->cap) % this->cap] = rightArray[s2Index];
                s2Index++;
            }
            mergedIndex++;
        }
 
        while (s1Index < subArrayOne) {
            arr[(mergedIndex + this->front + this->cap) % this->cap] = leftArray[s1Index];
            s1Index++;
            mergedIndex++;
        }

        while (s2Index < subArrayTwo) {
            arr[(mergedIndex + this->front + this->cap) % this->cap] = rightArray[s2Index];
            s2Index++;
            mergedIndex++;
        }

        delete [] leftArray;
        delete [] rightArray;
    }
    void mergeSortHelper(arraytype arr[], int start, int end) {
        if (start >= end) {
            return;
        }
        int mid = start + (end - start) / 2;
        mergeSortHelper(arr, start, mid);
        mergeSortHelper(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
    int binarySearchHelper(arraytype arr[], arraytype searchTerm, int left, int right) {
        int mid = (left + right) / 2;
        if (left > right) {
            return -1;
        }
        else {
            if (searchTerm == arr[(mid + this->front + this->cap) % this->cap]) {
                return mid;
            }
            else if (searchTerm > arr[(mid + this->front + this->cap) % this->cap]) {
                return binarySearchHelper(arr, searchTerm, mid + 1, right);
            }
            else {
                return binarySearchHelper(arr, searchTerm, left, mid - 1);
            }
        }
    }

    bool isFull() {
        if (this->cap == this->size) {
            return true;
        }
        return false;
    }
    void resizeArray(CircularDynamicArray &cda) {
        if (isFull()) {
            int newCap = cda.cap * 2;
            arraytype* newArray = new arraytype[newCap];
            for (int i = 0; i < cda.size; i++) {
                newArray[i] = cda.array[(cda.front + cda.cap + i) % cda.cap];
            }

            delete cda.array;
            cda.cap = newCap;
            cda.array = newArray;

            if (reversed) {
                cda.front = cda.size - 1;
                cda.end = 0;
            }
            else {
                cda.front = 0;
                cda.end = cda.size - 1;
            }
        }
        else if (cda.size <= cda.cap / 4) {
            int newCap = cda.cap / 2;
            arraytype* newArray = new arraytype[newCap];
            for (int i = 0; i < cda.size; i++) {
                newArray[i] = cda.array[(cda.front + cda.cap + i) % cda.cap];
            }

            delete cda.array;
            cda.cap = newCap;
            cda.array = newArray;

            if (reversed) {
                cda.front = cda.size - 1;
                cda.end = 0;
            }
            else {
                cda.front = 0;
                cda.end = cda.size - 1;
            }
        }
    }

    public:
    arraytype* array;
    int size, cap, front, end;
    
    CircularDynamicArray() {
        this->array = new arraytype[2];
        this->size = 0;
        this->cap = 2;
        this->front = this->end = -1;
        this->reversed = 0;
    }
    // s = size
    CircularDynamicArray(int s) {
        this->array = new arraytype[s];
        this->size = s;
        this->cap = s;
        this->front = 0;
        this->end = this->size - 1;
        this->reversed = 0;
    }
    ~CircularDynamicArray() {
        delete [] this->array;
    }

    CircularDynamicArray<arraytype>& operator=(CircularDynamicArray<arraytype>& cda) {
        delete this->array;
        this->array = new arraytype[cda.cap];
        for (int i = 0; i < cda.size; i++) {
            this->array[i] = cda.array[i];
        }
        this->size = cda.size;
        this->cap = cda.cap;
        this->front = cda.front;
        this->end = cda.end;
        this->outOfBounds = cda.outOfBounds;
        this->reversed = cda.reversed;

        return *this;
    }
    CircularDynamicArray(CircularDynamicArray& cda) {
        this->array = new arraytype[cda.cap];
        for (int i = 0; i < cda.size; i++) {
            this->array[i] = cda.array[i];
        }
        this->size = cda.size;
        this->cap = cda.cap;
        this->front = cda.front;
        this->end = cda.end;
        this->outOfBounds = cda.outOfBounds;
        this->reversed = cda.reversed;
    }

    arraytype& operator[](int i) {
        if (i > this->size) {
            cout << "Out of bounds" << endl;
            outOfBounds = NULL;
            return outOfBounds;
        }

        if (reversed) {
           return this->array[(this->front + this->cap - i) % this->cap]; 
        }

        return this->array[(this->front + this->cap + i) % this->cap];
    }

    void addEnd(arraytype v) {
        // check if array needs resizing (increase array by double) before adding new element
        resizeArray(*this);
        size++;
        // place new element at correct index.. this equation utilizing modulus ensures the correct index 
        // is chosen 
        if (reversed) {
            this->end = (this->end - 1 + this->cap) % this->cap;
        }
        else {
            this->end = (this->end + 1 + this->cap) % this->cap;
        }

        this->array[end] = v;
    }
    void addFront(arraytype v) {
        resizeArray(*this);
        size++;
        if (reversed) {
            this->front = (this->front + 1 + this->cap) % this->cap;
        }
        else {
            this->front = (this->front - 1 + this->cap) % this->cap;
        }

        this->array[front] = v;
    }
    void delEnd() {
        // update size after deletion before checking for the need to resize (decrease array by half)
        size--;
        resizeArray(*this);
        if (reversed) {
            this->end = (this->end + 1 + this->cap) % this->cap;
        }
        else {
            this->end = (this->end - 1 + this->cap) % this->cap;
        }
    }
    void delFront() {
        size--;
        resizeArray(*this);
        if (reversed) {
            this->front = (this->front - 1 + this->cap) % this->cap;  
        }
        else {
            this->front = (this->front + 1 + this->cap) % this->cap;
        }
    }

    int length() {
        return this->size;
    }
    int capacity() {
        return this->cap;
    }
    void clear() {
        delete [] this->array;
        this->array = new arraytype[2];
        this->size = 0;
        this->cap = 2;
        this->front = -1;
        this->end = -1;
    }

    arraytype QuickSelect(int k) {
        if (k < 1 || k > this->size) {
            return -1;
        }
        int left = 0;
        int right = this->size - 1;

        return quickSelectHelper(this->array, left, right, k);
    }
    void stableSort() {
        // merge sort meets the O(n log n) stable sorting requirement
        int left = 0;
        int right  = this->size - 1;
        mergeSortHelper(this->array, left, right);
    };
    int linearSearch(arraytype e) {
        for (int i = 0; i < this->length(); i++) {
            if (this->array[(this->front + this->cap + i) % this->cap] == e) {
                return i;
            }
        }
        return -1;
    }
    int binSearch(arraytype e) {
        int left = 0;
        int right = this->size - 1;
        this->stableSort();
        return binarySearchHelper(this->array, e, left, right);
    }
    void reverse() {
        this->reversed = !(this->reversed);
        int temp = this->front;
        this->front = this->end;
        this->end = temp;
    }
};
