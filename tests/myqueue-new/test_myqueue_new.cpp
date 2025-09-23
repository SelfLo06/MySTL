#include "myqueue-new/test_myqueue_new.h"
#include "common/test_common.h"
#include "MyQueue-new/MyQueue-new.h" // 包含您要测试的队列头文件
#include <cassert>
#include <stdexcept>

namespace TestMyQueueNew {

    void test_basic_operations() {
        MyQueue q;
        assert(q.size() == 0);

        // 测试 push 和 size
        q.push('a');
        q.push('b');
        q.push('c');
        assert(q.size() == 3);

        // 测试 pop 和先进先出 (FIFO) 顺序
        assert(q.pop() == 'a');
        assert(q.size() == 2);

        assert(q.pop() == 'b');
        assert(q.size() == 1);

        assert(q.pop() == 'c');
        assert(q.size() == 0);
    }

    void test_pop_from_empty() {
        MyQueue q;
        bool exception_thrown = false;
        try {
            q.pop(); // 应该抛出异常
        } catch (const std::out_of_range& e) {
            exception_thrown = true;
        }
        assert(exception_thrown);
    }

    void test_mixed_operations() {
        MyQueue q;

        q.push('1');
        q.push('2');
        assert(q.size() == 2);

        // 第一次 pop，触发 s1 -> s2 的元素转移
        assert(q.pop() == '1');
        assert(q.size() == 1);

        // 此时 s2 中有 '2'，s1 为空
        q.push('3'); // '3' 被压入 s1
        assert(q.size() == 2);

        // 第二次 pop，直接从 s2 弹出，不应发生转移
        assert(q.pop() == '2');
        assert(q.size() == 1);

        // 第三次 pop，s2 为空，触发 s1 -> s2 的转移
        assert(q.pop() == '3');
        assert(q.size() == 0);
    }

    // 创建测试用例注册表
    static const std::vector<TestCase> myqueue_new_test_cases = {
        {"Basic Operations Test", test_basic_operations},
        {"Pop from Empty Test", test_pop_from_empty},
        {"Mixed Operations Test", test_mixed_operations}
    };

    // 获取测试用例列表
    const std::vector<TestCase>& get_test_cases() {
        return myqueue_new_test_cases;
    }

    void run_all_tests() {
        TestRunner::print_separator("MyQueue-new (Two Stacks) Tests");

        for (const auto& test_case : myqueue_new_test_cases) {
            TestRunner::run_test(test_case.name, test_case.function);
        }

        TestRunner::print_summary();
        TestRunner::print_separator("MyQueue-new Tests Complete");
    }
}