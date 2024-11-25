#include "SplayTree.h"
#include <iostream>

void SplayTree::Splay(std::shared_ptr<Node> node) {
    while (node->p_parent) {
        if (!node->p_parent->p_parent) {
            if (node->IsLeft())
                RightRotate(node->p_parent);
            else
                LeftRotate(node->p_parent);
        } else {
            bool isLeftChild = node->IsLeft();
            bool parentIsLeftChild = node->p_parent->IsLeft();

            if (isLeftChild == parentIsLeftChild) {
                // Zig-Zig
                if (isLeftChild) {
                    RightRotate(node->p_parent->p_parent);
                    RightRotate(node->p_parent);
                } else {
                    LeftRotate(node->p_parent->p_parent);
                    LeftRotate(node->p_parent);
                }
            } else {
                // Zig-Zag
                if (isLeftChild) {
                    RightRotate(node->p_parent);
                    LeftRotate(node->p_parent);
                } else {
                    LeftRotate(node->p_parent);
                    RightRotate(node->p_parent);
                }
            }
        }
    }
}

std::shared_ptr<Node> SplayTree::RightRotate(std::shared_ptr<Node> node) {
    auto new_root = node->p_left;
    if (!new_root) return node;

    node->p_left = new_root->p_right;
    if (new_root->p_right) {
        new_root->p_right->p_parent = node;
    }

    new_root->p_parent = node->p_parent;
    if (!node->p_parent) {
        p_root = new_root;
    } else if (node->IsLeft()) {
        node->p_parent->p_left = new_root;
    } else {
        node->p_parent->p_right = new_root;
    }

    new_root->p_right = node;
    node->p_parent = new_root;

    return new_root;
}

std::shared_ptr<Node> SplayTree::LeftRotate(std::shared_ptr<Node> node) {
    auto new_root = node->p_right;
    if (!new_root) return node;

    node->p_right = new_root->p_left;
    if (new_root->p_left) {
        new_root->p_left->p_parent = node;
    }

    new_root->p_parent = node->p_parent;
    if (!node->p_parent) {
        p_root = new_root;
    } else if (node->IsLeft()) {
        node->p_parent->p_left = new_root;
    } else {
        node->p_parent->p_right = new_root;
    }

    new_root->p_left = node;
    node->p_parent = new_root;

    return new_root;
}

std::shared_ptr<Node> SplayTree::FindMin(std::shared_ptr<Node> node) {
    while (node && node->p_left)
        node = node->p_left;

    return node;
}

void SplayTree::Insert(const std::string &key, size_t ind) {
    if (!p_root) {
        p_root = std::make_shared<Node>(key, ind, nullptr);
        return;
    }

    std::shared_ptr<Node> p_cur_node = p_root;
    std::shared_ptr<Node> p_parent = nullptr;

    while (p_cur_node) {
        p_parent = p_cur_node;
        if (key < p_cur_node->key)
            p_cur_node = p_cur_node->p_left;
        else
            p_cur_node = p_cur_node->p_right;
    }

    if (key < p_parent->key) {
        p_parent->p_left = std::make_shared<Node>(key, ind, p_parent);
        Splay(p_parent->p_left);
    } else {
        p_parent->p_right = std::make_shared<Node>(key, ind, p_parent);
        Splay(p_parent->p_right);
    }
}

bool SplayTree::Find(const std::string &key, size_t &found_ind) {
    std::shared_ptr<Node> p_cur_node = p_root;

    while (p_cur_node && p_cur_node->key != key) {
        if (key < p_cur_node->key)
            p_cur_node = p_cur_node->p_left;
        else
            p_cur_node = p_cur_node->p_right;
    }

    if (p_cur_node) {
        found_ind = p_cur_node->link_to_record;
        Splay(p_cur_node);
    }

    return (bool)p_cur_node;
}

void SplayTree::Remove(const std::string &key) {
    size_t ind;
    if (!Find(key, ind))
        return;

    std::shared_ptr<Node> new_root = FindMin(p_root->p_right);
    new_root->p_parent = nullptr;

    if (new_root->IsLeft())
        new_root->p_parent->p_left = nullptr;

    new_root->p_left = p_root->p_left;
    new_root->p_right = p_root->p_right;

    p_root = new_root;
}

void SplayTree::PrintTree() {
    PrintHelper(p_root, "", false, true);
}

void SplayTree::PrintHelper(std::shared_ptr<Node> node, const std::string &prefix, bool isLeft, bool isRoot) {
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


