cmake_minimum_required(VERSION 3.16)

project(MySTL)

set(CMAKE_CXX_STANDARD 17)

# 设置包含目录
include_directories(include)
include_directories(tests)

# 添加可执行文件
add_executable(MySTL
        main.cpp
        tests/common/test_common.cpp
        tests/myvector/test_myvector.cpp
        include/MyLinkedList.h
        tests/mylinkedlist/test_mylinkedlist.cpp
        tests/mylinkedlist/test_mylinkedlist.h
        include/MyStack.h
        tests/mystack/test_mystack.cpp
        include/MyQueue.h
        tests/myqueue/test_myqueue.h
        tests/myqueue/test_myqueue.cpp
        include/MyBST.h
        tests/mybst/test_mybst.h
        tests/mybst/test_mybst.cpp
        include/MyQueue-new/MyQueue-new.h
        include/MyQueue-new/MyQueue-new.cpp
        tests/myqueue-new/test_myqueue_new.h
        tests/myqueue-new/test_myqueue_new.cpp
        include/MyHashMap.h
        tests/myhashmap/test_myhashmap.h
        tests/myhashmap/test_myhashmap.cpp
        # 未来可以添加：tests/mylist/test_mylist.cpp
)