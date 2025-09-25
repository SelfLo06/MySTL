#ifndef TEST_MYPRIORITYQUEUE_H
#define TEST_MYPRIORITYQUEUE_H

#include "common/test_common.h"
#include <vector>

namespace TestMyPriorityQueue {
    // --- 声明测试函数 ---
    void test_push_and_top();
    void test_pop();
    void test_integration(); // 综合测试

    // --- 声明管理函数 ---
    const std::vector<TestCase>& get_test_cases();
    void run_all_tests();
}

#endif // TEST_MYPRIORITYQUEUE_H