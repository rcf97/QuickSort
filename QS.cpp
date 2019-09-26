//#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
using namespace std;

#include "QS.h"

//QSInterface() {}
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

	/*
	* sortAll()
	*
	* Sorts elements of the array.  After this function is called, every
	* element in the array is less than or equal its successor.
	*
	* Does nothing if the array is empty.
	*/
void QS::sortAll() {
    quicksort(0,getSize() - 1);
}

	/*
	* medianOfThree()
	*
	* The median of three pivot selection has two parts:
	*
	* 1) Calculates the middle index by averaging the given left and right indices:
	*
	* middle = (left + right)/2
	*
	* 2) Then bubble-sorts the values at the left, middle, and right indices.
	*
	* After this method is called, data[left] <= data[middle] <= data[right].
	* The middle index will be returned.
	*
	* Returns -1 if the array is empty, if either of the given integers
	* is out of bounds, or if the left index is not less than the right
	* index.
	*
	* @param left
	* 		the left boundary for the subarray from which to find a pivot
	* @param right
	* 		the right boundary for the subarray from which to find a pivot
	* @return
	*		the index of the pivot (middle index); -1 if provided with invalid input
	*/
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

	/*
	* Partitions a subarray around a pivot value selected according to
	* median-of-three pivot selection.  Because there are multiple ways to partition a list,
	* we will follow the algorithm on page 611 of the course text when testing this function.
	*
	* The values which are smaller than the pivot should be placed to the left
	* of the pivot; the values which are larger than the pivot should be placed
	* to the right of the pivot.
	*
	* Returns -1 if the array is null, if either of the given integers is out of
	* bounds, or if the first integer is not less than the second integer, or if the
	* pivot is not within the sub-array designated by left and right.
	*
	* @param left
	* 		the left boundary for the subarray to partition
	* @param right
	* 		the right boundary for the subarray to partition
	* @param pivotIndex
	* 		the index of the pivot in the subarray
	* @return
	*		the pivot's ending index after the partition completes; -1 if
	* 		provided with bad input
	*/
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

	/*
	* Produces a comma delimited string representation of the array. For example: if my array
	* looked like {5,7,2,9,0}, then the string to be returned would look like "5,7,2,9,0"
	* with no trailing comma.  The number of cells included equals the number of values added.
	* Do not include the entire array if the array has yet to be filled.
	*
	* Returns an empty string, if the array is NULL or empty.
	*
	* @return
	*		the string representation of the current array
	*/
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

	/*
	* Returns the number of elements which have been added to the array.
	*/
int QS::getSize() const {
    if (this->arrayPtr == NULL) {
        return 0;
    }
    return this->insertPos;
}

	/*
	* Adds the given value to the end of the array starting at index 0.
	* For example, the first time addToArray is called,
	* the give value should be found at index 0.
	* 2nd time, value should be found at index 1.
	* 3rd, index 2, etc up to its max capacity.
	*
	* If the array is filled, do nothing.
	* returns true if a value was added, false otherwise.
	*/
bool QS::addToArray(int value) {
    if (this->insertPos == this->capacity) {
        return false;
    }
    this->arrayPtr[this->insertPos] = value;
    this->insertPos++;
    return true;
}

	/*
	* Dynamically allocates an array with the given capacity.
	* If a previous array had been allocated, delete the previous array.
	* Returns false if the given capacity is non-positive, true otherwise.
	*
	* @param
	*		size of array
	* @return
	*		true if the array was created, false otherwise
	*/
bool QS::createArray(int capacity) {
    //cout << "create reached" << endl;
    if (capacity < 0) {
        return false;
    }
    if (this->arrayPtr != NULL) {
        //cout << "delete reached" << endl;
        delete[] this->arrayPtr;
        this->arrayPtr = NULL;
        this->insertPos = 0;
    }
    //cout << "new reached" << endl;
    this->arrayPtr = new int[capacity];
    this->capacity = capacity;
    return true;
}

	/*
	* Resets the array to an empty or NULL state.
	*/
void QS::clear() {
    delete[] this->arrayPtr;
    this->arrayPtr = NULL;
    this->insertPos = 0;
}