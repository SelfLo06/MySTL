#include "myqueue/test_myqueue.h"
#include "common/test_common.h"
#include "MyQueue.h"
#include <cassert>

namespace TestMyQueue {
    void test_queue_operations() {
        MyQueue<int> q;
        assert(q.empty());

        // Push (入队)
        q.push(10); // q: 10
        q.push(20); // q: 10, 20
        q.push(30); // q: 10, 20, 30

        assert(q.size() == 3);

        // Front and Back (队头和队尾)
        assert(q.front() == 10);
        assert(q.back() == 30);

        // 修改队头
        q.front() = 15;
        assert(q.front() == 15);

        // Pop (出队)
        q.pop(); // q: 20, 30
        assert(q.size() == 2);
        assert(q.front() == 20);

        q.pop(); // q: 30
        assert(q.front() == 30);
        assert(q.back() == 30);

        q.pop(); // q: empty
        assert(q.empty());
    }

    // --- 测试用例注册表 ---
    static const std::vector<TestCase> queue_test_cases = {
        {"Queue Operations Test", test_queue_operations}
    };

    // --- get_test_cases ---
    const std::vector<TestCase>& get_test_cases() {
        return queue_test_cases;
    }

    // --- run_all_tests ---
    void run_all_tests() {
        TestRunner::print_separator("MyQueue Tests");
        for (const auto& test_case : queue_test_cases) {
            TestRunner::run_test(test_case.name, test_case.function);
        }
        TestRunner::print_summary();
        TestRunner::print_separator("MyQueue Tests Complete");
    }
}