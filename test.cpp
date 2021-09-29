#include <iostream>
#include <fstream>
#include <exception>
#include <algorithm>
#include "rand_generator.h"

using namespace std;

int main()
{
	Random_number_generator<int> a(10);
	auto p = a.get_random_numbers(0, 100);

	ofstream outFile("C:\\Users\\XUWL\\Desktop\\data.txt", ios::ate | ios::out | ios::app);
	if (!outFile) throw runtime_error("open file error");

	sort(get<1>(p).first, get<1>(p).second);

	outFile << a << endl;

	a.get_random_numbers(0, 100);

	sort(get<1>(p).first, get<1>(p).second, [](double a, double b) -> bool { return a > b; });

	outFile << a << endl;

	return 0;
}