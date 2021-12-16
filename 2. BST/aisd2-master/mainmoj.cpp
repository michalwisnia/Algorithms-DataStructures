#include <iostream>
#include <vector>
#include "OWL.h"
#include "BST.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <queue>

struct Listnode
{
    int value;
    Listnode *next;

};
class SList
{
    public:
    Listnode *first, *last;
    list()
    {
        first=NULL;
        last=NULL;
    }
    Slist();
    void buildlist(std::vector<int> in);
    void insert(int);
    void deletefirst();
    void print();
    void search(int);
};

void SList::insert(int value)
{
      Listnode *temp=new Listnode;
      temp->value=value;
      temp->next=NULL;
      if(first==NULL)
      {
        first=temp;
        last=temp;
        temp=NULL;
      }
      else
      {
        last->next=temp;
        last=temp;
      }
}

void SList::buildlist(const std::vector<int> in)
{
    for (auto i : in)
        SList::insert(i);
}

void SList::search(int value)
{
    Listnode* temp = first;
    while (temp->next != nullptr && temp->value != value)
    {
        temp = temp->next;
    }
}

void SList::deletefirst()
{
    Listnode *temp = new Listnode;
    temp=first;
    while(temp)
    {   first=first->next;
        delete temp;
        Listnode *temp = new Listnode;
    }
}

void SList::print()
{
    Listnode *temp = new Listnode;
    temp=first;
    if (temp == NULL) std::cout << "Empty";
    else
    {while(temp!=NULL)
    {
        std::cout<<temp->value<<" ";
        temp=temp->next;
    }
    }
}

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

std::random_device rd;
std::mt19937 g(rd());

std::vector<int> getData(unsigned int size)
{
    std::vector<int> out(size);
    for (int & i : out)
        i = size--;
    std::shuffle(out.begin(), out.end(), g);
    return out;
}

long long time_buildBST(int datasize)
{
    std::vector<int> data = getData(datasize);
    std::chrono::high_resolution_clock::time_point p1 = std::chrono::high_resolution_clock::now();
    BST bst;
    bst.buildBST(data);
    std::chrono::high_resolution_clock::time_point p2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(p2 - p1).count();

}

long long time_buildlist(int datasize)
{
    std::vector<int> data = getData(datasize);
    std::chrono::high_resolution_clock::time_point p1 = std::chrono::high_resolution_clock::now();
    SList slist;
    slist.buildlist(data);
    std::chrono::high_resolution_clock::time_point p2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(p2 - p1).count();
}

long long time_searchBST(std::vector<int> in, BST bst)
{
    std::chrono::high_resolution_clock::time_point p1 = std::chrono::high_resolution_clock::now();
    for (auto i: in)
    {
        bst.search(i);
    }
    std::chrono::high_resolution_clock::time_point p2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(p2 - p1).count();
}

long long time_searchlist(std::vector<int> in, SList slist)
{
    std::chrono::high_resolution_clock::time_point p1 = std::chrono::high_resolution_clock::now();
    for (auto i: in)
    {
        slist.search(i);
    }
    std::chrono::high_resolution_clock::time_point p2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(p2 - p1).count();
}

long long time_deleteBST(BST bst)
{
    std::chrono::high_resolution_clock::time_point p1 = std::chrono::high_resolution_clock::now();
        bst.deletePostorder();
    std::chrono::high_resolution_clock::time_point p2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(p2 - p1).count();
}

long long time_deletelist(SList slist)
{
    std::chrono::high_resolution_clock::time_point p1 = std::chrono::high_resolution_clock::now();

    slist.deletefirst();

    std::chrono::high_resolution_clock::time_point p2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(p2 - p1).count();
}



int main()
{

    for (int i=100000;i<2000000;i+=100000)
    {
        std::cout<<i<<" "<<time_buildBST(i)<<" "<<time_buildlist(i)<<std::endl;
    }
    //int tab[10]={4,68,234,2,24,6,100,1,500,125};
    std::vector<int> data = getData(10000);
    BST bst;
    bst.buildBST(data);
    SList slist;
    slist.buildlist(data);



    //std::cout<<time_searchBST(data, bst)<<" "<<time_searchlist(data,slist)<<std::endl;






    return 0;
}
