#include <queue>
#include "BinarySearchTree.h"

void BinarySearchTree::Insert(int key) {
    if (!p_root) {
        p_root = new Node(key, nullptr);
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
        p_parent->p_left = new Node(key, p_parent);
    else
        p_parent->p_right = new Node(key, p_parent);
}


int BinarySearchTree::Find(int key) const {
    int result = 0;
    Node* p_cur_node = p_root;

    while (p_cur_node && p_cur_node->key != key) {
        result += 3;
        if (key < p_cur_node->key)
            p_cur_node = p_cur_node->p_left;
        else
            p_cur_node = p_cur_node->p_right;
    }

    return result;
}

BinarySearchTree::~BinarySearchTree() {
    delete p_root;
    p_root = nullptr;
}

size_t BinarySearchTree::MemoryUsage() {
    size_t memory = sizeof(*this);

    std::queue<Node*> q;
    q.push(p_root);

    while (!q.empty()) {
        Node* p_cur_node = q.front();
        q.pop();

        if (p_cur_node) {
            memory += sizeof(Node);
            q.push(p_cur_node->p_left);
            q.push(p_cur_node->p_right);
        }
    }

    return memory;
}

