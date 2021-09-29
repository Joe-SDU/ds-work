#include <iostream>
#include "rand_generator.h"

using namespace std;

int main()
{
	Random_number_generator<double> a(10);

	a.get_random_numbers(0, 100);

	cout << a;

	return 0;
}