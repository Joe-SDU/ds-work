#pragma once

#include <tuple>
#include <vector>
#include <memory>
#include <random>
#include <typeinfo>
#include <ctime>
#include <ostream>
#include <exception>

/*
	1. ����ʵ����һ���������������
	2. ��������:
			1. ���ñ�׼�����������������������顣
			2. �ṩ����ĵ������� �����׼���㷨����������в����� ��������������ʵ�������
			3. ������һϵ�ж���������в����ķ�����

	3. ���ɵ���������:
			1. (0): ����cnt���������, ��Χ��[low, high];
			2. (1): ����cnt�����ʵ��, ��Χ��[low, high];

*/

template <typename T> class Random_number_generator;

template <typename T>
std::ostream& operator<<(std::ostream&, Random_number_generator<T>&);

template <typename T>
class Random_number_generator
{
public:
	friend std::ostream& operator<<<T>(std::ostream&, Random_number_generator&);
	typedef typename std::vector<T>::size_type index_type;
	Random_number_generator(index_type rand_numbers) 
		: rand_container(new std::vector<T>()), rand_count(rand_numbers) {}
	~Random_number_generator() = default;
	std::tuple<index_type, std::pair<typename std::vector<T>::iterator, typename std::vector<T>::iterator>>
		get_random_numbers(T, T);
	T& operator[](index_type i) { return (*rand_container)[i]; }
	const T& operator[](index_type i) const { return (*rand_container)[i]; }
private:
	std::shared_ptr<std::vector<T>> rand_container;
	index_type rand_count;
	static std::default_random_engine e;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, Random_number_generator<T>& rhs)
{
	for (auto it = rhs.rand_container->cbegin(); it != rhs.rand_container->cend(); it++)
		os << *it << ' ';
	
	return os;
}

template <typename T>
std::default_random_engine Random_number_generator<T>::e(time(nullptr));

template <typename T>
std::tuple<typename Random_number_generator<T>::index_type, std::pair<typename std::vector<T>::iterator, typename std::vector<T>::iterator>>
Random_number_generator<T>::get_random_numbers(T low, T high)
{
	if (typeid(T) == typeid(double))
	{
		static std::uniform_real_distribution<> u(low, high);
		for (index_type i = 0; i < rand_count; i++)
			rand_container->push_back(u(e));
	}
	else if (typeid(T) == typeid(int))
	{
		static std::uniform_int_distribution<> u(low, high);
		for (index_type i = 0; i < rand_count; i++)
			rand_container->push_back(u(e));
	}
	else throw std::runtime_error("illegal type for generating!");

	return std::make_tuple(rand_count, std::make_pair(rand_container->begin(), rand_container->end()));
}

