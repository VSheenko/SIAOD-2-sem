#ifndef CODE_FILEWORKER_H
#define CODE_FILEWORKER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

std::vector<std::string> Split(std::string s, const std::string& separator) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;

    while ((pos = s.find(separator)) != std::string::npos) {
        token = s.substr(0, pos);

        if (!token.empty())
            tokens.push_back(token);

        s.erase(0, pos + separator.length());
    }

    if (!s.empty())
        tokens.push_back(s);

    return tokens;
}

void PrintFileContent(const std::string& s_file_name) {
    std::ifstream file(s_file_name);

    std::string s;
    while (std::getline(file, s)) {
        std::cout << s << '\n';
    }

    file.close();
}

void AppendContentToFile(const std::string& s_file_name, const std::string& s_content, bool& SUCCESS_CODE) {
    std::ofstream file(s_file_name, std::ios::app);

    file << s_content;

    SUCCESS_CODE = file.good();
    file.close();
}

int GetNumByOrdinal(const std::string& s_file_name, int ordinal_num, bool& SUCCESS_CODE) {
    std::ifstream file(s_file_name);
    SUCCESS_CODE = true;

    std::string s;
    int cur_num = 0;
    while (std::getline(file, s)) {
        std::vector<std::string> parts = Split(s, " ");


        for (const auto &part: parts) {
            cur_num++;

            if (cur_num == ordinal_num) {
                file.close();
                return std::stoi(part);
            }
        }
    }

    file.close();
    SUCCESS_CODE = false;
    return SUCCESS_CODE;
}

int CountNum(const std::string& s_file_name) {
    std::ifstream file(s_file_name);

    std::string s;
    int count = 0;
    while (std::getline(file, s)) {
        std::vector<std::string> parts = Split(s, " ");

        for (const auto &part: parts)
            count++;
    }

    file.close();
    return count;
}

void Partition(const std::string& s_file_name) {
    int count = CountNum(s_file_name);

    std::ifstream in_file(s_file_name);
    std::ofstream out_a_file("a_half.txt");
    std::ofstream out_b_file("b_half.txt");

    int k = 0;
    std::string s;
    int half = count / 2;
    while (std::getline(in_file, s)) {
        std::vector<std::string> parts = Split(s, " ");

        for (const auto &part: parts) {
            if (k < half)
                out_a_file << part << '\n';
            else
                out_b_file << part << '\n';
            k++;
        }
    }

    in_file.close();
    out_a_file.close();
    out_b_file.close();
}

void Merge(const std::string& s_file_name) {
    std::ifstream in_a_file("a_half.txt");
    std::ifstream in_b_file("b_half.txt");
    std::ofstream out_file(s_file_name);

    std::string s_a;
    std::string s_b;

    bool a_no_eof = (bool)std::getline(in_a_file, s_a);
    bool b_no_eof = (bool)std::getline(in_b_file, s_b);

    while (a_no_eof || b_no_eof) {
        int a = a_no_eof ? std::stoi(s_a) : -1;
        int b = b_no_eof ? std::stoi(s_b) : -1;

        if (a_no_eof && b_no_eof) {
            if (a > b)
                out_file << a << '\n' << b << '\n';
            else
                out_file << b << '\n' << a << '\n';
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

    out_file.close();
    in_b_file.close();
    in_a_file.close();
}

#endif //CODE_FILEWORKER_H
