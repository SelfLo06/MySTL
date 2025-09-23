#ifndef TEST_MYVECTOR_H
#define TEST_MYVECTOR_H
#include <vector>

#include "common/test_common.h"


namespace TestMyVector {
    void test_constructor();
    void test_push_back();
    void test_access();
    void test_capacity();
    void test_copy_and_assignment();
    void test_modifiers_and_capacity();
    void test_iterator();
    void run_all_tests();

    const std::vector<TestCase>& get_test_cases();
    void run_all_tests();
}

#endif