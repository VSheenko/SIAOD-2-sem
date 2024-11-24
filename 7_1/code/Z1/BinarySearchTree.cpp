#include "BinarySearchTree.h"

void BinarySearchTree::Insert(const std::string &key, size_t ind) {
    if (!p_root) {
        p_root = new Node(key, ind);
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
        p_parent->p_left = new Node(key, ind);
    else
        p_parent->p_right = new Node(key, ind);
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

void BinarySearchTree::Remove(const std::string &key) {
    Node* p_delete_node = p_root;
    Node* p_parent = p_delete_node;

    while (p_delete_node && p_delete_node->key != key) {
        p_parent = p_delete_node;
        if (key < p_delete_node->key)
            p_delete_node = p_delete_node->p_left;
        else
            p_delete_node = p_delete_node->p_right;
    }

    Node* replace_node = nullptr;
    Node* parent_replace_node = nullptr;

    if (!p_delete_node)
        return;

    if (p_delete_node->p_left) {
        parent_replace_node = p_delete_node;
        replace_node = p_delete_node->p_left;

        while (replace_node->p_right) {
            parent_replace_node = replace_node;
            replace_node = replace_node->p_right;
        }

        parent_replace_node->p_right = replace_node->p_left;
        replace_node->p_left = p_delete_node->p_left;
        replace_node->p_right = p_delete_node->p_right;
        p_parent->p_left = replace_node;
        delete p_delete_node;
        return;
    }

    if (p_delete_node->p_right) {
        parent_replace_node = p_delete_node;
        replace_node = p_delete_node->p_left;

        while (replace_node->p_left) {
            parent_replace_node = replace_node;
            replace_node = replace_node->p_left;
        }

        parent_replace_node->p_left = replace_node->p_right;
        replace_node->p_left = p_delete_node->p_left;
        replace_node->p_right = p_delete_node->p_right;
        p_parent->p_right = replace_node;
        delete p_delete_node;
        return;
    }


    if (p_parent->p_left == p_delete_node)
        p_parent->p_left = nullptr;
    else
        p_parent->p_right = nullptr;

    delete p_delete_node;
}

