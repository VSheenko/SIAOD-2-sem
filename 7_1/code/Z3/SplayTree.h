#ifndef CODE_SPLAYTREE_H
#define CODE_SPLAYTREE_H

#include "Node.h"

class SplayTree {
private:
    std::shared_ptr<Node> p_root = nullptr;
    std::shared_ptr<Node> RightRotate(std::shared_ptr<Node> node);
    std::shared_ptr<Node> LeftRotate(std::shared_ptr<Node> node);
    int Splay(std::shared_ptr<Node> node);

public:
    void Insert(int key);
    int Find(int key);
    size_t MemoryUsage();
};


#endif //CODE_SPLAYTREE_H
