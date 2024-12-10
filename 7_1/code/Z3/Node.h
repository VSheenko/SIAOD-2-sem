#ifndef CODE_NODE_H
#define CODE_NODE_H

#include <string>
#include <memory>

struct Node {
    int key;
    size_t link_to_record;

    std::shared_ptr<Node> p_parent = nullptr;
    std::shared_ptr<Node> p_left   = nullptr;
    std::shared_ptr<Node> p_right  = nullptr;

    Node(int key, std::shared_ptr<Node> p_parent) {
        this->key = key;
        this->p_parent = std::move(p_parent);
    }

    bool IsLeft() const {
        return p_parent && p_parent->p_left.get() == this;
    }
};

#endif //CODE_NODE_H
