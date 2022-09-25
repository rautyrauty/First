#include "MacletsovSolutions.h"
#include <cassert>
#include <iostream>

int Solutions::GetFibonacciByNumber(const int& n)
{
	assert(n >= 0);

	int a = 0, b = 1, tmp;

	if (n == 0) return a;
	if (n == 1) return b;

	while (b < n)
	{
		tmp = b + a;
		a = b;
		b = tmp;
	}
	
	return b;
}

int Solutions::GetClosestFibonacciNumberByValue(const int& n)
{
	int a = 0, b = 1, tmp;
	
	if (n == 0) return a;
	if (n == 1) return b;
	
	while (b<n)
	{
		tmp = b + a;
		a = b;
		b = tmp;
	}
	
	if (b - n > n - a) return a;
	else return b;
}

void Solutions::PrintClosestFibonacciNumbersByValue(const int& EnteredNumber, const int& CountOfNearestFibonacciNumbers)
{
	if (CountOfNearestFibonacciNumbers == 0) return;
	if (EnteredNumber < 1)
	{
		for (int i = 0; i < CountOfNearestFibonacciNumbers; ++i)
		{

		}
	}
	unsigned long int a = 0, b = 1, tmpRight,tmpLeft, n = static_cast<unsigned long int>(N);

	while (b < n)
	{
		tmpRight = b + a;

		a = b;
		
		b = tmpRight;
	}
	tmpLeft = a;

	unsigned long int tmp;
	bool NullLeftFlag = 1;

	for (int i = 0; i < CountOfNearestFibonacciNumbers; i++)
	{
		if ((NullLeftFlag) and (tmpRight - n > n - tmpLeft))
		{
			std::cout << tmpLeft << '\t';


			tmp = tmpLeft;
			tmpLeft = b - tmpLeft;
			b = tmp;

			if (tmpLeft == 0) NullLeftFlag = false;
		}
		else
		{
			std::cout << tmpRight << '\t';
			tmp = tmpRight;
			tmpRight = a+tmpRight;
			a = tmp;
		}
	}
}