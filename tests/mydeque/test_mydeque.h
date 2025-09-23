// tests/mydeque/test_mydeque.h
#ifndef TEST_MYDEQUE_H
#define TEST_MYDEQUE_H

#include "common/test_common.h"
#include <vector>

namespace TestMyDeque {

    // 获取本模块所有测试用例的函数
    const std::vector<TestCase>& get_test_cases();

    // 运行本模块所有测试用例的函数
    void run_all_tests();

} // namespace TestMyDeque

#endif // TEST_MYDEQUE_H