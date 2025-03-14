#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// 辅助函数：在中序序列中查找根节点的位置
int findRootIndex(int *inorder, int inStart, int inEnd, int rootVal) {
    for (int i = inStart; i <= inEnd; i++) {
        if (inorder[i] == rootVal) {
            return i;
        }
    }
    return -1; // 理论上不会执行到这里（输入合法）
}

// 递归构建二叉树
struct TreeNode* buildTreeHelper(
    int *inorder, int inStart, int inEnd,
    int *postorder, int postStart, int postEnd
) {
    if (postStart > postEnd) return NULL;
    
    // 创建根节点
    struct TreeNode *root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = postorder[postEnd];
    root->left = root->right = NULL;
    
    // 找到根节点在中序中的位置
    int rootIdx = findRootIndex(inorder, inStart, inEnd, root->val);
    int leftSize = rootIdx - inStart; // 左子树节点数
    
    // 递归构建左子树
    root->left = buildTreeHelper(
        inorder, inStart, rootIdx - 1,
        postorder, postStart, postStart + leftSize - 1
    );
    
    // 递归构建右子树
    root->right = buildTreeHelper(
        inorder, rootIdx + 1, inEnd,
        postorder, postStart + leftSize, postEnd - 1
    );
    
    return root;
}

// 主函数：根据中序和后序遍历构建二叉树
struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
    if (inorderSize == 0 || postorderSize == 0) return NULL;
    return buildTreeHelper(inorder, 0, inorderSize - 1, postorder, 0, postorderSize - 1);
}

// 示例：打印二叉树（前序遍历）
void printPreOrder(struct TreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->val);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

int main() {
    // 示例输入
    int inorder[] = {9, 3, 15, 20, 7};
    int postorder[] = {9, 15, 7, 20, 3};
    
    // 构建二叉树
    struct TreeNode* root = buildTree(inorder, 5, postorder, 5);
    
    // 打印前序遍历结果验证
    printf("PreOrder: ");
    printPreOrder(root); // 输出应为：3 9 20 15 7
    return 0;
}
