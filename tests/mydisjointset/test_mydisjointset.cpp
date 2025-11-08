#include "mydisjointset/test_mydisjointset.h"
#include "common/test_common.h"
#include "MyDisjointSet.h" // 包含您将要实现的头文件
#include <cassert>
#include <string>

namespace TestMyDisjointSet {

    // 辅助函数，用于快速创建一个包含 0 到 size-1 的并查集
    MyDisjointSet<int> create_int_set(size_t size) {
        MyDisjointSet<int> ds;
        for (size_t i = 0; i < size; ++i) {
            ds.make_set(i);
        }
        return ds;
    }

    void test_initialization() {
        MyDisjointSet<int> ds = create_int_set(10);
        assert(ds.count() == 10);
        for (int i = 0; i < 10; ++i) {
            assert(ds.find(i) == i); // 每个元素都是自己的根
            for (int j = i + 1; j < 10; ++j) {
                assert(!ds.connected(i, j)); // 初始时互不连通
            }
        }
    }

    void test_basic_union_and_find() {
        MyDisjointSet<int> ds = create_int_set(10);
        ds.unite(0, 1);
        assert(ds.count() == 9);
        assert(ds.connected(0, 1));
        assert(ds.find(0) == ds.find(1)); // 它们应该有共同的根

        ds.unite(2, 3);
        assert(ds.count() == 8);
        assert(ds.connected(2, 3));
        assert(ds.find(2) == ds.find(3));

        assert(!ds.connected(0, 2)); // 不同集合不应连通
    }

    void test_transitivity() {
        MyDisjointSet<int> ds = create_int_set(10);
        ds.unite(0, 1);
        ds.unite(1, 2);
        ds.unite(2, 3);

        assert(ds.count() == 7);
        assert(ds.connected(0, 3)); // 验证连通的传递性
        assert(ds.find(0) == ds.find(3));
    }

    void test_string_type() {
        MyDisjointSet<std::string> ds;
        ds.make_set("A");
        ds.make_set("B");
        ds.make_set("C");
        ds.make_set("D");

        assert(ds.count() == 4);
        assert(ds.find("A") == "A");
        assert(!ds.connected("A", "B"));

        ds.unite("A", "B");
        assert(ds.count() == 3);
        assert(ds.connected("A", "B"));
        assert(!ds.connected("A", "C"));

        ds.unite("C", "D");
        ds.unite("A", "D");
        assert(ds.count() == 1);
        assert(ds.connected("B", "C"));
        assert(ds.find("A") == ds.find("D"));
    }

    void test_exceptions() {
        MyDisjointSet<int> ds = create_int_set(5);
        bool caught = false;
        try {
            ds.find(99); // 查找不存在的元素
        } catch (const std::runtime_error&) {
            caught = true;
        }
        assert(caught);

        caught = false;
        try {
            ds.unite(1, 99); // 合并包含不存在元素的集合
        } catch (const std::runtime_error&) {
            caught = true;
        }
        assert(caught);
    }

    // --- 创建测试用例注册表 ---
    static const std::vector<TestCase> mydisjointset_test_cases = {
        {"Initialization Test (int)", test_initialization},
        {"Basic Union and Find (int)", test_basic_union_and_find},
        {"Transitivity Test (int)", test_transitivity},
        {"Generic Type Test (std::string)", test_string_type},
        {"Exception Safety Test", test_exceptions}
    };

    const std::vector<TestCase>& get_test_cases() {
        return mydisjointset_test_cases;
    }

    void run_all_tests() {
        TestRunner::reset();
        TestRunner::print_separator("MyDisjointSet Tests");
        for (const auto& test_case : mydisjointset_test_cases) {
            TestRunner::run_test(test_case.name, test_case.function);
        }
        TestRunner::print_summary();
        TestRunner::print_separator("MyDisjointSet Tests Complete");
    }

} // namespace TestMyDisjointSet