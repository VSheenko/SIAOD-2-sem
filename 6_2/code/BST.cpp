#include "BST.h"


void BST::InsertElem(const std::string &str) {
    Node* p_new_node = new Node(str, CountDigit(str));

    if (!this->p_root) {
        this->p_root = p_new_node;
        return;
    }

    Node* p_cur_node = this->p_root;
    Node* p_parent_node = nullptr;

    while (p_cur_node) {
        p_parent_node = p_cur_node;
        if (str < p_cur_node->s_key)
            p_cur_node = p_cur_node->p_left;
        else
            p_cur_node = p_cur_node->p_right;
    }

    if (str < p_parent_node->s_key)
        p_parent_node->p_left = p_new_node;
    else
        p_parent_node->p_right = p_new_node;
}

void BST::InitTree(const std::vector<std::string> &elems) {
    for (const auto& i : elems)
        InsertElem(i);
}


void BST::PrintTree() {
    if (!this->p_root) {
        std::cout << "Empty tree\n";
        return;
    }

    PrintTreeHelper(p_root, "", true, true);
}

void BST::PrintTreeHelper(Node* node, const std::string& prefix, bool isLeft, bool isRoot) {
    if (node != nullptr) {

        std::cout << prefix;
        if (isRoot)
            std::cout <<  "----";
        else
            std::cout << (isLeft ? "L---" : "|---");

        std::cout << node->s_key << std::endl;

        PrintTreeHelper(node->p_right, prefix + (isLeft ? "    " : "|   "), false);
        PrintTreeHelper(node->p_left, prefix + (isLeft ? "    " : "|   "), true);
    }
}

BST::~BST() {
    std::queue<Node*> q;
    q.push(this->p_root);

    while (!q.empty()) {
        Node* cur = q.front();
        q.pop();

        if (cur->p_left)
            q.push(cur->p_left);
        if (cur->p_right)
            q.push(cur->p_right);

        delete cur;
    }
}

int BST::SpecCount(int num) {
    std::queue<Node*> q;
    q.push(this->p_root);

    int res = 0;

    while (!q.empty()) {
        Node* cur = q.front();
        q.pop();

        if (cur->digit_count > num)
            res++;

        if (cur->p_left)
            q.push(cur->p_left);
        if (cur->p_right)
            q.push(cur->p_right);
    }

    return res;
}

bool BST::IsDegenerate() {
    if (!this->p_root)
        return false;

    bool left = (this->p_root->p_left ? true : false);
    Node* cur = p_root;

    while (cur) {
        if (left && cur->p_right)
            return false;

        if (!left && cur->p_left)
            return false;

        cur = (left ? cur->p_left : cur->p_right);
    }

    return true;
}

unsigned short BST::CountDigit(const std::string &str) {
    unsigned short res = 0;
    for (auto& i : str)
        if (isdigit(i))
            res++;

    return res;
}

void BST::CopyTree(BST& old_tree) {
    if (!old_tree.p_root || this->p_root)
        return;

    this->p_root = new Node();
    CopyNode(this->p_root, old_tree.p_root);
}

void BST::CopyNode(BST::Node *p_new_node, Node* p_cur_node) {
    p_new_node->s_key = p_cur_node->s_key;
    p_new_node->digit_count = p_cur_node->digit_count;

    if (p_cur_node->p_left) {
        Node* p = new Node();
        p_new_node->p_left = p;
        CopyNode(p, p_cur_node->p_left);
    }

    if (p_cur_node->p_right) {
        Node* p = new Node();
        p_new_node->p_right = p;
        CopyNode(p, p_cur_node->p_right);
    }
}


