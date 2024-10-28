#ifndef CODE_TASK_1_H
#define CODE_TASK_1_H

#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

struct Node {
    std::string key;

    bool prK = false;
    bool opened = true;
    bool deleted = false;

    int ind_data;
};

struct HashTable {
    size_t table_size = 5;
    size_t num_closed = 0;
    Node* hash_table;

    HashTable() {
        hash_table = new Node[table_size];
    }

    ~HashTable() {
        delete[] hash_table;
    }
};

void ResizeTable(HashTable&);
void PrintHashTable(HashTable&);
void InsertElem(HashTable&, std::string key, size_t ind_data);

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

size_t HashFun(const std::string& str) {
    size_t hash_value = 0;
    for (char ch : str) {
        hash_value += static_cast<size_t>(ch);
        hash_value += (hash_value << 10);
        hash_value ^= (hash_value >> 6);
    }
    hash_value += (hash_value << 3);
    hash_value ^= (hash_value >> 11);
    hash_value += (hash_value << 15);
    return hash_value;
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
            InsertElem(hashTable, old_table[i].key, old_table[i].ind_data);
        }
    }

    delete[] old_table;
}

void InsertElem(HashTable& hashTable, std::string key, size_t ind_data) {
    size_t pos = HashFun(key) % hashTable.table_size;
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

    hashTable.hash_table[pos].key = key;
    hashTable.hash_table[pos].prK = K;
    hashTable.hash_table[pos].ind_data = ind_data;
    hashTable.hash_table[pos].opened = false;
    hashTable.hash_table[pos].deleted = false;

    if ((float)hashTable.num_closed / (float)hashTable.table_size > 0.75)
        ResizeTable(hashTable);
}

void DeleteElem(HashTable& hashTable, const std::string& key) {
    size_t pos = HashFun(key) % hashTable.table_size;

    while ((!hashTable.hash_table[pos].opened || hashTable.hash_table[pos].deleted)
            && hashTable.hash_table[pos].key != key) {
        pos++;

        if (pos == hashTable.table_size)
            pos = 0;
    }

    if (hashTable.hash_table[pos].key != key)
        return;

    hashTable.hash_table[pos].deleted = true;
    hashTable.hash_table[pos].opened = true;
}

void PrintHashTable(HashTable& table) {
    std::cout << std::right << std::setw(4) << "#" << std::setw(10) << "KEY"
        << std::setw(12) << "OpenKey" << std::setw(12) << "DeletedKey" << std::setw(8) << "prK" <<
        std::setw(16) << "Hash % size" << '\n';
    for (size_t i = 0; i < table.table_size; i++) {
        bool flag = !table.hash_table[i].opened && !table.hash_table[i].deleted;
        std::cout << std::right << std::setw(4) << i << std::setw(10) << (flag ? table.hash_table[i].key : std::string(9, '.')) <<
                  std::boolalpha << std::setw(12) << table.hash_table[i].opened <<
                  std::setw(12) << table.hash_table[i].deleted <<
                  std::setw(8) << table.hash_table[i].prK << std::setw(16) <<
                  (flag ? std::to_string(HashFun(table.hash_table[i].key) % table.table_size) : std::string(15, '.')) << '\n';
    }
}

size_t FindElem (HashTable& hashTable, const std::string& key) {
    size_t pos = HashFun(key) % hashTable.table_size;

    while ((!hashTable.hash_table[pos].opened || hashTable.hash_table[pos].deleted)
           && hashTable.hash_table[pos].key != key) {
        pos++;

        if (pos == hashTable.table_size)
            pos = 0;
    }

    if (hashTable.hash_table[pos].key != key || hashTable.hash_table[pos].deleted)
        return -1;

    return hashTable.hash_table[pos].ind_data;
}

#endif //CODE_TASK_1_H
