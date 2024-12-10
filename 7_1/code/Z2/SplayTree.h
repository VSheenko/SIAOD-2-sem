#ifndef CODE_SPLAYTREE_H
#define CODE_SPLAYTREE_H

#include "Node.h"


class SplayTree {
private:
    std::shared_ptr<Node> p_root = nullptr;
    std::shared_ptr<Node> RightRotate(std::shared_ptr<Node> node);
    std::shared_ptr<Node> LeftRotate(std::shared_ptr<Node> node);
    void Splay(std::shared_ptr<Node> node);
    std::shared_ptr<Node> FindMin(std::shared_ptr<Node> node);
    void PrintHelper(std::shared_ptr<Node> node, const std::string& prefix, bool isLeft, bool isRoot = false);

public:
    int rotations = 0; // for testing

    void Insert(const std::string &key, size_t ind);
    bool Find(const std::string &key, size_t& found_ind);
    void Remove(const std::string &key);
    void PrintTree();
};


#endif //CODE_SPLAYTREE_H
