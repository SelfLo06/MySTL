#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <iostream>
#include <string>

class TestRunner {
public:
    static void run_test(const std::string& test_name, void (*test_func)());
    static void print_separator(const std::string& title);
    static void print_result(const std::string& test_name, bool passed, const std::string& message = "");
    static void print_summary();
    static void reset();

private:
    static int passed_count;
    static int total_count;
    static double total_time_ms;

};

#endif