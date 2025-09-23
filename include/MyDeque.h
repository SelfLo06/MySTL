#ifndef MYDEQUE_H
#define MYDEQUE_H

#include <cstddef> // For size_t

template<typename T>
class MyDeque {
public:
    // --- Typedefs ---
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;

    // --- Iterator ---
    // 迭代器是 MyDeque 的核心部分，它需要知道如何在不同的数据块之间跳转
    struct iterator {
        T *_current; // 指向当前元素
        T *_first; // 指向当前数据块的头部
        T *_last; // 指向当前数据块的尾部 (最后一个元素的下一个位置)
        T **_map_node; // 指向中控数组中，管理着当前数据块的那个指针

        // 后续我们将在这里实现迭代器的各种操作 (++, --, *, ->, ==, !=)
        void set_new_node(T **new_map_node);
    };


    MyDeque();
    ~MyDeque();

    // --- Public Interface ---
    // 后续我们将在这里实现 push_back, push_front, pop_back, pop_front, operator[] 等函数

    void push_back(const T &value);
    void push_front(const T &value);

    void pop_back();
    void pop_front();

    T& front();
    const T& front() const; // const 版本
    T& back();
    const T& back() const;  // const 版本

    T&operator[](size_type index);

    size_t size() const;
    bool empty() const;

private:
    // --- Member Variables ---
    T **_map; // 中控数组（“动车组的编组图”）
    size_t _map_size; // 中控数组的大小
    static const size_t BLOCK_SIZE = 8;

    iterator _start; // 指向第一个元素的迭代器（“第一位乘客”）
    iterator _finish; // 指向最后一个元素下一个位置的迭代器（“最后一个空位”）

    void _reallocate_map();
};

// 在 MyDeque.h 文件中，MyDeque 类的 } 之后

template<typename T>
MyDeque<T>::MyDeque() {
    _map_size = 16;
    _map = new T *[_map_size]; // T**
    for (size_t i = 0; i < _map_size; ++i) { _map[i] = nullptr; }

    size_t initial_node_index = _map_size / 2;
    _map[initial_node_index] = new T[8]; // T*

    _start._map_node = &_map[initial_node_index]; // T**
    _start._current = _map[initial_node_index] + 4; // T*
    _start._first = _map[initial_node_index]; // T*
    _start._last = _map[initial_node_index] + 8; // T*

    _finish._map_node = &_map[initial_node_index]; // T**
    _finish._current = _map[initial_node_index] + 4; // T*
    _finish._first = _map[initial_node_index]; // T*
    _finish._last = _map[initial_node_index] + 8; // T*
}

template <typename T>
MyDeque<T>::~MyDeque() {
    // 检查 _map 是否为空指针，以防万一（比如对象被移动后）
    if (_map) {
        // 步骤1: 销毁所有被分配了的数据块
        // 遍历范围是从第一个被使用的map节点到最后一个被使用的map节点
        for (T** node = _start._map_node; node <= _finish._map_node; ++node) {
            // *node 的类型是 T*，它指向一个数据块
            // 我们使用 delete[] 来销毁这个数据块数组
            delete[] *node;
        }

        // 步骤2: 销毁中控数组本身
        // _map 是通过 new T*[] 创建的，所以用 delete[]
        delete[] _map;
    }
}

template<typename T>
//当你告诉迭代器一个新的 _map_node 位置时，它负责更新自己的 _first, _last, 和 _current 指针到新“车厢”的正确位置。
void MyDeque<T>::iterator::set_new_node(T **new_map_node) {
    _map_node = new_map_node;
    _first = *new_map_node;
    _last = _first + BLOCK_SIZE;
    _current = _first;
}


template <typename T>
void MyDeque<T>::push_back(const T& value) {
    // 步骤1: 在当前 _finish 位置的 "座位" 上放入数据
    // 我们需要先为这个位置构造对象，而不是直接赋值，使用 placement new
    new (_finish._current) T(value);

    // 步骤2: 将 _finish 迭代器移动到下一个位置
    ++_finish._current;

    // 步骤3: 检查 _finish 是否走到了当前 "车厢" 的尽头
    // [start, finish)
    if (_finish._current == _finish._last) {
        // --- 换车厢逻辑 ---
        // 在尝试访问 _map_node + 1 之前，必须先检查 map 空间是否足够
        if (_finish._map_node == _map + _map_size - 1) { // 轨道到头了
            _reallocate_map();
        }
        // 1. 检查下一节 "车厢" 是否已经存在。
        //    *(_finish._map_node + 1) 就是下一节车厢的 T* 指针
        if (*(_finish._map_node + 1) == nullptr) {
            // 如果不存在，就 new 一个新的数据块（车厢）并挂接上去
            *(_finish._map_node + 1) = new T[BLOCK_SIZE];
        }

        // 2. 调用辅助函数，让 _finish 跳转到下一节车厢的开头
        _finish.set_new_node(_finish._map_node + 1);
    }
}

template <typename T>
// [start, finish)
void MyDeque<T>::push_front(const T& value) {
    // 检查是否需要在头部换车厢
    // 如果 _start 的当前位置就是块的开头
    if (_start._current == _start._first) {
        // --- 换车厢逻辑 ---
        // 在尝试访问 _map_node - 1 之前，必须先检查 map 空间是否足够
        if (_start._map_node == _map) { // 轨道到头了
            _reallocate_map();
        }

        if (*(_start._map_node - 1) == nullptr) {
            *(_start._map_node - 1) = new T[BLOCK_SIZE];
        }
        _start.set_new_node(_start._map_node - 1);
        // 跳转后，将 _start 定位到新块的末尾
        _start._current = _start._last;
    }

    // 将 _start 向前移动一格，指向要插入的空位
    --_start._current;

    // 在这个空位上构造新对象
    new (_start._current) T(value);
}

template <typename T>
// [first, last)
void MyDeque<T>::pop_back() {
    if (empty()) { return; }

    if (_finish._current == _finish._first) {
        // 边界情况
        // 只需要处理换车厢，不需要扩容
        // 我们也不释放内存块，以提高效率
        _finish.set_new_node(_finish._map_node - 1);
        _finish._current = _finish._last;
    }

    // _finish.current 一定无元素，但他的前一个一定有元素
    --_finish._current;
    _finish._current->~T();
}

template<typename T>
// [first, last)
void MyDeque<T>::pop_front() {
    if (empty()) { return; }

    // _start._current 一定有元素
    _start._current->~T();
    ++_start._current;

    if (_start._current == _start._last) {
        // 边界情况
        // 只需要处理换车厢，不需要扩容
        // 我们也不释放内存块
        _start.set_new_node(_start._map_node + 1);
    }
}

template<typename T>
T& MyDeque<T>::front() {
    return *_start._current;
}

template<typename T>
const T& MyDeque<T>::front() const {
    return *_start._current;
}

template<typename T>
T& MyDeque<T>::back() {
    // 最后一个元素总是在 _finish 的前一个位置
    iterator temp = _finish;
    --temp._current;
    // 如果回退导致需要换车厢...
    if (temp._current < temp._first) {
        // 跳转到上一个块的末尾
        temp.set_new_node(temp._map_node - 1);
        temp._current = temp._last - 1;
    }
    return *temp._current;
}

template<typename T>
const T& MyDeque<T>::back() const {
    iterator temp = _finish;
    --temp._current;
    if (temp._current < temp._first) {
        temp.set_new_node(temp._map_node - 1);
        temp._current = temp._last - 1;
    }
    return *temp._current;
}

template<typename T>
T& MyDeque<T>::operator[](size_type index) {
    // 1. 计算 _start 在其块内的偏移
    const size_type start_offset_in_block = _start._current - _start._first;

    // 2. 计算目标元素相对于 _start 所在块头部的总偏移, 补全前面方便计算
    const size_type total_offset = start_offset_in_block + index;

    // 3. 计算目标元素在 map 中的节点索引 和 在块内的索引
    const size_type target_map_node_offset = total_offset / BLOCK_SIZE;
    const size_type target_block_offset = total_offset % BLOCK_SIZE ;

    // 4. 获取目标 map 节点 和 目标数据块
    T** target_map_node = _start._map_node + target_map_node_offset;
    T* target_block = *target_map_node;

    // 5. 返回目标元素的引用
    return target_block[target_block_offset];
}

template<typename T>
bool MyDeque<T>::empty() const {
    return _start._current == _finish._current;
}


template <typename T>
typename MyDeque<T>::size_type MyDeque<T>::size() const {
    // Case 1: 如果 _start 和 _finish 在同一个数据块中
    if (_start._map_node == _finish._map_node) {
        // 大小就是两个指针的直接距离
        return _finish._current - _start._current;
    }
    // Case 2: 如果 _start 和 _finish 跨越了多个数据块
    else {
        // _map_node 的类型是 T**，它们之间的距离可以直接相减
        // 1. 计算中间有多少个 "完整" 的数据块
        size_type num_full_blocks = (_finish._map_node - _start._map_node) - 1;

        // 2. 计算 _start 所在 "头部" 数据块中的元素数量
        size_type num_start_elements = _start._last - _start._current;

        // 3. 计算 _finish 所在 "尾部" 数据块中的元素数量
        size_type num_finish_elements = _finish._current - _finish._first;

        // 4. 总数 = 头部块元素 + 中间满块元素 + 尾部块元素
        return num_start_elements + (num_full_blocks * BLOCK_SIZE) + num_finish_elements;
    }
}

template <typename T>
void MyDeque<T>::_reallocate_map() {
    // 步骤1: 创建一个通常是两倍大的新 map，并初始化为空
    const size_type old_num_nodes = _finish._map_node - _start._map_node + 1;
    const size_type new_map_size = _map_size + std::max(_map_size, old_num_nodes) + 2;
    T** new_map = new T*[new_map_size];
    for (size_type i = 0; i < new_map_size; ++i) {
        new_map[i] = nullptr;
    }

    // 步骤2: 计算旧内容在新 map 中的拷贝位置 (居中)
    T** new_start_node = new_map + (new_map_size - old_num_nodes) / 2;

    // 步骤3: 执行拷贝
    T** old_node = _start._map_node;
    T** new_node = new_start_node;
    for (size_type i = 0; i < old_num_nodes; ++i) {
        *new_node = *old_node;
        ++new_node;
        ++old_node;
    }

    // 步骤4:  更新 _start 和 _finish 的 _map_node 指针
    // 计算 _finish 相对于 _start 的偏移量
    size_type finish_offset = _finish._map_node - _start._map_node;

    // 更新 _start 和 _finish 的 map_node 以指向新 map 中的位置
    _start._map_node = new_start_node;
    _finish._map_node = new_start_node + finish_offset;

    // 步骤5: 释放旧 map 并更新成员变量
    delete[] _map;
    _map = new_map;
    _map_size = new_map_size;
}

#endif
