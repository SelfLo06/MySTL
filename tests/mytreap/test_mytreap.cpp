#include "mytreap/test_mytreap.h"
#include "common/test_common.h"
#include "MyTreap.h"
#include <cassert>
#include <algorithm>

namespace TestMyTreap {

    void test_insert_and_find() {
        MyTreap<int> treap;

        // 1. 空树测试
        assert(!treap.find(10));
        assert(treap.size() == 0);

        // 2. 插入并查找
        treap.insert(50);
        treap.insert(30);
        treap.insert(70);
        treap.insert(20);
        treap.insert(40);
        treap.insert(60);
        treap.insert(80);

        // 3. 验证已插入的元素
        assert(treap.find(50));
        assert(treap.find(30));
        assert(treap.find(70));
        assert(treap.find(20));
        assert(treap.find(80));

        // 4. 验证不存在的元素
        assert(!treap.find(99));
        assert(!treap.find(10));
        assert(!treap.find(55));

        // 5. 测试重复插入 (size不应改变)
        size_t size_before = treap.size();
        treap.insert(30); // 插入一个已存在的值
        assert(treap.find(30));
        assert(treap.size() == size_before);
    }

    // 对于Treap，我们无法预测其具体结构，因此不能测试前序和后序遍历的具体结果。
    // 但我们可以，也必须测试其中序遍历的结果一定是有序的。
    void test_inorder_is_sorted() {
        MyTreap<int> treap;
        std::vector<int> data = {50, 30, 70, 20, 40, 60, 80};
        for (int x : data) {
            treap.insert(x);
        }

        std::vector<int> inorder_result;
        // 假设你的 MyTreap 实现了 inorder 遍历
        // 如果没有，你需要先添加它，逻辑和 MyBST 的完全一样
        treap.inorder([&](const int& value) {
            inorder_result.push_back(value);
        });

        // 验证1: 元素数量正确
        assert(inorder_result.size() == data.size());

        // 验证2: 遍历结果是严格有序的
        assert(std::is_sorted(inorder_result.begin(), inorder_result.end()));
    }

    void test_remove() {
        // 辅助函数，用于验证树的中序遍历结果是否符合预期
        auto verify_inorder = [](MyTreap<int>& treap, const std::vector<int>& expected) {
            std::vector<int> inorder_result;
            treap.inorder([&](const int& value) {
                inorder_result.push_back(value);
            });
            // 先对 expected 排序，因为 Treap 的结构不固定，但中序结果一定有序
            std::vector<int> sorted_expected = expected;
            std::sort(sorted_expected.begin(), sorted_expected.end());
            assert(inorder_result == sorted_expected);
        };

        // Case 1: 综合性删除测试
        {
            MyTreap<int> treap;
            treap.insert(50); treap.insert(30); treap.insert(70);
            treap.insert(20); treap.insert(40); treap.insert(60);
            treap.insert(80);
            assert(treap.size() == 7);

            // a. 删除一个叶子节点（概率较大）
            treap.remove(20);
            assert(!treap.find(20));
            assert(treap.size() == 6);
            verify_inorder(treap, {30, 40, 50, 60, 70, 80});

            // b. 删除一个有两个孩子的节点（概率较大）
            treap.remove(70);
            assert(!treap.find(70));
            assert(treap.size() == 5);
            verify_inorder(treap, {30, 40, 50, 60, 80});

            // c. 删除根节点（可能的根之一）
            treap.remove(50);
            assert(!treap.find(50));
            assert(treap.size() == 4);
            verify_inorder(treap, {30, 40, 60, 80});

            // d. 尝试删除不存在的节点
            treap.remove(99);
            assert(treap.size() == 4);
            verify_inorder(treap, {30, 40, 60, 80});
        }
    }

    void test_resource_management() {
        auto create_test_treap = []() {
            MyTreap<int> treap;
            treap.insert(50);
            treap.insert(30);
            treap.insert(70);
            return treap;
        };

        auto verify_inorder = [](MyTreap<int>& treap, const std::vector<int>& expected) {
            std::vector<int> result;
            treap.inorder([&](const int& val){ result.push_back(val); });
            assert(result == expected);
        };

        // Case 1: 测试拷贝构造函数
        {
            MyTreap<int> treap1 = create_test_treap();
            MyTreap<int> treap2 = treap1;

            verify_inorder(treap2, {30, 50, 70});
            assert(treap1.size() == treap2.size());

            treap1.insert(80);
            assert(treap1.size() == 4);
            assert(treap2.size() == 3); // 证明是深拷贝
            verify_inorder(treap2, {30, 50, 70});
        }

        // Case 2: 测试拷贝赋值运算符
        {
            MyTreap<int> treap1 = create_test_treap();
            MyTreap<int> treap2;
            treap2.insert(1);
            treap2.insert(2);

            treap2 = treap1;
            verify_inorder(treap2, {30, 50, 70});
            assert(treap1.size() == treap2.size());

            treap1.remove(30);
            assert(treap1.size() == 2);
            assert(treap2.size() == 3); // 证明是深拷贝
            verify_inorder(treap2, {30, 50, 70});
        }

        // Case 3: 测试自我赋值
        {
             MyTreap<int> treap = create_test_treap();
             treap = treap;
             assert(treap.size() == 3);
             verify_inorder(treap, {30, 50, 70});
        }
    }

    void test_size_basic() {
        MyTreap<int> treap;
        assert(treap.size() == 0);

        treap.insert(50);
        treap.insert(30);
        treap.insert(70);
        assert(treap.size() == 3);

        treap.remove(30);
        assert(treap.size() == 2);

        treap.insert(50); // 重复插入
        assert(treap.size() == 2);

        treap.remove(99); // 删除不存在
        assert(treap.size() == 2);

        treap.remove(50);
        treap.remove(70);
        assert(treap.size() == 0);
    }

    void test_size_copy_and_assign() {
        MyTreap<int> a;
        a.insert(50); a.insert(30); a.insert(70);
        assert(a.size() == 3);

        MyTreap<int> b = a;
        assert(b.size() == 3);

        a.remove(30);
        assert(a.size() == 2);
        assert(b.size() == 3);

        MyTreap<int> c;
        c.insert(1);
        c = b;
        assert(c.size() == b.size());
        c = c;
        assert(c.size() == b.size());
    }

    // --- 创建测试用例注册表 ---
    static const std::vector<TestCase> mytreap_test_cases = {
        {"Insert and Find Test", test_insert_and_find},
        {"In-order is Sorted Test", test_inorder_is_sorted},
        {"Remove Test", test_remove},
        {"Resource Management (Copy/Assign)", test_resource_management},
        {"Size Basic Test", test_size_basic},
        {"Size Copy/Assign Test", test_size_copy_and_assign}
    };

    const std::vector<TestCase>& get_test_cases() {
        return mytreap_test_cases;
    }

    void run_all_tests() {
        TestRunner::reset();
        TestRunner::print_separator("MyTreap Tests");
        for (const auto& test_case : mytreap_test_cases) {
            TestRunner::run_test(test_case.name, test_case.function);
        }
        TestRunner::print_summary();
        TestRunner::print_separator("MyTreap Tests Complete");
    }

} // namespace TestMyTreap