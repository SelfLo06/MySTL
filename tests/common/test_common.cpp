#include "common/test_common.h"
#include <chrono>

int TestRunner::passed_count = 0;
int TestRunner::total_count = 0;
double TestRunner::total_time_ms = 0.0;

void TestRunner::run_test(const std::string& test_name, const std::function<void()>& test_func) {
    std::cout << "\n========== " << test_name << " ==========" << std::endl;
    total_count++;
    auto start = std::chrono::high_resolution_clock::now();
    try {
        test_func();
        auto end = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double, std::milli>(end - start).count();
        total_time_ms += duration;
        print_result(test_name, true, "耗时: " + std::to_string(duration) + " ms");
        passed_count++;
    } catch (const std::exception& e) {
        auto end = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double, std::milli>(end - start).count();
        total_time_ms += duration;
        print_result(test_name, false, std::string(e.what()) + " | 耗时: " + std::to_string(duration) + " ms");
    }
    std::cout << "============================\n" << std::endl;
}

void TestRunner::reset() {
    passed_count = 0;
    total_count = 0;
    total_time_ms = 0;
}


void TestRunner::print_separator(const std::string& title) {
    std::cout << "\n=================== " << title << " ===================" << std::endl;
}

void TestRunner::print_result(const std::string& test_name, bool passed, const std::string& message) {
    if (passed) {
        std::cout << "✓ " << test_name << " 通过. " << message << std::endl;
    } else {
        std::cout << "✗ " << test_name << " 失败. 原因: " << message << std::endl;
    }
}

void TestRunner::print_summary() {
    std::cout << "\n========== 测试统计 ==========" << std::endl;
    std::cout << "通过测试点: " << passed_count << " / 总测试点: " << total_count << std::endl;
    std::cout << "总耗时: " << total_time_ms << " ms" << std::endl;
    std::cout << "==============================" << std::endl;
}

