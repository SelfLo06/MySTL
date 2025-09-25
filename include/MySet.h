#ifndef MYSTL_MYSET_H
#define MYSTL_MYSET_H

#include "MyBST.h"

template <typename T>
class MySet {
private:
    MyBST<T> _tree;

public:
    void insert(const T& value);
    bool contains(const T& value) const;
    void erase(const T& value);
    size_t size() const;
    bool empty() const;
    void clear();
};

template<typename T>
void MySet<T>::insert(const T &value) {
    _tree.insert(value);
}

template<typename T>
bool MySet<T>::contains(const T &value) const {
    return _tree.find(value);
}

template<typename T>
void MySet<T>::erase(const T &value) {
    _tree.remove(value);
}

template<typename T>
size_t MySet<T>::size() const {
    return _tree.size();
}

template<typename T>
bool MySet<T>::empty() const {
    return _tree.empty();
}

template<typename T>
void MySet<T>::clear() {
    _tree.clear();
}

#endif //MYSTL_MYSET_H