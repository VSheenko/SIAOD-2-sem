#include "SplayTree.h"
#include <iostream>
#include <queue>

int SplayTree::Splay(std::shared_ptr<Node> node) {
    int result = 0;

    while (node->p_parent) {
        if (!node->p_parent->p_parent) {
            if (node->IsLeft())
                RightRotate(node->p_parent);
            else
                LeftRotate(node->p_parent);
            result += 3;
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
                result += 4;
            } else {
                // Zig-Zag
                if (isLeftChild) {
                    RightRotate(node->p_parent);
                    LeftRotate(node->p_parent);
                } else {
                    LeftRotate(node->p_parent);
                    RightRotate(node->p_parent);
                }
                result += 4;
            }
        }
    }

    return result;
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


void SplayTree::Insert(int key) {
    if (!p_root) {
        p_root = std::make_shared<Node>(key, nullptr);
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
        p_parent->p_left = std::make_shared<Node>(key, p_parent);
        Splay(p_parent->p_left);
    } else {
        p_parent->p_right = std::make_shared<Node>(key, p_parent);
        Splay(p_parent->p_right);
    }
}

int SplayTree::Find(int key) {
    int result = 0;
    std::shared_ptr<Node> p_cur_node = p_root;

    result += 1;
    while (p_cur_node && p_cur_node->key != key) {
        result += 3;
        if (key < p_cur_node->key)
            p_cur_node = p_cur_node->p_left;
        else
            p_cur_node = p_cur_node->p_right;
    }

    if (p_cur_node.get()) {
        result += Splay(p_cur_node);
    }

    if (p_cur_node && p_cur_node->key == key) {
        return result;
    }

    return -1;
}

size_t SplayTree::MemoryUsage() {
    size_t memory = sizeof *this;
    std::queue<std::shared_ptr<Node>> q;
    q.push(p_root);

    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        if (!node) continue;

        memory += sizeof *node;
        q.push(node->p_left);
        q.push(node->p_right);
    }

    return memory;
}


