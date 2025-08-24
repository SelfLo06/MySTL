#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <cstddef>

template <typename T>
class MyVector {

public:
    // 定义迭代器
    class iterator {
    public:
        // 构造函数：用一个 T* 指针来初始化迭代器
        iterator(T* ptr) : _ptr(ptr) {}

        // 1. 解引用操作 (*it)
        // 返回指针指向的元素的引用
        T& operator*() {
            return *_ptr;
        }

        // 2. 不等比较操作 (it != other_it)
        // 比较两个迭代器是否指向同一个位置
        bool operator!=(const iterator& other) const {
            return _ptr != other._ptr;
        }

        bool operator==(const iterator& other) const {
            return _ptr == other._ptr;
        }

        // 3. 前缀递增操作 (++it)
        // 将指针向前移动一位，并返回自身的引用
        iterator& operator++() {
            ++_ptr;
            return *this;
        }

    private:
        T* _ptr; // 迭代器内部的核心就是一个原生指针
    };


    // 构造与析构
    MyVector();
    MyVector(const MyVector& other); // 拷贝构造函数
    MyVector& operator=(const MyVector& other); // 拷贝赋值运算符
    ~MyVector();

    // 容量相关
    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }
    bool empty() const;

    // 元素访问
    T& operator[](size_t index);
    const T& operator[](size_t index) const; //  const 版本

    T& back() {
        if (empty()) {
            throw std::out_of_range("back() called on empty vector");
        }
        return _data[_size - 1];
    }

    const T& back() const {
        if (empty()) {
            throw std::out_of_range("back() called on empty vector");
        }
        return _data[_size - 1];
    }

    iterator begin() {
        // begin() 应该返回一个指向第一个元素的迭代器
        // 如何用 _data 创建一个迭代器？
        return iterator(_data);
    }

    iterator end() {
        // end() 应该返回一个指向“尾后”位置的迭代器
        // 这个位置是最后一个元素的下一个位置。这是STL的惯例。
        // 思考：如果 _data 指向开始，_size 是元素个数，那么尾后位置的指针是什么？
        return iterator(_data + _size);
    }

    // 修改器
    void push_back(const T& value);
    void pop_back();
    void clear();

private:
    T* _data;
    size_t _size;
    size_t _capacity;

    void _resize(size_t new_capacity);

};

/*
 *C++“三法则”：
 *如果一个类需要自定义析构函数、拷贝构造函数或拷贝赋值运算符中的任意一个，那么它很可能需要同时定义这三个。
*/

template <typename T>
MyVector<T>::MyVector() : _data(nullptr), _size(0), _capacity(0) {
    std::cout << "Default constructor called!" << std::endl;
}

// In MyVector.h, after the destructor's implementation
template <typename T>
MyVector<T>::MyVector(const MyVector& other)
    // C++ 推荐使用成员初始化列表来初始化成员变量
    : _size(other._size), _capacity(other._capacity), _data(nullptr)
{
    std::cout << "Copy constructor called!" << std::endl;

    // 思考：如果 other 是一个空的 vector (capacity 为 0)，我们还需要 new 内存吗？
    if (other._capacity > 0) {
        // 1. 为 _data 分配一块新的、属于自己的内存。
        //    大小应该是多少？
        _data = new T[other.capacity()];

        // 2. 将 'other' 对象中的数据逐个拷贝到这块新内存中。
        //    应该循环多少次？是从 0 到 _size 还是 _capacity？
        for (size_t i = 0; i < other.size(); ++i) {
            _data[i] = other._data[i];
        }
    }
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    std::cout << "Copy assignment operator called!" << std::endl;

    // 步骤 1: 检查自我赋值
    // 思考：如果有人写了 vec1 = vec1; 会发生什么？
    // 如果不加检查，delete[] _data; 会释放掉自己，后面就无法从自己这里拷贝数据了。
    if (this == &other) { // 'this' 是一个指向当前对象的指针
        return *this;
    }

    // 步骤 2: 释放当前对象已有的内存
    // 因为我们将要从 'other' 拷贝新的数据，所以旧的内存不再需要。
    /* ... 释放 _data 指向的内存 ... */
    delete[] _data;


    // 步骤 3: 进行和拷贝构造函数几乎一样的深拷贝
    _size = other._size;
    _capacity = other._capacity;
    _data = nullptr; // 好习惯：在分配新内存前，先将指针置为 nullptr

    if (other._capacity > 0) {
        // 分配新内存
        _data = new T[_capacity];
        // 循环拷贝数据
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = other._data[i];
        }
    }

    // 为什么 operator= 需要返回 MyVector<T>&？
    // 步骤 4: 返回对当前对象的引用
    // 这是为了支持链式赋值，例如 a = b = c;
    return *this;
}

template <typename T>
MyVector<T>::~MyVector() {
    std::cout << "Destructor called!" << std::endl;
    delete[] _data;
}

template <typename T>
void MyVector<T>::push_back(const T& value) {
    if (_size == _capacity) {
        _resize(_capacity == 0 ? 1 : _capacity * 2);
    }
    _data[_size++] = value;
}

template <typename T>
void MyVector<T>::_resize(size_t new_capacity) {
    std::cout << "Resizing from " << _capacity << " to " << new_capacity << std::endl;
    T* new_data = new T[new_capacity];
    for (size_t i = 0; i < _size; i++) {
        new_data[i] = _data[i];
    }
    delete[] _data;
    _data = new_data;
    _capacity = new_capacity;
}

template<typename T>
bool MyVector<T>::empty() const {return _size == 0;}


template<typename T>
T& MyVector<T>::operator[](size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}

template<typename T>
const T &MyVector<T>::operator[](size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}

template<typename T>
void MyVector<T>::pop_back() {
    if (_size > 0) _size--;
}

template<typename T>
void MyVector<T>::clear() {
    _size = 0;
}


#endif