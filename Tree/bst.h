#ifndef BST_H
#define BST_H

typedef struct bst_node {
    int data;
    struct bst_node* left;
    struct bst_node* right;
} BST_NODE;

BST_NODE* bst_insert(BST_NODE* root, int data);
BST_NODE* bst_search(BST_NODE* root, int data);
BST_NODE* bst_delete(BST_NODE* root, int data);
BST_NODE* bst_min(BST_NODE* root);
BST_NODE* bst_max(BST_NODE* root);
void bst_inorder(BST_NODE* root);
void bst_free(BST_NODE* root);
void bst_main();

#endif //BST_H
