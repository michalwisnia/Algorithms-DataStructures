#include <iostream>
#include <vector>
#include "OWL.h"
#include "BST.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <fstream>


std::random_device rd;
std::mt19937 g(rd());

std::vector<long long > getData(long long  size)
{
    std::vector<long long> out(size);
    for (long long & i : out)
        i = size--;
    std::shuffle(out.begin(), out.end(), g);
    return out;
}

#define START 1000
#define STEP 1000

void meassuresBST()
{
    std::fstream file;
    std::chrono::high_resolution_clock::time_point t1, t2;
    file.open("BST.txt", std::ios::out);
    file << "ilosc budowa szukanie usuwanie\n\r";
    std::cout << "Badanie dla BST \r\n";
    for (int j = 0; j < 15; j++) {
        long long results[3] = {0};
        for (int i = 0; i < 5; i++) {
            auto data = getData(START + j * STEP);
            BST bst;
            //Build time
            t1 = std::chrono::high_resolution_clock::now();
            bst.buildBST(data);
            t2 = std::chrono::high_resolution_clock::now();
            results[0] += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 5;

            std::shuffle(data.begin(), data.end(), g);
            //Searching time
            t1 = std::chrono::high_resolution_clock::now();
            for (auto b : data)
                bst.search(b);
            t2 = std::chrono::high_resolution_clock::now();
            results[1] += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 5;

            //Searching time
            t1 = std::chrono::high_resolution_clock::now();
            bst.deletePostorder();
            t2 = std::chrono::high_resolution_clock::now();
            results[2] += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 5;
        }
        file << START + j * STEP << " " << results[0] << " " << results[1] << " " << results[2] << "\n\r";
        std::cout << START + j * STEP << " " << results[0] << " " << results[1] << " " << results[2] << "\n\r";
    }
    file.close();
}

void meassureOWL()
{
    std::fstream file;
    std::chrono::high_resolution_clock::time_point t1, t2;
    file.open("OWL.txt", std::ios::out);
    file << "ilosc budowa szukanie usuwanie\n\r";
    std::cout << "Badanie dla OWL \r\n";
    for (int j = 0; j < 15; j++) {
        long long results[3] = {0};
        for (int i = 0; i < 5; i++) {
            auto data = getData(START + j * STEP);
            OWL owl;
            //Build time
            t1 = std::chrono::high_resolution_clock::now();
            owl.build(data);
            t2 = std::chrono::high_resolution_clock::now();
            results[0] += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 5;

            std::shuffle(data.begin(), data.end(), g);
            //Searching time
            t1 = std::chrono::high_resolution_clock::now();
            for (auto b : data)
                owl.search(b);
            t2 = std::chrono::high_resolution_clock::now();
            results[1] += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 5;

            //Searching time
            t1 = std::chrono::high_resolution_clock::now();
            owl.clear();
            t2 = std::chrono::high_resolution_clock::now();
            results[2] += std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 5;
        }
        file << START + j * STEP << " " << results[0] << " " << results[1] << " " << results[2] << "\n\r";
        std::cout << START + j * STEP << " " << results[0] << " " << results[1] << " " << results[2] << "\n\r";
    }
    file.close();
}

void meassureHeight()
{
    std::fstream file;
    file.open("AVL.txt", std::ios::out);
    file << "ilosc bst avl\n\r";
    std::cout << "Badanie dla AVL \r\n";
    for (int j = 0; j < 15; j++) {
        long long results[2] = {0};
        long long size = START * std::pow(2,j);
        for (int i = 0; i < 5; i++) {
            auto data = getData(size);
            BST bst;
            //Build time
            bst.buildBST(data);
            results[0] += bst.getHeight();

            auto foo = bst.getInorder(size);
            bst.buildALV(foo);
            results[1] += bst.getHeight();
        }
        file << size << " " << results[0] / 5 << " " << results[1] / 5 << "\n\r";
        std::cout << size << " " << results[0] / 5 << " " << results[1] / 5 << "\n\r";
    }
    file.close();
}


int main() 
{
    meassuresBST();
    meassureOWL();
    meassureHeight();
    return 0;
}
