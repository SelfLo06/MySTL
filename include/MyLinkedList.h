#ifndef MYLINKEDLIST_H
#define MYLINKEDLIST_H

#include <cstddef>
#include <iostream>
#include <stdexcept> // for std::out_of_range

template <typename T>
class MyLinkedList {
private:
    // 定义节点
    struct Node {
        T data;
        Node* next;
        Node* prev;

        // 节点的构造函数，方便我们创建新节点
        Node(const T& value);
    };


    Node* _head;
    Node* _tail;
    size_t _size;

public:
    // 双向迭代器
    class iterator {
    public:
        // 构造函数
        iterator(Node* ptr);

        // 解引用 (*it)，返回节点数据的引用
        T& operator*();

        // 成员访问 (it->member)，返回节点指针，以便访问 T 的成员
        T* operator->();

        // 前缀递增 (++it)
        iterator& operator++();

        // 前缀递减 (--it)
        iterator& operator--();

        // 比较操作 (it == other, it != other)
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;

    private:
        Node* _node_ptr; // 迭代器内部封装的是一个 Node 指针
    };

    // 反向迭代器
    class reverse_iterator {
    public:
        // 构造函数，接收一个普通迭代器
        reverse_iterator(iterator it);

        T& operator*();
        reverse_iterator& operator++();
        reverse_iterator& operator--();

        // 比较操作: 直接比较内部的 current 迭代器
        bool operator==(const reverse_iterator& other) const;
        bool operator!=(const reverse_iterator& other) const;

    private:
        iterator current; // 内部封装了一个正向迭代器
    };

    // 构造函数
    MyLinkedList();

    // 拷贝构造函数
    MyLinkedList(const MyLinkedList& other);

    // 拷贝赋值运算符
    MyLinkedList& operator=(const MyLinkedList& other);

    // 析构函数 (非常重要！)
    ~MyLinkedList();

    // 返回链表大小
    size_t size() const;

    // 判断链表是否为空
    bool empty() const;

    void push_back(const T& value);
    void push_front(const T& value);

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;

    void pop_front();
    void pop_back();

    iterator begin();
    iterator end();

    reverse_iterator rbegin();
    reverse_iterator rend();
};


// 节点构造函数
template <typename T>
MyLinkedList<T>::Node::Node(const T& value)
    : data(value), next(nullptr), prev(nullptr) {}

// ------------------- 迭代器实现 -------------------

// 构造函数
template <typename T>
MyLinkedList<T>::iterator::iterator(Node* ptr) : _node_ptr(ptr) {}

// 解引用 (*it)，返回节点数据的引用
template <typename T>
T& MyLinkedList<T>::iterator::operator*() {
    return _node_ptr->data;
}

// 成员访问 (it->member)，返回节点指针，以便访问 T 的成员
template <typename T>
T* MyLinkedList<T>::iterator::operator->() {
    return &(_node_ptr->data);
}

// 前缀递增 (++it)
template <typename T>
typename MyLinkedList<T>::iterator& MyLinkedList<T>::iterator::operator++() {
    // 思考: 如何移动到下一个节点？
    _node_ptr = _node_ptr->next;
    return *this;
}

// 前缀递减 (--it)
template <typename T>
typename MyLinkedList<T>::iterator& MyLinkedList<T>::iterator::operator--() {
    // 思考: 如何移动到上一个节点？
    _node_ptr = _node_ptr->prev;
    return *this;
}

// 比较操作 (it == other, it != other)
template <typename T>
bool MyLinkedList<T>::iterator::operator==(const iterator& other) const {
    return _node_ptr == other._node_ptr;
}

template <typename T>
bool MyLinkedList<T>::iterator::operator!=(const iterator& other) const {
    return _node_ptr != other._node_ptr;
}

// ------------------- 反向迭代器实现 -------------------

// 构造函数，接收一个普通迭代器
template <typename T>
MyLinkedList<T>::reverse_iterator::reverse_iterator(iterator it) : current(it) {}

// 解引用操作
template <typename T>
T& MyLinkedList<T>::reverse_iterator::operator*() {
    // 直接解引用内部的正向迭代器
    return *current;
}

//  前缀递增操作
template <typename T>
typename MyLinkedList<T>::reverse_iterator& MyLinkedList<T>::reverse_iterator::operator++() {
    // 反向迭代器的++，就是让其内部的正向迭代器--
    --current;
    return *this;
}

template <typename T>
typename MyLinkedList<T>::reverse_iterator& MyLinkedList<T>::reverse_iterator::operator--() {
    // 想要“反向”后退一步，就是让“正向”的迭代器++
    ++current;
    return *this;
}

// 比较操作: 直接比较内部的 current 迭代器
template <typename T>
bool MyLinkedList<T>::reverse_iterator::operator==(const reverse_iterator& other) const {
    return current == other.current;
}

template <typename T>
bool MyLinkedList<T>::reverse_iterator::operator!=(const reverse_iterator& other) const {
    return current != other.current;
}

// ------------------- MyLinkedList 成员函数实现 -------------------

// 构造函数
template <typename T>
MyLinkedList<T>::MyLinkedList()
    // 思考：一个空的链表，它的 head, tail, size 应该是什么？
    : _head(nullptr), _tail(nullptr), _size(0)
{
    std::cout << "LinkedList default constructor called!" << std::endl;
}

// 拷贝构造函数
template <typename T>
MyLinkedList<T>::MyLinkedList(const MyLinkedList& other)
    : _head(nullptr), _tail(nullptr), _size(0)
{
    std::cout << "Copy constructor called!" << std::endl;
    // 遍历 'other' 链表中的每一个节点
    Node* current = other._head;
    while (current != nullptr) {
        push_back(current->data);
        current = current->next;
    }
}

// 拷贝赋值运算符
template <typename T>
MyLinkedList<T>& MyLinkedList<T>::operator=(const MyLinkedList& other) {
    std::cout << "Copy assignment operator called!" << std::endl;

    // 步骤 1: 检查自我赋值
    if (this == &other) {
        return *this;
    }

    // 步骤 2: 释放当前对象已有的内存
    while(!empty()) {
        pop_front();
    }

    // 步骤 3: 进行和拷贝构造函数几乎一样的深拷贝
    Node* current = other._head;
    while (current != nullptr) {
        push_back(current->data);
        current = current->next;
    }

    // 步骤 4: 返回对当前对象的引用
    return *this;
}

// 析构函数 (非常重要！)
template <typename T>
MyLinkedList<T>::~MyLinkedList() {
    std::cout << "LinkedList destructor called!" << std::endl;

    // 思考：如何安全地释放所有节点，防止内存泄漏？
    // 需要从头到尾遍历，并一个个 delete 掉节点。
    Node* current = _head;
    while (current != nullptr) {
        Node* next_node = current->next; // 先保存下一个节点的地址
        delete current;                  // 再删除当前节点
        current = next_node;
    }
}

// 返回链表大小
template <typename T>
size_t MyLinkedList<T>::size() const {
    return _size;
}

// 判断链表是否为空
template <typename T>
bool MyLinkedList<T>::empty() const {
    return _size == 0;
}

template <typename T>
void MyLinkedList<T>::push_back(const T& value) {
    Node* new_node = new Node(value);

    if (empty()) {
        _head = new_node;
        _tail = new_node;
    }
    else {
        _tail->next = new_node;
        new_node->prev = _tail;
        _tail = new_node;
    }

    _size++;
}

template <typename T>
void MyLinkedList<T>::push_front(const T& value) {
    Node* new_node = new Node(value);
    if (empty()) {
        _head = new_node;
        _tail = new_node;
    }
    else {
        new_node->next = _head;
        _head->prev = new_node;
        _head = new_node;
    }

    _size++;
}

template <typename T>
T& MyLinkedList<T>::front() {
    if (empty()) {
        throw std::out_of_range("Accessing front on empty list");
    }
    return _head->data;
}

template <typename T>
const T& MyLinkedList<T>::front() const {
    if (empty()) {
        throw std::out_of_range("Accessing front on empty list");
    }
    return _head->data;
}

template <typename T>
T& MyLinkedList<T>::back() {
    if (empty()) {
        throw std::out_of_range("Accessing back on empty list");
    }
    return _tail->data;
}

template <typename T>
const T& MyLinkedList<T>::back() const {
    if (empty()) {
        throw std::out_of_range("Accessing back on empty list");
    }
    return _tail->data;
}

template <typename T>
void MyLinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Popping front on empty list");
    }

    Node* node_to_delete = _head;

    if (_size == 1) {
        _head = nullptr;
        _tail = nullptr;
    }
    else {
        _head = _head->next;
        _head->prev = nullptr;
    }

    delete node_to_delete;

    _size--;
}

template <typename T>
void MyLinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Popping back on empty list");
    }

    Node* node_to_delete = _tail;

    if (_size == 1) {
        _head = nullptr;
        _tail = nullptr;
    }
    else {
        _tail = _tail->prev;
        _tail->next = nullptr;
    }

    delete node_to_delete;

    _size--;
}

template <typename T>
typename MyLinkedList<T>::iterator MyLinkedList<T>::begin() {
    return iterator(_head);
}

template <typename T>
typename MyLinkedList<T>::iterator MyLinkedList<T>::end() {
    return iterator(nullptr);
}

// rbegin() 实现
template <typename T>
typename MyLinkedList<T>::reverse_iterator MyLinkedList<T>::rbegin() {
    // rbegin() 指向链表的最后一个元素
    return reverse_iterator(iterator(_tail));
}

//  rend() 实现
template <typename T>
typename MyLinkedList<T>::reverse_iterator MyLinkedList<T>::rend() {
    // rend() 指向链表第一个元素之前的位置 (nullptr)
    return reverse_iterator(iterator(nullptr));
}

#endif