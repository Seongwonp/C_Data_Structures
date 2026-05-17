#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct avl_node {
    int data;
    int height;
    struct avl_node* left;
    struct avl_node* right;
} AVL_NODE;

AVL_NODE* avl_insert(AVL_NODE* root, int data);
AVL_NODE* avl_delete(AVL_NODE* root, int data);
void avl_inorder(AVL_NODE* root);
void avl_free(AVL_NODE* root);
void avl_main();

#endif //AVL_TREE_H
