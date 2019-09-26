#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#include "QSInterface.h"

class QS : public QSInterface
{
public:
	QS() {}
	virtual ~QS();
	void quicksort(int left, int right);
    void sortAll();
    int medianOfThree(int left, int right);
    int partition(int left, int right, int pivotIndex);
    string getArray() const;
    int getSize() const;
    bool addToArray(int value);
    bool createArray(int capacity);
    void clear();
private:
    int* arrayPtr = NULL;
    int insertPos = 0;
    int capacity;
};