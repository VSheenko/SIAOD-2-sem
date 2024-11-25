#ifndef CODE_NODE_H
#define CODE_NODE_H

#include <string>
#include <memory>

struct Node {
    std::string key;
    size_t link_to_record;

    std::shared_ptr<Node> p_parent = nullptr;
    std::shared_ptr<Node> p_left   = nullptr;
    std::shared_ptr<Node> p_right  = nullptr;

    Node(std::string key, size_t link_to_record, std::shared_ptr<Node> p_parent) {
        this->key = std::move(key);
        this->link_to_record = link_to_record;
        this->p_parent = std::move(p_parent);
    }

    bool IsLeft() const {
        return p_parent && p_parent->p_left.get() == this;
    }
};

#endif //CODE_NODE_H
