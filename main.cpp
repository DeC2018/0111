#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
  int minDepth(TreeNode* root) {
    if (root == nullptr)
      return 0;
    if (root->left == nullptr)
      return minDepth(root->right) + 1;
    if (root->right == nullptr)
      return minDepth(root->left) + 1;
    return min(minDepth(root->left), minDepth(root->right)) + 1;
  }
};

// Helper function to build a binary tree from a level-order traversal
TreeNode* buildTree(const vector<string>& nodes) {
    if (nodes.empty() || nodes[0] == "null") return nullptr;

    TreeNode* root = new TreeNode(stoi(nodes[0]));
    queue<TreeNode*> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < nodes.size()) {
        TreeNode* current = q.front();
        q.pop();

        if (i < nodes.size() && nodes[i] != "null") {
            current->left = new TreeNode(stoi(nodes[i]));
            q.push(current->left);
        }
        i++;

        if (i < nodes.size() && nodes[i] != "null") {
            current->right = new TreeNode(stoi(nodes[i]));
            q.push(current->right);
        }
        i++;
    }

    return root;
}

// Helper function to parse input string like "[3,9,20,null,null,15,7]"
vector<string> parseInput(const string& s) {
    vector<string> res;
    string t = s;
    t.erase(remove(t.begin(), t.end(), '['), t.end());
    t.erase(remove(t.begin(), t.end(), ']'), t.end());
    stringstream ss(t);
    string item;
    while (getline(ss, item, ',')) {
        // Remove whitespace
        item.erase(remove_if(item.begin(), item.end(), ::isspace), item.end());
        res.push_back(item);
    }
    return res;
}

// Helper function to free the memory of a tree
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    vector<string> inputs = {
        "[3,9,20,null,null,15,7]",
        "[2,null,3,null,4,null,5,null,6]"
    };

    Solution solution;

    for (const auto& input : inputs) {
        cout << "Input: root = " << input << endl;

        auto nodes = parseInput(input);
        TreeNode* root = buildTree(nodes);

        int result = solution.minDepth(root);
        cout << "Output: " << result << endl;

        deleteTree(root);
    }

    return 0;
}
