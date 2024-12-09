#include "SplayTree.h"
#include <iostream>

int main() {
    SplayTree tree;
    int mode;

    std::cout << "1. Insert\n" <<
                  "2. Find\n" <<
                  "3. Remove\n" <<
                  "4. Print\n" <<
                  "5. Exit\n";
    std::cin >> mode;

    size_t ind;
    std::string key;
    while (mode != 5) {
        switch (mode) {
            case 1:
                std::cout << "Enter key and index: ";
                std::cin >> key >> ind;
                tree.Insert(key, ind);
                break;
            case 2:
                std::cout << "Enter key: ";
                std::cin >> key;
                size_t found_ind;
                if (tree.Find(key, found_ind))
                    std::cout << "Found at index " << found_ind << std::endl;
                else
                    std::cout << "Not found" << std::endl;
                break;
            case 3:
                std::cout << "Enter key: ";
                std::cin >> key;
                tree.Remove(key);
                break;
            case 4:
                tree.PrintTree();
                break;
            default:
                std::cout << "Invalid mode" << std::endl;
                break;
        }

        std::cout << "1. Insert\n" <<
                  "2. Find\n" <<
                  "3. Remove\n" <<
                  "4. Print\n" <<
                  "5. Exit\n";
        std::cin >> mode;


    }
}
