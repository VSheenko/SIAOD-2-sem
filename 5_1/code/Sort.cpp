#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <bitset>

void sort() {
    std::vector<int> source_nums;
    int count;

    std::cout << "Enter the number of numbers" << '\n';
    std::cin >> count;

    int temp;
    std::cout << "Enter the numbers one by one" << '\n';
    for (int i = 0; i < count; i++) {
        std::cin >> temp;
        source_nums.push_back(temp);
    }

//--------------------------------------------------------------------------------------------------------------------
    int maxim_volume = 10000;
    int len_bit_arr = static_cast<int>(std::ceil(maxim_volume / 8));

    char* bit_arr = new char[len_bit_arr];
    for (int i = 0; i < len_bit_arr; i++)
        bit_arr[i] = 0; //1. Инициализация бит массива нулевыми значениями


    for (int source_num : source_nums)
        bit_arr[source_num >> 3] |= (char)(1 << (source_num & 7)); //2.	Считывание целых чисел из файла и установка в 1 соответствующих бит;
    source_nums.clear();


    for (int i = 0; i < len_bit_arr; i++)
        for (int j = 0; j < sizeof(char) * 8; j++)
            if ((char)(1 << j) & bit_arr[i])
                source_nums.push_back(i * 8 + j); //3.	Формирование упорядоченного выходного файла путем последовательной проверки бит массива.



    delete[] bit_arr;
    bit_arr = nullptr;

//-----------------------------------------------------------------------------------------------------------------

    for (int num : source_nums) {
        std::cout << num << ' ';
    }
    std::cout << '\n';
}

TEST(T, sort) {
    sort();
}
