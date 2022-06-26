#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;
double f(double x) // бинарный поиск корня функции с погрешностью
{
	return (x - 2.21313) * (x - 7);
}
void binSearch1()
{
	double a, b; cout << "enter boundaries [a,b]: "; cin >> a >> b;
	double error; cout << "enter error: "; cin >> error;
	if (f(a) * f(b) < 0) {
		while ((b - a) / 2. > error) {
			double c = (a + b) / 2;
			if (f(c) == 0) {
				cout << "omg!!! 1001% answer is: " << c << '\n';

			}
			if (f(a) * f(c) <= 0) b = c;
			else a = c;
		}
		cout << "answer is: " << setprecision(17) << (a + b) / 2 << '\n';
	}
	else { cout << "cant use binsearch of root bcs f(a) * f(b) >= 0\n"; }
}
int main()
{
	binSearch1();
}