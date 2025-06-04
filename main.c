#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100000

// Definition for a binary tree node.
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Helper to create a new tree node
struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Helper to parse input string like "[3,9,20,null,null,15,7]" to array
int parseInput(const char* s, char arr[][16], int* n) {
    int i = 0, j = 0, k = 0;
    while (s[i] && (s[i] == ' ' || s[i] == '[')) ++i;
    while (s[i] && s[i] != ']') {
        if (s[i] == ',') {
            arr[k][j] = '\0';
            ++k; j = 0;
        } else if (s[i] != ' ') {
            arr[k][j++] = s[i];
        }
        ++i;
    }
    if (j > 0) {
        arr[k][j] = '\0';
        ++k;
    }
    *n = k;
    return k;
}

// Helper to build tree from level-order array
struct TreeNode* buildTree(char arr[][16], int n) {
    if (n == 0 || strcmp(arr[0], "null") == 0) return NULL;
    struct TreeNode** nodes = (struct TreeNode**)malloc(n * sizeof(struct TreeNode*));
    for (int i = 0; i < n; ++i) nodes[i] = NULL;
    struct TreeNode* root = newNode(atoi(arr[0]));
    nodes[0] = root;
    int idx = 1;
    for (int i = 0; i < n && idx < n; ++i) {
        if (!nodes[i]) continue;
        // left child
        if (idx < n && strcmp(arr[idx], "null") != 0) {
            nodes[i]->left = newNode(atoi(arr[idx]));
            nodes[idx] = nodes[i]->left;
        }
        idx++;
        // right child
        if (idx < n && strcmp(arr[idx], "null") != 0) {
            nodes[i]->right = newNode(atoi(arr[idx]));
            nodes[idx] = nodes[i]->right;
        }
        idx++;
    }
    free(nodes);
    return root;
}

// Helper to free the memory of a tree
void deleteTree(struct TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

// BFS to find minimum depth
int minDepth(struct TreeNode* root) {
    if (root == NULL) return 0;

    struct TreeNode** queue = malloc(sizeof(struct TreeNode*) * MAX_NODES);
    int front = 0, rear = 0;
    queue[rear++] = root;

    int depth = 1;

    while (front < rear) {
        int levelSize = rear - front;

        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queue[front++];
            if (node->left == NULL && node->right == NULL) {
                free(queue);
                return depth;
            }
            if (node->left) queue[rear++] = node->left;
            if (node->right) queue[rear++] = node->right;
        }
        depth++;
    }

    free(queue);
    return depth;
}

int main() {
    const char* inputs[] = {
        "[3,9,20,null,null,15,7]",
        "[2,null,3,null,4,null,5,null,6]"
    };
    int num_cases = sizeof(inputs) / sizeof(inputs[0]);

    for (int i = 0; i < num_cases; ++i) {
        printf("Input: root = %s\n", inputs[i]);
        char arr[MAX_NODES][16];
        int n = 0;
        parseInput(inputs[i], arr, &n);
        struct TreeNode* root = buildTree(arr, n);

        int result = minDepth(root);
        printf("Output: %d\n", result);

        deleteTree(root);
    }
    return 0;
}
