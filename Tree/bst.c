#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

// 이진 탐색 트리 (BST): 왼쪽 < 부모 < 오른쪽 규칙으로 정렬된 이진 트리
// 평균 탐색/삽입/삭제: O(log n), 최악(편향): O(n)

// 새 노드 생성
static BST_NODE* create_node(int data) {
    BST_NODE* node = (BST_NODE*)malloc(sizeof(BST_NODE));
    node->data  = data;
    node->left  = NULL;
    node->right = NULL;
    return node;
}

// 삽입: 값에 따라 왼쪽/오른쪽으로 내려가며 빈 자리에 삽입
BST_NODE* bst_insert(BST_NODE* root, int data) {
    if (root == NULL) return create_node(data);
    if (data < root->data)
        root->left  = bst_insert(root->left,  data);
    else if (data > root->data)
        root->right = bst_insert(root->right, data);
    // data == root->data: 중복 삽입 무시
    return root;
}

// 탐색: 찾으면 노드 반환, 없으면 NULL
BST_NODE* bst_search(BST_NODE* root, int data) {
    if (root == NULL || root->data == data) return root;
    if (data < root->data) return bst_search(root->left,  data);
    else                   return bst_search(root->right, data);
}

// 서브트리에서 최솟값 노드 반환 (delete에서 후계자 탐색에 사용)
BST_NODE* bst_min(BST_NODE* root) {
    if (root == NULL) return NULL;
    while (root->left != NULL) root = root->left;
    return root;
}

// 서브트리에서 최댓값 노드 반환
BST_NODE* bst_max(BST_NODE* root) {
    if (root == NULL) return NULL;
    while (root->right != NULL) root = root->right;
    return root;
}

// 삭제: 3가지 경우 처리
// 1) 자식 없음: 그냥 제거
// 2) 자식 1개: 자식으로 대체
// 3) 자식 2개: 오른쪽 서브트리의 최솟값(중위 후계자)으로 대체
BST_NODE* bst_delete(BST_NODE* root, int data) {
    if (root == NULL) return NULL;

    if (data < root->data) {
        root->left  = bst_delete(root->left,  data);
    } else if (data > root->data) {
        root->right = bst_delete(root->right, data);
    } else {
        // 삭제할 노드 발견
        if (root->left == NULL) {
            BST_NODE* tmp = root->right;
            free(root);
            return tmp;
        } else if (root->right == NULL) {
            BST_NODE* tmp = root->left;
            free(root);
            return tmp;
        }
        // 자식 2개: 중위 후계자(오른쪽 서브트리 최솟값)로 교체
        BST_NODE* successor = bst_min(root->right);
        root->data  = successor->data;
        root->right = bst_delete(root->right, successor->data);
    }
    return root;
}

// 중위 순회 출력 → 정렬된 순서로 출력됨
void bst_inorder(BST_NODE* root) {
    if (root == NULL) return;
    bst_inorder(root->left);
    printf("%d ", root->data);
    bst_inorder(root->right);
}

// 메모리 해제
void bst_free(BST_NODE* root) {
    if (root == NULL) return;
    bst_free(root->left);
    bst_free(root->right);
    free(root);
}

void bst_main() {
    printf("===== BST (이진 탐색 트리) =====\n");
    BST_NODE* root = NULL;
    int values[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++)
        root = bst_insert(root, values[i]);

    printf("중위 순회 (정렬): ");
    bst_inorder(root);
    printf("\n");

    printf("40 탐색: %s\n", bst_search(root, 40) ? "발견" : "없음");
    printf("99 탐색: %s\n", bst_search(root, 99) ? "발견" : "없음");
    printf("최솟값: %d\n", bst_min(root)->data);
    printf("최댓값: %d\n", bst_max(root)->data);

    root = bst_delete(root, 30);
    printf("30 삭제 후: ");
    bst_inorder(root);
    printf("\n");

    bst_free(root);
}
