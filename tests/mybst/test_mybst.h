#ifndef TEST_MYBST_H
#define TEST_MYBST_H

#include <vector>
#include "common/test_common.h"

namespace TestMyBST {
    void test_insert_and_find();
    void test_traversals();
    void test_lower_bound();
    void test_upper_bound();
    void test_remove();
    void test_resource_management();
    void run_all_tests();

    const std::vector<TestCase>& get_test_cases();
}

#endif
