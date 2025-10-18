#ifndef MYBST_H
#define MYBST_H

#include <iostream>
#include <functional>

template <typename T>
class MyBST {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        size_t size;

        Node(const T& value)
            : data(value), left(nullptr), right(nullptr), size(1){}
    };

/*
 * 对于树中的任意一个节点：
    它所有左子树的节点值，都小于该节点的值。
    它所有右子树的节点值，都大于该节点的值。
 */

    Node* _root; // 一棵树，只需要一个根节点就够了

    void _destroy_tree(Node* node);// 私有辅助函数：递归地释放树的内存
    Node* _copy_tree(Node* other_node) const;// 速度拷贝函数

    Node* _insert(Node* node, const T& value);

    bool _find(Node* node, const T& value) const;

    // 三种遍历方法
    void _inorder(Node* node, std::function<void(const T&)> func) const;
    void _preorder(Node* node, std::function<void(const T&)> func) const;
    void _postorder(Node* node, std::function<void(const T&)> func) const;

    // 找到第一个不小于/严格大于 value 的值
    Node* _lower_bound(Node* node, const T& value) const;
    Node* _upper_bound(Node* node, const T& value) const;

    Node* _remove(Node* node, const T& value);
    Node* _find_min(Node* node) const;

    // 递归查找size，虽然复杂度为O(n)，但容易维护，
    /* 这是单纯二叉搜索树的缺陷，即删除和更新size的操作没办法同步，只有下一个函数才知道有没有成功删除
     * STL中使用的是红黑树
     * 在 STL 的实现中，节点的内存分配 (new Node) 和释放 (delete Node) 通常由一个叫做分配器 (Allocator) 的模板参数来管理。
     * insert 和 erase 等操作被设计得非常精细。它们的核心逻辑（查找、链接指针、旋转等）与节点的物理删除是分开的。
     * erase 函数在找到要删除的节点后，会执行一系列指针操作（可能包括树旋转）来“解除”这个节点的链接，然后才会调用分配器去释放该节点的内存
    * 正因为“解除链接”和“释放内存”是分开的，计数逻辑就变得非常简单。
    * insert 操作: 当且仅当分配器真的创建了一个新节点时，_size 才会 ++。
    * erase 操作: 当且仅当一个节点真的被解除链接并准备释放时，_size 才会 --。
    * 在双子节点的情况下，红黑树的 erase 逻辑会找到中序后继，用后继节点的数据覆盖要删除的节点（或者直接交换节点），
    * 然后真正被解除链接并删除的是那个后继节点。由于每个节点只会被删除一次，所以 _size-- 也只会被执行一次
    */
    // size_t _size(Node* node) const;

public:
    MyBST() : _root(nullptr) {}
    MyBST(const MyBST& other); // 拷贝函数
    MyBST<T>& operator=(const MyBST<T>& other);
    ~MyBST() {_destroy_tree(_root);}// 从根节点开始，递归地销毁整棵树

    void insert(const T& value);
    bool find(const T& value) const;

    // 三种遍历方法
    void inorder(std::function<void(const T&)> func) const;
    void preorder(std::function<void(const T&)> func) const;
    void postorder(std::function<void(const T&)> func) const;

    Node* lower_bound(const T& value) const;
    Node* upper_bound(const T& value) const;

    void remove(const T& value);
    void clear();

    size_t size() const;
    bool empty() const;

    T* find_value(const T& value_to_find) const;
};

template <typename T>
void MyBST<T>::_destroy_tree(Node* node) {
    if (node == nullptr) {
        return; // Base case: 如果节点为空，什么都不做
    }

    // 后序遍历 (Post-order Traversal) 删除左右子树
    _destroy_tree(node->left);
    _destroy_tree(node->right);

    //std::cout << "Deleting node: " << node->data << std::endl; // 方便调试
    delete node;
}

template<typename T>
typename MyBST<T>::Node *MyBST<T>::_copy_tree(Node *other_node) const {
    if (other_node == nullptr) {
        return nullptr;
    }

    Node* newNode = new Node(other_node->data);
    newNode->data = other_node->data;
    newNode->left = _copy_tree(other_node->left);
    newNode->right = _copy_tree(other_node->right);
    newNode->size = other_node->size;

    return newNode;
}

template<typename T>
MyBST<T>::MyBST(const MyBST &other) {
    _root = _copy_tree(other._root);
}

template<typename T>
MyBST<T> &MyBST<T>::operator=(const MyBST<T> &other) {
    if (this == &other) return *this;
    _destroy_tree(_root);
    _root = _copy_tree(other._root);
    return *this;
}


template <typename T> // 时间复杂度为 O(h), h为树的高度
typename MyBST<T>::Node* MyBST<T>::_insert(Node* node, const T& value) {
    // 1. 基本情况：找到了插入位置 (当前节点为空)
    if (node == nullptr) {
        // 创建一个新节点并返回它的地址
        return new Node(value);
    }

    // 2. 递归步骤
    if (value < node->data) {
        // 去左子树继续寻找
        node->left = _insert(node->left,value);
    } else if (value > node->data) {
        // 去右子树继续寻找
        node->right = _insert(node->right,value);
    }
    // 如果 value == node->data，我们什么都不做，直接返回原节点

    // 更新 size
    node->size = 1 + (node->left ? node->left->size : 0) + (node->right ? node->right->size : 0);

    // 3. 返回当前节点（可能它的 left 或 right 已经被更新）
    // 实际是树的更新
    return node;
}


template <typename T>
void MyBST<T>::insert(const T& value) {
    // 注意空树情况
    _root = _insert(_root,value);
}

template <typename T>
// 对于平衡的树，有 N / 2^ h = 1 (即分到最小就是1), 其高度大约为log(N), 则复杂度为 O(logN)
// 对于不平衡的树，最差情况为退化为一个链表，则高度为N, 复杂度为 O(N)
bool MyBST<T>::_find(Node *node, const T &value) const {
    if (node == nullptr) {// 1. 基本情况1：没找到 (当前节点为空)
        return false;
    }

    if (value == node->data) {// 2. 基本情况2：找到了！
        return true;
    }

    // 3. 递归步骤
    if (value < node->data) {// 去左子树继续寻找
        return _find(node->left, value);
    }else {// 去右子树继续寻找
        return _find(node->right, value);
    }
}

template<typename T>
bool MyBST<T>::find(const T &value) const {
    return _find(_root, value);
}

template<typename T>
void MyBST<T>::_inorder(Node *node, std::function<void(const T &)> func) const {
    if (node == nullptr) return;

    // 遵循“左 -> 根 -> 右”的顺序
    // 1. 递归访问左子树
    _inorder(node->left, func);

    // 2. 访问根节点 (调用 func)
    func(node->data);

    // 3. 递归访问右子树
    _inorder(node->right, func);
}

template<typename T>
void MyBST<T>::_preorder(Node *node, std::function<void(const T &)> func) const {
    if (node == nullptr) return;

    // 遵循“根 -> 左 -> 右”的顺序
    // 1. 访问根节点 (调用 func)
    func(node->data);

    // 2. 递归访问左子树
    _preorder(node->left, func);

    // 3. 递归访问右子树
    _preorder(node->right, func);
}

template<typename T>
void MyBST<T>::_postorder(Node *node, std::function<void(const T &)> func) const {
    if (node == nullptr) return;

    // 遵循“左 -> 右 -> 根”的顺序
    // 1. 递归访问左子树
    _postorder(node->left, func);

    // 2. 递归访问右子树
    _postorder(node->right, func);

    // 3. 访问根节点 (调用 func)
    func(node->data);
}

template <typename T>
void MyBST<T>::inorder(std::function<void(const T&)> func) const {
    _inorder(_root, func);
}

template <typename T>
void MyBST<T>::preorder(std::function<void(const T&)> func) const {
    _preorder(_root, func);
}

template <typename T>
void MyBST<T>::postorder(std::function<void(const T&)> func) const {
    _postorder(_root, func);
}

template<typename T>
// 找到第一个不小于 value 的值
typename MyBST<T>::Node *MyBST<T>::_lower_bound(Node *node, const T &value) const {
    if (node == nullptr) {
        return nullptr;
    }

    if (!(node->data < value)) {
        Node* left_result = _lower_bound(node->left, value);
        if (left_result != nullptr) {
            return left_result;
        }
        else return node;
    }
    else {
        return _lower_bound(node->right, value);
    }
}

template<typename T>
// 找到第一个不小于 value 的值
typename MyBST<T>::Node *MyBST<T>::lower_bound(const T &value) const {
    return _lower_bound(_root,value);
}

template<typename T>
// 找到第一个严格大于 value 的值
typename MyBST<T>::Node *MyBST<T>::_upper_bound(Node *node, const T &value) const {
    if (node == nullptr) {
        return nullptr;
    }

    if (value < node->data) {
        Node* left_result = _upper_bound(node->left, value);
        if (left_result != nullptr) {
            return left_result;
        }
        else return node;
    }
    else return _upper_bound(node->right, value);
}

template<typename T>
// 找到第一个严格大于 value 的值
typename MyBST<T>::Node *MyBST<T>::upper_bound(const T &value) const {
    return _upper_bound(_root, value);
}

template<typename T>
typename MyBST<T>::Node *MyBST<T>::_find_min(Node *node) const {
    if (node == nullptr) return nullptr;
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

/*       50                     (1. 找到后继 S=60)
        /  \                    (2. 将S的数据拷贝过来)
      30   80
          /  \
        60   90
          \
           70

           |
           V

          60  <--- S(60)的数据被拷贝到D(50)的位置
         /  \
       30   80 <--- (3. 现在问题变成在右子树中删除60)
           /  \
          60   90
           \
            70

            |
            V (递归删除后，60被其子节点70替代)

           60
         /  \
       30   80
           /  \
         70   90
*/

template<typename T>
// _remove 函数应该返回经过删除操作后，这棵（子）树的新的根节点指针，用来维护整棵树。
typename MyBST<T>::Node *MyBST<T>::_remove(Node *node, const T &value) {
    if (node == nullptr) {
        return nullptr;
    }

    if (value < node->data) {
        node->left = _remove(node->left,value);
    }
    else if (value > node->data){
        node->right = _remove(node->right,value);
    }

    else{
        // 叶情况
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        // 有一棵子树的情况
        else if (node->left != nullptr && node->right == nullptr){
            Node* temp = node->left;
            delete node;
            return temp;
        }
        else if (node->left == nullptr && node->right != nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        // 有两棵子树的情况，需要找到中序后继，再递归删除
        else {
            Node* successor = _find_min(node->right);
            node->data = successor->data;
            node->right = _remove(node->right, successor->data);
        }
    }
    // 更新 size
    node->size = 1 + (node->left ? node->left->size : 0) + (node->right ? node->right->size : 0);

    return node;
}

template<typename T>
void MyBST<T>::remove(const T &value) {
    _root = _remove(_root, value);
}

template<typename T>
void MyBST<T>::clear() {
    _destroy_tree(_root);
    _root = nullptr;
}

// template<typename T>
// size_t MyBST<T>::_size(Node* node) const {
//     if (!node) return 0;
//     return 1 + _size(node->left) + _size(node->right);
// }

template<typename T>
size_t MyBST<T>::size() const {
    return _root ? _root->size : 0;
}

template<typename T>
bool MyBST<T>::empty() const {
    return _root == nullptr;
}

template<typename T>
T *MyBST<T>::find_value(const T &value_to_find) const {
    Node* node = lower_bound(value_to_find);
    // 如果找到了节点，并且节点的数据确实等于我们要找的
    // (因为 lower_bound 可能返回的是下一个更大的元素)
    if (node != nullptr && !(value_to_find < node->data) && !(node->data < value_to_find)) { // 等价于 value_to_find == node->data
        return &(node->data);
    }
    return nullptr;
}

#endif

