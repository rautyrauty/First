#include <iostream>
#include <stdexcept>

#include <Windows.h>

using namespace std;

int main()
{
	for (size_t i = 0; i < 256; i += 1) cout << char(i) << ' ' << i << '\n';
	return 0;
}