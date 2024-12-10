#ifndef CODE_TASK_1_H
#define CODE_TASK_1_H

#include <string>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

struct HashTable_Node {
    int key;

    bool opened = true;
    bool deleted = false;
};

struct HashTable {
    size_t table_size = 5;
    size_t num_closed = 0;
    HashTable_Node* hash_table;

    HashTable() {
        hash_table = new HashTable_Node[table_size];
    }

    ~HashTable() {
        delete[] hash_table;
    }
};

void ResizeTable(HashTable&);
void PrintHashTable(HashTable&);
void InsertElem(HashTable&, int key);
size_t MemoryUsage(HashTable&);

size_t MemoryUsage(HashTable& table) {
    return table.table_size * sizeof(HashTable_Node) + sizeof(HashTable);
}

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

size_t HashFun(int key) {
    unsigned int hash = key;
    hash ^= (hash >> 16);
    hash *= 0x45d9f3b;
    hash ^= (hash >> 16);
    return hash;
}

void ResizeTable(HashTable& hashTable) {
    size_t old_size = hashTable.table_size;
    HashTable_Node* old_table = hashTable.hash_table;

    size_t new_size = old_size * 2 + 1;
    while (!isPrime(new_size))
        new_size += 2;

    hashTable.table_size = new_size;
    hashTable.hash_table = new HashTable_Node[hashTable.table_size];
    hashTable.num_closed = 0;


    for (size_t i = 0; i < old_size; i++) {
        if (!old_table[i].opened) {
            InsertElem(hashTable, old_table[i].key);
        }
    }

    delete[] old_table;
}

void InsertElem(HashTable& hashTable, int key) {
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
    hashTable.hash_table[pos].opened = false;
    hashTable.hash_table[pos].deleted = false;

    if ((float)hashTable.num_closed / (float)hashTable.table_size > 0.75)
        ResizeTable(hashTable);
}

void PrintHashTable(HashTable& table) {
    std::cout << std::right << std::setw(4) << "#" << std::setw(10) << "KEY"
        << std::setw(12) << "OpenKey" << std::setw(12) << "DeletedKey" <<
        std::setw(16) << "Hash % size" << '\n';
    for (size_t i = 0; i < table.table_size; i++) {
        bool flag = !table.hash_table[i].opened && !table.hash_table[i].deleted;
        std::cout << std::right << std::setw(4) << i << std::setw(10) << (flag ? std::to_string(table.hash_table[i].key) : std::string(9, '.')) <<
                  std::boolalpha << std::setw(12) << table.hash_table[i].opened <<
                  std::setw(12) << table.hash_table[i].deleted <<
                  (flag ? std::to_string(HashFun(table.hash_table[i].key) % table.table_size) : std::string(15, '.')) << '\n';
    }
}

int FindElem (HashTable& hashTable, int key) {
    int result = 0;
    size_t pos = HashFun(key) % hashTable.table_size;

    while ((!hashTable.hash_table[pos].opened || hashTable.hash_table[pos].deleted)
           && hashTable.hash_table[pos].key != key) {
        pos++;

        if (pos == hashTable.table_size)
            pos = 0;

        result += 3;
    }

    result += 2;
    if (hashTable.hash_table[pos].key != key || hashTable.hash_table[pos].deleted)
        return false;

    return result;
}

#endif //CODE_TASK_1_H
