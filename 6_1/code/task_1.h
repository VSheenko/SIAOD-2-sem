
#ifndef CODE_TASK_1_H
#define CODE_TASK_1_H

#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

struct ViolationData {
    std::string carNum;
    std::string name;
    std::string model;
    std::string data;
    std::string place;
    std::string article;
    short fine;
};

struct Node {
    std::string key;

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
    size_t table_size = 5;
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
void PrintHashTable(HashTable&);
void InsertElem(HashTable&, ViolationData*);

bool isPrime(int num) {
    int q = (int)sqrt(num);

    if (q*q == num)
        return false;

    for (int i = 2; i < q; i++) {
        if (num % i == 0)
            return false;
    }

    return true;
}

size_t djb2Hash(const std::string& str) {
    size_t hash = 5381;
    for (char c : str) {
        hash = ((hash << 5) + hash) + static_cast<size_t>(c);
    }
    return hash;
}



void ResizeTable(HashTable& hashTable) {
    size_t old_size = hashTable.table_size;
    Node* old_table = hashTable.hash_table;

    size_t new_size = old_size * 2 + 1;
    while (!isPrime(new_size))
        new_size += 2;

    hashTable.table_size = new_size;
    hashTable.hash_table = new Node[hashTable.table_size];
    hashTable.num_closed = 0;


    for (size_t i = 0; i < old_size; i++) {
        if (!old_table[i].opened) {
            InsertElem(hashTable, old_table[i].data);
        }
    }

    delete[] old_table;
}

void InsertElem(HashTable& hashTable, ViolationData* p_violation) {
    size_t pos = djb2Hash(p_violation->carNum) % hashTable.table_size;
    bool K = false;

    while (!hashTable.hash_table[pos].opened) {
        K = true;
        pos++;

        if (pos == hashTable.table_size) {
            pos = 0;
        }
    }

    if (!hashTable.hash_table[pos].deleted)
        hashTable.num_closed++;

    hashTable.hash_table[pos].key = p_violation->carNum;
    hashTable.hash_table[pos].prK = K;
    hashTable.hash_table[pos].data = p_violation;
    hashTable.hash_table[pos].opened = false;
    hashTable.hash_table[pos].deleted = false;

    if ((float)hashTable.num_closed / (float)hashTable.table_size > 0.75)
        ResizeTable(hashTable);
}

void DeleteElem(HashTable& hashTable, const std::string& key) {
    size_t pos = djb2Hash(key) % hashTable.table_size;

    while ((!hashTable.hash_table[pos].opened || hashTable.hash_table[pos].deleted)
            && hashTable.hash_table[pos].key != key) {
        pos++;

        if (pos == hashTable.table_size) {
            pos = 0;
        }
    }

    if (hashTable.hash_table[pos].key != key) {
        return;
    }

    delete hashTable.hash_table[pos].data;
    hashTable.hash_table[pos].data = nullptr;

    hashTable.hash_table[pos].deleted = true;
    hashTable.hash_table[pos].opened = true;
}

void PrintHashTable(HashTable& table) {
    std::cout << std::right << std::setw(4) << "#" << std::setw(10) << "KEY" << std::setw(16) << "Name"
        << std::setw(12) << "OpenKey" << std::setw(12) << "DeletedKey" << std::setw(8) << "prK" <<
        std::setw(16) << "Hash % size" << '\n';
    for (size_t i = 0; i < table.table_size; i++) {
        bool flag = !table.hash_table[i].opened && !table.hash_table[i].deleted;
        std::cout << std::right << std::setw(4) << i << std::setw(10) << (flag ? table.hash_table[i].key : std::string(9, '.')) <<
                    std::setw(16) << (flag ? table.hash_table[i].data->name : std::string(15, '.')) <<
                    std::boolalpha << std::setw(12) << table.hash_table[i].opened <<
                    std::setw(12) << table.hash_table[i].deleted <<
                    std::setw(8) << table.hash_table[i].prK << std::setw(16) <<
                    (flag ? std::to_string(djb2Hash(table.hash_table[i].key) % table.table_size) : std::string(15, '.')) << '\n';
    }
}

size_t FindElem (HashTable& hashTable, const std::string& key) {
    size_t pos = djb2Hash(key) % hashTable.table_size;

    while ((!hashTable.hash_table[pos].opened || hashTable.hash_table[pos].deleted)
           && hashTable.hash_table[pos].key != key) {
        pos++;

        if (pos == hashTable.table_size) {
            pos = 0;
        }
    }

    if (hashTable.hash_table[pos].key != key)
        return -1;

    return pos;
}

#endif //CODE_TASK_1_H
