#include "test_mybinaryheap.h"

#include <cassert>

#include "common/test_common.h"
#include "MyBinaryHeap.h"
#include <stdexcept>

namespace TestMyBinaryHeap {
    void test_simple_insert_and_peek() {
        MyBinaryHeap<int> heap;

        heap.insert(10);
        if (heap.peek() != 10) {
            throw std::runtime_error(
                "Assertion failed: Expected heap.peek() to be 10, but it was " + std::to_string(heap.peek()));
        }

        heap.insert(5);
        if (heap.peek() != 5) {
            throw std::runtime_error(
                "Assertion failed: Expected heap.peek() to be 5, but it was " + std::to_string(heap.peek()));
        }

        heap.insert(20);
        if (heap.peek() != 5) {
            throw std::runtime_error(
                "Assertion failed: Expected heap.peek() to be 5, but it was " + std::to_string(heap.peek()));
        }

        heap.insert(3);
        if (heap.peek() != 3) {
            throw std::runtime_error(
                "Assertion failed: Expected heap.peek() to be 3, but it was " + std::to_string(heap.peek()));
        }
        std::cout << "Simple insert and peek test passed." << std::endl;
    }

    void test_insert_ordering() {
        // 1. 测试倒序插入 (每次都应该触发 bubble_up 到顶)
        MyBinaryHeap<int> descending_heap;
        descending_heap.insert(10);
        descending_heap.insert(9);
        if (descending_heap.peek() != 9) throw std::runtime_error("Descending insert failed at 9");
        descending_heap.insert(8);
        if (descending_heap.peek() != 8) throw std::runtime_error("Descending insert failed at 8");
        descending_heap.insert(5);
        if (descending_heap.peek() != 5) throw std::runtime_error("Descending insert failed at 5");
        std::cout << "Descending insert ordering test passed." << std::endl;

        // 2. 测试正序插入 (最小值应该一直不变)
        MyBinaryHeap<int> ascending_heap;
        ascending_heap.insert(5);
        ascending_heap.insert(8);
        if (ascending_heap.peek() != 5) throw std::runtime_error("Ascending insert failed at 8");
        ascending_heap.insert(9);
        if (ascending_heap.peek() != 5) throw std::runtime_error("Ascending insert failed at 9");
        ascending_heap.insert(10);
        if (ascending_heap.peek() != 5) throw std::runtime_error("Ascending insert failed at 10");
        std::cout << "Ascending insert ordering test passed." << std::endl;
    }

    void test_empty_and_size() {
        MyBinaryHeap<int> heap;
        if (!heap.isEmpty()) throw std::runtime_error("A new heap should be empty.");
        if (heap.size() != 0) throw std::runtime_error("A new heap's size should be 0.");

        heap.insert(100);
        if (heap.isEmpty()) throw std::runtime_error("Heap should not be empty after one insert.");
        if (heap.size() != 1) throw std::runtime_error("Heap size should be 1 after one insert.");

        heap.insert(50);
        if (heap.size() != 2) throw std::runtime_error("Heap size should be 2 after two inserts.");
        std::cout << "Empty and size test passed." << std::endl;
    }

    void test_peek_on_empty() {
        MyBinaryHeap<int> heap;
        try {
            heap.peek();
            // 如果代码能执行到这里，说明 peek() 没有抛出异常，这是错误的
            throw std::runtime_error("Test failed: std::out_of_range was NOT thrown for peek() on an empty heap.");
        } catch (const std::out_of_range &e) {
            // 这正是我们期望的！捕获到异常，说明测试通过
            std::cout << "Peek on empty test passed: Caught expected exception." << std::endl;
        } catch (...) {
            // 捕获任何其他意料之外的异常
            throw std::runtime_error("Test failed: An unexpected type of exception was thrown.");
        }
    }


    //  Add this new test function
    void test_extract() {
        MyBinaryHeap<int> heap;
        heap.insert(10);
        heap.insert(5);
        heap.insert(20);
        heap.insert(3);
        heap.insert(8);
        // At this point, the heap's top should be 3.
        // The internal order might be something like: [3, 5, 20, 10, 8]

        if (heap.size() != 5) throw std::runtime_error("Extract test failed: Initial size incorrect.");

        // 1. Extract the minimum element (3)
        int min_val = heap.extract();
        if (min_val != 3) {
            throw std::runtime_error("Extract test failed: Expected to extract 3, but got " + std::to_string(min_val));
        }
        if (heap.size() != 4) throw std::runtime_error("Extract test failed: Size should be 4 after one extract.");
        // After extracting 3, 8 is moved to the top and bubbles down. 5 should be the new top.
        if (heap.peek() != 5) {
            throw std::runtime_error(
                "Extract test failed: Expected new peek to be 5, but got " + std::to_string(heap.peek()));
        }

        // 2. Extract the next minimum (5)
        min_val = heap.extract();
        if (min_val != 5) {
            throw std::runtime_error("Extract test failed: Expected to extract 5, but got " + std::to_string(min_val));
        }
        // After extracting 5, 10 is moved to top and bubbles down. 8 should be the new top.
        if (heap.peek() != 8) {
            throw std::runtime_error(
                "Extract test failed: Expected new peek to be 8, but got " + std::to_string(heap.peek()));
        }

        // 3. Extract the rest
        if (heap.extract() != 8) throw std::runtime_error("Extract test failed at value 8.");
        if (heap.extract() != 10) throw std::runtime_error("Extract test failed at value 10.");
        if (heap.extract() != 20) throw std::runtime_error("Extract test failed at value 20.");

        // 4. Final check
        if (!heap.isEmpty()) throw std::runtime_error(
            "Extract test failed: Heap should be empty after extracting all elements.");
        if (heap.size() != 0) throw std::runtime_error("Extract test failed: Final size should be 0.");

        std::cout << "Extract test passed." << std::endl;
    }

    //  Add this new test function for exception handling
    void test_extract_on_empty() {
        MyBinaryHeap<int> heap;
        try {
            heap.extract();
            // If we reach here, the test fails because no exception was thrown
            throw std::runtime_error("Test failed: std::out_of_range was NOT thrown for extract() on an empty heap.");
        } catch (const std::out_of_range &e) {
            // Correct behavior: exception was caught.
            std::cout << "Extract on empty test passed: Caught expected exception." << std::endl;
        } catch (...) {
            // Catch any other unexpected exceptions
            throw std::runtime_error(
                "Test failed: An unexpected type of exception was thrown during extract on empty.");
        }
    }

    // --- 核心改动：创建一个该模块的“测试用例注册表” ---
    static const std::vector<TestCase> mybinaryheap_test_cases = {
        {"Simple Insert and Peek", test_simple_insert_and_peek},
        {"Insert Ordering", test_insert_ordering},
        {"Empty and Size", test_empty_and_size},
        {"Peek on Empty Heap", test_peek_on_empty},
        {"Extract Value and Order", test_extract},
        {"Extract on Empty Heap", test_extract_on_empty}
    };

    // --- 实现管理函数 ---
    const std::vector<TestCase> &get_test_cases() {
        return mybinaryheap_test_cases;
    }

    void run_all_tests() {
        TestRunner::print_separator("MyBinaryHeap Tests");
        for (const auto &test_case: mybinaryheap_test_cases) {
            TestRunner::run_test(test_case.name, test_case.function);
        }
        TestRunner::print_summary();
        TestRunner::print_separator("MyBinaryHeap Tests Complete");
    }
}
