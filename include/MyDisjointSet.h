#ifndef MY_DISJOINT_SET_H
#define MY_DISJOINT_SET_H

#include "MyVector.h"
#include "MyHashMap.h" // 关键！引入哈希表用于类型到索引的映射
#include <stdexcept>   // 用于在找不到元素时抛出异常

/**
 * @brief 一个泛型的并查集（不相交集）数据结构。
 * @tparam T 元素的类型。T 必须是可哈希的 (以便用于 MyHashMap) 且支持相等比较 (operator==)。
 */
template <typename T>
class MyDisjointSet {
private:
    // --- 内部数据结构 ---
    MyVector<size_t> _parent; // 核心数据结构，存储父节点的 *索引*
    MyVector<int>    _rank;   // 存储每个集合的“秩”
    size_t           _count;  // 记录独立集合的数量

    // --- 映射层 ---
    MyHashMap<T, size_t> _to_index;   // 从用户数据 T -> 内部索引 size_t
    MyVector<T>          _from_index; // 从内部索引 size_t -> 用户数据 T

    /**
     * @brief 内部实现的 find，操作的是整数索引。包含路径压缩。
     * @param index 要查找的元素的内部索引。
     * @return 该元素所在集合的根节点的 *索引*。
     */
    size_t _find_internal(size_t index) {
        // 这部分和非泛型版本的逻辑完全一样，只是操作的是索引。
        // 1. 检查 index 是否是根节点 (index == _parent[index])。
        // 2. 如果不是，递归查找，并进行路径压缩：
        //    _parent[index] = _find_internal(_parent[index]);
        // 3. 返回根节点的索引。
        if (index != _parent[index]) {
            _parent[index] = _find_internal(_parent[index]);
        }
        return _parent[index];
    }


public:
    // --- 构造与析构 ---
    MyDisjointSet() : _count(0) {} // 默认构造，创建一个空的并查集

    // --- 核心 API ---

    /**
     * @brief 向并查集中添加一个新元素，使其自成一个集合。
     * @param element 要添加的元素。如果元素已存在，则此操作无效。
     */
    void make_set(const T& element) {
        // 1. 使用 _to_index.find() 检查元素是否已经存在。如果存在，直接 return。
        if (_to_index.find(element)) return;
        // 2. 获取新元素的内部索引 (即当前 _from_index 的大小)。
        int new_index = _from_index.size();
        // 3. 将 {element, new_index} 存入 _to_index。
        _to_index.insert(element, new_index);
        // 4. 将 element 存入 _from_index。
        _from_index.push_back(element);
        // 5. 在 _parent 和 _rank 的末尾添加新元素的信息 (父节点是自己，秩为0)。
        _parent.push_back(new_index);
        _rank.push_back(0);
        // 6. 别忘了将 _count 加 1。
        _count++;
    }

    /**
     * @brief 查找元素 element 所在集合的代表元。
     * @param element 要查找的元素。
     * @return 该元素所在集合的代表元的值 (类型为 T)。
     * @throws std::runtime_error 如果元素不存在。
     */
    const T& find(const T& element) {
        // 1. 使用 _to_index.find() 查找 element 对应的内部索引。
        size_t* index_ptr = _to_index.find(element);
        // 2. 如果找不到，抛出异常。
        if (index_ptr == nullptr) {
            throw std::runtime_error("Element not found in the set.");
        }
        size_t index = *index_ptr;

        // 3. 调用 _find_internal(index) 找到根节点的 索引。
        size_t root = _find_internal(index);
        // 4. 使用 _from_index 从根节点索引反查到对应的 T 类型的值并返回。

        return _from_index[root];
    }

    /**
     * @brief 合并包含元素 p 和元素 q 的两个集合。
     * @param p 第一个元素。
     * @param q 第二个元素。
     * @throws std::runtime_error 如果任一元素不存在。
     */
    void unite(const T& p, const T& q) {
        // 1. 使用 _to_index 分别找到 p 和 q 的内部索引 p_idx 和 q_idx。找不到就抛异常。
        size_t* p_idx = _to_index.find(p);
        size_t* q_idx = _to_index.find(q);
        if (p_idx == nullptr || q_idx == nullptr) throw std::runtime_error("Element not found in the set.");
        // 2. 调用 _find_internal 分别找到它们的根节点索引 rootP_idx 和 rootQ_idx。
        size_t rootP = _find_internal(*p_idx);
        size_t rootQ = _find_internal(*q_idx);
        // 3. 如果根节点相同，则它们已在同一集合，直接 return。
        if (rootP == rootQ) return;
        // 4. 否则，执行“按秩合并”逻辑（这部分和非泛型版本完全一样）。
        if (_rank[rootP] > _rank[rootQ]) {
            _parent[rootQ] = rootP;
        }
        else if (_rank[rootP] < _rank[rootQ]) {
            _parent[rootP] = rootQ;
        }
        else {
            _parent[rootQ] = rootP;
            ++_rank[rootP];
        }
        // 5. 别忘了将 _count 减 1。
        _count--;
    }

    // --- 辅助查询 ---

    /**
     * @brief 检查两个元素 p 和 q 是否属于同一个集合。
     * @return 如果它们连通则返回 true，否则返回 false。
     * @throws std::runtime_error 如果任一元素不存在。
     */
    bool connected(const T& p, const T& q) {
        return find(p) == find(q);
    }

    /**
     * @brief 返回当前独立集合的数量。
     */
    size_t count() const {
        return _count;
    }
};

#endif // MY_DISJOINT_SET_H


// #ifndef MY_DISJOINT_SET_H
// #define MY_DISJOINT_SET_H
//
// #include "MyVector.h"    // 使用您自己实现的 MyVector
// #include <cstddef>       // 为了 size_t
// #include <stdexcept>     // 为了 std::out_of_range 异常
//
// /**
//  * @brief 一个高效的并查集（不相交集）数据结构。
//  * @note  这个版本仅支持从 0 到 size-1 的连续整数作为元素。
//  */
// class MyDisjointSet {
// private:
//     MyVector<size_t> _parent; // _parent[i] 存储元素 i 的父节点索引
//     MyVector<int>    _rank;   // _rank[i] 存储以 i 为根的树的“秩” (高度的一个上界)
//     size_t           _count;  // 记录当前独立集合（连通分量）的数量
//
// public:
//     /**
//      * @brief 构造函数
//      * @param size 要管理的元素的总数 (将创建从 0 到 size-1 的元素)。
//      */
//     explicit MyDisjointSet(size_t size) {
//         _count = size;
//         _parent.resize(size);
//         _rank.resize(size);
//         for (size_t i = 0; i < size; ++i) {
//             _parent[i] = i; // 初始时，每个元素都是自己的根
//             _rank[i] = 0;   // 初始时，每个集合的秩都为 0
//         }
//     }
//
//     /**
//      * @brief 查找元素 p 所在集合的代表元（根节点）。
//      * @param p 要查找的元素 (必须在 [0, size-1] 范围内)。
//      * @return 元素 p 的根节点索引。
//      * @details 此实现包含了“路径压缩”优化。
//      */
//     size_t find(size_t p) {
//         // 1. 边界检查
//         if (p >= _parent.size()) {
//             throw std::out_of_range("DisjointSet::find - Index out of bounds.");
//         }
//
//         // 2. 递归查找根节点
//         // 如果 p 不是根节点 (它的父节点不是它自己)
//         if (_parent[p] != p) {
//             // 递归地调用 find 找到最终的根，并在这个过程中
//             // 将 p 的父节点直接指向根，这就是“路径压缩”。
//             _parent[p] = find(_parent[p]);
//         }
//
//         // 3. 返回根节点
//         return _parent[p];
//     }
//
//     /**
//      * @brief 合并元素 p 和元素 q 所在的两个集合。
//      * @param p 第一个元素。
//      * @param q 第二个元素。
//      * @details 此实现包含了“按秩合并”优化。
//      */
//     void unite(size_t p, size_t q) {
//         // 1. 找到 p 和 q 的根节点
//         // find 方法内部已经处理了边界检查
//         size_t rootP = find(p);
//         size_t rootQ = find(q);
//
//         // 2. 如果根节点相同，说明它们已在同一个集合中，无需操作
//         if (rootP == rootQ) {
//             return;
//         }
//
//         // 3. 按秩合并：将秩小的树合并到秩大的树上
//         if (_rank[rootP] < _rank[rootQ]) {
//             // 将 p 所在的树（较矮）的根指向 q 所在的树（较高）的根
//             _parent[rootP] = rootQ;
//         }
//         else if (_rank[rootP] > _rank[rootQ]) {
//             // 反之，将 q 所在的树的根指向 p 所在的树的根
//             _parent[rootQ] = rootP;
//         }
//         else {
//             // 如果两个树的秩相等，任选一个作为新根，并将新根的秩加 1
//             _parent[rootQ] = rootP;
//             _rank[rootP]++;
//         }
//
//         // 4. 合并后，独立集合的总数减 1
//         _count--;
//     }
//
//     /**
//      * @brief 检查两个元素 p 和 q 是否属于同一个集合。
//      * @return 如果它们连通则返回 true，否则返回 false。
//      */
//     bool connected(size_t p, size_t q) {
//         // 两个元素连通的充要条件是它们有共同的根节点
//         return find(p) == find(q);
//     }
//
//     /**
//      * @brief 返回当前独立集合的数量。
//      * @return 集合的数量。
//      */
//     size_t count() const {
//         return _count;
//     }
// };
//
// #endif // MY_DISJOINT_SET_H