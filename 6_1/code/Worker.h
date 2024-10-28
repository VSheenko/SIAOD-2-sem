#ifndef CODE_WORKER_H
#define CODE_WORKER_H

#include "BinFileWorker.h"
#include "task_1.h"

bool ExtractRecordToHash(HashTable& h, const std::string& s_bin_file, size_t ordinal_num);
bool DelRecord(HashTable& h, const std::string& s_bin_file, const std::string& key);
bool ChangeIndDataInTable (HashTable& h, const std::string& car_num, size_t ind_new);
Violation GetViolationByKey(HashTable& h, const std::string& s_bin_file, const std::string& key, bool& SUCCESS_CODE);

bool ExtractRecordToHash(HashTable &h, const std::string &s_bin_file, size_t ordinal_num) {
    bool flag;
    std::string car_name = GetViolationByOrdinalNum(s_bin_file, ordinal_num, flag).carNumber;

    if (flag) {
        InsertElem(h, car_name, ordinal_num);
        return true;
    }

    return false;
    DelRecord(h, s_bin_file, "l");
}

bool DelRecord(HashTable& h, const std::string& s_bin_file, const std::string& key) {
    size_t ind = DeleteViolationByCarNum(s_bin_file, key);

    if (ind == -1)
        return false;

    DeleteElem(h, key);

    bool flag = false;
    std::string car_num = GetViolationByOrdinalNum(s_bin_file, ind, flag).carNumber;

    if (!flag)
        return false;

    return ChangeIndDataInTable(h, car_num, ind);
}

Violation GetViolationByKey(HashTable& h, const std::string& s_bin_file, const std::string& key, bool& SUCCESS_CODE) {
    SUCCESS_CODE = false;
    size_t target = FindElem(h, key);

    if (target == -1)
        return {};

    return GetViolationByOrdinalNum(s_bin_file, target, SUCCESS_CODE);
}

bool ChangeIndDataInTable (HashTable& h, const std::string& car_num, size_t ind_new) {
    size_t pos = HashFun(car_num) % h.table_size;

    while ((!h.hash_table[pos].opened || h.hash_table[pos].deleted)
           && h.hash_table[pos].key != car_num) {
        pos++;

        if (pos == h.table_size)
            pos = 0;
    }

    if (h.hash_table[pos].key != car_num)
        return false;

    h.hash_table[pos].ind_data = ind_new;
    return true;
}



#endif //CODE_WORKER_H
