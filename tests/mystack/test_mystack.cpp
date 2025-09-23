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

    // --- 创建测试用例注册表 ---
    static const std::vector<TestCase> mystack_test_cases = {
        {"Stack Operations Test", test_stack_operations}
    };

    // --- 实现 get_test_cases 函数 ---
    const std::vector<TestCase>& get_test_cases() {
        return mystack_test_cases;
    }

    void run_all_tests() {
        TestRunner::print_separator("MyStack Tests");
        // 从注册表中读取并运行测试
        for (const auto& test_case : mystack_test_cases) {
            TestRunner::run_test(test_case.name, test_case.function);
        }
        TestRunner::print_summary();
        TestRunner::print_separator("MyStack Tests Complete");
    }
}
