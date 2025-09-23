#ifndef TEST_MYQUEUE_H
#define TEST_MYQUEUE_H

#include <vector>
#include "common/test_common.h"

namespace TestMyQueue {
    void test_queue_operations();
    void run_all_tests();

    const std::vector<TestCase>& get_test_cases();
}

#endif
