#include "MyQueue-new.h"

using namespace std;
MyQueue::MyQueue() {}

int MyQueue::size() const {
    return s1.size() + s2.size();
}

void MyQueue::push(char c) {
    s1.push(c);
}

char MyQueue::pop() {

    if (s2.empty()) {
        if (s1.empty()) throw std::out_of_range("The Queue is Empty!");

        while (!s1.empty()) {
            char t = s1.top();
            s2.push(t);
            s1.pop();
        }
    }

    char res = s2.top();
    s2.pop();
    return res;
}



