#include "Solutions.h"
#include <iostream>
using namespace std;
int main()
{
	TreeNode* Tree = new TreeNode[7];
	//[3, 9, 20, null, null, 15, 7]
	Tree[0].val = 3;
	Tree[1].val = 9;
	Tree[2].val = 20;
	Tree[5].val = 15;
	Tree[6].val = 7;
	Tree[0].left = &Tree[1];
	Tree[0].right = &Tree[2];
	Tree[2].left = &Tree[5];
	Tree[2].right = &Tree[6];
	vector<vector<int>> NewTree = Solutions::verticalTraversal(&Tree[0]);
	cout << 1;
	delete[] Tree;
	return 0;
}