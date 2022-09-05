//Given the root of a binary tree, calculate the vertical order traversal of the binary tree.
//
//For each node at position(row, col), its leftand right children will be at positions(row + 1, col - 1)
//and (row + 1, col + 1) respectively.The root of the tree is at(0, 0).
//
//The vertical order traversal of a binary tree is a list of top - to - bottom orderings
//for each column index starting from the leftmost columnand ending on the rightmost column.
//There may be multiple nodes in the same rowand same column.
//In such a case, sort these nodes by their values.
//
//Return the vertical order traversal of the binary tree.
#include "Solutions.h"
void RecursionMaxAndMinFinder(const TreeNode* currentNode, const int currentPos, int& Max, int& Min)
{
	if (currentPos > Max) Max = currentPos;
	else if (currentPos < Min) Min = currentPos;
	if (currentNode->right) RecursionMaxAndMinFinder(currentNode->right, currentPos + 1, Max, Min);
	if (currentNode->left) RecursionMaxAndMinFinder(currentNode->left, currentPos-1, Max, Min);
}
void GetTraversalCountAndDigitForShift(const TreeNode* root, unsigned long long& TraversalCount, int& DigitForShift)
{
	int Max = 0, Min = 0;
	RecursionMaxAndMinFinder(root, 0, Max, Min);
	TraversalCount = static_cast<unsigned long long>(Max-Min+1);
	DigitForShift = 1 -Min;
}
void NestingElementsInContainers(const TreeNode* currentNode, const int currentPos, vector<vector<int>>& ANSWER, int& DigitForShift)
{
	ANSWER[currentPos+ DigitForShift].push_back(currentNode->val);
	if (currentNode->right) NestingElementsInContainers(currentNode->right, currentPos + 1,ANSWER, DigitForShift);
	if (currentNode->left) NestingElementsInContainers(currentNode->left, currentPos - 1, ANSWER, DigitForShift);
}
vector<vector<int>> Solutions::verticalTraversal(TreeNode* root)
{
	unsigned long long TraversalCount;
	int DigitForShift;
	GetTraversalCountAndDigitForShift(root,TraversalCount, DigitForShift);
	vector<vector<int>> ANSWER (TraversalCount);
	NestingElementsInContainers(root, 0,ANSWER,DigitForShift);
	return ANSWER;
}