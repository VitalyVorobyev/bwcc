#pragma once

#include <stdlib.h>

struct TreeNode {
    char c;
    int f;
    struct TreeNode *left, *right;
};

typedef struct TreeNode TreeNode;


TreeNode* crete_node(char c){
    TreeNode *R = (TreeNode*)malloc(sizeof(TreeNode));
    R->left=NULL;
    R->right=NULL;
    R->c=c;
    R->f=0;
    return R;
}

TreeNode* joint_nodes(TreeNode *left, TreeNode *right){
    TreeNode *R = (TreeNode*)malloc(sizeof(TreeNode));
    R->c = 0;
    R->f = left->f + right->f;
    R->left = left;
    R->right = right;
    return R;
}

void  T(int lvl, TreeNode *N, int A[], int *K[], int *x){
    if (N != NULL) {
        if (!N->left) {
            K[N->c] = (int*)malloc((lvl + 1) * sizeof(int));
            K[N->c][0]=lvl;
            if (lvl > *x) *x = lvl;
            for (int i = 0; i < lvl; i++) {
                K[N->c][i+1] = A[i];
            }
        } else {
            A[lvl] = 0;
            T(lvl + 1, N->left, A, K, x);
            A[lvl] = 1;
            T(lvl + 1, N->right, A, K, x);
        }
    }
}
