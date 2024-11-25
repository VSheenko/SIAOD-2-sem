#ifndef CODE_BINARYSEARCHTREE_H
#define CODE_BINARYSEARCHTREE_H

#include <cstddef>
#include <string>
#include <iostream>
#include <iomanip>

class BinarySearchTree {
private:
    struct Node {
        std::string key;
        size_t link_to_record = 0;

        Node* p_parent = nullptr;
        Node* p_left = nullptr;
        Node* p_right = nullptr;

        explicit Node(std::string s, size_t ind, Node* parent) : key(std::move(s)),
                                                                 link_to_record(ind),
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

    void PrintHelper(Node* node, const std::string& prefix, bool isLeft, bool isRoot = false);
    Node* FindMin(Node* node);
public:
    BinarySearchTree() = default;
    ~BinarySearchTree();

    void Insert(const std::string& key, size_t linkToRecord);
    bool Find(const std::string& key, size_t& found_ind) const;
    void Remove(const std::string& key);
    void PrintTree();
};


#endif //CODE_BINARYSEARCHTREE_H
