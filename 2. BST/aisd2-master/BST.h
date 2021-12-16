//
// Created by pokawa on 27.03.2019.
//

#ifndef AISD2_BST_H
#define AISD2_BST_H

#include <vector>
#include <iostream>



struct BSTNode
{
    int value;
    BSTNode* left;
    BSTNode* right;
};

class BST {
public:
    void insert(int);
    void buildBST(std::vector<int> in);
    void buildALV(std::vector<int> in);
    void buildALV();
    BSTNode* root;
    void search(int);
    void printInorder(BSTNode *);
    std::vector<int> getInorder(BSTNode *, std::vector<int>&);
    std::vector<int> getInorder(std::vector<int>&);
    std::vector<int> getInorder();
    void printInorder();
    BST();
    void deletePostorder(BSTNode*&);
    void deletePostorder();
    int getHeight(BSTNode*);
    int getHeight();

};


#endif //AISD2_BST_H
