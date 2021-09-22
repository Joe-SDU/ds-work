#pragma once

// 数组实现的链表类

#include <algorithm>
#include <iostream>
#include <sstream>
#include "linearList.h"
#include "exception_class.h"

template <typename T>
void changeArrayLength1D(T*& a, int oldLength, int newLength)
{
	if (newLength < 0) throw illegalParameterValue("new length must > 0");

	T* temp = new T[newLength];
	int number = (oldLength <= newLength ? oldLength : newLength);
	for (int i = 0; i < number; i++) temp[i] = a[i];
	delete[]a;
	a = temp;
}

template <typename T> class arrayList;

template <typename T>
std::ostream& operator<<(std::ostream&, arrayList<T>&);

template <typename T>
void swap(arrayList<T>&, arrayList<T>&);

template <typename T>
class arrayList : public linearList<T>
{
	friend std::ostream& operator<<<>(std::ostream&, arrayList&); // 多对一友好关系
	friend void swap<>(arrayList&, arrayList&);
public:
	arrayList(int initCapacity = 10);
	arrayList(const arrayList&);
	arrayList(arrayList&&) noexcept;
	arrayList& operator=(arrayList);
	~arrayList() { delete[]element; }
	bool empty() const override { return listSize == 0; }
	int size() const override { return listSize; }
	T& get(int) const override;
	int indexOf(const T&) const override;
	void erase(int) override;
	void insert(int, const T&) override;
	void output(std::ostream&) const override;
protected:
	void checkIndex(int) const;
	T* element;
	int arrayLength;
	int listSize;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, arrayList<T>& theList)
{
	theList.output(os);
	return os;
}

template <typename T>
void swap(arrayList<T>& lhs, arrayList<T>& rhs)
{
	using std::swap;
	swap(lhs.element, rhs.element);
	swap(lhs.listSize, rhs.listSize);
	swap(lhs.arrayLength, rhs.arrayLength);
}

template <typename T>
arrayList<T>::arrayList(int initCapacity)
{
	listSize = 0;
	element = new T[initCapacity];
	arrayLength = initCapacity;
}

template <typename T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{
	listSize = theList.listSize;
	arrayLength = theList.arrayLength;
	element = new T[arrayLength];
	std::copy(theList.element, theList.element + listSize, element);
}

template <typename T>
arrayList<T>::arrayList(arrayList<T>&& theList)  noexcept
	: element(theList.element), listSize(theList.listSize), arrayLength(theList.arrayLength)
{
	theList.element = nullptr;
}

template <typename T>
arrayList<T>& arrayList<T>::operator=(arrayList<T> rhs)
{
	swap(*this, rhs);
	return *this;
}

template <typename T>
T& arrayList<T>::get(int theIndex) const
{
	checkIndex(theIndex);

	return element[theIndex];
}

template <typename T>
int arrayList<T>::indexOf(const T& theElement) const
{
	for (int i = 0; i < listSize; i++)
		if (element[i] == theElement)
			return i;
	return -1;
}

template <typename T>
void arrayList<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	
	for (int i = theIndex; i < listSize; i++)
		element[i] = element[i + 1];
	element[--listSize].~T();
}

template <typename T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << " listSize = " << listSize;
		throw illegalParameterValue(s.str());
	}

	if (listSize == arrayLength)
	{
		changeArrayLength1D(element, arrayLength, arrayLength * 2);
		for (int i = listSize - 1; i >= theIndex; i--)
			arrayLength *= 2;
	}
	for(int i = listSize - 1; i >= theIndex;i--)
		element[i + 1] = element[i];
	element[theIndex] = theElement;
	listSize++;
}

template <typename T>
void arrayList<T>::output(std::ostream& os) const
{
	for (int i = 0; i < listSize; i++) os << element[i] << ' ';
}

template <typename T>
void arrayList<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= arrayLength)
		throw illegalParameterValue("out of range");
}

