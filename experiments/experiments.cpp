#include <iostream>
#include <vector>
using namespace std;
int main()
{
	vector<vector<int>> a;
	cout << a.size() << '\n';
	a.push_back({});
	cout << a.size() << ' ' << a[0].size() << '\n';
}