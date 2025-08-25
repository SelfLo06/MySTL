#include "myhashmap/test_myhashmap.h"
#include "common/test_common.h"
#include "MyHashMap.h"
#include <cassert>
#include <string>

namespace TestMyHashMap {

    void test_insert_and_access() {
        MyHashMap<std::string, int> map;

        // 0. 测试 size()
        assert(map.size() == 0);

        // 1. 测试 insert
        map.insert("one", 1);
        map.insert("two", 2);
        assert(map.size() == 2);

        // 2. 测试 operator[] 的访问功能
        assert(map["one"] == 1);
        assert(map["two"] == 2);

        // 3. 测试 insert 的更新功能
        map.insert("one", 111);
        assert(map.size() == 2); // Size 不应改变
        assert(map["one"] == 111);

        // 4. 测试 operator[] 的创建功能
        // 访问一个不存在的 key "three"
        // int() 的默认值是 0
        assert(map["three"] == 0);
        assert(map.size() == 3); // Size 应该增加

        // 5. 测试 operator[] 的赋值功能
        map["four"] = 4;
        map["two"] = 222;
        assert(map["four"] == 4);
        assert(map["two"] == 222);
        assert(map.size() == 4);
    }

    // ... test_insert_and_access() ...

    void test_find_and_erase() {
        MyHashMap<std::string, int> map;
        map.insert("one", 1);
        map.insert("two", 2);
        map.insert("three", 3);
        assert(map.size() == 3);

        // 1. 测试 find 的基本功能
        int* val_ptr = map.find("two");
        assert(val_ptr != nullptr); // 应该能找到
        assert(*val_ptr == 2);

        assert(map.find("four") == nullptr); // 应该找不到

        // 2. 测试通过 find 返回的指针修改 value
        *val_ptr = 22;
        assert(map["two"] == 22); // 验证值已被修改

        // 3. 测试 erase 的基本功能
        bool erased = map.erase("one");
        assert(erased == true);
        assert(map.size() == 2);
        assert(map.find("one") == nullptr); // 确认已被删除

        // 4. 测试 erase 不存在的 key
        erased = map.erase("five");
        assert(erased == false);
        assert(map.size() == 2); // size 不应改变

        // 5. 测试 erase 后，不影响同一个桶中的其他元素
        //    (这是一个简化测试，假设 "two" 和 "three" 不在同一个桶)
        assert(map["two"] == 22);
        assert(map["three"] == 3);

        // 把所有元素都删除
        map.erase("two");
        map.erase("three");
        assert(map.size() == 0);
        assert(map.find("three") == nullptr);
    }

    void run_all_tests() {
        TestRunner::reset();
        TestRunner::print_separator("MyHashMap Tests");
        TestRunner::run_test("Insert and Access Test", test_insert_and_access);
        TestRunner::run_test("Find and Erase Test", test_find_and_erase);
        TestRunner::print_summary();
        TestRunner::print_separator("MyHashMap Tests Complete");
    }
}