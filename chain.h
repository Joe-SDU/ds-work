#pragma once

#include <iostream>
#include <sstream>
#include "linearList.h"
#include "exception_class.h"

// 指针实现的链表

template <typename T>
struct chainNode
{
	chainNode() { next = nullptr; };
	chainNode(const T& theElement) 
		: element(theElement), next(nullptr) {}
	chainNode(const T& theElement, chainNode* theNext)
		: element(theElement), next(theNext) {}
	~chainNode() = default;

	T element;
	chainNode<T>* next;
};

template <typename T> class chain;

template <typename T>
std::ostream& operator<<(std::ostream&, const chain<T>&);

template <typename T>
void swap(chain<T>& lhs, chain<T>& rhs);

template <typename T>
class chain : public linearList<T>
{
	friend std::ostream& operator<<<T>(std::ostream&, const chain&);
	friend void swap<T>(chain&, chain&);
public:
	chain() : firstNode(nullptr), listSize(0) {}
	chain(const chain&);
	chain(chain&&) noexcept;
	~chain();
	chain& operator=(chain);
	bool empty() const override { return listSize == 0; }
	int size() const override { return listSize; }
	T& get(int) const override;
	int indexOf(const T&) const override;
	void erase(int) override;
	void insert(int, const T&) override;
	template <typename... Args> void emplace_back(Args&&... args);
protected:
	void output(std::ostream&) const override;
	void checkIndex(int) const;
	chainNode<T>* firstNode;
	int listSize;
};

template <typename T>
chain<T>::chain(const chain<T>& theList)
{
	listSize = theList.listSize;
	if (!listSize)
	{
		firstNode = nullptr;
		return;
	}
	chainNode<T>* sourceNode = theList.firstNode;
	firstNode = new chainNode<T>(sourceNode->element);
	sourceNode = sourceNode->next;
	chainNode<T>* targetNode = firstNode;
	while (sourceNode)
	{
		targetNode->next = new chainNode<T>(sourceNode->element);
		sourceNode = sourceNode->next;
		targetNode = targetNode->next;
	}
	// default: target = nullptr;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const chain<T>& theList)
{
	theList.output(os);
	return os;
}

template <typename T>
void swap(chain<T>& lhs, chain<T>& rhs)
{
	using std::swap;
	swap(lhs.firstNode, rhs.firstNode);
	swap(lhs.listSize, rhs.listSize);
}

template <typename T>
chain<T>::chain(chain<T>&& theList) noexcept
	: firstNode(theList.firstNode), listSize(theList.listSize)
{
	theList.firstNode = nullptr;
}

template <typename T>
chain<T>& chain<T>::operator=(chain<T> rhs)
{
	swap(*this, rhs);
	return *this;
}

template <typename T>
chain<T>::~chain()
{
	while (firstNode)
	{
		chainNode<T>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template <typename T>
T& chain<T>::get(int theIndex) const
{
	checkIndex(theIndex);

	chainNode<T>* targetNode = firstNode;
	while (theIndex--) targetNode = targetNode->next;
	return targetNode->element;
}

template <typename T>
int chain<T>::indexOf(const T& theElement) const
{
	chainNode<T>* targetNode = firstNode;
	for (int theIndex = 0; theIndex < listSize; theIndex++)
	{
		if (targetNode->element == theElement)
			return theIndex;
		targetNode = targetNode->next;
	}
	return -1; // not found
}

template <typename T>
void chain<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	chainNode<T>* delNode;
	if (!theIndex)
	{
		firstNode = firstNode->next;
		delNode = firstNode;
	}
	else
	{
		chainNode<T>* targetNode = firstNode;
		while (--theIndex) targetNode = targetNode->next;
		delNode = targetNode->next;
		targetNode->next = delNode->next;
	}
	delete delNode;
	listSize--;
}

template <typename T>
void chain<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex > listSize)
	{
		std::ostringstream s;
		s << "index = " << theIndex << " listSize = " << listSize;
		throw illegalParameterValue(s.str());
	}

	if (theIndex == 0) 
		firstNode = new chainNode<T>(theElement, firstNode);
	else
	{
		chainNode<T>* targetNode = firstNode;
		while (--theIndex) targetNode = targetNode->next;
		targetNode->next = new chainNode<T>(theElement, targetNode->next);
	}
	listSize++;
}

template <typename T>
void chain<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize)
		throw illegalParameterValue("out of range");
}

template <typename T>
void chain<T>::output(std::ostream& os) const
{
	chainNode<T>* curNode = firstNode;
	while (curNode)
	{
		os << curNode->element << ' ';
		curNode = curNode->next;
	}
}

template <typename T>
template <typename... Args>
void chain<T>::emplace_back(Args&&... args)
{
	this->insert(listSize, T(std::forward<Args>(args)...));
}
