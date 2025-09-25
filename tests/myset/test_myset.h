#ifndef TEST_MYSET_H
#define TEST_MYSET_H
#include "common/test_common.h"
#include <vector>
namespace TestMySet {
    void test_insert_and_contains();
    void test_duplicates();
    void test_erase();
    void test_clear_and_empty();

    const std::vector<TestCase>& get_test_cases();
    void run_all_tests();
}
#endif // TEST_MYSET_H