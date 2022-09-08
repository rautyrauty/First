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
#include < algorithm >
#include <iostream>
void RecursionMaxVerticalLineNumAndMinVerticalLineNumFinder(const TreeNode* currentNode, const int currentPos, int& MaxVerticalLineNum, int& MinVerticalLineNum)
{
	if (currentPos > MaxVerticalLineNum) MaxVerticalLineNum = currentPos;
	else if (currentPos < MinVerticalLineNum) MinVerticalLineNum = currentPos;
	if (currentNode->right) RecursionMaxVerticalLineNumAndMinVerticalLineNumFinder(currentNode->right, currentPos + 1, MaxVerticalLineNum, MinVerticalLineNum);
	if (currentNode->left) RecursionMaxVerticalLineNumAndMinVerticalLineNumFinder(currentNode->left, currentPos-1, MaxVerticalLineNum, MinVerticalLineNum);
}
void GetVerticalLinesCountAndDigitForShift(const TreeNode* root, unsigned long long& VerticalLinesCount, int& DigitForShift)
{
	int MaxVerticalLineNum = 0, MinVerticalLineNum = 0;
	RecursionMaxVerticalLineNumAndMinVerticalLineNumFinder(root, 0, MaxVerticalLineNum, MinVerticalLineNum);
	VerticalLinesCount = static_cast<unsigned long long>(MaxVerticalLineNum-MinVerticalLineNum+1);
	DigitForShift = -MinVerticalLineNum;
}
int compare(const pair<int, TreeNode*>* x1, const pair<int, TreeNode*>* x2)
{
	if (x1 > x2) return 1;
	if (x1 == x2)
	{
		if ((x1->second == nullptr) and (x2->second)) return -1;
		if ((x2->second == nullptr) and (x1->second)) return 1;
		if ((x1->second == nullptr) and (x2->second == nullptr)) return 0;
		if (x1->second->val > x2->second->val) return 1;
		return 0;
	}
	return -1;
}
vector<vector<int>> Solutions::verticalTraversal(TreeNode* root)
{
	unsigned long long VerticalLinesCount;
	int DigitForShift;
	GetVerticalLinesCountAndDigitForShift(root,VerticalLinesCount, DigitForShift);
	vector<vector<int>> ANSWER (VerticalLinesCount);
	vector<pair<int, TreeNode*>> queue{ pair<int,TreeNode*>(0, root) }; // int - номер верт линии
	int flagCounter = 1;
	vector<pair<int, TreeNode*>> tmpQueue; // int - верт линия
	bool flag = true;
	int counter = 0;
	for (int i = 0; true; i++)
	{
		if (queue[i].second)
		{
			tmpQueue.push_back(pair<int, TreeNode*> (queue[i].first-1, queue[i].second->left));
			tmpQueue.push_back(pair<int, TreeNode*>(queue[i].first + 1, queue[i].second->right));
			flag = false;
		}
		else
		{
			tmpQueue.push_back(pair<int, TreeNode*>(queue[i].first - 1, nullptr));
			tmpQueue.push_back(pair<int, TreeNode*>(queue[i].first + 1, nullptr));
		}
		if (++counter == flagCounter)
		{
			if (flag)
			{
				break;
			}
			flag = true;
			counter = 0;
			flagCounter *= 2;
			bool flagSort = true;
			while (flagSort)
			{
				flagSort = false;
				sort(tmpQueue.begin(), tmpQueue.end(), [](pair<int, TreeNode*> a, pair<int, TreeNode*> b)
					{
						if (a > b) return false;
						if (a == b)
						{
							if ((a.second == nullptr) and (b.second)) return true;
							if ((b.second == nullptr) and (a.second)) return false;
							if ((a.second == nullptr) and (b.second == nullptr)) return true;
							return a.second->val > b.second->val;
						}
						return true;
					});
				/*for (int k = 0; k < flagCounter - 1; k++)
				{
					//debug
					for (int j = k + 1; j < flagCounter; j++)
					{
						if ((tmpQueue[k].second == nullptr) or (tmpQueue[k + 1].second == nullptr))
						{
							continue;
						}
						if ((tmpQueue[k].first > tmpQueue[j].first) or ((tmpQueue[k].first == tmpQueue[j].first) and (tmpQueue[k].second->val > tmpQueue[j].second->val)))
						{
							flagSort = true;
							swap(tmpQueue[k], tmpQueue[j]);
							continue;
						}
					}
				}*/
			}
			for (auto& t : tmpQueue) queue.push_back(t);
			tmpQueue.clear();
		}
	}
	for (auto& queueEl : queue)
	{
		if (queueEl.second)
		{
			ANSWER[queueEl.first+DigitForShift].push_back(queueEl.second->val);
		}
	}
	return ANSWER;
}