#ifndef TEST_MYMAPPRO_H
#define TEST_MYMAPPRO_H

#include "common/test_common.h"
#include <vector>

namespace TestMyMapPro {
    // --- 声明测试函数 ---
    void test_insert_and_find();
    void test_operator_square_brackets();
    void test_overwrite_and_duplicates();
    void test_size_empty_clear();
    void test_erase_and_remove();

    // --- 声明管理函数 ---
    const std::vector<TestCase>& get_test_cases();
    void run_all_tests();
}

#endif // TEST_MYMAPPRO_H
