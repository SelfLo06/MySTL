#include "myqueue/test_myqueue.h"
#include "common/test_common.h"
#include "MyQueue.h"
#include <cassert>

namespace TestMyQueue {
    void test_queue_operations() {
        MyQueue<int> q;
        assert(q.empty());

        // Push (入队)
        q.push(10); // q: 10
        q.push(20); // q: 10, 20
        q.push(30); // q: 10, 20, 30

        assert(q.size() == 3);

        // Front and Back (队头和队尾)
        assert(q.front() == 10);
        assert(q.back() == 30);

        // 修改队头
        q.front() = 15;
        assert(q.front() == 15);

        // Pop (出队)
        q.pop(); // q: 20, 30
        assert(q.size() == 2);
        assert(q.front() == 20);

        q.pop(); // q: 30
        assert(q.front() == 30);
        assert(q.back() == 30);

        q.pop(); // q: empty
        assert(q.empty());
    }

    void run_all_tests() {
        TestRunner::print_separator("MyQueue Tests");
        TestRunner::run_test("Queue Operations Test", test_queue_operations);
        TestRunner::print_summary();
        TestRunner::print_separator("MyQueue Tests Complete");
    }
}