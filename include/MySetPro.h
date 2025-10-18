#ifndef MYSTL_MYSETPRO_H
#define MYSTL_MYSETPRO_H

#include "MyTreap.h"

template <typename T>
class MySetPro {
private:
    MyTreap<T> _tree;

public:
    void insert(const T& value);
    bool contains(const T& value) const;
    void erase(const T& value);
    size_t size() const;
    bool empty() const;
    void clear();
};

template<typename T>
void MySetPro<T>::insert(const T &value) {
    _tree.insert(value);
}

template<typename T>
bool MySetPro<T>::contains(const T &value) const {
    return _tree.find(value);
}

template<typename T>
void MySetPro<T>::erase(const T &value) {
    _tree.remove(value);
}

template<typename T>
size_t MySetPro<T>::size() const {
    return _tree.size();
}

template<typename T>
bool MySetPro<T>::empty() const {
    return _tree.empty();
}

template<typename T>
void MySetPro<T>::clear() {
    _tree.clear();
}

#endif //MYSTL_MYSETPRO_H