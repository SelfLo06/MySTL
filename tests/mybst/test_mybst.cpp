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

    void run_all_tests() {
        TestRunner::print_separator("MyBST Tests");
        TestRunner::run_test("Insert and Find Test", test_insert_and_find);
        TestRunner::run_test("Traversals Test", test_traversals);
        TestRunner::print_summary();
        TestRunner::print_separator("MyBST Tests Complete");
    }
}