#include "mylinkedlist/test_mylinkedlist.h"
#include "common/test_common.h"
#include "MyLinkedList.h"
#include <cassert>
#include <vector>

namespace TestMyLinkedList {

    void test_constructor_and_empty() {
        MyLinkedList<int> list;
        assert(list.size() == 0);
        assert(list.empty());
    }

    void test_push_back() {
        MyLinkedList<int> list;
        list.push_back(10);
        list.push_back(20);
        assert(list.size() == 2);
        assert(!list.empty());
    }

    void test_push_front() {
        MyLinkedList<int> list;
        list.push_front(10);
        list.push_front(20);
        list.push_front(30);
        assert(list.size() == 3);
    }

    void test_access_and_pop() {
        MyLinkedList<int> list;
        list.push_back(10); // list: 10
        list.push_back(20); // list: 10, 20
        list.push_front(5); // list: 5, 10, 20

        assert(list.front() == 5);
        assert(list.back() == 20);
        assert(list.size() == 3);

        list.front() = 1;
        assert(list.front() == 1);

        list.pop_front(); // list: 10, 20
        assert(list.front() == 10);
        assert(list.size() == 2);

        list.pop_back(); // list: 10
        assert(list.front() == 10);
        assert(list.back() == 10);
        assert(list.size() == 1);

        list.pop_back();
        assert(list.empty());

        // Test popping from an empty list (should be safe, no crash)
        try {
            list.pop_front();
            list.pop_back();
        } catch (const std::exception& e) {
            // It's also ok if it throws, depending on the implementation.
            // The main point is that it doesn't crash.
        }
        assert(list.empty());
    }

    // 正向迭代器测试
    void test_iterator() {
        MyLinkedList<int> list;
        list.push_back(10);
        list.push_back(20);
        list.push_back(30);

        // 1. 测试范围 for 循环
        int sum = 0;
        for (int& val : list) {
            sum += val;
        }
        assert(sum == 60);

        // 2. 测试通过迭代器修改
        for (int& val : list) {
            val += 1;
        }
        assert(list.front() == 11 && list.back() == 31);

        // 3. 测试空链表的 begin() 和 end()
        MyLinkedList<int> empty_list;
        assert(empty_list.begin() == empty_list.end());
    }

    // 反向迭代器测试
    void test_reverse_iterator() {
        MyLinkedList<int> list;
        list.push_back(10);
        list.push_back(20);
        list.push_back(30);

        std::vector<int> reversed_order;
        // 使用 rbegin() 和 rend() 进行反向遍历
        for (auto it = list.rbegin(); it != list.rend(); ++it) {
            reversed_order.push_back(*it);
        }

        assert(reversed_order.size() == 3);
        assert(reversed_order[0] == 30);
        assert(reversed_order[1] == 20);
        assert(reversed_order[2] == 10);
    }

    // “三法则”测试
    void test_copy_semantics() {
        MyLinkedList<int> list1;
        list1.push_back(10);
        list1.push_back(20);

        // 1. 测试拷贝构造函数
        MyLinkedList<int> list2 = list1;

        assert(list2.size() == 2);
        assert(list2.front() == 10);
        assert(list2.back() == 20);

        // 验证深拷贝：修改 list2 不应影响 list1
        list2.push_back(30);
        assert(list1.size() == 2);
        assert(list2.size() == 3);
        assert(list1.back() == 20);
        assert(list2.back() == 30);

        // 2. 测试拷贝赋值运算符
        MyLinkedList<int> list3;
        list3.push_back(99);
        list3 = list1;

        assert(list3.size() == 2);
        assert(list3.front() == 10);

        // 验证深拷贝
        list3.pop_front();
        assert(list1.size() == 2);
        assert(list1.front() == 10);
        assert(list3.size() == 1);
        assert(list3.front() == 20);
    }


    // 创建测试用例注册表
    static const std::vector<TestCase> mylinkedlist_test_cases = {
        {"Constructor and Empty Test", test_constructor_and_empty},
        {"Push Back Test", test_push_back},
        {"Push Front Test", test_push_front},
        {"Access and Pop Test", test_access_and_pop},
        {"Iterator Test", test_iterator},
        {"Reverse Iterator Test", test_reverse_iterator},
        {"Copy Semantics Test", test_copy_semantics}
    };

    // 获取测试用例列表
    const std::vector<TestCase>& get_test_cases() {
        return mylinkedlist_test_cases;
    }

    void run_all_tests() {
        TestRunner::print_separator("MyLinkedList Tests");

        for (const auto& test_case : mylinkedlist_test_cases) {
            TestRunner::run_test(test_case.name, test_case.function);
        }

        TestRunner::print_summary();
        TestRunner::print_separator("MyLinkedList Tests Complete");
    }
}