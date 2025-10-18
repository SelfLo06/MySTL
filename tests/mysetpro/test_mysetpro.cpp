#include "test_mysetpro.h"

#include <stdexcept>
#include "common/test_common.h"
#include "MySetPro.h"

namespace TestMySetPro {

    void test_insert_and_contains() {
        MySetPro<int> s;
        s.insert(10);
        s.insert(20);
        s.insert(5);

        if (!s.contains(10) || !s.contains(20) || !s.contains(5)) {
            throw std::runtime_error("Insert/Contains test failed: Element not found after insertion.");
        }
        if (s.contains(99)) {
            throw std::runtime_error("Insert/Contains test failed: Found an element that was not inserted.");
        }
        if (s.size() != 3) {
            throw std::runtime_error("Insert/Contains test failed: Size is incorrect.");
        }
        std::cout << "Insert and Contains Test Passed." << std::endl;
    }

    void test_duplicates() {
        MySetPro<int> s;
        s.insert(10);
        s.insert(20);
        s.insert(10); // Insert duplicate

        if (s.size() != 2) {
            throw std::runtime_error("Duplicates test failed: Size should remain 2 after duplicate insertion.");
        }
        if (!s.contains(10) || !s.contains(20)) {
            throw std::runtime_error("Duplicates test failed: Original elements are missing.");
        }
        std::cout << "Duplicates Test Passed." << std::endl;
    }

    void test_erase() {
        MySetPro<int> s;
        s.insert(10);
        s.insert(20);
        s.insert(5);

        s.erase(99); // Erase non-existent element
        if (s.size() != 3) {
            throw std::runtime_error("Erase test failed: Size should not change when erasing non-existent element.");
        }

        s.erase(10);
        if (s.contains(10)) {
            throw std::runtime_error("Erase test failed: Element 10 should have been erased.");
        }
        if (s.size() != 2) {
            throw std::runtime_error("Erase test failed: Size should be 2 after erasing 10.");
        }
        if (!s.contains(5) || !s.contains(20)) {
            throw std::runtime_error("Erase test failed: Other elements were affected by erase.");
        }
        std::cout << "Erase Test Passed." << std::endl;
    }

    void test_clear_and_empty() {
        MySetPro<int> s;
        if (!s.empty()) throw std::runtime_error("A new set should be empty.");

        s.insert(100);
        s.insert(200);
        if (s.empty()) throw std::runtime_error("Set should not be empty after insertion.");

        s.clear();
        if (!s.empty()) throw std::runtime_error("Set should be empty after clear.");
        if (s.size() != 0) throw std::runtime_error("Set size should be 0 after clear.");
        if (s.contains(100)) {
            throw std::runtime_error("Clear test failed: Set should not contain elements after clear.");
        }
        std::cout << "Clear and Empty Test Passed." << std::endl;
    }

    // --- 注册所有测试用例 ---
    static const std::vector<TestCase> mysetpro_test_cases = {
        {"Insert and Contains", test_insert_and_contains},
        {"Duplicates", test_duplicates},
        {"Erase", test_erase},
        {"Clear and Empty", test_clear_and_empty}
    };

    // --- 实现管理函数 ---
    const std::vector<TestCase>& get_test_cases() {
        return mysetpro_test_cases;
    }

    void run_all_tests() {
        TestRunner::print_separator("MySetPro Tests");
        for (const auto& test_case : mysetpro_test_cases) {
            TestRunner::run_test(test_case.name, test_case.function);
        }
        TestRunner::print_summary();
        TestRunner::print_separator("MySetPro Tests Complete");
    }

} // namespace TestMySetPro
