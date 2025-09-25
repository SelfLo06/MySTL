#ifndef MYSTL_MYPRIORITYQUEUE_H
#define MYSTL_MYPRIORITYQUEUE_H

#pragma once

#include "MyBinaryHeap.h"

template<typename T>
class MyPriorityQueue {
private:
    MyBinaryHeap<T> heap;

public:
    void push(const T &value) {
        heap.insert(value);
    }

    void pop(){
        heap.extract();
    }

    const T& top() const{
        return heap.peek();
    }

    size_t size() const{
        return heap.size();
    }

    bool empty() const {
        return heap.isEmpty();
    }
};

#endif //MYSTL_MYPRIORITYQUEUE_H