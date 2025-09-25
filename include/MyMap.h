// MyMap.h

#ifndef MYSTL_MYMAP_H
#define MYSTL_MYMAP_H

#include "MyBST.h"

// 1. 定义 Pair 结构体
template <typename Key, typename Value>
struct Pair {
    Key key;
    Value value;

    Pair(const Key& k, const Value& v = Value{}) : key(k), value(v) {}

    // --- [NEW] 提供所有必要的比较运算符 ---
    // 比较只基于 key
    bool operator<(const Pair& other) const {
        return key < other.key;
    }
    bool operator>(const Pair& other) const {
        return key > other.key;
    }
    bool operator<=(const Pair& other) const {
        return key <= other.key;
    }
    bool operator>=(const Pair& other) const {
        return key >= other.key;
    }
    bool operator==(const Pair& other) const {
        return key == other.key;
    }
    bool operator!=(const Pair& other) const {
        return key != other.key;
    }
};

// 2. 搭建 MyMap 框架
template <typename Key, typename Value>
class MyMap {
private:
    // 使用 MyBST 存储 Pair 对象
    MyBST<Pair<Key, Value>> _tree;

public:
    void insert(const Key& key, const Value& value);
    Value* find(const Key& key) const;
    Value& operator[](const Key& key);

    size_t size() const { return _tree.size(); }
    bool empty() const { return _tree.empty(); }
    void clear() { _tree.clear(); }
};

template<typename Key, typename Value>
void MyMap<Key, Value>::insert(const Key &key, const Value &value) {
    // 为了查找，我们需要一个临时的 Pair 对象，
    // 它的 value 部分是什么无所谓，因为比较只看 key。
    Pair<Key, Value> temp_pair(key, Value{}); // Value{} 是 T 类型的默认构造

    if (_tree.find_value(temp_pair) == nullptr) { // 利用 find_value 检查 key 是否已存在
        // 如果不存在，就插入新的 Pair
        _tree.insert(Pair(key, value));
    }
}

template<typename Key, typename Value>
Value *MyMap<Key, Value>::find(const Key &key) const{
    Pair<Key, Value> temp_pair(key);
    Pair<Key, Value>* found_pair = _tree.find_value(temp_pair);// 传入整个 Pair

    if (found_pair != nullptr) {
        // 返回指针，即地址
        return &(found_pair->value);
    }

    return nullptr;
}

template<typename Key, typename Value>
Value &MyMap<Key, Value>::operator[](const Key &key) {
    Value* found_value = find(key);

    if (found_value != nullptr) {
        return *found_value;
    }
    else {
        // 如果键不存在就插入
        insert(key, Value{});

        found_value = find(key);
        return *found_value;
    }
}


#endif //MYSTL_MYMAP_H