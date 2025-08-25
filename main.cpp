#include <iostream>
#include <limits>

#include "myvector/test_myvector.h"
#include "mylinkedlist/test_mylinkedlist.h"
#include "mystack/test_mystack.h"
#include "myqueue/test_myqueue.h"
#include "mybst/test_mybst.h"
#include "myqueue-new/test_myqueue_new.h"
#include "myhashmap/test_myhashmap.h" // <-- 1. 包含新头文件

using namespace std;

// 函数：显示测试菜单
void display_menu() {
    cout << "\n========== CHOOSE A TEST TO RUN ==========\n";
    cout << "  1. MyVector Tests\n";
    cout << "  2. MyLinkedList Tests\n";
    cout << "  3. MyStack Tests\n";
    cout << "  4. MyQueue (from LinkedList) Tests\n";
    cout << "  5. MyBST Tests\n";
    cout << "  6. MyQueue (from two Stacks) Tests\n";
    cout << "  7. MyHashMap Tests\n"; // <-- 2. 添加新菜单项
    cout << "------------------------------------------\n";
    cout << "  0. Run ALL tests\n";
    cout << " -1. Exit\n";
    cout << "==========================================\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    while (true) {
        display_menu();
        cin >> choice;

        if (cin.fail()) {
            cout << "\n[Error] Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: TestMyVector::run_all_tests(); break;
            case 2: TestMyLinkedList::run_all_tests(); break;
            case 3: TestMyStack::run_all_tests(); break;
            case 4: TestMyQueue::run_all_tests(); break;
            case 5: TestMyBST::run_all_tests(); break;
            case 6: TestMyQueueNew::run_all_tests(); break;
            case 7: TestMyHashMap::run_all_tests(); break;

            case 0:
                cout << "\n--- Running all tests sequentially ---\n";
                TestMyVector::run_all_tests();
                TestMyLinkedList::run_all_tests();
                TestMyStack::run_all_tests();
                TestMyQueue::run_all_tests();
                TestMyBST::run_all_tests();
                TestMyQueueNew::run_all_tests();
                TestMyHashMap::run_all_tests();
                cout << "\n--- All tests completed ---\n";
                break;
            case -1:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "\n[Error] Invalid choice. Please try again.\n";
                break;
        }
    }
}