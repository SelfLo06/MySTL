#include <iostream>     // 用于标准输入输出 (cout, cin)
#include <limits>       // 用于处理输入错误 (numeric_limits)
#include <string>       // 用于处理命令行参数
#include <vector>       // 用于创建我们的“测试清单”
#include <functional>   // 用于在结构体中存储可调用的测试函数

// 包含所有需要被测试的模块的头文件
#include "common/test_common.h" // 确保包含了 test_common.h
#include "myvector/test_myvector.h"
#include "mylinkedlist/test_mylinkedlist.h"
#include "mystack/test_mystack.h"
#include "myqueue/test_myqueue.h"
#include "mybst/test_mybst.h"
#include "myqueue-new/test_myqueue_new.h"
#include "myhashmap/test_myhashmap.h"
#include "mydeque/test_mydeque.h"
#include "mybinaryheap/test_mybinaryheap.h"
#include "mypriorityqueue/test_mypriorityqueue.h"
#include "myset/test_myset.h"
#include "mymap/test_mymap.h"
#include "mytreap/test_mytreap.h"
#include "mysetpro/test_mysetpro.h"
#include "mymappro/test_mymappro.h"
#include "mydisjointset/test_mydisjointset.h"


// 帮助函数: 将所有测试按顺序执行。
void run_all_tests_sequentially() {
    using namespace std; // 在函数作用域内使用
    cout << "\n--- Running all tests sequentially ---" << endl;

    // 我们假设每个模块的 run_all_tests 都会重置和打印自己的摘要
    TestMyVector::run_all_tests();
    TestMyLinkedList::run_all_tests();
    TestMyStack::run_all_tests();
    TestMyQueue::run_all_tests();
    TestMyBST::run_all_tests();
    TestMyQueueNew::run_all_tests();
    TestMyHashMap::run_all_tests();
    TestMyDeque::run_all_tests();
    TestMyBinaryHeap::run_all_tests();
    TestMyPriorityQueue::run_all_tests();
    TestMyMap::run_all_tests();
    TestMySet::run_all_tests();
    TestMyTreap::run_all_tests();
    TestMySetPro::run_all_tests();
    TestMyMapPro::run_all_tests();
    TestMyDisjointSet::run_all_tests();

    cout << "\n--- All tests completed ---" << endl;
}


// 模式一：为人类设计的交互式菜单
void runInteractiveMode() {
    using namespace std; // 在函数作用域内使用

    // 注意：这个函数现在可能与我们新的数据驱动架构有点脱节
    // 但作为备用调试工具，我们暂时保留它。
    // 一个更好的实现也会从各个模块的 get_test_cases() 动态生成菜单。

    int choice;
    while (true) {
        cout << "\n========== CHOOSE A TEST GROUP TO RUN ==========\n";
        cout << "  1. MyVector Tests\n";
        cout << "  2. MyLinkedList Tests\n";
        cout << "  3. MyStack Tests\n";
        cout << "  4. MyQueue (from List) Tests\n";
        cout << "  5. MyBST Tests\n";
        cout << "  6. MyQueue (from Stacks) Tests\n";
        cout << "  7. MyHashMap Tests\n";
        cout << "  8. MyDeque Tests\n";
        cout << "  9. MyBinaryHeap Tests\n";
        cout << " 10. MyPriorityQueue Tests\n";
        cout << " 11. MySet Tests\n";
        cout << " 12. MyMap Tests\n";
        cout << " 13. MyTreap Tests\n";
        cout << " 14. MySetPro Tests\n";
        cout << " 15. MyMapPro Tests\n";
        cout << " 16. MyDisjointSet Tests\n";
        cout << "------------------------------------------\n";
        cout << "  0. Run ALL tests\n";
        cout << " -1. Exit\n";
        cout << "==========================================\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail()) {
            cout << "\n[Error] Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        TestRunner::reset(); // 每次选择都重置
        switch(choice) {
            case 1: TestMyVector::run_all_tests(); TestRunner::print_summary(); break;
            case 2: TestMyLinkedList::run_all_tests(); TestRunner::print_summary(); break;
            case 3: TestMyStack::run_all_tests(); TestRunner::print_summary(); break;
            case 4: TestMyQueue::run_all_tests(); TestRunner::print_summary(); break;
            case 5: TestMyBST::run_all_tests(); TestRunner::print_summary(); break;
            case 6: TestMyQueueNew::run_all_tests(); TestRunner::print_summary(); break;
            case 7: TestMyHashMap::run_all_tests(); TestRunner::print_summary(); break;
            case 8: TestMyDeque::run_all_tests(); TestRunner::print_summary();break;
            case 9: TestMyBinaryHeap::run_all_tests(); TestRunner::print_summary();break;
            case 10: TestMyPriorityQueue::run_all_tests(); TestRunner::print_summary(); break;
            case 11: TestMySet::run_all_tests(); TestRunner::print_summary(); break;
            case 12: TestMyMap::run_all_tests(); TestRunner::print_summary(); break;
            case 13: TestMyTreap::run_all_tests(); TestRunner::print_summary(); break;
            case 14: TestMySetPro::run_all_tests(); TestRunner::print_summary(); break;
            case 15: TestMyMapPro::run_all_tests(); TestRunner::print_summary(); break;
            case 16: TestMyDisjointSet::run_all_tests(); TestRunner::print_summary(); break;
            case 0: run_all_tests_sequentially(); break; // 这个函数自己会处理摘要
            case -1: cout << "Exiting program.\n"; return;
            default: cout << "\n[Error] Invalid choice. Please try again.\n"; break;
        }
    }
}

// 模式二：为Python设计的命令模式
void runCommandMode(int argc, char* argv[]) {
    using namespace std; // 在函数作用域内使用

    string command = argv[1];

    // --- 模式 1: 列出所有测试组 ---
    if (command == "list_tests" && argc == 2) {
        cout << "test_vector;MyVector Tests" << endl;
        cout << "test_list;MyLinkedList Tests" << endl;
        cout << "test_stack;MyStack Tests" << endl;
        cout << "test_queue;MyQueue (from List) Tests" << endl;
        cout << "test_bst;MyBST Tests" << endl;
        cout << "test_queue_new;MyQueue (from Stacks) Tests" << endl;
        cout << "test_hashmap;MyHashMap Tests" << endl;
        cout << "test_deque;MyDeque Tests" << endl;
        cout << "test_heap;MyBinaryHeap Tests" << endl;
        cout << "test_pq;MyPriorityQueue Tests" << endl;
        cout << "test_set;MySet Tests" << endl;
        cout << "test_map;MyMap Tests" << endl;
        cout << "test_treap;MyTreap Tests" << endl;
        cout << "test_setpro;MySetPro Tests" << endl;
        cout << "test_mappro;MyMapPro Tests" << endl;
        cout << "test_disjointset;MyDisjointSet Tests" << endl;
        cout << "test_all;Run ALL Tests" << endl;
        return;
    }

    // --- 模式 2: 列出指定组内的所有单个测试 ---
    if (command == "list_tests" && argc == 3) {
        string group_name = argv[2];
        const vector<TestCase>* test_cases = nullptr;

        if (group_name == "test_vector") test_cases = &TestMyVector::get_test_cases();
        else if (group_name == "test_list") test_cases = &TestMyLinkedList::get_test_cases();
        else if (group_name == "test_stack") test_cases = &TestMyStack::get_test_cases();
        else if (group_name == "test_queue") test_cases = &TestMyQueue::get_test_cases();
        else if (group_name == "test_bst") test_cases = &TestMyBST::get_test_cases();
        else if (group_name == "test_queue_new") test_cases = &TestMyQueueNew::get_test_cases();
        else if (group_name == "test_hashmap") test_cases = &TestMyHashMap::get_test_cases();
        else if (group_name == "test_deque") test_cases = &TestMyDeque::get_test_cases();
        else if (group_name == "test_heap") test_cases = &TestMyBinaryHeap::get_test_cases();
        else if (group_name == "test_pq") test_cases = &TestMyPriorityQueue::get_test_cases();
        else if (group_name == "test_set") test_cases = &TestMySet::get_test_cases();
        else if (group_name == "test_map") test_cases = &TestMyMap::get_test_cases();
        else if (group_name == "test_treap") test_cases = &TestMyTreap::get_test_cases();
        else if (group_name == "test_setpro") test_cases = &TestMySetPro::get_test_cases();
        else if (group_name == "test_mappro") test_cases = &TestMyMapPro::get_test_cases();
        else if (group_name == "test_disjointset") test_cases = &TestMyDisjointSet::get_test_cases();

        if (test_cases) {
            for (const auto& test_case : *test_cases) {
                cout << test_case.name << endl;
            }
        } else {
            cout << "ERROR: Unknown test group '" << group_name << "'" << endl;
        }
        return;
    }

    // --- 模式 3: 运行指定的单个测试 ---
    if (command == "run_single" && argc == 4) {
        string group_name = argv[2];
        string test_name = argv[3];
        const vector<TestCase>* test_cases = nullptr;

        if (group_name == "test_vector") test_cases = &TestMyVector::get_test_cases();
        else if (group_name == "test_list") test_cases = &TestMyLinkedList::get_test_cases();
        else if (group_name == "test_stack") test_cases = &TestMyStack::get_test_cases();
        else if (group_name == "test_queue") test_cases = &TestMyQueue::get_test_cases();
        else if (group_name == "test_bst") test_cases = &TestMyBST::get_test_cases();
        else if (group_name == "test_queue_new") test_cases = &TestMyQueueNew::get_test_cases();
        else if (group_name == "test_hashmap") test_cases = &TestMyHashMap::get_test_cases();
        else if (group_name == "test_deque") test_cases = &TestMyDeque::get_test_cases();
        else if (group_name == "test_heap") test_cases = &TestMyBinaryHeap::get_test_cases();
        else if (group_name == "test_pq") test_cases = &TestMyPriorityQueue::get_test_cases();
        else if (group_name == "test_set") test_cases = &TestMySet::get_test_cases();
        else if (group_name == "test_map") test_cases = &TestMyMap::get_test_cases();
        else if (group_name == "test_treap") test_cases = &TestMyTreap::get_test_cases();
        else if (group_name == "test_setpro") test_cases = &TestMySetPro::get_test_cases();
        else if (group_name == "test_mappro") test_cases = &TestMyMapPro::get_test_cases();
        else if (group_name == "test_disjointset") test_cases = &TestMyDisjointSet::get_test_cases();

        if (test_cases) {
            bool found = false;
            for (const auto& test_case : *test_cases) {
                if (test_case.name == test_name) {
                    TestRunner::reset();
                    TestRunner::run_test(test_case.name, test_case.function);
                    TestRunner::print_summary();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "ERROR: Test '" << test_name << "' not found in group '" << group_name << "'" << endl;
            }
        } else {
            cout << "ERROR: Unknown test group '" << group_name << "'" << endl;
        }
        return;
    }

    // --- 模式 4: 运行整个测试组 ---
    TestRunner::reset();
    if (command == "test_vector") TestMyVector::run_all_tests();
    else if (command == "test_list") TestMyLinkedList::run_all_tests();
    else if (command == "test_stack") TestMyStack::run_all_tests();
    else if (command == "test_queue") TestMyQueue::run_all_tests();
    else if (command == "test_bst") TestMyBST::run_all_tests();
    else if (command == "test_queue_new") TestMyQueueNew::run_all_tests();
    else if (command == "test_hashmap") TestMyHashMap::run_all_tests();
    else if (command == "test_deque") TestMyDeque::run_all_tests();
    else if (command == "test_heap") TestMyBinaryHeap::run_all_tests();
    else if (command == "test_pq") TestMyPriorityQueue::run_all_tests();
    else if (command == "test_set") TestMySet::run_all_tests();
    else if (command == "test_map") TestMyMap::run_all_tests();
    else if (command == "test_treap") TestMyTreap::run_all_tests();
    else if (command == "test_setpro") TestMySetPro::run_all_tests();
    else if (command == "test_mappro") TestMyMapPro::run_all_tests();
    else if (command == "test_disjointset") TestMyDisjointSet::run_all_tests();
    else if (command == "test_all") {
        run_all_tests_sequentially();
        return; // all tests 模式自己管理摘要，所以提前退出
    }
    else {
        cout << "ERROR: Unknown command or invalid arguments for command '" << command << "'" << endl;
        return;
    }
    // 运行完一组后打印摘要
    TestRunner::print_summary();
}

// ===================================================================================
//  主函数 (Main Entry Point)
// ===================================================================================
int main(int argc, char* argv[]) {
    // argc 是命令行参数的总数。如果只有程序名，argc为1。
    if (argc > 1) {
        // 如果有超过1个参数，说明用户提供了额外的指令，进入命令模式
        runCommandMode(argc, argv);
    } else {
        // 否则，像以前一样，进入为人类设计的交互模式
        runInteractiveMode();
    }
    return 0; // 程序正常结束
}