#pragma once
#include "Tree.h"
using namespace std;
template <typename T>
class AVLNode {
public:
    T key;
    AVLNode<T>* left;
    AVLNode<T>* right;
    int height; //высота

    AVLNode(T value) : key(value), left(nullptr), right(nullptr), height(1) {}
};


template <typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    void fill(Node<T>* node);
    int height(AVLNode<T>* node);
    int balanceFactor(AVLNode<T>* node);
    AVLNode<T>* rightRotate(AVLNode<T>* p);
    AVLNode<T>* leftRotate(AVLNode<T>* q);
    AVLNode<T>* balance(AVLNode<T>* node, T key);
    AVLNode<T>* insert(AVLNode<T>* node, T key);
    AVLNode<T>* removemin(AVLNode<T>* p);
    AVLNode<T>* minValueNode(AVLNode<T>* node);
    AVLNode<T>* deleteNode(AVLNode<T>* node, T key);
    AVLNode<T>* search(AVLNode<T>* node, T key);
    void LCR(AVLNode<T>* node);
    void CLR(AVLNode<T>* node);
    void LRC(AVLNode<T>* node);
    void breadth(AVLNode<T>* root);

public:
    AVLTree() : root(nullptr) {}
    AVLTree(BinaryTree<T> tree);
    T insert(T key);
    void LCR();
    void CLR();
    void LRC();
    void breadth();
    T removemin();
    T deleteNode(T key);
    AVLNode<T>* search(T key);
};


template <typename T>
void AVLTree<T>::fill(Node<T>* node) {
    if (node == nullptr)
        return;
    root = insert(root, node->data);//ц-л-п
    fill(node->left);
    fill(node->right);
}


template <typename T>
int AVLTree<T>::height(AVLNode<T>* node) { //просто вернуть высоту
    if (node == nullptr)
        return 0;
    return node->height;
}



template <typename T>
int AVLTree<T>::balanceFactor(AVLNode<T>* node) {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);//вычисление баланс фактора
}




template <typename T>
AVLNode<T>* AVLTree<T>::rightRotate(AVLNode<T>* p) {
    AVLNode<T>* q = p->left;
    p->left = q->right;
    q->right = p;
    //

    p->height = max(height(p->left), height(p->right)) + 1;
    q->height = max(height(q->left), height(q->right)) + 1;

    return q;
}


template <typename T>
AVLNode<T>* AVLTree<T>::leftRotate(AVLNode<T>* q) {
    AVLNode<T>* p = q->right;
    q->right = p->left;
    p->left = q;

    q->height = max(height(q->left), height(q->right)) + 1;
    p->height = max(height(p->left), height(p->right)) + 1;

    return p;
}


template <typename T>
AVLNode<T>* AVLTree<T>::balance(AVLNode<T>* node, T key) {
    int balance_factor = balanceFactor(node);

    // Правый поворот
    if (balance_factor > 1 && key < node->left->key) {
        return rightRotate(node);
    }


    // Левый поворот
    if (balance_factor < -1 && key > node->right->key)
        return leftRotate(node);

    // ЛП поворот
    if (balance_factor > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // ПЛ поворот
    if (balance_factor < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

template <typename T>
AVLNode<T>* AVLTree<T>::insert(AVLNode<T>* node, T key) {
    if (node == nullptr)
        return new AVLNode<T>(key);

    if (key < node->key) //если ключ меньше ключа корня то втсавляем влево
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);// если больше то вправо
    else
        return node; // ключ уже существует

    node->height = 1 + max(height(node->left), height(node->right));
    return balance(node, key);
}



template <typename T>
AVLNode<T>* AVLTree<T>::removemin(AVLNode<T>* p) // удаление узла с минимальным ключом из дерева 
{
    if (p->left == 0)
        return p->right;
    p->left = removemin(p->left);
    return balance(p, p->key);
}

template <typename T>
AVLNode<T>* AVLTree<T>::minValueNode(AVLNode<T>* node) {
    AVLNode<T>* current = node;

    while (current->left != nullptr) {
        current = current->left;
    }

    return current;
}

template <typename T>
AVLNode<T>* AVLTree<T>::deleteNode(AVLNode<T>* node, T key) {
    if (node == nullptr) {
        return node;
    }

    if (key < node->key) {
        node->left = deleteNode(node->left, key);
    }
    else if (key > node->key) {
        node->right = deleteNode(node->right, key);
    }
    else {
        if ((node->left == nullptr) || (node->right == nullptr)) {
            AVLNode<T>* temp = (node->left != nullptr) ? node->left : node->right;

            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            }
            else {
                *node = *temp;
            }

            delete temp;
        }
        else {
            AVLNode<T>* temp = minValueNode(node->right);

            node->key = temp->key;
            node->right = deleteNode(node->right, temp->key);
        }
    }

    if (node == nullptr) {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    return balance(node, key);
}

template <typename T>
AVLNode<T>* AVLTree<T>::search(AVLNode<T>* node, T key) { //поиск
    if (node == nullptr || node->key == key) {
        return node;
    }
    if (key < node->key) {
        return search(node->left, key);
    }
    else {
        return search(node->right, key);//возвращает узел
    }
}

template <typename T>
void AVLTree<T>::LCR(AVLNode<T>* node) {
    if (node != nullptr) {
        LCR(node->left);
        cout << node->key << " ";
        LCR(node->right);
    }
}

template <typename T>
void AVLTree<T>::CLR(AVLNode<T>* node) {
    if (node != nullptr) {
        cout << node->key << " ";
        CLR(node->left);
        CLR(node->right);
    }
}

template <typename T>
void AVLTree<T>::LRC(AVLNode<T>* node) {
    if (node != nullptr) {
        LRC(node->left);
        LRC(node->right);
        cout << node->key << " ";

    }
}

template <typename T>
void AVLTree<T>::breadth(AVLNode<T>* root) {
    if (root == nullptr)
        return;

    queue<AVLNode<T>*> q;
    q.push(root);

    while (!q.empty()) {
        AVLNode<T>* current = q.front();
        q.pop();

        std::cout << current->key << " ";

        if (current->left)
            q.push(current->left);

        if (current->right)
            q.push(current->right);

    }
}
template <typename T>
AVLTree<T>::AVLTree(BinaryTree<T> tree) {
    fill(tree.getRoot());
}
template <typename T>
T AVLTree<T>::insert(T key) {
    root = insert(root, key);
    return key;
}

template <typename T>
void AVLTree<T>::LCR() {
    LCR(root);
    cout << endl;
}

template <typename T>
void AVLTree<T>::CLR() {
    CLR(root);
    cout << endl;
}

template <typename T>
void AVLTree<T>::LRC() {
    LRC(root);
    cout << endl;
}

template <typename T>
void AVLTree<T>::breadth() {
    breadth(root);
    cout << endl;
}

template <typename T>
T AVLTree<T>::removemin() {
    return removemin(root)->key;
}

template <typename T>
T AVLTree<T>::deleteNode(T key) {
    root = deleteNode(root, key);
    return key;
}

template <typename T>
AVLNode<T>* AVLTree<T>::search(T key) {
    return search(root, key);
}
