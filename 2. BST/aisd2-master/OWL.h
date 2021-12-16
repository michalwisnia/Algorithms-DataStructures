//
// Created by pokawa on 27.03.2019.
//

#ifndef AISD2_OWL_H
#define AISD2_OWL_H

#include <vector>

struct OWLNode {
    int value;
    OWLNode *next;
};

class OWL {
private:
    OWLNode *first;
public:
    int size;

    OWL();

    void insert(int);

    int &get(unsigned int);

    void build(std::vector<int>);

    void popFirst();

    int &operator[](unsigned int);

    void search(int);

    void clear();
};


#endif //AISD2_OWL_H
