#include <iostream>
#include <bitset>
#include <iomanip>
#include "gtest/gtest.h"


void r1_1() {
    unsigned int value;
    unsigned int mask;
    unsigned int res;

    value = 0xa412;
    mask = 0xfffffbeb;
    res = value & mask;

    std::cout << '\n';
    std::cout << std::left << std::setw(16) << " "
        << std::setw(16) << "10 c.c"
        << std::setw(16) << "16 c.c"
        << std::setw(32) << "2 c.c" << '\n';


    std::cout  << std::left << std::setw(16) << "Variable value"
        << std::setw(16) << std::dec << value
        << std::setw(16) << std::hex << value
        << std::setw(32) << std::bitset<sizeof (unsigned int) * CHAR_BIT>(value) << '\n';
    ;

    std::cout  << std::left << std::setw(16) << "Mask value"
               << std::setw(16) << std::dec << mask
               << std::setw(16) << std::hex << mask
               << std::setw(32) << std::bitset<sizeof (mask) * CHAR_BIT>(mask) << '\n';

    std::cout  << std::left << std::setw(16) << "Result value"
               << std::setw(16) << std::dec << res
               << std::setw(16) << std::hex << res
               << std::setw(32) << std::bitset<sizeof (unsigned int) * CHAR_BIT>(res) << '\n';

    std::cout << '\n';
}

TEST(z1, r1_1) {
    r1_1();
}

void r1_2() {
    unsigned int value;
    unsigned int mask;
    unsigned int res;

    value = 0xa122;
    mask = ~((1 << 10)|(1 << 4)|(1 << 2));
    res = value & mask;

    std::cout << '\n';
    std::cout << std::left << std::setw(16) << " "
              << std::setw(16) << "10 c.c"
              << std::setw(16) << "16 c.c"
              << std::setw(32) << "2 c.c" << '\n';


    std::cout  << std::left << std::setw(16) << "Variable value"
               << std::setw(16) << std::dec << value
               << std::setw(16) << std::hex << value
               << std::setw(32) << std::bitset<sizeof (unsigned int) * CHAR_BIT>(value) << '\n';
    ;

    std::cout  << std::left << std::setw(16) << "Mask value"
               << std::setw(16) << std::dec << mask
               << std::setw(16) << std::hex << mask
               << std::setw(32) << std::bitset<sizeof (mask) * CHAR_BIT>(mask) << '\n';

    std::cout  << std::left << std::setw(16) << "Result value"
               << std::setw(16) << std::dec << res
               << std::setw(16) << std::hex << res
               << std::setw(32) << std::bitset<sizeof (unsigned int) * CHAR_BIT>(res) << '\n';

    std::cout << '\n';
}

TEST(z1, r1_2) {
    r1_2();
}
