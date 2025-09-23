#ifndef TEST_MYSTACK_H
#define TEST_MYSTACK_H

#include <vector>
#include "common/test_common.h"

namespace TestMyStack {
    void test_stack_operations();
    void run_all_tests();

    const std::vector<TestCase>& get_test_cases();
}

#endif
