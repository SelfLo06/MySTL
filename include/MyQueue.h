#ifndef MYQUEUE_H
#define MYQUEUE_H

#include "MyLinkedList.h" // <-- 底层容器是 MyLinkedList
#include <cstddef>

template <typename T>
class MyQueue {
private:
    MyLinkedList<T> _container;

public:
    MyQueue() {}

    size_t size() const {
        return _container.size();
    }

    bool empty() const {
        return _container.empty();
    }

    // front(): 查看队头元素
    T& front() {
        // 队头对应 MyLinkedList 的_head
        if (empty()) throw std::out_of_range("The Queue is Empty!");
        return _container.front();
    }

    const T& front() const {
        return _container.front();
    }

    // back(): 查看队尾元素
    T& back() {
        // 队尾对应 MyLinkedList 的_tail
        if (empty()) throw std::out_of_range("The Queue is Empty!");
        return _container.back();
    }

    const T& back() const {
        return _container.back();
    }

    // push(value): 在队尾入队
    void push(const T& value) {
        // 入队对应 MyLinkedList 的push_back
        _container.push_back(value);
    }

    // pop(): 在队头出队
    void pop() {
        // 出队对应 MyLinkedList 的pop_front
        if (empty()) throw std::out_of_range("The Queue is Empty!");
        _container.pop_front();
    }
};

#endif // MYQUEUE_H