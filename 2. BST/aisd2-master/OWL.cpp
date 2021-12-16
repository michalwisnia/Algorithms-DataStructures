//
// Created by pokawa on 27.03.2019.
//

#include "OWL.h"

void OWL::insert(int value) {
    if (!size) {
        first = new OWLNode{value, nullptr};
    } else {
        if (value > first->value)
            first = new OWLNode{value, first};
        else {
            OWLNode *i = first;
            while (i->next && value <= i->next->value)
                i = i->next;
            i->next = new OWLNode{value, i->next};
        }
    }
    size++;
}

void OWL::popFirst() {
    OWLNode *del = first;
    first = first->next;
    delete del;
    size--;
}

int &OWL::get(unsigned int index) {
    if (index > size - 1)
        return first->value;

    OWLNode *i = first;
    for (index; index; index--, i = i->next);
    return i->value;
}

OWL::OWL() : size(0) {}

int &OWL::operator[](unsigned int index) {
    return get(index);
}

void OWL::search(int value) {
    OWLNode* i = first;
    while(i->next && i->value != value)
        i = i->next;
}

void OWL::build(const std::vector<int> in) {
    for (auto a : in)
        insert(a);
}

void OWL::clear() {
    while (size)
        popFirst();
}
