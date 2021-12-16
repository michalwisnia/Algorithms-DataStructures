//
// Created by pokawa on 27.03.2019.
//

#include <queue>
#include "BST.h"

void BST::search(long long key) {
    BSTNode* i = root;
    while (i && i->value != key) {
        if (key > i->value)
            i = i->right;
        else
            i = i->left;
    }
}

void BST::insert(long long value) {
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

int BST::getHeight(BSTNode* i) {
    if (i == nullptr)
        return 0;
    return 1 + std::max(getHeight(i->left), getHeight(i->right));
}

int BST::getHeight() {
    return getHeight(root);
}

void BST::buildBST(const std::vector<long long> in) {
    for (auto i : in)
        insert(i);
}

void BST::buildALV(std::vector<long long> in) {
    deletePostorder();
    std::queue<long long> l,r;
    long long a;
    l.push(0);
    r.push((long long)in.size()-1);
    while(!l.empty() && !r.empty())
    {
        a = (l.front() + r.front()) / 2;
        insert(in[a]);
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
}

void BST::printPostorder(BSTNode * i) {
    if (i != nullptr)
    {
        printInorder(i->left);
        printInorder(i->right);
        std::cout << i->value << " ";

    }
}

void BST::printPostorder() {
    printPostorder(root);
}

void BST::printPreorder() {
    printPreorder(root);
}

void BST::printPreorder(BSTNode* i) {
    if (i != nullptr)
    {
        std::cout << i->value << " ";
        printInorder(i->left);
        printInorder(i->right);
    }
}

std::vector<long long> BST::getInorder(const long long & size) {
    std::vector<long long>out(size);
    auto a = out.begin();
    getInorder(root, a, out);
    return out;
}

void BST::getInorder(BSTNode * i, std::vector<long long> ::iterator &iter, std::vector<long long> & out) {
    if (i != nullptr)
    {
        getInorder(i->left, iter, out);
        *(iter++) = (i->value);
        getInorder(i->right, iter, out);
    }
}










