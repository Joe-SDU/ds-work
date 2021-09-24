#include <iostream>
#include <string>
#include <vector>
#include "arrayList.h"

using namespace std;

int main()
{
	arrayList<string> a;
	a.emplace_back("abcde");
	a.emplace_back(10, 'r');

	for (auto x = a.begin(); x != a.end(); x++) cout << *x;

	return 0;
}