#ifndef TEST_MYLINKEDLIST_H
#define TEST_MYLINKEDLIST_H

#include <vector>
#include "common/test_common.h"

namespace TestMyLinkedList {
    void test_constructor_and_empty();
    void test_push_back();
    void test_push_front();
    void test_access_and_pop();
    void test_iterator();
    void test_reverse_iterator();
    void test_copy_semantics();

    // 获取测试用例列表
    const std::vector<TestCase>& get_test_cases();

    // 运行所有 MyLinkedList 的测试
    void run_all_tests();
}

#endif
