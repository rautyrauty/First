//Roman numerals are represented by seven different symbols : I, V, X, L, C, Dand M.
//For example, 2 is written as II in Roman numeral, just two ones added together. 
// 12 is written as XII, which is simply X + II.The number 27 is written as XXVII, which is XX + V + II.
//
//Roman numerals are usually written largest to smallest from left to right.However,
//the numeral for four is not IIII.Instead, the number four is written as IV.
//Because the one is before the five we subtract it making four.
// The same principle applies to the number nine, which is written as IX.
// There are six instances where subtraction is used :
//
//I can be placed before V(5) and X(10) to make 4 and 9.
//X can be placed before L(50) and C(100) to make 40 and 90.
//C can be placed before D(500) and M(1000) to make 400 and 900.
//Given a roman numeral, convert it to an integer.
#include <string>
#include "Solutions.h"
#define I 1
#define V 5
#define X 10
#define L 50
#define C 100
#define D 500
#define M 1000
int Solutions::RomanToInt(string RomanStr)
{
	const int RomanStrSize = RomanStr.size();
	int* RomanStrInIntegerArray = new int[RomanStrSize];
	for (int i = 0; i < RomanStrSize; i++)
	{
		switch (RomanStr[i])
		{
		case 'I':
			RomanStrInIntegerArray[i] = I;
			break;
		case 'V':
			RomanStrInIntegerArray[i] = V;
			break;
		case 'X':
			RomanStrInIntegerArray[i] = X;
			break;
		case 'L':
			RomanStrInIntegerArray[i] = L;
			break;
		case 'C':
			RomanStrInIntegerArray[i] = C;
			break;
		case 'D':
			RomanStrInIntegerArray[i] = D;
			break;
		case 'M':
			RomanStrInIntegerArray[i] = M;
			break;
		default:
			exit(101);
		}
	}
	int Result = 0;
	for (int i = 0; i < RomanStrSize-1; i++)
	{
		if (RomanStrInIntegerArray[i] < RomanStrInIntegerArray[i + 1])
		{
			Result -= RomanStrInIntegerArray[i];
			continue;
		}
		Result += RomanStrInIntegerArray[i];
	}
	Result += RomanStrInIntegerArray[RomanStrSize - 1];
	delete[] RomanStrInIntegerArray;
	return Result;
}