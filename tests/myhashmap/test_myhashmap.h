#ifndef TEST_MYHASHMAP_H
#define TEST_MYHASHMAP_H

#include <vector>
#include "common/test_common.h"

namespace TestMyHashMap {
    void test_insert_and_access();
    void test_find_and_erase();
    void test_rehash();
    void run_all_tests();

    const std::vector<TestCase>& get_test_cases();
}

#endif
