#pragma once

#include <iostream>
#include <sstream>
#include <stack>
#include <queue>
//����
template<typename T>
class Node {
public:
    T data;
    Node* left;
    Node* right;

    Node(T value) : data(value), left(nullptr), right(nullptr) {}
};

template<typename T>
class BinaryTree {
private:
    Node<T>* root;

    void recursiveTraversal(Node<T>* node);

    Node<T>* parseTree(const std::string& expression);

    bool checkValidCharacters(const std::string& str);

    bool checkBrackets(const std::string& input) const;
    
public:
    BinaryTree(const std::string& input);
    Node<T>* getRoot();
    void recursiveTraversal();
};
template<typename T>
Node<T>* BinaryTree<T>::getRoot() {
    return root;
}
template<typename T>
void BinaryTree<T>::recursiveTraversal(Node<T>* node) {
    if (node == nullptr)
        return;
    std::cout << node->data << " ";//�-�-�
    recursiveTraversal(node->left);
    recursiveTraversal(node->right);
}

template<typename T>
Node<T>* BinaryTree<T>::parseTree(const std::string& expression) {
    std::stack<Node<T>*> nodeStack;
    Node<T>* root = nullptr;

    std::istringstream iss(expression); // ��� ��������� ��������

    char token;
    while (iss >> token) {
        if (isdigit(token)) {
            iss.unget();
            int value;
            iss >> value;
            Node<T>* newNode = new Node<T>(value);

            if (!nodeStack.empty()) {
                Node<T>* parent = nodeStack.top();
                if (parent->left==nullptr) {
                    parent->left = newNode;
                }
                else if (parent->right==nullptr) {
                    parent->right = newNode;
                }
                else {
                    std::cerr << "Non-binary tree" << std::endl;
                    return nullptr;//���� ������  � ����� ��� ��� ������ �� ��� ��� ��������� ������ � ���� ����
                    //������ ��� �� �������� ������
                }
            }
            else {
                root = newNode;
            }

            nodeStack.push(newNode);
        }
        else if (token == ')') {
            nodeStack.pop();
        }
    }

    return root;
}

template<typename T>
bool BinaryTree<T>::checkValidCharacters(const std::string& str) {
    char c;
    for (int i = 0; i < str.size(); i++) {
        c = str[i];
        if (!std::isdigit(c) && c != '.' && c != '(' && c != ')' && c != ' ') {
            return false; //���� ���� ����������� �������
        }
    }
    return true;
}

template<typename T>
bool BinaryTree<T>::checkBrackets(const std::string& input) const {
    std::stack<char> brackets;

    for (char c : input) {
        if (c == '(') {
            brackets.push(c);
        }
        else if (c == ')') {
            if (brackets.empty() || brackets.top() != '(') {
                return false; //� ������ ���� ������ ��������� �������� ����������
            }
            brackets.pop();
        }
    }

    return brackets.empty();
}

template<typename T>
BinaryTree<T>::BinaryTree(const std::string& input) {
    if (!checkValidCharacters(input)) {
        std::cerr << "Invalid symbol" << std::endl;
    }

    else if (!checkBrackets(input)) {
        std::cerr << "Incorrect bracket positions" << std::endl;
    }
    else {
        std::istringstream iss(input);
        root = parseTree(input);
    }
}

template<typename T>
void BinaryTree<T>::recursiveTraversal() {
    recursiveTraversal(root);
    std::cout << std::endl;
}
