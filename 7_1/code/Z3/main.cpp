#include <fstream>
#include "HashTable.h"
#include "BinarySearchTree.h"
#include "SplayTree.h"
#include <chrono>
#include <cassert>

std::string path = "../Z3/nums";

void InitHashTable(HashTable& hashTable, int count = 0) {
    std::ifstream file(path);
    int num;

    if (count > 0) {
        for (int i = 0; i < count; i++) {
            file >> num;
            InsertElem(hashTable, num);
        }
    } else {
        while (file >> num) {
            InsertElem(hashTable, num);
        }
    }

    file.close();
}

void InitBinarySearchTree(BinarySearchTree& tree, int count = 0) {
    std::ifstream file(path);
    int num;

    if (count > 0) {
        for (int i = 0; i < count; i++) {
            file >> num;
            tree.Insert(num);
        }
    } else {
        while (file >> num) {
            tree.Insert(num);
        }
    }

    file.close();
}

void InitSplayTree(SplayTree& tree, int count = 0) {
    std::ifstream file(path);
    int num;

    if (count > 0) {
        for (int i = 0; i < count; i++) {
            file >> num;
            tree.Insert(num);
        }
    } else {
        while (file >> num) {
            tree.Insert(num);
        }
    }

    file.close();

}

int main () {
    HashTable hashTable;
    BinarySearchTree tree;
    SplayTree splayTree;

    int count = 0;
    int toFind = 9735410;

    InitHashTable(hashTable, count);
    InitBinarySearchTree(tree, count);
    InitSplayTree(splayTree, count);

    int k1;
    int k2;
    int k3;
    int k4;

    auto start = std::chrono::high_resolution_clock::now();
    k1 = FindElem(hashTable, toFind);
    auto end = std::chrono::high_resolution_clock::now();

    auto hashTableTime = std::chrono::duration<double>(end - start).count();;

    start = std::chrono::high_resolution_clock::now();
    k2 = tree.Find(toFind);
    end = std::chrono::high_resolution_clock::now();

    auto binaryTreeTime = std::chrono::duration<double>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    k3 = splayTree.Find(toFind);
    end = std::chrono::high_resolution_clock::now();

    auto splayTreeTime = std::chrono::duration<double>(end - start).count();


    start = std::chrono::high_resolution_clock::now();
    k4 = splayTree.Find(toFind);
    end = std::chrono::high_resolution_clock::now();

    auto repeatSplayTreeTime = std::chrono::duration<double>(end - start).count();

    std::cout << std::fixed << std::setprecision(9) << "HashTable time:        " << hashTableTime << " s | "
    << MemoryUsage(hashTable) << " byte | " << k1 << std::endl;
    std::cout << std::fixed << std::setprecision(9) << "BinarySearchTree time: " << binaryTreeTime << " s | "
    << tree.MemoryUsage() << " byte | " << k2 << std::endl;
    std::cout << std::fixed << std::setprecision(9) << "SplayTree time:        " << splayTreeTime << " s | "
    << splayTree.MemoryUsage() << " byte | " << k3 << std::endl;
    std::cout << std::fixed << std::setprecision(9) << "Repeat SplayTree time: " << repeatSplayTreeTime << " s | "
    << splayTree.MemoryUsage() << " byte | " << k4  << std::endl;
}