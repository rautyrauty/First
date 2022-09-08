#include "Solutions.h"
#include <iostream>
using namespace std;
int main()
{
	TreeNode* Tree = new TreeNode[7];
	//[3, 9, 20, null, null, 15, 7]
	Tree[0].val = 1;
	Tree[1].val = 2;
	Tree[2].val = 3;
	Tree[3].val = 4;
	Tree[4].val = 6;
	Tree[5].val = 5;
	Tree[6].val = 7;
	Tree[0].left = &Tree[1];
	Tree[0].right = &Tree[2];
	Tree[1].left = &Tree[3];
	Tree[1].right = &Tree[4];
	Tree[2].left = &Tree[5];
	Tree[2].right = &Tree[6];
	vector<vector<int>> NewTree = Solutions::verticalTraversal(&Tree[0]);
	for (auto& i : NewTree)
	{
		cout << '[';
		for (auto& j : i)
		{
			cout << j << ',';
		}
		cout << ']';
	}
	delete[] Tree;
	return 0;
}