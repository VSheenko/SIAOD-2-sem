#include "SplayTree.h"

int main() {
    SplayTree tree;

    tree.Insert("g", 1);
    tree.Insert("d", 2);
    tree.Insert("h", 3);
    tree.Insert("q", 4);
    tree.Insert("a", 5);
    tree.Insert("b", 6);

    tree.PrintTree();
}