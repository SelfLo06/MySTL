// tests/mydeque/test_mydeque.cpp
#include "mydeque/test_mydeque.h"
#include "common/test_common.h"
#include "MyDeque.h" // 确保包含了你的 Deque 头文件
#include <cassert>

namespace TestMyDeque {

    void test_deque_operations() {
        MyDeque<int> d;
        assert(d.empty());
        assert(d.size() == 0);

        // --- Test push_back ---
        // Pushing 20 elements to force multiple block allocations
        for (int i = 1; i <= 20; ++i) {
            d.push_back(i);
        }
        assert(!d.empty());
        assert(d.size() == 20);
        assert(d.front() == 1);
        assert(d.back() == 20);

        // --- Test random access operator[] ---
        assert(d[0] == 1);
        assert(d[7] == 8);  // Edge of a block
        assert(d[8] == 9);  // Start of a new block
        assert(d[15] == 16); // Edge of another block
        assert(d[19] == 20);
        d[19] = 200;
        assert(d[19] == 200);

        // --- Test pop_back ---
        d.pop_back(); // Removes 200
        assert(d.size() == 19);
        assert(d.back() == 19);

        // --- Test push_front ---
        // Pushing 20 elements to the front
        for (int i = 0; i >= -19; --i) {
            d.push_front(i);
        }
        assert(d.size() == 19 + 20); // 39
        assert(d.front() == -19);
        assert(d.back() == 19);

        // Check random access again after push_front
        assert(d[0] == -19);
        assert(d[19] == 0);
        assert(d[20] == 1); // Old front
        assert(d[38] == 19); // Old back

        // --- Test pop_front ---
        d.pop_front(); // Removes -19
        assert(d.size() == 38);
        assert(d.front() == -18);

        // --- Clear the deque ---
        while (!d.empty()) {
            d.pop_front();
        }
        assert(d.empty());
        assert(d.size() == 0);
    }

    void test_deque_reallocation() {
        // --- Case 1: Force reallocation with push_back ---
        {
            MyDeque<int> d;
            // Our initial map size is 16, with 8 slots on the right.
            // Each block holds 8 elements.
            // Pushing 100 elements will definitely force a map reallocation.
            for (int i = 0; i < 100; ++i) {
                d.push_back(i);
            }

            assert(d.size() == 100);
            assert(d.front() == 0);
            assert(d.back() == 99);
            // Check random access across multiple reallocations
            assert(d[0] == 0);
            assert(d[50] == 50);
            assert(d[99] == 99);
        }

        // --- Case 2: Force reallocation with push_front ---
        {
            MyDeque<int> d;
            // Pushing 100 elements to the front will also force reallocation
            for (int i = 0; i < 100; ++i) {
                d.push_front(i);
            }

            assert(d.size() == 100);
            assert(d.front() == 99); // The last element pushed is the new front
            assert(d.back() == 0);   // The first element pushed is the new back
            // Check random access
            assert(d[0] == 99);
            assert(d[50] == 49);
            assert(d[99] == 0);
        }
    }

    // --- 测试用例注册表 ---
    static const std::vector<TestCase> deque_test_cases = {
        {"Deque Basic Operations and Block Crossing", test_deque_operations},
        {"Deque Map Reallocation Stress Test", test_deque_reallocation}
    };

    // --- get_test_cases ---
    const std::vector<TestCase>& get_test_cases() {
        return deque_test_cases;
    }

    // --- run_all_tests ---
    void run_all_tests() {
        TestRunner::print_separator("MyDeque Tests");
        for (const auto& test_case : deque_test_cases) {
            TestRunner::run_test(test_case.name, test_case.function);
        }
        TestRunner::print_summary();
        TestRunner::print_separator("MyDeque Tests Complete");
    }

} // namespace TestMyDeque