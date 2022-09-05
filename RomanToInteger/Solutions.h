#pragma once
#include <string>
#include <vector>
using namespace std;
struct TreeNode;
class Solutions {
public:
    static bool canConstruct(string ransomNote, string magazine);
    static int RomanToInt(string RomanStr);
    static vector<int> numsSameConsecDiff(int n, int k);
    static vector<vector<int>> verticalTraversal(TreeNode* root);
};
  //Definition for a binary tree node.
  struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };
