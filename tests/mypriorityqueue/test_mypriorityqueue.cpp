#include "test_mypriorityqueue.h"

#include <stdexcept>
#include <string>
#include "common/test_common.h"
#include "MyPriorityQueue.h" // 包含你要测试的类

namespace TestMyPriorityQueue {

    // 测试基本的 push 和 top 是否符合最小堆的预期
    void test_push_and_top() {
        MyPriorityQueue<int> pq;

        // 验证空和大小
        if (!pq.empty()) throw std::runtime_error("New PQ should be empty.");
        if (pq.size() != 0) throw std::runtime_error("New PQ size should be 0.");

        pq.push(20);
        if (pq.top() != 20) throw std::runtime_error("Push/top failed. Expected 20.");
        if (pq.size() != 1) throw std::runtime_error("Size should be 1.");

        pq.push(10);
        if (pq.top() != 10) throw std::runtime_error("Push/top failed. Expected 10.");

        pq.push(30);
        if (pq.top() != 10) throw std::runtime_error("Push/top should remain 10.");

        pq.push(5);
        if (pq.top() != 5) throw std::runtime_error("Push/top failed. Expected 5.");
        if (pq.empty()) throw std::runtime_error("PQ should not be empty.");

        std::cout << "Push and Top Test Passed." << std::endl;
    }

    // 测试 pop 是否能正确移除优先级最高的元素
    void test_pop() {
        MyPriorityQueue<int> pq;
        pq.push(15);
        pq.push(10);
        pq.push(20); // top is 10

        pq.pop(); // Remove 10
        if (pq.size() != 2) throw std::runtime_error("Size should be 2 after one pop.");
        if (pq.top() != 15) {
            throw std::runtime_error("Pop failed. Expected new top to be 15, but got " + std::to_string(pq.top()));
        }

        pq.pop(); // Remove 15
        if (pq.top() != 20) {
            throw std::runtime_error("Pop failed. Expected new top to be 20, but got " + std::to_string(pq.top()));
        }

        pq.pop(); // Remove 20
        if (!pq.empty()) throw std::runtime_error("PQ should be empty after all pops.");

        std::cout << "Pop Test Passed." << std::endl;
    }

    // 综合测试，模拟一个完整的使用流程
    void test_integration() {
        MyPriorityQueue<int> pq;
        int values[] = {40, 80, 10, 50, 30, 90, 20, 60, 70};
        for (int v : values) {
            pq.push(v);
        }

        // 验证按优先级顺序出队
        int expected_order[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
        for (int i = 0; i < 9; ++i) {
            int expected = expected_order[i];
            int actual = pq.top();
            if (actual != expected) {
                throw std::runtime_error(
                    "Integration test failed. Expected " + std::to_string(expected) +
                    ", but got " + std::to_string(actual)
                );
            }
            pq.pop();
        }

        if (!pq.empty()) throw std::runtime_error("Integration test failed: PQ should be empty at the end.");

        // 测试异常
        try {
            pq.top();
            throw std::runtime_error("Integration test failed: top() on empty PQ did not throw.");
        } catch (const std::out_of_range&) {
            // Expected
        }

        try {
            pq.pop();
            // 如果代码执行到这里，说明没有抛出异常，测试失败
            throw std::runtime_error("Integration test failed: pop() on empty PQ did not throw.");
        } catch (const std::out_of_range& e) {
            // 成功捕获了我们期望的 out_of_range 异常，这才是正确的行为！
            // 我们可以什么都不做，让测试安静地通过，或者打印一条成功信息
        } catch (...) {
            // 捕获了其他类型的异常，说明有问题
            throw std::runtime_error("Integration test failed: pop() on empty PQ threw an unexpected type of exception.");
        }

        std::cout << "Integration Test Passed." << std::endl;
    }

    // --- 注册所有测试用例 ---
    static const std::vector<TestCase> mypriorityqueue_test_cases = {
        {"Push and Top", test_push_and_top},
        {"Pop", test_pop},
        {"Integration", test_integration}
    };

    // --- 实现管理函数 ---
    const std::vector<TestCase>& get_test_cases() {
        return mypriorityqueue_test_cases;
    }

    void run_all_tests() {
        TestRunner::print_separator("MyPriorityQueue Tests");
        for (const auto& test_case : mypriorityqueue_test_cases) {
            TestRunner::run_test(test_case.name, test_case.function);
        }
        TestRunner::print_summary();
        TestRunner::print_separator("MyPriorityQueue Tests Complete");
    }

} // namespace TestMyPriorityQueue