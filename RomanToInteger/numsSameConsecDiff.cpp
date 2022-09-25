//Return all non - negative integers of length n such that the absolute
//difference between every two consecutive digits is k.
//
//Note that every number in the answer must not have leading zeros.
//For example, 01 has one leading zero and is invalid.
//
//You may return the answer in any order.
#include "Solutions.h"
void Recursiya(std::vector<int>& ANSWER,int n, const int& k, const int& prev, int currentAns_el, int& countSR)
{
	if (n == 0)
	{
		ANSWER.push_back(currentAns_el);
		return;
	}
	int discharge = 1;
	for (int x = n - 1; x > 0; x--) discharge *= 10;
	countSR += 2;
	if (prev + k < 10)
	{
		Recursiya(ANSWER, n - 1, k, prev + k, currentAns_el + (prev + k) * discharge, countSR);
	}
	if ((prev - k > -1) and (k!=0))
	{
		Recursiya(ANSWER, n - 1, k, prev - k, currentAns_el + (prev - k) * discharge, countSR);
	}
}
std::vector<int> Solutions::numsSameConsecDiff(int n, int k) {
	std::vector<int> ANSWER;
	int countSR = 0;
	int discharge;
	for (short int i = 1; i < 10; i++)
	{
		discharge = 1;
		for (unsigned short int x = n - 1; x > 0; x--) discharge *= 10;
		Recursiya(ANSWER, n - 1, k, i, i * discharge, countSR);
	}
	return ANSWER;
}