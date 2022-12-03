#include <iostream>
#include <stdexcept>

#include <Windows.h>

using namespace std;

int main()
{
	int a = 10;
	delete &a;
	return 0;
}