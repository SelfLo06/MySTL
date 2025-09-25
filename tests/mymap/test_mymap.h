#ifndef TEST_MYMAP_H
#define TEST_MYMAP_H

#include "common/test_common.h"
#include <vector>

namespace TestMyMap {
    // --- 声明测试函数 ---
    void test_insert_and_find();
    void test_operator_square_brackets();
    void test_overwrite_and_duplicates();
    void test_size_empty_clear();

    // --- 声明管理函数 ---
    const std::vector<TestCase>& get_test_cases();
    void run_all_tests();
}

#endif // TEST_MYMAP_H