#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    vector<int> A{ 1,2,3 };
    sort(A.begin(), A.end(), [](int a, int b) 
        {
            return a > b;
        });
    for (auto& a : A) cout << a << '\n';
    return 0;
}