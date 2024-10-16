
#ifndef CODE_TASK_1_H
#define CODE_TASK_1_H

#include <string>
#include <iostream>
#include <algorithm>

struct ViolationData {
    std::string CarNum;
};

struct Node {
    std::string key;
    size_t ind{};
    bool prK = false;

    bool opened = true;
    bool deleted = false;

    ViolationData* data = nullptr;
};

void DelTableArr(Node* hash_table, size_t table_size) {
    for (int i = 0; i < table_size; i++) {
        if (hash_table[i].data != nullptr) {
            delete hash_table[i].data;
            hash_table[i].data = nullptr;
        }
    }

    delete[] hash_table;
    hash_table = nullptr;
}

struct HashTable {
    size_t table_size = 20;
    size_t num_closed = 0;
    Node* hash_table;

    HashTable() {
        hash_table = new Node[table_size];
    }

    ~HashTable() {
        DelTableArr(hash_table, table_size);
    }
};


void ResizeTable(HashTable&, float);
void InsertElem(HashTable&, ViolationData*);



size_t djb2Hash(const std::string& str) {
    size_t hash = 5381;
    for (char c : str) {
        hash = ((hash << 5) + hash) + static_cast<size_t>(c);
    }
    return hash;
}

void ResizeTable(HashTable& hashTable, float factor = 1.5) {
    size_t old_size = hashTable.table_size;
    Node* old_table = new Node[old_size];

    memcpy(old_table, hashTable.hash_table, old_size);
    DelTableArr(hashTable.hash_table, old_size);

    hashTable.table_size = (size_t)(old_size * factor);
    hashTable.hash_table = new Node[hashTable.table_size];

    for (size_t i = 0; i < old_size; i++) {
        if (old_table[i].opened) {
            InsertElem(hashTable, old_table[i].data);
        }
    }

    DelTableArr(old_table, old_size);
}

void InsertElem(HashTable& hashTable, ViolationData* p_violation) {
    size_t pos = djb2Hash(p_violation->CarNum) % hashTable.table_size;
    bool K = false;

    while (!hashTable.hash_table[pos].opened) {
        K = true;
        pos++;

        if (pos == hashTable.table_size) {
            pos = 0;
        }
    }

    hashTable.hash_table[pos].key = p_violation->CarNum;
    hashTable.hash_table[pos].prK = K;
    hashTable.hash_table[pos].data = p_violation;
    hashTable.hash_table[pos].opened = false;
    hashTable.hash_table[pos].deleted = false;
    hashTable.hash_table[pos].ind = pos;

    hashTable.num_closed++;

    if ((float)hashTable.num_closed / (float)hashTable.table_size > 0.75)
        ResizeTable(hashTable);
}


#endif //CODE_TASK_1_H
