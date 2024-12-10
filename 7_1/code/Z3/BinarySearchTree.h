#ifndef CODE_BINARYSEARCHTREE_H
#define CODE_BINARYSEARCHTREE_H

#include <cstddef>
#include <string>
#include <iostream>
#include <iomanip>

class BinarySearchTree {
private:
    struct Node {
        int key;
        size_t link_to_record = 0;

        Node* p_parent = nullptr;
        Node* p_left = nullptr;
        Node* p_right = nullptr;

        explicit Node(int s, Node* parent) : key(s),
                                             p_parent(parent) {};

        ~Node() {
            if (!p_left) {
                delete p_left;
                p_left = nullptr;
            }

            if (!p_right) {
                delete p_right;
                p_right = nullptr;
            }

        }
    };

    Node* p_root = nullptr;
public:
    BinarySearchTree() = default;
    ~BinarySearchTree();


    size_t MemoryUsage();
    void Insert(int key);
    int Find(int key) const;
};


#endif //CODE_BINARYSEARCHTREE_H
