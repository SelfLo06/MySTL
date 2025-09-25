#ifndef TEST_MYBINARYHEAP_H
#define TEST_MYBINARYHEAP_H

#include "common/test_common.h"
#include <vector>

namespace TestMyBinaryHeap {
    void test_simple_insert_and_peek();
    void test_insert_ordering();
    void test_empty_and_size();
    void test_peek_on_empty();
    void test_extract();
    void test_extract_on_empty();

    const std::vector<TestCase>& get_test_cases();
    void run_all_tests();
}

#endif // TEST_MYBINARYHEAP_H