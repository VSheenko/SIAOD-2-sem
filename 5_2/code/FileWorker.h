#ifndef CODE_FILEWORKER_H
#define CODE_FILEWORKER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

void PrintFileContent(std::ifstream& file) {
    std::string s;
    while (std::getline(file, s)) {
        std::cout << s << '\n';
    }
}

void AppendContentToFile(std::ofstream& file, const std::string& s_content) {
    file << s_content << '\n';
}

int GetNumByOrdinal(std::ifstream& file, int ordinal_num, bool& SUCCESS_CODE) {
    int num;
    int cur_num = 0;
    while (file >> num) {
        cur_num++;

        if (cur_num == ordinal_num) {
            file.close();
            return num;
        }
    }

    SUCCESS_CODE = false;
    return SUCCESS_CODE;
}

int CountNum(std::ifstream& file) {
    int num;
    int count = 0;
    while (file >> num) {
        count++;
    }

    return count;
}

void Partition(std::ifstream& in_file) {
    int count = CountNum(in_file);

    std::ofstream out_a_file("a_half.txt");
    std::ofstream out_b_file("b_half.txt");

    if (!out_a_file.is_open() || !out_b_file.is_open()) {
        std::cerr << "File not found\n";
        return;
    }

    int k = 0;
    int num;
    int half = count / 2;

    in_file.clear();
    in_file.seekg(0, std::ios::beg);
    while (in_file >> num) {
        if (k < half)
            out_a_file << num << '\n';
        else
            out_b_file << num << '\n';
        k++;

    }

    out_a_file.close();
    out_b_file.close();
}

void Merge(std::ofstream& out_file) {
    std::ifstream in_a_file("a_half.txt");
    std::ifstream in_b_file("b_half.txt");

    if (!in_b_file.is_open() || !out_file.is_open()) {
        std::cerr << "File not found\n";
        return;
    }

    std::string s_a;
    std::string s_b;

    bool a_no_eof = (bool)std::getline(in_a_file, s_a);
    bool b_no_eof = (bool)std::getline(in_b_file, s_b);

    while (a_no_eof || b_no_eof) {
        int a = a_no_eof ? std::stoi(s_a) : -1;
        int b = b_no_eof ? std::stoi(s_b) : -1;

        if (a_no_eof && b_no_eof) {
            if (a > b)
                out_file << b << '\n' << a << '\n';
            else
                out_file << a << '\n' << b << '\n';
            a_no_eof = (bool)std::getline(in_a_file, s_a);
            b_no_eof = (bool)std::getline(in_b_file, s_b);
        } else if (a_no_eof) {
            out_file << a << '\n';
            a_no_eof = (bool)std::getline(in_a_file, s_a);
        } else {
            out_file << b << '\n';
            b_no_eof = (bool) std::getline(in_b_file, s_b);
        }
    }

    in_b_file.close();
    in_a_file.close();
}

#endif //CODE_FILEWORKER_H
