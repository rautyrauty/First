#pragma once

#include <string>
#include <vector>

struct TreeNode;

class Solutions {
public:
    static bool canConstruct(std::string ransomNote, std::string magazine);
    static int RomanToInt(std::string RomanStr);
    static std::vector<int> numsSameConsecDiff(int n, int k);
    static std::vector<std::vector<int>> verticalTraversal(TreeNode* root);
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
