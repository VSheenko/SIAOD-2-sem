#include "Worker.h"

int main() {
    std::cout << sizeof(Violation) << '\n';

    HashTable h;
    std::string s_bin_file = "BinTest";

    // Вставка из бинарника в хэш-таблицу
    TextToBin("Z:\\MIREA\\SIAOD2\\SIAOD-3-sem\\6_1\\code\\BigTest", s_bin_file);
    size_t cur_pos = 0;
    while (ExtractRecordToHash(h, s_bin_file, cur_pos++));

    bool flag;

    GetViolationByKey(h, s_bin_file, "K079CD50", flag);
    std::cout << std::boolalpha << flag << '\n';

    DelRecord(h, s_bin_file, "K079CD50");

    GetViolationByKey(h, s_bin_file, "K079CD50", flag);
    std::cout << std::boolalpha << flag << '\n';

    Violation v = GetViolationByKey(h, s_bin_file, "B119GN23", flag); // Изначально последняя запись, которая теперь должна заменить удаленную
    std::cout << std::boolalpha << flag << '\n';
    std::cout << v.ToString() << '\n';
}