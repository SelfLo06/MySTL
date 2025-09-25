#ifndef MYSTL_MYBINARYHEAP_H
#define MYSTL_MYBINARYHEAP_H

#pragma once

#include "../include/MyVector.h"

template<typename T>
class MyBinaryHeap {
public:

    /*
     *由于 MyBinaryHeap 完全依赖 MyVector<T> 来管理内存和资源，
     *它不需要做任何额外的初始化或清理工作。
     *C++ 编译器会为它自动生成
     */

    void insert(const T &value);
    const T& peek() const;
    T extract(); // 提取堆顶元素,注意 返回 T 而不是 T&，因为提取操作已经删除了

    size_t size() const;
    bool isEmpty() const;

private:
    MyVector<T> _elements;

    // 维护堆属性的辅助函数
    void _bubble_up(size_t index);
    void _bubble_down(size_t index);

    // 索引计算的辅助函数
    // 由于这些函数该函数在执行其任务时，完全不需要访问任何非 static 的成员变量或调用任何非 static 的成员函数
    // 换句话说，它的逻辑是自包含的，其输出只依赖于它接收到的输入参数，而不依赖于它是在哪个对象上被调用的。
    // 所以推荐设置成static函数。
    static size_t _get_parent_index(size_t index);
    static size_t _get_left_child_index(size_t index);
    static size_t _get_right_child_index(size_t index);

    // 交换元素的辅助函数
    void _swap(size_t index1, size_t index2);
};

template<typename T>
size_t MyBinaryHeap<T>::_get_parent_index(const size_t index) {
    return (index - 1) / 2;
}

template<typename T>
size_t MyBinaryHeap<T>::_get_left_child_index(const size_t index) {
    return 2 * index + 1;
}

template<typename T>
size_t MyBinaryHeap<T>::_get_right_child_index(const size_t index) {
    return 2 * index + 2;
}

template<typename T>
void MyBinaryHeap<T>::_swap(size_t index1, size_t index2) {
    std::swap(_elements[index1], _elements[index2]);
}

template<typename T>
void MyBinaryHeap<T>::_bubble_up(size_t index) {
    size_t currentIndex = index;
    while (currentIndex > 0) {
        size_t parentIndex =  _get_parent_index(currentIndex);
        if (_elements[currentIndex] < _elements[parentIndex]) {
            _swap(currentIndex, parentIndex);
            currentIndex = parentIndex;
        }
        else break;
    }
}

template<typename T>
void MyBinaryHeap<T>::insert(const T &value) {
    // 1. 将元素添加到数组末尾
    _elements.push_back(value);
    // 2. 从新元素的索引开始执行“上浮”
    _bubble_up(_elements.size() - 1);
}

template<typename T>
size_t MyBinaryHeap<T>::size() const {
    return _elements.size();
}

template<typename T>
bool MyBinaryHeap<T>::isEmpty() const {
    return _elements.empty();
}

template<typename T>
const T& MyBinaryHeap<T>::peek() const {
    if (isEmpty()) {
        throw std::out_of_range("The Heap is empty!");
    }
    return _elements[0];
}

template<typename T>
void MyBinaryHeap<T>::_bubble_down(size_t index) {
    size_t currentIndex = index;
    while (true) {
        size_t leftChildIndex = _get_left_child_index(currentIndex);
        if (leftChildIndex >= _elements.size()) {
            break;
        }

        size_t smallerChildIndex = leftChildIndex;
        size_t rightChildIndex = _get_right_child_index(currentIndex);

        if (rightChildIndex < _elements.size() && _elements[smallerChildIndex] > _elements[rightChildIndex]) {
            smallerChildIndex = rightChildIndex;
        }

        if (_elements[currentIndex] > _elements[smallerChildIndex]) {
            _swap(currentIndex, smallerChildIndex);
            currentIndex = smallerChildIndex;
        }
        else break;
    }
}

template<typename T>
T MyBinaryHeap<T>::extract() {
    if (isEmpty()) {
        throw std::out_of_range("The Heap is empty!");
    }
    T element = _elements[0];
    _elements[0] = _elements.back();
    _elements.pop_back();

    if (!_elements.empty()) {
        _bubble_down(0);
    }
    return element;
}




#endif //MYSTL_MYBINARYHEAP_H