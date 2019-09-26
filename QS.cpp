#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
using namespace std;

#include "QS.h"

QS::~QS() {
    QS::clear();
}

void QS::quicksort(int left, int right) {
    if (this->arrayPtr == NULL) {
        return;
    }
    if (left < right) {
        int pivot = medianOfThree(left, right);
        int newPivot = partition(left,right,pivot);
        quicksort(left, newPivot - 1);
        quicksort(newPivot + 1, right);
    }
    else {
        return;
    }
}

void QS::sortAll() {
    quicksort(0,getSize() - 1);
}

int QS::medianOfThree(int left, int right) {
    int middle = (left + right) / 2;
    if (this->arrayPtr == NULL || left >= right || left < 0 || (right >= this->insertPos)) {
        return -1;
    }
    if (this->arrayPtr[left] > this->arrayPtr[middle]) {
        int tmp = this->arrayPtr[left];
        this->arrayPtr[left] = this->arrayPtr[middle];
        this->arrayPtr[middle] = tmp;
    }
    if (this->arrayPtr[right] < this->arrayPtr[middle]) {
        int tmp = this->arrayPtr[middle];
        this->arrayPtr[middle] = this->arrayPtr[right];
        this->arrayPtr[right] = tmp;
    }
    if (this->arrayPtr[left] > this->arrayPtr[middle]) {
        int tmp = this->arrayPtr[left];
        this->arrayPtr[left] = this->arrayPtr[middle];
        this->arrayPtr[middle] = tmp;
    }
    return middle;
}

int QS::partition(int left, int right, int pivotIndex) {
    if (this->arrayPtr == NULL || left < 0 || right >= this->insertPos || left >= right 
        || pivotIndex < left || pivotIndex > right)
    {
        return -1;
    }
    int tmp = this->arrayPtr[left];
    this->arrayPtr[left] = this->arrayPtr[pivotIndex];
    this->arrayPtr[pivotIndex] = tmp;
    int up = left + 1;
    int down = right;
    do {
        while (this->arrayPtr[up] <= this->arrayPtr[left] && up < right) {up++;}
        while (this->arrayPtr[down] > this->arrayPtr[left] && down > left) {down--;}
        if (up < down) {
            tmp = this->arrayPtr[up];
            this->arrayPtr[up] = this->arrayPtr[down];
            this->arrayPtr[down] = tmp;
        }
    } while (up < down);
    tmp = this->arrayPtr[left];
    this->arrayPtr[left] = this->arrayPtr[down];
    this->arrayPtr[down] = tmp;
    return down;
}

string QS::getArray() const {
    string output;
    if (this->arrayPtr == NULL || this->arrayPtr == 0) {
        return output;
    }
    for (int i = 0; i < insertPos; i++) {
        stringstream ss;
        ss << this->arrayPtr[i];
        output += ss.str();
        if (i != insertPos - 1) {
            output += ",";
        }
    }
    return output;
}

int QS::getSize() const {
    if (this->arrayPtr == NULL) {
        return 0;
    }
    return this->insertPos;
}

bool QS::addToArray(int value) {
    if (this->insertPos == this->capacity) {
        return false;
    }
    this->arrayPtr[this->insertPos] = value;
    this->insertPos++;
    return true;
}

bool QS::createArray(int capacity) {
    if (capacity < 0) {
        return false;
    }
    if (this->arrayPtr != NULL) {
        delete[] this->arrayPtr;
        this->arrayPtr = NULL;
        this->insertPos = 0;
    }
    this->arrayPtr = new int[capacity];
    this->capacity = capacity;
    return true;
}

void QS::clear() {
    delete[] this->arrayPtr;
    this->arrayPtr = NULL;
    this->insertPos = 0;
}
