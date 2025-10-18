#include <random>
#include <iostream>
#include <functional>

template <typename T>
struct TreapNode {
    T key;
    int priority; // 新增！用于维护堆的性质
    int size;
    TreapNode* left;
    TreapNode* right;

    TreapNode(const T& k) : key(k), size(1),left(nullptr), right(nullptr) {
        // 优先级必须是随机的！
        // C++11 之后的标准方法
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(1, 10000); // 范围可以自定义
        priority = distrib(gen);
    }
};

template <typename T>
class MyTreap {
private:
    TreapNode<T>* _root;


    // 核心辅助函数
    TreapNode<T>* _insert(TreapNode<T>* node, const T& key);
    TreapNode<T>* _remove(TreapNode<T>* node, const T& key);
    bool _find(TreapNode<T>* node, const T& key) const;

    void _destroy_tree(TreapNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        _destroy_tree(node->left);
        _destroy_tree(node->right);
        delete node;
    }

    TreapNode<T>* _copy_tree(const TreapNode<T>* other_node) {
        if (other_node == nullptr) {
            return nullptr;
        }

        // 1. 复制当前节点
        TreapNode<T>* new_node = new TreapNode<T>(other_node->key);
        new_node->priority = other_node->priority; // 复制优先级！
        new_node->size = other_node->size;         // 复制 size！

        // 2. 递归地复制左右子树
        new_node->left = _copy_tree(other_node->left);
        new_node->right = _copy_tree(other_node->right);

        return new_node;
    }

    // Treap 的灵魂：旋转操作
    TreapNode<T>* _leftRotate(TreapNode<T>* x);
    TreapNode<T>* _rightRotate(TreapNode<T>* y);

    // 递归地对以 node 为根的子树进行中序遍历
    void _inorder(TreapNode<T>* node, const std::function<void(const T&)>& visit) const {
        if (node == nullptr) {
            return;
        }
        // 1. 递归遍历左子树
        _inorder(node->left, visit);

        // 2. 访问当前节点
        visit(node->key);

        // 3. 递归遍历右子树
        _inorder(node->right, visit);
    }

    T* _find_value(TreapNode<T>* node, const T& value) const;

public:
    MyTreap() : _root(nullptr) {}
    MyTreap(const MyTreap& other) {
        _root = _copy_tree(other._root);
    }
    MyTreap& operator=(const MyTreap& other) {
        // 1. 处理自我赋值 (e.g., treap = treap;)
        if (this != &other) {
            // a. 清理自己现有的资源
            _destroy_tree(_root);

            // b. 从 other 深拷贝一份新的资源
            _root = _copy_tree(other._root);
        }
        // 2. 返回对自身的引用
        return *this;
    }
    ~MyTreap() {
        _destroy_tree(_root);
    }

    void insert(const T& key) {
        _root = _insert(_root, key);
    }

    void remove(const T& key) {
        _root = _remove(_root, key);
    }

    bool find(const T& key) const {
        return _find(_root, key);
    }

    size_t size() const {
        return  _root ? _root->size : 0;
    }

    void inorder(const std::function<void(const T&)>& visit) const {
        _inorder(_root, visit);
    }

    void clear() {
        _destroy_tree(_root);
        _root = nullptr;
    }

    bool empty() const {return _root == nullptr;}

    T* find_value(const T& value) const {
        return _find_value(_root, value);
    }
};

template <typename T>
bool MyTreap<T>::_find(TreapNode<T> *node, const T &key) const {
    if (node == nullptr) return false;

    if (node->key == key) {
        return true;
    }

    if (node->key > key) {
        return _find(node->left,key);
    }
    else return _find(node->right, key);
}


// 对节点 x 进行左旋，返回旋转后的新根节点 y
template <typename T>
TreapNode<T>* MyTreap<T>::_leftRotate(TreapNode<T>* x) {
    TreapNode<T>* y = x->right;      // 1. y 是 x 的右孩子
    TreapNode<T>* T2 = y->left;      // 2. T2 是 y 的左孩子

    // 3. 开始旋转
    y->left = x;                     //    y 的左边挂上 x
    x->right = T2;                   //    x 的右边挂上 T2

    // 更新 size
    x->size = 1 + (x->left ? x->left->size : 0) + (x->right ? x->right->size : 0);
    y->size = 1 + (y->left ? y->left->size : 0) + (y->right ? y->right->size : 0);

    // 4. 返回新的子树根节点
    return y;
}

// 对节点 y 进行右旋，返回旋转后的新根节点 x
template<typename T>
TreapNode<T> *MyTreap<T>::_rightRotate(TreapNode<T> *y) {
    TreapNode<T>* x = y->left;
    TreapNode<T>* T2 = x->right;

    x->right = y;
    y->left = T2;

    // 更新 size
    y->size = 1 + (y->left ? y->left->size : 0) + (y->right ? y->right->size : 0);
    x->size = 1 + (x->left ? x->left->size : 0) + (x->right ? x->right->size : 0);

    return x;
}

template<typename T>
TreapNode<T> *MyTreap<T>::_insert(TreapNode<T> *node, const T &key) {
    if (node == nullptr) {
        return new TreapNode<T>(key);
    }


    // 大体还是 BST 的插入
    if (key < node->key) {
        node->left =  _insert(node->left, key);
        if (node->left->priority < node->priority) {
            // 左孩子“太轻了”，需要把它提上来。对 node 进行一次右旋转
            node = _rightRotate(node);
        }
    }
    else if (key > node->key) {
        node->right = _insert(node->right, key);
        if (node->right->priority < node->priority) {
            // 右孩子“太轻了”，需要把它提上来。对 node 进行一次左旋转
            node = _leftRotate(node);
        }
    }
    // 键已存在，什么都不做，直接返回原节点

    // 更新 size
    node->size = 1 + (node->left ? node->left->size : 0) + (node->right ? node->right->size : 0);

    return node;
}

template<typename T>
TreapNode<T> *MyTreap<T>::_remove(TreapNode<T> *node, const T &key) {
    if (node == nullptr) return nullptr;

    if (key < node->key) {
        node->left = _remove(node->left, key);
    }
    else if (key > node->key) {
        node->right = _remove(node->right, key);
    }
    else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        if (node->left != nullptr && node->right == nullptr) {
            TreapNode<T>* temp = node->left;
            delete node;
            return temp;
        }
        if (node->left == nullptr && node->right != nullptr) {
            TreapNode<T>* temp = node->right;
            delete node;
            return temp;
        }
        else {
            // Base Case: 如果是叶子节点，直接删除
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            // 如果应该左旋 (把右孩子提上来)
            // 条件：1. 没有左孩子, 2. 或者右孩子的优先级更小
            if (node->left == nullptr || (node->right != nullptr && node->right->priority < node->left->priority)) {
                node = _leftRotate(node);
                node->left = _remove(node->left, key);
            }
            // 否则，就右旋 (把左孩子提上来)
            else {
                node = _rightRotate(node);
                node->right = _remove(node->right, key);
            }
        }
    }

    // 更新 size
    node->size = 1 + (node->left ? node->left->size : 0) + (node->right ? node->right->size : 0);

    return node;
}

template<typename T>
T *MyTreap<T>::_find_value(TreapNode<T> *node, const T &value) const {
    if (node == nullptr) {
        return nullptr;
    }

    if (value < node->key) {
        return _find_value(node->left, value);
    }
    else if (value > node->key) {
        return _find_value(node->right, value);
    }
    else {
        return &(node->key);
    }
}


