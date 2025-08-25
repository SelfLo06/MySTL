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
        // 思考：如何将 _buckets 初始化为 bucket_count 个空的链表？
        // 你可能需要为 MyVector 添加一个新的构造函数或 resize 方法
        // MyVector(size_t count, const T& value)
        // 或者 MyVector::resize(size_t count)
        _buckets.resize(bucket_count); // 假设 MyVector 有一个 resize 方法
    }
};

#endif // MYHASHMAP_H