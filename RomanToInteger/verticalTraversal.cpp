/*
 * Given the root of a binary tree, calculate the vertical order traversal of the binary tree.
 *
 * For each node at position(row, col), its leftand right children will be at positions(row + 1, col - 1)
 * and (row + 1, col + 1) respectively.The root of the tree is at(0, 0).
 *
 * The vertical order traversal of a binary tree is a list of top - to - bottom orderings
 * for each column index starting from the leftmost columnand ending on the rightmost column.
 * There may be multiple nodes in the same rowand same column.
 * In such a case, sort these nodes by their values.
 * 
 * Return the vertical order traversal of the binary tree.
 */


/*
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */


#include "Solutions.h"

#include <algorithm>

std::vector<std::vector<int>> Solutions::verticalTraversal(TreeNode* root)
{
	if (root == nullptr) return {};

	std::vector<std::vector<int>> ANSWERright; // Широта уходит в положительные значения
	std::vector<std::vector<int>> ANSWERleft; // Широта уходит в отрицательные значения

	std::vector<std::pair<int,TreeNode*>> queue { std::pair<int,TreeNode*>(0,root)}; // pair широта и сама тринода

	while (true)
	{
		std::vector<std::pair<int, TreeNode*>> TMP_queue; // для временных действий c очередью
		bool QueueClearFlag = 1;
		for (const auto& t : queue)
		{
			if (t.second)
			{
				QueueClearFlag = 0;
				if (t.second->left)
				{
					TMP_queue.push_back(std::pair<int, TreeNode*>(t.first - 1, t.second->left));
				}
				if (t.second->right)
				{
					TMP_queue.push_back(std::pair<int, TreeNode*>(t.first + 1, t.second->right));
				}
			}
			else
			{
				TMP_queue.push_back(std::pair<int, TreeNode*>(t.first - 1, nullptr));
				TMP_queue.push_back(std::pair<int, TreeNode*>(t.first + 1, nullptr));
			}
		}

		if (QueueClearFlag) break;

		for (const auto& t : queue)
		{
			if (t.second == nullptr) continue;

			if (t.first < 0)
			{
				while (-(t.first+1) >= ANSWERleft.size())
				{
					ANSWERleft.push_back({});
				}
				ANSWERleft[-(t.first+1)].push_back(t.second->val);
			}
			else
			{
				while ((t.first) >= ANSWERright.size())
				{
					ANSWERright.push_back({});
				}
				ANSWERright[(t.first)].push_back(t.second->val);
			}
		}

		queue = TMP_queue;

		sort(queue.begin(), queue.end(), [](std::pair<int, TreeNode*> a, std::pair<int, TreeNode*> b)
			{
				return ((a.first < b.first) or ((a.first == b.first) and (a.second->val < b.second->val)));
			});

	}

	std::vector<std::vector<int>> ANSWER;
	for (int i = ANSWERleft.size()-1; i>= 0; --i)
	{
		ANSWER.push_back(ANSWERleft[i]);
	}
	for (const auto& t : ANSWERright)
	{
		ANSWER.push_back(t);
	}

	return ANSWER;
}