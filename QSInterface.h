#ifndef QSINTERFACE_H_
#define QSINTERFACE_H_

#include <iostream>
#include <string>
using namespace std;

class QSInterface
{
public:
	QSInterface() {}
	virtual ~QSInterface() {}
	virtual void sortAll() = 0;
	virtual int medianOfThree(int left, int right) = 0;
	virtual int partition(int left, int right, int pivotIndex) = 0;
	virtual string getArray() const = 0;
	virtual int getSize() const = 0;
	virtual bool addToArray(int value) = 0;
	virtual bool createArray(int capacity) = 0;
	virtual void clear() = 0;
};

#endif
	
