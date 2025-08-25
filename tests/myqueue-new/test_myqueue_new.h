#ifndef TEST_MYQUEUE_NEW_H
#define TEST_MYQUEUE_NEW_H

namespace TestMyQueueNew {
    // 测试基本的入队、出队和大小功能
    void test_basic_operations();

    // 测试对空队列执行 pop 操作是否会抛出异常
    void test_pop_from_empty();

    // 测试混合的 push 和 pop 操作，以验证两个栈之间的元素转移逻辑
    void test_mixed_operations();

    // 运行所有 MyQueue-new 的测试
    void run_all_tests();
}

#endif // TEST_MYQUEUE_NEW_H