#ifndef BSTREE_H
#define BSTREE_H
/*
 * Class for a binary search tree (BST) with integer keys
 * for Data Structures (BST) lab
 */
#include <iostream>

class BST {
    public:
    BST();
    ~BST();

    void unbalancedInsert(int v);

    void inOrder(std::ostream& out) const;
    void preOrder(std::ostream& out) const;
    void levelOrder(std::ostream& out) const;

    void postOrderDelete();

    private:
    struct BSTNode {
        int      value;
        BSTNode* left;
        BSTNode* right;
    };
    BSTNode* root;

    BSTNode* newBSTNode(int v);
    BSTNode* newBSTNode(int v, BSTNode* left, BSTNode* right);

    bool     isEmpty(BSTNode* curr) const;
    BSTNode* unbalancedInsert(BSTNode* curr, int v);
    void     inOrder(BSTNode* curr, std::ostream& out) const;
    void     preOrder(BSTNode* curr, std::ostream& out) const;
    void     levelOrder(BSTNode* curr, std::ostream& out) const;
    void     postOrderDelete(BSTNode* curr);
};

#endif
