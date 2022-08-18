#include <iostream>
#include <functional>
using namespace std;
int mult(int a,int b)
{
	return a * b;
}
int sum(int a, int b)
{
	return a + b;
}
int del(int a, int b)
{
	return a / b;
}
void clan(int(*banan)(int a, int b))
{
	cout << banan(1000, 10) << '\n';
}
int main()
{
	int(*banan)(int a, int b);
	banan = mult;
	clan(banan);
	banan = del;
	clan(banan);
	banan = sum;
	clan(banan);
	return 0;
}