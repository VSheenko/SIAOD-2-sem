#include "BinarySearchTree.h"

void BinarySearchTree::Insert(const std::string &key, size_t ind) {
    if (!p_root) {
        p_root = new Node(key, ind, nullptr);
        return;
    }

    Node* p_cur_node = p_root;
    Node* p_parent = p_cur_node;

    while (p_cur_node) {
        p_parent = p_cur_node;
        if (key < p_cur_node->key)
            p_cur_node = p_cur_node->p_left;
        else
            p_cur_node = p_cur_node->p_right;
    }


    if (key < p_parent->key)
        p_parent->p_left = new Node(key, ind, p_parent);
    else
        p_parent->p_right = new Node(key, ind, p_parent);
}


bool BinarySearchTree::Find(const std::string &key, size_t& found_ind) const {
    Node* p_cur_node = p_root;

    while (p_cur_node && p_cur_node->key != key) {
        if (key < p_cur_node->key)
            p_cur_node = p_cur_node->p_left;
        else
            p_cur_node = p_cur_node->p_right;
    }

    if (p_cur_node)
        found_ind = p_cur_node->link_to_record;

    return p_cur_node;
}

BinarySearchTree::Node *BinarySearchTree::FindMin(BinarySearchTree::Node *node) {
    while (node && node->p_left)
        node = node->p_left;

    return node;
}

void BinarySearchTree::Remove(const std::string &key) {
    Node* p_delete_node = p_root;

    if (p_root->key == key) {
        Node* p_min_node = FindMin(p_root->p_right);
        p_min_node->p_parent->p_left = nullptr;

        p_min_node->p_left = p_root->p_left;
        p_min_node->p_right = p_root->p_right;
        delete p_root;
        p_root = p_min_node;
        return;
    }

    while (p_delete_node && p_delete_node->key != key) {
        if (key < p_delete_node->key)
            p_delete_node = p_delete_node->p_left;
        else
            p_delete_node = p_delete_node->p_right;
    }

    if (!p_delete_node)
        return;

    if (!p_delete_node->p_left) {
        if (p_delete_node->p_parent->p_left == p_delete_node) {
            p_delete_node->p_parent->p_left = p_delete_node->p_right;
            p_delete_node->p_left->p_parent = p_delete_node->p_parent;
        } else {
            p_delete_node->p_parent->p_right = p_delete_node->p_right;
            p_delete_node->p_right->p_parent = p_delete_node->p_parent;
        }

        delete p_delete_node;
        return;
    }

    if (!p_delete_node->p_right) {
        if (p_delete_node->p_parent->p_left == p_delete_node) {
            p_delete_node->p_parent->p_left = p_delete_node->p_left;
            p_delete_node->p_left->p_parent = p_delete_node->p_parent;
        } else {
            p_delete_node->p_parent->p_right = p_delete_node->p_left;
            p_delete_node->p_left->p_parent = p_delete_node->p_parent;
        }

        delete p_delete_node;
        return;
    }

    Node* p_min_node = FindMin(p_delete_node->p_right);
    p_min_node->p_parent->p_left = nullptr;

    if (p_delete_node->p_parent->p_left == p_delete_node) {
        p_delete_node->p_parent->p_left = p_min_node;
    } else {
        p_delete_node->p_parent->p_right = p_min_node;
    }

    p_min_node->p_left = p_delete_node->p_left;
    p_delete_node->p_left->p_parent = p_min_node;

    p_min_node->p_right = p_delete_node->p_right;
    p_delete_node->p_right->p_parent = p_min_node;

    p_min_node->p_parent = p_delete_node->p_parent;
    delete p_delete_node;
}

void BinarySearchTree::PrintTree() {
    if (!this->p_root) {
        std::cout << "Empty tree\n";
        return;
    }

    PrintHelper(p_root, "", true, true);
}

void BinarySearchTree::PrintHelper(Node* node, const std::string& prefix, bool isLeft, bool isRoot) {
    if (node != nullptr) {

        std::cout << prefix;
        if (isRoot)
            std::cout <<  "----";
        else
            std::cout << (isLeft ? "L---" : "|---");

        std::cout << node->key << std::endl;

        PrintHelper(node->p_right, prefix + (isLeft ? "    " : "|   "), false);
        PrintHelper(node->p_left, prefix + (isLeft ? "    " : "|   "), true);
    }
}

BinarySearchTree::~BinarySearchTree() {
    delete p_root;
    p_root = nullptr;
}

