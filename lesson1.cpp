#include <iostream>
#include <vector>
using namespace std;
void print_vector(const vector<int>& A) // Распечатка вектора //lessons 1-11
{
	for (int i = 0; i < A.size(); i++)
	{
		cout << A[i] << ' ';
	}
	cout << '\n';
}
 
void shift_right(vector<int>& A) // Сдвиг вектора вправо
{
	int x = A[A.size()-1];
	for (int i = A.size() - 1; i > 0; i--)
	{
		A[i] = A[i - 1];
	}
	A[0] = x;
}
 
void shift_left(vector<int>& A) // Сдвиг вектора влево
{
	int x = A[0];
	for (int i = 0; i < A.size()-1; i++)
	{
		A[i] = A[i + 1];
	}
	A[A.size()-1] = x;
}
 
void reverse(vector<int>& A) // Поменять значения вектора задом наперёд
{
	int N = A.size();
	for (int i = 0; i <= N/2; i++)
	{
		int x = A[i];
		A[i] = A[N - i - 1];
		A[N - i - 1] = x;
	}
}
int main()
{
	vector<int> A = { 1,2,3,4,5,6,7,8,9,10 };
	print_vector(A);
	reverse(A);
	print_vector(A);
	shift_right(A);
	print_vector(A);
	shift_left(A);
	reverse(A);
	print_vector(A);
	return 0;
}