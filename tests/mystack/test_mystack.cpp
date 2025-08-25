#include "mystack/test_mystack.h"
#include "common/test_common.h"
#include "MyStack.h"
#include <cassert>

namespace TestMyStack {

    void test_stack_operations() {
        MyStack<int> s;
        assert(s.empty());
        assert(s.size() == 0);

        // Push 操作
        s.push(10);
        s.push(20);
        s.push(30);

        assert(!s.empty());
        assert(s.size() == 3);

        // Top 操作
        assert(s.top() == 30);

        // 修改 top
        s.top() = 35;
        assert(s.top() == 35);

        // Pop 操作
        s.pop();
        assert(s.size() == 2);
        assert(s.top() == 20);

        s.pop();
        assert(s.top() == 10);

        s.pop();
        assert(s.empty());
    }

    void run_all_tests() {
        TestRunner::reset();
        TestRunner::print_separator("MyStack Tests");
        TestRunner::run_test("Stack Operations Test", test_stack_operations);
        TestRunner::print_summary();
        TestRunner::print_separator("MyStack Tests Complete");
    }
}
