#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include "btree_node.h"

template<typename T>
class BTree{
public:
    BTree(size_t min=1, bool dupes=false);
    //BIG3
    ~BTree();
    BTree(const BTree<T>& copy);
    BTree<T>& operator =(const BTree<T>& copy);
    //MEMBER FUNCTIONS
    bool insert(const T& input);
    bool remove(const T& input);

    bool exists(const T& input);
    T& get(const T& input);

    void print();
    bool verify() const;
    size_t size() const;
    template<typename U>
    friend std::ostream& operator <<(std::ostream& outs, BTree<U>& bt);
private:
    size_t _min;
    bool __dupes;
    btree_node<T>* __head;
};

template<typename T>
BTree<T>::BTree(size_t min, bool dupes): _min(min), __dupes(dupes){
    __head = new btree_node<T>(min, dupes);
}
template<typename T>
BTree<T>::~BTree(){
    delete __head;
}
template<typename T>
BTree<T>::BTree(const BTree<T>& copy){
    /*this->*/
    _min = copy._min;
    __dupes = copy.__dupes;
    __head = new btree_node<T>((*copy.__head));
}
template<typename T>
BTree<T>& BTree<T>::operator =(const BTree<T>& copy){
    if(this == (&copy))
        return (*this);
    BTree temp(copy);
    swap(_min, temp._min);
    swap(__dupes, temp.__dupes);
    swap(__head, temp.__head);
    return (*this);
}
template<typename T>
bool BTree<T>::insert(const T &input){
    bool check = __head->insert(input);
    fix_excess(__head);
//    assert(__head->verify());
    return check;
}
template<typename T>
bool BTree<T>::remove(const T &input){
    //Tries to remove a desired input;
    //Returns false if no found input;
    bool check = __head->remove(input);
    //Check if __head needs reorganizing too
    fix_excess(__head);
    return check;
}
template<typename T>
void BTree<T>::print(){
    __head->print();
}
template<typename T>
bool BTree<T>::verify() const{
    bool check = __head->verify();
//    if(check)
//        cout << "----VERIFIED----\n";
//    else
//        cout << "!!!!FAILED VERIFICATION!!!!\n";
    return check;
}
template<typename T>
std::ostream& operator <<(std::ostream& outs, BTree<T>& bt){
    bt.print();
    return outs;
}
template<typename T>
bool BTree<T>::exists(const T &input){
    return (__head->exists(input) != nullptr);
}
template<typename T>
T& BTree<T>::get(const T &input){
    T* val = __head->exists(input);
    assert(val!=nullptr);
    return (*val);
}
template<typename T>
size_t BTree<T>::size() const{
    return __head->size();
}

#endif // BTREE_H
