#ifndef MYHASHMAP_H
#define MYHASHMAP_H

#include "MyVector.h"    // 我们将使用 MyVector 作为桶数组
#include "MyLinkedList.h" // 每个桶是一个 MyLinkedList
#include <functional>    // 需要 std::hash

template <typename K, typename V>
class MyHashMap {
private:
    // 1. 定义存储键值对的节点结构
    // (注意：这里我们暂时不自己实现Node，而是直接利用 MyLinkedList)

    // 2. 定义桶数组
    // 桶数组是一个向量，每个元素是一个链表
    // 链表中的每个节点，理论上应该是一个键值对。
    // 为了简单起见，我们先让链表直接存储 std::pair<K, V>
    // 这意味着我们需要为 MyLinkedList 添加一个 find/search 方法
    // 或者，我们可以让 MyLinkedList 存储 Node*，Node里有 K, V, next

    // 我们选择更简单的方式：让 MyLinkedList 存储键值对 std::pair
    // 这要求我们的 MyLinkedList 功能比较完善

    // 为了从零开始，我们自己定义Node，并让 MyLinkedList 存储 Node
    struct Node {
        K key;
        V value;
        // 注意：这个Node不需要next/prev，因为MyLinkedList会处理
        Node(const K& k, const V& v) : key(k), value(v) {}
    };

    MyVector<MyLinkedList<Node>> _buckets;
    size_t _size; // Map中总的键值对数量

    // 私有辅助函数：根据 key 计算桶的索引
    size_t _get_bucket_index(const K& key) const {
        // 使用C++标准库提供的 std::hash
        std::hash<K> hasher;
        return hasher(key) % _buckets.size();
    }

public:
    // 构造函数：初始化桶数组
    explicit MyHashMap(size_t bucket_count = 16)
        : _size(0)
    {
        _buckets.resize(bucket_count);
    }

    void insert(const K& key, const V& value);
    V& operator[](const K& key);

    size_t size() const { return _size; }

    //根据 key 查找，如果找到了，返回一个指向 value 的指针；如果没找到，返回 nullptr。
    V* find(const K& key);
    const V* find(const K& key) const;

    bool erase(const K &key);
};

template <typename K, typename V>
V* MyHashMap<K, V>::find(const K& key) {
    size_t bucket_index = _get_bucket_index(key);
    MyLinkedList<Node>& bucket = _buckets[bucket_index];

    // 遍历桶
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it.getNode()->data.key == key) {
            // 找到了！返回这个节点 value 的地址
            return  &it.getNode()->data.value;
        }
    }
    // 循环结束了还没找到，返回空指针
    return nullptr;
}

template <typename K, typename V>
const V* MyHashMap<K, V>::find(const K& key) const {
    size_t bucket_index = _get_bucket_index(key);
    const MyLinkedList<Node>& bucket = _buckets[bucket_index];

    // 遍历桶
    for (auto it = bucket.cbegin(); it != bucket.cend(); ++it) {
        if (it.getNode()->data.key == key) {
            // 找到了！返回这个节点 value 的地址
            return  &it.getNode()->data.value;
        }
    }
    // 循环结束了还没找到，返回空指针
    return nullptr;
}

template <typename K, typename V>
void MyHashMap<K, V>::insert(const K& key, const V& value) {
    // 1. 获取桶的索引和桶本身
    size_t bucket_index = _get_bucket_index(key);
    MyLinkedList<Node>& bucket = _buckets[bucket_index];

    // 2. 遍历桶，寻找key
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it.getNode()->data.key == key) {

            // 3. 如果找到了，说明 key 已存在
            //    更新这个节点的 value，然后就可以结束函数了
            it.getNode()->data.value = value;
            return;
        }
    }

    // 4. 如果 for 循环正常结束了，说明 key 不存在
    //    在桶的末尾添加一个新的 Node
    bucket.push_back(Node(key,value));

    // 5. 只有在真正添加了新节点时，才需要增加 _size
    _size++;
}

template <typename K, typename V>
V& MyHashMap<K, V>::operator[](const K& key) {
    // 1. 获取桶的索引和桶本身
    size_t bucket_index = _get_bucket_index(key);
    MyLinkedList<Node>& bucket = _buckets[bucket_index];

    // 2. 遍历桶，寻找 key
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it.getNode()->data.key == key) {
            return it.getNode()->data.value;
        }
    }

    // 4. 如果循环结束了还没找到：
    //    A. 在桶的末尾插入一个新节点，其 value 为 V 类型的默认值 (V())。
    bucket.push_back(Node(key,V()));

    //    B. 增加 _size
    _size++;

    //    C. 返回这个刚刚被创建的新节点的 value 的引用。
    return bucket.back().value;
}

template <typename K, typename V>
bool MyHashMap<K, V>::erase(const K& key) {
    size_t bucket_index = _get_bucket_index(key);
    MyLinkedList<Node>& bucket = _buckets[bucket_index];

    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it.getNode()->data.key == key) {
            bucket.erase(it);
            _size--;
            return true;
        }
    }
    return false;
}

#endif