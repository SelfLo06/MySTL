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

        Node(const T& value)
            : data(value), left(nullptr), right(nullptr) {}
    };

/*
 * 对于树中的任意一个节点：
    它所有左子树的节点值，都小于该节点的值。
    它所有右子树的节点值，都大于该节点的值。
 */

    Node* _root; // 一棵树，只需要一个根节点就够了

    void _destroy_tree(Node* node);// 私有辅助函数：递归地释放树的内存
    Node* _insert(Node* node, const T& value);

    bool _find(Node* node, const T& value) const;

    // 三种遍历方法
    void _inorder(Node* node, std::function<void(const T&)> func) const;
    void _preorder(Node* node, std::function<void(const T&)> func) const;
    void _postorder(Node* node, std::function<void(const T&)> func) const;

public:
    MyBST() : _root(nullptr) {}
    ~MyBST() {_destroy_tree(_root);}// 从根节点开始，递归地销毁整棵树

    void insert(const T& value);
    bool find(const T& value) const;

    // 三种遍历方法
    void inorder(std::function<void(const T&)> func) const;
    void preorder(std::function<void(const T&)> func) const;
    void postorder(std::function<void(const T&)> func) const;
};

template <typename T>
void MyBST<T>::_destroy_tree(Node* node) {
    if (node == nullptr) {
        return; // Base case: 如果节点为空，什么都不做
    }

    // 后序遍历 (Post-order Traversal) 删除左右子树
    _destroy_tree(node->left);
    _destroy_tree(node->right);

    std::cout << "Deleting node: " << node->data << std::endl; // 方便调试
    delete node;
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

#endif

