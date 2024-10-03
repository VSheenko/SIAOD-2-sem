#include <iostream>
#include <bitset>
#include "gtest/gtest.h"

void r5() {
    unsigned int value;
    unsigned int mask = 0x80000000;
    unsigned int res;

    std::cin >> value;

    mask = (mask >> 4)|(mask >> 7)|(mask >> 15)|(mask >> 23);
    res = value ^ mask;


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

TEST(z5, test) {
    r5();
}
