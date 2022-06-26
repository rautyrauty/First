#include <iostream>
#include <fstream>
#include <vector>
//#include <iomanip>
using namespace std;
typedef double T;
int left_boundary(T x, const vector<T>& A)
{
	int left = 0;
	while (left < int(A.size()) and A[left] < x) left++;
	return left;
}
int right_boundary(T x, const vector<T>& A)
{
	int right = A.size()-1;
	while (right > 0 and A[right] > x) right--;
	return right;
}
int binleft_boundary(T x, const vector<T>& A)
{
	int l = 0, r = A.size()-1;
	while (r - l > 1)
	{
		int middle = (r + l) / 2;
		if (middle >= x) r = middle;
		else l = middle;
	}
	return l;
}
int binright_boundary(T x, const vector<T>& A)
{
	int l = 0, r = A.size() - 1;
	while (r - l > 1)
	{
		int middle = (r + l) / 2;
		if (middle <= x) l = middle;
		else r = middle;
	}
	return r;
}
int main()
{
	T x; vector<T> A = { 2,2,2,3,3,3,5,5,5,5,5,6,7,7,9,9 };
	cout << "What to find? x = "; cin >> x;
	int left = left_boundary(x, A); int right = right_boundary(x, A);
	cout << "Noob finder give answer: "
		 << '[' << left << ';' << right << ']' << '\n';
	int binleft = binleft_boundary(x, A); int binright = binright_boundary(x, A);
	cout << "Binsearch finder give answer: "
		<< '[' << left << ';' << right << ']' << '\n';
	return 0;
}