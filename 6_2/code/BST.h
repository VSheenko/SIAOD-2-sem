#ifndef CODE_BST_H
#define CODE_BST_H

#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

class BST {
private:
    struct Node {
        std::string s_key;
        unsigned short digit_count;

        short balance = 0;
        Node* p_left = nullptr;
        Node* p_right = nullptr;
    };

    Node* p_root = nullptr;
    unsigned short CountDigit(const std::string& str);
    void PrintTreeHelper(Node* node, const std::string& prefix, bool isLeft, bool isRoot = false);

    void CopyNode(Node* p_new_node, Node* p_cur_node);

public:
    BST() = default;
    ~BST();

    void InsertElem(const std::string& str);
    void InitTree(const std::vector<std::string>& elems);
    void PrintTree();

    int SpecCount(int num);
    bool IsDegenerate();
    void CopyTree(BST& new_tree);
};
















#endif //CODE_BST_H