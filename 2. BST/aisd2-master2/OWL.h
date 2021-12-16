//
// Created by pokawa on 27.03.2019.
//

#ifndef AISD2_OWL_H
#define AISD2_OWL_H

#include <vector>

struct OWLNode {
    long long value;
    OWLNode *next;
};

class OWL {
private:
    OWLNode *first;
public:
    long long size;

    OWL();

    void insert(long long);

    long long &get(long long);

    void build(std::vector<long long>);

    void popFirst();

    long long &operator[](long long);

    void search(long long);

    void clear();
};


#endif //AISD2_OWL_H
