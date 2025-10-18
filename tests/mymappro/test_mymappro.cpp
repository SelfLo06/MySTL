#include "test_mymappro.h"

#include <stdexcept>
#include <string>
#include "common/test_common.h"
#include "MyMapPro.h"

namespace TestMyMapPro {

    void test_insert_and_find() {
        MyMapPro<std::string, int> ages;
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
        MyMapPro<std::string, int> scores;

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
        MyMapPro<int, std::string> city_codes;
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
        MyMapPro<int, int> m;
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

    void test_erase_and_remove() {
        MyMapPro<std::string, int> m;
        m.insert("A", 1);
        m.insert("B", 2);
        m.insert("C", 3);

        if (m.size() != 3) throw std::runtime_error("Erase test failed: initial size should be 3.");

        // 删除中间节点
        m.erase("B");
        if (m.find("B") != nullptr) throw std::runtime_error("Erase test failed: 'B' should have been removed.");
        if (m.size() != 2) throw std::runtime_error("Erase test failed: size should be 2 after removing 'B'.");

        // 删除不存在的键，不应改变大小
        m.erase("X");
        if (m.size() != 2) throw std::runtime_error("Erase test failed: erasing non-existent key should not change size.");

        // 删除首/尾元素
        m.erase("A");
        if (m.find("A") != nullptr) throw std::runtime_error("Erase test failed: 'A' should have been removed.");
        if (m.size() != 1) throw std::runtime_error("Erase test failed: size should be 1 after removing 'A'.");

        // 删除最后一个
        m.erase("C");
        if (!m.empty()) throw std::runtime_error("Erase test failed: map should be empty after removing all keys.");

        // operator[] 插入后删除
        m["D"] = 4;
        if (m.find("D") == nullptr || *(m.find("D")) != 4) throw std::runtime_error("Erase test failed: 'D' should exist with value 4.");
        m.erase("D");
        if (m.find("D") != nullptr) throw std::runtime_error("Erase test failed: 'D' should have been removed after erase.");

        std::cout << "Erase and Remove Test Passed." << std::endl;
    }

    // 在 mymappro_test_cases 中注册
    static const std::vector<TestCase> mymappro_test_cases = {
        {"Insert and Find", test_insert_and_find},
        {"Operator Square Brackets", test_operator_square_brackets},
        {"Overwrite and Duplicates", test_overwrite_and_duplicates},
        {"Size, Empty, Clear", test_size_empty_clear},
        {"Erase and Remove", test_erase_and_remove}
    };


    // --- 实现管理函数 ---
    const std::vector<TestCase>& get_test_cases() {
        return mymappro_test_cases;
    }

    void run_all_tests() {
        TestRunner::print_separator("MyMapPro Tests");
        for (const auto& test_case : mymappro_test_cases) {
            TestRunner::run_test(test_case.name, test_case.function);
        }
        TestRunner::print_summary();
        TestRunner::print_separator("MyMapPro Tests Complete");
    }

} // namespace TestMyMapPro
