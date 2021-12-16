//
// Created by pokawa on 27.03.2019.
//

#include <queue>
#include "BST.h"

void BST::search(int key) {
    BSTNode* i = root;
    while (i && i->value != key) {
        if (key > i->value)
            i = i->right;
        else
            i = i->left;
    }
}

void BST::insert(int value) {
    if (root == nullptr) {
        root = new BSTNode{value, nullptr, nullptr};
    }
    else {
        BSTNode * i = root;
        while(i) {
            if (value > i->value)
                if (i->right)
                    i = i->right;
                else {
                    i->right = new BSTNode{value, nullptr, nullptr};
                    break;
                }
            else
                if (i->left)
                    i = i->left;
                else {
                    i->left = new BSTNode{value, nullptr, nullptr};
                    break;
                }
            }
    }
}


BST::BST() : root(nullptr) {}

void BST::deletePostorder(BSTNode*& i)
{
    if (i != nullptr)
    {
        deletePostorder(i->left);
        deletePostorder(i->right);
        delete i;
        i = nullptr;
    }
}

void BST::printInorder(BSTNode* i)
{
    if (i != nullptr) 
    {
        printInorder(i->left);
	    std::cout << i->value << " ";
        printInorder(i->right);
    }
}

void BST::deletePostorder() {
    deletePostorder(root);
}

void BST::printInorder() {
    printInorder(root);
}

std::vector<int> BST::getInorder(std::vector<int> & out) {
    return getInorder(root, out);
}

std::vector<int> BST::getInorder(BSTNode * i, std::vector<int> & out) {
    if (i != nullptr)
    {
        getInorder(i->left, out);
        out.push_back(i->value);
        getInorder(i->right, out);
    }
    return out;
}

std::vector<int> BST::getInorder() {
    std::vector<int>out;
    return getInorder(out);
}

int BST::getHeight(BSTNode* i) {
    if (i == nullptr)
        return 0;
    return 1 + std::max(getHeight(i->left), getHeight(i->right));
}

int BST::getHeight() {
    return getHeight(root);
}

void BST::buildBST(const std::vector<int> in) {
    for (auto i : in)
        insert(i);
}

std::vector<int> binaryOrder(const std::vector<int> &in)
{
    std::vector<int> out;
    std::queue<int> l,r;
    int a;
    l.push(0);
    r.push((int)in.size()-1);
    while(!l.empty() && !r.empty())
    {
        a = (l.front() + r.front()) / 2;
        out.push_back(in[a]);
        if (r.front() - l.front() > 1)
        {
            l.push(l.front());
            r.push(a - 1);
        }
        if (r.front() - l.front())
        {
            l.push(a + 1);
            r.push(r.front());
        }
        l.pop();
        r.pop();
    }
    return out;
}

void BST::buildALV(std::vector<int> in) {
    std::vector<int> data = binaryOrder(in);
    deletePostorder();
    for (auto a : data)
        insert(a);
}

void BST::buildALV() {
    buildALV(getInorder());
}








