#include "avl_tree.h"
#include <stdio.h>
#include <stdlib.h>

// AVL 트리: BST + 자동 균형 유지
// 모든 노드에서 좌우 서브트리 높이 차(balance factor)가 -1, 0, 1 이내
// 삽입/삭제 후 불균형 발생 시 회전(rotation)으로 복구 → 항상 O(log n) 보장

static int height(AVL_NODE* n) {
    return n ? n->height : 0;
}

static int max2(int a, int b) {
    return a > b ? a : b;
}

static int balance_factor(AVL_NODE* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

static void update_height(AVL_NODE* n) {
    if (n) n->height = 1 + max2(height(n->left), height(n->right));
}

static AVL_NODE* create_node(int data) {
    AVL_NODE* n = (AVL_NODE*)malloc(sizeof(AVL_NODE));
    n->data = data; n->height = 1;
    n->left = n->right = NULL;
    return n;
}

// LL 회전 (우회전): 왼쪽 자식이 과도하게 커졌을 때
//      z              y
//     / \            / \
//    y   T4  →     x    z
//   / \           / \  / \
//  x  T3         T1 T2 T3 T4
static AVL_NODE* rotate_right(AVL_NODE* z) {
    AVL_NODE* y  = z->left;
    AVL_NODE* T3 = y->right;
    y->right = z;
    z->left  = T3;
    update_height(z);
    update_height(y);
    return y;
}

// RR 회전 (좌회전): 오른쪽 자식이 과도하게 커졌을 때
static AVL_NODE* rotate_left(AVL_NODE* z) {
    AVL_NODE* y  = z->right;
    AVL_NODE* T2 = y->left;
    y->left  = z;
    z->right = T2;
    update_height(z);
    update_height(y);
    return y;
}

// 불균형 해소: balance factor에 따라 적절한 회전 수행
static AVL_NODE* rebalance(AVL_NODE* n) {
    update_height(n);
    int bf = balance_factor(n);

    if (bf > 1) { // 왼쪽 과부하
        if (balance_factor(n->left) < 0) // LR 케이스
            n->left = rotate_left(n->left);
        return rotate_right(n); // LL 케이스
    }
    if (bf < -1) { // 오른쪽 과부하
        if (balance_factor(n->right) > 0) // RL 케이스
            n->right = rotate_right(n->right);
        return rotate_left(n); // RR 케이스
    }
    return n; // 균형 유지
}

AVL_NODE* avl_insert(AVL_NODE* root, int data) {
    if (!root) return create_node(data);
    if (data < root->data)      root->left  = avl_insert(root->left,  data);
    else if (data > root->data) root->right = avl_insert(root->right, data);
    return rebalance(root);
}

static AVL_NODE* avl_min(AVL_NODE* n) {
    while (n->left) n = n->left;
    return n;
}

AVL_NODE* avl_delete(AVL_NODE* root, int data) {
    if (!root) return NULL;
    if (data < root->data) {
        root->left  = avl_delete(root->left,  data);
    } else if (data > root->data) {
        root->right = avl_delete(root->right, data);
    } else {
        if (!root->left || !root->right) {
            AVL_NODE* tmp = root->left ? root->left : root->right;
            free(root);
            return tmp;
        }
        AVL_NODE* successor = avl_min(root->right);
        root->data  = successor->data;
        root->right = avl_delete(root->right, successor->data);
    }
    return rebalance(root);
}

void avl_inorder(AVL_NODE* root) {
    if (!root) return;
    avl_inorder(root->left);
    printf("%d(h=%d) ", root->data, root->height);
    avl_inorder(root->right);
}

void avl_free(AVL_NODE* root) {
    if (!root) return;
    avl_free(root->left);
    avl_free(root->right);
    free(root);
}

void avl_main() {
    printf("===== AVL 트리 =====\n");
    AVL_NODE* root = NULL;

    // 순서대로 삽입하면 일반 BST는 편향되지만 AVL은 자동 균형 유지
    int values[] = {10, 20, 30, 40, 50, 25};
    for (int i = 0; i < 6; i++) {
        root = avl_insert(root, values[i]);
        printf("%d 삽입 후 루트: %d (높이: %d)\n",
               values[i], root->data, root->height);
    }

    printf("중위 순회: ");
    avl_inorder(root);
    printf("\n");

    root = avl_delete(root, 30);
    printf("30 삭제 후: ");
    avl_inorder(root);
    printf("\n루트: %d\n", root->data);

    avl_free(root);
}
