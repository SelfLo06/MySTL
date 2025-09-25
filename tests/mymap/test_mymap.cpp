#include "test_mymap.h"

#include <stdexcept>
#include <string>
#include "common/test_common.h"
#include "MyMap.h"

namespace TestMyMap {

    void test_insert_and_find() {
        MyMap<std::string, int> ages;
        ages.insert("Alice", 30);
        ages.insert("Bob", 25);

        int* alice_age = ages.find("Alice");
        if (alice_age == nullptr || *alice_age != 30) {
            throw std::runtime_error("Insert/Find test failed: Could not find or incorrect value for Alice.");
        }

        int* bob_age = ages.find("Bob");
        if (bob_age == nullptr || *bob_age != 25) {
            throw std::runtime_error("Insert/Find test failed: Could not find or incorrect value for Bob.");
        }

        if (ages.find("Charlie") != nullptr) {
            throw std::runtime_error("Insert/Find test failed: Found a key that was not inserted.");
        }
        std::cout << "Insert and Find Test Passed." << std::endl;
    }

    void test_operator_square_brackets() {
        MyMap<std::string, int> scores;

        // 1. 测试赋值 (key "Alice" 不存在，应创建)
        scores["Alice"] = 100;
        if (*(scores.find("Alice")) != 100) {
            throw std::runtime_error("Operator[] test failed: Failed to assign value to a new key.");
        }
        if (scores.size() != 1) {
             throw std::runtime_error("Operator[] test failed: Size should be 1 after first insertion.");
        }


        // 2. 测试读取 (key "Bob" 不存在，应创建并赋予默认值 0)
        int bob_score = scores["Bob"];
        if (bob_score != 0) {
            throw std::runtime_error("Operator[] test failed: Reading a new key should return a default-constructed value (0).");
        }
        if (scores.size() != 2) {
             throw std::runtime_error("Operator[] test failed: Size should be 2 after auto-insertion.");
        }
        if (*(scores.find("Bob")) != 0) {
            throw std::runtime_error("Operator[] test failed: Auto-inserted key 'Bob' does not have value 0 in the map.");
        }

        // 3. 测试修改 (key "Alice" 已存在，应修改其值)
        scores["Alice"] = 95;
        if (*(scores.find("Alice")) != 95) {
            throw std::runtime_error("Operator[] test failed: Failed to update the value of an existing key.");
        }
        if (scores.size() != 2) {
             throw std::runtime_error("Operator[] test failed: Size should remain 2 after updating a value.");
        }
        std::cout << "Operator[] Test Passed." << std::endl;
    }

    void test_overwrite_and_duplicates() {
        MyMap<int, std::string> city_codes;
        city_codes.insert(10, "Beijing");
        city_codes.insert(21, "Shanghai");

        // insert a duplicate key, should be ignored
        city_codes.insert(10, "New York");
        if (*(city_codes.find(10)) != "Beijing") {
            throw std::runtime_error("Overwrite test failed: insert() should not overwrite existing values.");
        }
        if (city_codes.size() != 2) {
            throw std::runtime_error("Overwrite test failed: Size should not change on duplicate insert.");
        }

        // operator[] should overwrite
        city_codes[21] = "Guangzhou";
        if (*(city_codes.find(21)) != "Guangzhou") {
            throw std::runtime_error("Overwrite test failed: operator[] failed to overwrite existing value.");
        }
        std::cout << "Overwrite and Duplicates Test Passed." << std::endl;
    }

    void test_size_empty_clear() {
        MyMap<int, int> m;
        if (!m.empty()) throw std::runtime_error("A new map should be empty.");
        if (m.size() != 0) throw std::runtime_error("A new map's size should be 0.");

        m[1] = 1;
        if (m.empty()) throw std::runtime_error("Map should not be empty after insertion.");
        if (m.size() != 1) throw std::runtime_error("Map's size should be 1.");

        m.clear();
        if (!m.empty()) throw std::runtime_error("Map should be empty after clear.");
        if (m.size() != 0) throw std::runtime_error("Map's size should be 0 after clear.");
        std::cout << "Size, Empty, Clear Test Passed." << std::endl;
    }


    // --- 注册所有测试用例 ---
    static const std::vector<TestCase> mymap_test_cases = {
        {"Insert and Find", test_insert_and_find},
        {"Operator Square Brackets", test_operator_square_brackets},
        {"Overwrite and Duplicates", test_overwrite_and_duplicates},
        {"Size, Empty, Clear", test_size_empty_clear}
    };

    // --- 实现管理函数 ---
    const std::vector<TestCase>& get_test_cases() {
        return mymap_test_cases;
    }

    void run_all_tests() {
        TestRunner::print_separator("MyMap Tests");
        for (const auto& test_case : mymap_test_cases) {
            TestRunner::run_test(test_case.name, test_case.function);
        }
        TestRunner::print_summary();
        TestRunner::print_separator("MyMap Tests Complete");
    }

} // namespace TestMyMap