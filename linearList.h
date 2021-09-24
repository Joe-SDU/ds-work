#pragma once

// 抽象基类, 不希望创造这样的一个类的对象， 我们只希望将其作为一个接口

#include <iostream>

template <typename T>
class linearList
{
public:
	virtual ~linearList() {}
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T& get(int theIndex) const = 0;
	virtual int indexOf(const T& theElement) const = 0;
	virtual void erase(int theIndex) = 0;
	virtual void insert(int theIndex, const T& theElement) = 0;
	virtual void output(std::ostream& os) const = 0;
};