#ifndef TEST_MYTREAP_H
#define TEST_MYTREAP_H

#include <vector>
#include "common/test_common.h"

namespace TestMyTreap {
    void test_insert_and_find();
    void test_inorder_is_sorted(); // <-- Treap 无法测试固定结构，但可以验证中序遍历的有序性
    void test_remove();
    void test_resource_management();
    void test_size_basic();
    void test_size_copy_and_assign();
    // Treap 一般不实现 lower/upper_bound，所以我们先不测试它们

    void run_all_tests();
    const std::vector<TestCase>& get_test_cases();
}

#endif