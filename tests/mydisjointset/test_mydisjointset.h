#ifndef TEST_MYDISJOINTSET_H
#define TEST_MYDISJOINTSET_H

#include <vector>
#include "common/test_common.h"

namespace TestMyDisjointSet {
    void test_initialization();
    void test_basic_union_and_find();
    void test_transitivity();
    void test_path_compression_effect();
    void test_union_by_rank_effect();
    void test_edge_cases();

    void run_all_tests();
    const std::vector<TestCase>& get_test_cases();
}

#endif // TEST_MYDISJOINTSET_H