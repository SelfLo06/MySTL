#include "mybst/test_mybst.h"
#include "common/test_common.h"
#include "MyBST.h" // 确保包含了你的头文件
#include <cassert>

namespace TestMyBST {

    void test_insert_and_find() {
        MyBST<int> bst;

        // 1. 空树测试
        assert(!bst.find(10));

        // 2. 插入并查找
        bst.insert(50);
        bst.insert(30);
        bst.insert(70);
        bst.insert(20);
        bst.insert(40);
        bst.insert(60);
        bst.insert(80);

        // 3. 验证已插入的元素
        assert(bst.find(50)); // root
        assert(bst.find(30)); // left child of root
        assert(bst.find(70)); // right child of root
        assert(bst.find(20)); // leaf
        assert(bst.find(80)); // leaf

        // 4. 验证不存在的元素
        assert(!bst.find(99));
        assert(!bst.find(10));
        assert(!bst.find(55));

        // 5. (可选)测试重复插入
        bst.insert(30); // 插入一个已存在的值，树结构不应改变
        assert(bst.find(30));
    }

    void test_traversals() {
        MyBST<int> bst;
        // 使用和之前一样的插入顺序，得到一棵结构确定的树
        bst.insert(50);
        bst.insert(30);
        bst.insert(70);
        bst.insert(20);
        bst.insert(40);
        bst.insert(60);
        bst.insert(80);

        // 1. 测试中序遍历 (In-order)
        std::vector<int> inorder_result;
        bst.inorder([&](const int& value) {
            inorder_result.push_back(value);
        });

        assert(inorder_result == std::vector<int>({20, 30, 40, 50, 60, 70, 80}));


        // 2. 测试前序遍历 (Pre-order)
        std::vector<int> preorder_result;
        bst.preorder([&](const int& value) {
            preorder_result.push_back(value);
        });

        assert(preorder_result == std::vector<int>({50, 30, 20, 40, 70, 60, 80}));


        // 3. 测试后序遍历 (Post-order)
        std::vector<int> postorder_result;
        bst.postorder([&](const int& value) {
            postorder_result.push_back(value);
        });

        assert(postorder_result == std::vector<int>({20, 40, 30, 60, 80, 70, 50}));
    }

      void test_lower_bound() {
        MyBST<int> bst;
        // 使用一个确定的数据集: 20, 30, 40, 50, 60, 70, 80
        bst.insert(50);
        bst.insert(30);
        bst.insert(70);
        bst.insert(20);
        bst.insert(40);
        bst.insert(60);
        bst.insert(80);

        // 为了访问Node中的数据，我们需要修改MyBST类，
        // 将Node结构体设为public，或者提供一个公共的迭代器。
        // 这里我们假设Node是public的，以便直接访问node->data。

        // 1. 查找一个精确存在的值
        // lower_bound(40) 应该返回指向40的节点
        auto node1 = bst.lower_bound(40);
        assert(node1 != nullptr && node1->data == 40);

        // 2. 查找一个不存在的值，但有比它大的值
        // lower_bound(45) 应该返回第一个不小于45的节点，即50
        auto node2 = bst.lower_bound(45);
        assert(node2 != nullptr && node2->data == 50);

        // 3. 查找一个小于所有元素的值
        // lower_bound(10) 应该返回最小的元素，即20
        auto node3 = bst.lower_bound(10);
        assert(node3 != nullptr && node3->data == 20);

        // 4. 查找等于最小元素的值
        // lower_bound(20) 应该返回20
        auto node4 = bst.lower_bound(20);
        assert(node4 != nullptr && node4->data == 20);

        // 5. 查找一个大于所有元素的值
        // lower_bound(99) 应该返回nullptr，因为没有不小于99的元素
        auto node5 = bst.lower_bound(99);
        assert(node5 == nullptr);

        // 6. 查找等于最大元素的值
        // lower_bound(80) 应该返回80
        auto node6 = bst.lower_bound(80);
        assert(node6 != nullptr && node6->data == 80);

        // 7. 测试空树的情况
        MyBST<int> empty_bst;
        auto node7 = empty_bst.lower_bound(100);
        assert(node7 == nullptr);
    }

    void test_upper_bound() {
        MyBST<int> bst;
        // 使用和之前一样的确定数据集: {20, 30, 40, 50, 60, 70, 80}
        bst.insert(50);
        bst.insert(30);
        bst.insert(70);
        bst.insert(20);
        bst.insert(40);
        bst.insert(60);
        bst.insert(80);

        // 假设 Node 结构体在 MyBST 中是 public 的

        // 1. 查找一个精确存在的值
        // upper_bound(40) 应该返回第一个严格大于40的节点，即50
        auto node1 = bst.upper_bound(40);
        assert(node1 != nullptr && node1->data == 50);

        // 2. 查找一个不存在的值
        // upper_bound(45) 应该返回第一个严格大于45的节点，即50
        auto node2 = bst.upper_bound(45);
        assert(node2 != nullptr && node2->data == 50);

        // 3. 查找一个小于所有元素的值
        // upper_bound(10) 应该返回最小的元素，即20
        auto node3 = bst.upper_bound(10);
        assert(node3 != nullptr && node3->data == 20);

        // 4. 查找等于最小元素的值
        // upper_bound(20) 应该返回第一个严格大于20的节点，即30
        auto node4 = bst.upper_bound(20);
        assert(node4 != nullptr && node4->data == 30);

        // 5. 查找一个大于所有元素的值
        // upper_bound(99) 应该返回nullptr，因为没有比99大的元素
        auto node5 = bst.upper_bound(99);
        assert(node5 == nullptr);

        // 6. 查找等于最大元素的值
        // upper_bound(80) 应该返回nullptr，因为没有比80大的元素
        auto node6 = bst.upper_bound(80);
        assert(node6 == nullptr);

        // 7. 测试空树的情况
        MyBST<int> empty_bst;
        auto node7 = empty_bst.upper_bound(100);
        assert(node7 == nullptr);
    }

void test_remove() {
        // 使用 lambda 表达式来快速构建一棵结构固定的树，方便复用
        auto create_test_tree = []() {
            MyBST<int> bst;
            bst.insert(50);
            bst.insert(30);
            bst.insert(70);
            bst.insert(20);
            bst.insert(40);
            bst.insert(60);
            bst.insert(80);
            bst.insert(35);
            bst.insert(45);
            return bst;
        };

        // 辅助函数，用于验证树的中序遍历结果是否符合预期
        auto verify_inorder = [](MyBST<int>& bst, const std::vector<int>& expected) {
            std::vector<int> inorder_result;
            bst.inorder([&](const int& value) {
                inorder_result.push_back(value);
            });
            assert(inorder_result == expected);
        };

        // Case 1: 删除叶子节点 (20)
        {
            MyBST<int> bst = create_test_tree();
            bst.remove(20);
            assert(!bst.find(20));
            verify_inorder(bst, {30, 35, 40, 45, 50, 60, 70, 80});
        }

        // Case 2: 删除只有一个右子节点的节点 (为了构造这个场景，我们先删掉35，让40只有一个右孩子45)
        {
            MyBST<int> bst = create_test_tree();
            bst.remove(35);
            bst.remove(40); // 40现在只有一个孩子45
            assert(!bst.find(40));
            assert(bst.find(45)); // 45应该被链接到30
            verify_inorder(bst, {20, 30, 45, 50, 60, 70, 80});
        }

        // Case 3: 删除只有一个左子节点的节点 (为了构造这个场景，我们先删掉45)
        {
            MyBST<int> bst = create_test_tree();
            bst.remove(45);
            bst.remove(40); // 40现在只有一个孩子35
            assert(!bst.find(40));
            assert(bst.find(35)); // 35应该被链接到30
            verify_inorder(bst, {20, 30, 35, 50, 60, 70, 80});
        }

        // Case 4: 删除有两个子节点的节点 (30)
        {
            MyBST<int> bst = create_test_tree();
            bst.remove(30);
            assert(!bst.find(30));
            // 30的位置被它的中序后继35取代
            verify_inorder(bst, {20, 35, 40, 45, 50, 60, 70, 80});
        }

        // Case 5: 删除根节点 (50)
        {
            MyBST<int> bst = create_test_tree();
            bst.remove(50);
            assert(!bst.find(50));
            // 根节点50的位置被它的中序后继60取代
            verify_inorder(bst, {20, 30, 35, 40, 45, 60, 70, 80});
        }

        // Case 6: 尝试删除不存在的节点 (99)
        {
            MyBST<int> bst = create_test_tree();
            bst.remove(99); // 树结构不应改变
            verify_inorder(bst, {20, 30, 35, 40, 45, 50, 60, 70, 80});
        }
    }

    void test_resource_management() {
        // 复用之前的辅助函数
        auto create_test_tree = []() {
            MyBST<int> bst;
            bst.insert(50);
            bst.insert(30);
            bst.insert(70);
            return bst;
        };

        auto verify_inorder = [](MyBST<int>& bst, const std::vector<int>& expected) {
            std::vector<int> inorder_result;
            bst.inorder([&](const int& value) {
                inorder_result.push_back(value);
            });
            assert(inorder_result == expected);
        };

        // Case 1: 测试拷贝构造函数
        {
            MyBST<int> bst1 = create_test_tree();

            // 使用 bst1 初始化 bst2
            MyBST<int> bst2 = bst1;

            // 验证1: bst2 的内容应该和 bst1 完全一样
            verify_inorder(bst2, {30, 50, 70});

            // 验证2: 修改 bst1，bst2 不应该受影响（证明是深拷贝）
            bst1.insert(80);
            verify_inorder(bst1, {30, 50, 70, 80});
            verify_inorder(bst2, {30, 50, 70}); // bst2 保持不变
        }

        // Case 2: 测试拷贝赋值运算符
        {
            MyBST<int> bst1 = create_test_tree();

            MyBST<int> bst2; // 创建一个不同的树
            bst2.insert(1);
            bst2.insert(2);

            // 执行赋值操作
            bst2 = bst1;

            // 验证1: bst2 的内容现在应该和 bst1 完全一样
            verify_inorder(bst2, {30, 50, 70});

            // 验证2: 修改 bst1，bst2 不应该受影响
            bst1.insert(20);
            verify_inorder(bst1, {20, 30, 50, 70});
            verify_inorder(bst2, {30, 50, 70}); // bst2 保持不变
        }

        // Case 3: 测试自我赋值
        {
            MyBST<int> bst = create_test_tree();

            // 执行自我赋值
            bst = bst;

            // 验证: 树的内容不应改变，程序不应崩溃
            verify_inorder(bst, {30, 50, 70});
        }
    }

    // --- 创建测试用例注册表 ---
    static const std::vector<TestCase> mybst_test_cases = {
        {"Insert and Find Test", test_insert_and_find},
        {"Traversals Test", test_traversals},
        {"Lower Bound Test", test_lower_bound},
        {"Upper Bound Test", test_upper_bound},
        {"Remove Test", test_remove},
        {"Resource Management (Copy/Assign)", test_resource_management}
    };

    // --- 实现管理函数 ---
    const std::vector<TestCase>& get_test_cases() {
        return mybst_test_cases;
    }

    void run_all_tests() {
        TestRunner::reset();
        TestRunner::print_separator("MyBST Tests");

        // 从注册表中读取并运行所有测试
        for (const auto& test_case : mybst_test_cases) {
            TestRunner::run_test(test_case.name, test_case.function);
        }

        TestRunner::print_summary();
        TestRunner::print_separator("MyBST Tests Complete");
    }
}