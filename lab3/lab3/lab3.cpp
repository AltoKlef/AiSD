#include <iostream>
#include <fstream>
#include "AVL_Tree.h"
using namespace std;
int main() {
    string filePath = "test.txt";
    //string input = "(8 (3 (1) (6 (4) (7))) (10 (14 (13))))";
    string input;
    ifstream inputFile(filePath);
    if (!inputFile.is_open()) {
        cerr << "can't open the file: " << filePath << endl;
        return 1; 
    }
    getline(inputFile, input);

    cout << "Your input is: " << input<<endl;
    cout << "output : ";
    BinaryTree<int> test1(input);//тут  сначала создается 3 дерева с ошибками а потом нормальное, и уже оно конвертируется
    test1.recursiveTraversal();


    getline(inputFile, input);
    cout << "Your input is: " << input << endl;
    cout << "output : ";
    BinaryTree<int> test2(input);
    test2.recursiveTraversal();


    getline(inputFile, input);
    cout << "Your input is: " << input << endl;
    cout << "output : ";
    BinaryTree<int> test3(input);
    test3.recursiveTraversal();

    getline(inputFile, input);
    cout << "Your input is: " << input << endl;
    cout << "output : ";
    BinaryTree<int> test4(input);
    test4.recursiveTraversal();


    cout << endl << "converting to AVL...."<<endl;
    AVLTree<int> avlTree(test4);//создание авл дерева на основе обычного
    cout << "LCR traversal: ";
    avlTree.LCR();//лево-центр-право
    cout << "CLR traversal: ";
    avlTree.CLR();//центр-лево-право
    cout << "LRC traversal: ";
    avlTree.LRC();//лево-право-центр
    cout << "breadth traversal: ";
    avlTree.breadth();//обход по ширине

    /*avlTree.removemin();
    cout << endl<<"LCR traversal: ";
    avlTree.LCR();
    cout << "CLR traversal: ";
    avlTree.CLR();
    cout << "LRC traversal: ";
    avlTree.LRC();
    cout << "breadth traversal: ";
    avlTree.breadth();
    avlTree.deleteNode(4);
    cout << endl << "LCR traversal: ";
    avlTree.LCR();
    cout << "CLR traversal: ";
    avlTree.CLR();
    cout << "LRC traversal: ";
    avlTree.LRC();
    cout << "breadth traversal: ";
    avlTree.breadth();
    cout << endl << avlTree.search(8)->key;*/

    return 0;
}