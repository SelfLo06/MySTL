#ifndef MYSTL_MYQUEUE_NEW_H
#define MYSTL_MYQUEUE_NEW_H

#include "../MyStack.h"
#include <iostream>


class MyQueue {
private:
    MyStack<char> s1;
    MyStack<char> s2;

public:
    MyQueue();
    void push(char c);
    char pop();
    int size() const;
};

#endif // MYSTL_MYQUEUE_NEW_H