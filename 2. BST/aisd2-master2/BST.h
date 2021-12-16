//
// Created by pokawa on 27.03.2019.
//

#ifndef AISD2_BST_H
#define AISD2_BST_H

#include <vector>
#include <iostream>


struct BSTNode
{
    long long value;
    BSTNode* left;
    BSTNode* right;
};

class BST {
public:
    void insert(long long);
    void buildBST(std::vector<long long> in);
    void buildALV(std::vector<long long> in);
    BSTNode* root;
    void search(long long);
    void printInorder(BSTNode *);
    void getInorder(BSTNode * i, std::vector<long long>::iterator &, std::vector<long long> & );
    std::vector<long long> getInorder(const long long& );
    void printInorder();
    void printPostorder();
    void printPostorder(BSTNode*);
    void printPreorder(BSTNode*);
    void printPreorder();
    BST();
    void deletePostorder(BSTNode*&);
    void deletePostorder();
    int getHeight(BSTNode*);
    int getHeight();

};


#endif //AISD2_BST_H
