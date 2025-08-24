#ifndef MYSTACK_H
#define MYSTACK_H

#include "MyVector.h" // 引入底层容器
#include <cstddef>

template <typename T>
class MyStack {
private:
    // 内部包含一个 MyVector 作为底层存储
    MyVector<T> _container;

public:
    // 构造函数 (默认即可)
    MyStack() {}

    // size(): 返回栈中元素的数量
    size_t size() const {
        // 委托给 MyVector 的 size()
        return _container.size();
    }

    // empty(): 判断栈是否为空
    bool empty() const {
        // 委托给 MyVector 的 empty()
        return _container.empty();
    }

    // top(): 返回栈顶元素的引用
    T& top() {
        // 栈顶对应 MyVector 的end末端
        if (empty()) throw std::out_of_range("The Stack is Empty!");
        return _container.back();
    }

    const T& top() const {
        if (empty()) throw std::out_of_range("The Stack is Empty!");
        return _container.back();
    }

    // push(value): 将元素压入栈顶
    void push(const T& value) {
        // 压入栈顶对应 MyVector 的 push_back
        _container.push_back(value);
    }

    // pop(): 弹出栈顶元素
    void pop() {
        // 弹出栈顶对应 MyVector 的 pop_back
        _container.pop_back();
    }
};

#endif // MYSTACK_H