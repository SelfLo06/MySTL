#include "myvector/test_myvector.h"

#include <cassert>

#include "common/test_common.h"
#include "MyVector.h"
#include <stdexcept>

namespace TestMyVector {
    void test_constructor() {
        MyVector<int> vec;
        if (vec.size() != 0 || vec.capacity() != 0) {
            throw std::runtime_error("Constructor test failed");
        }
        std::cout << "Constructor: size=" << vec.size() << ", capacity=" << vec.capacity() << std::endl;
    }

    void test_push_back() {
        MyVector<int> vec;
        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);

        if (vec.size() != 3) {
            throw std::runtime_error("Push back test failed");
        }
        std::cout << "Push back: size=" << vec.size() << ", capacity=" << vec.capacity() << std::endl;
    }

    void test_access() {
        MyVector<int> vec;
        vec.push_back(100);
        vec.push_back(200);

        if (vec[0] != 100 || vec[1] != 200) {
            throw std::runtime_error("Access test failed");
        }
        std::cout << "Access: vec[0]=" << vec[0] << ", vec[1]=" << vec[1] << std::endl;
    }

    void test_capacity() {
        MyVector<int> vec;
        for (int i = 0; i < 10; ++i) {
            vec.push_back(i);
        }

        std::cout << "Capacity test: final size=" << vec.size() << ", capacity=" << vec.capacity() << std::endl;
        std::cout << "Elements: ";
        for (size_t i = 0; i < vec.size(); ++i) {
            std::cout << vec[i] << " ";
        }
        std::cout << std::endl;
    }

    void test_copy_and_assignment() {
        MyVector<int> vec1;
        vec1.push_back(10);
        vec1.push_back(20);

        // 1. 测试拷贝构造函数
        MyVector<int> vec2 = vec1;
        assert(vec2.size() == 2);
        // if (vec2.size() != 1) {
        //     // 确保 throw 的内容不包含 "耗时"
        //     throw std::runtime_error(
        //         "Assertion failed: Expected vec2.size() to be 1, but it was " + std::to_string(vec2.size()));
        // } // 错误测试
        assert(vec2[0] == 10);
        assert(vec2[1] == 20);

        // 验证是深拷贝：修改 vec2 不应影响 vec1
        vec2.push_back(30);
        assert(vec1.size() == 2); // vec1 应该不变
        assert(vec2.size() == 3);
        std::cout << "Copy constructor test passed." << std::endl;

        // 2. 测试拷贝赋值运算符
        MyVector<int> vec3;
        vec3.push_back(99);
        vec3 = vec1; // 赋值
        assert(vec3.size() == 2);
        assert(vec3[0] == 10);

        // 验证是深拷贝：修改 vec1 不应影响 vec3
        vec1.push_back(40);
        assert(vec3.size() == 2); // vec3 应该不变
        assert(vec1.size() == 3);
        std::cout << "Copy assignment test passed." << std::endl;

        // 3. 测试自我赋值
        vec3 = vec3;
        assert(vec3.size() == 2);
        assert(vec3[0] == 10);
        std::cout << "Self-assignment test passed." << std::endl;
    }

    void test_modifiers_and_capacity() {
        MyVector<int> vec;
        assert(vec.empty()); // 测试 empty

        vec.push_back(10);
        vec.push_back(20);
        assert(!vec.empty());
        assert(vec.size() == 2);

        vec.pop_back(); // 测试 pop_back
        assert(vec.size() == 1);
        assert(vec[0] == 10);

        vec.clear(); // 测试 clear
        assert(vec.empty());
        assert(vec.size() == 0);
        // std::vector 的 clear() 不改变 capacity，我们也遵循这个惯例
        assert(vec.capacity() > 0);
        std::cout << "Modifiers and capacity test passed." << std::endl;
    }

    void test_iterator() {
        MyVector<int> vec;
        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);

        // 1. 测试遍历和读取
        std::cout << "Iterator test: Traversing and reading..." << std::endl;
        int sum = 0;
        for (int &value: vec) {
            sum += value;
        }
        assert(sum == 60);

        // 2. 测试通过迭代器修改
        std::cout << "Iterator test: Modifying through iterator..." << std::endl;
        for (int &value: vec) {
            value += 1;
        }
        assert(vec[0] == 11 && vec[1] == 21 && vec[2] == 31);

        // 3. 模拟传统 for 循环
        std::cout << "Iterator test: Traditional loop simulation..." << std::endl;
        MyVector<int>::iterator it = vec.begin();
        assert(*it == 11);
        ++it;
        assert(*it == 21);
        ++it;
        assert(*it == 31);
        ++it;
        assert(it == vec.end()); // 验证 end() 的位置

        // 4. 测试空容器
        std::cout << "Iterator test: Empty vector..." << std::endl;
        MyVector<int> empty_vec;
        assert(empty_vec.begin() == empty_vec.end());
    }

    // --- 核心改动：创建一个该模块的“测试用例注册表” ---
    static const std::vector<TestCase> myvector_test_cases = {
        {"Constructor Test", test_constructor},
        {"Push Back Test", test_push_back},
        {"Access Test", test_access},
        {"Capacity Test", test_capacity},
        {"Copy and Assignment Test", test_copy_and_assignment},
        {"Modifiers and Capacity Test", test_modifiers_and_capacity},
        {"Iterator Test", test_iterator}
    };

    // --- 实现管理函数 ---
    const std::vector<TestCase>& get_test_cases() {
        return myvector_test_cases;
    }



    // 升级 run_all_tests，让它从注册表中读取并运行
    void run_all_tests() {
        TestRunner::print_separator("MyVector Tests");
        // 直接遍历我们静态的测试用例列表
        for (const auto& test_case : myvector_test_cases) {
            // 直接调用 TestRunner::run_test，
            // test_case.function 本身就是 void(*)() 类型的函数指针，
            // 正好符合 run_test 函数的第二个参数类型。
            TestRunner::run_test(test_case.name, test_case.function);
        }
        TestRunner::print_summary();
        TestRunner::print_separator("MyVector Tests Complete");
    }
}
