#ifndef CODE_BINFILEWORKER_H
#define CODE_BINFILEWORKER_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <filesystem>

namespace fs = std::filesystem;

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

struct Violation {
    char carNumber[16];
    char name[32];
    char model[32];
    char data[32];
    char place[32];
    char article[32];
    short fine;

    void SetFieldsByStr(const std::string& s) {
        std::vector<std::string> tokens = Split(s, ";");

        if (tokens.size() != 7) {
            std::cerr << "Reading Error" << '\n';
            return;
        }

        strcpy(carNumber, tokens[0].c_str());
        strcpy(name, tokens[1].c_str());
        strcpy(model, tokens[2].c_str());
        strcpy(data, tokens[3].c_str());
        strcpy(place, tokens[4].c_str());
        strcpy(article, tokens[5].c_str());
        fine = std::stoi(tokens[6]);
    }

    std::string ToString() {
        std::string res;

        res = carNumber + std::string(";") + name + std::string(";") + model + std::string(";") +
                data + std::string(";") + place + std::string(";") + article + std::string(";") +
                std::to_string(fine) + std::string(";");

        return res;
    }
};

void TextToBin(const std::string& file_name, const std::string& bin_file_name) {
    std::ifstream file(file_name);
    std::ofstream bin_file(bin_file_name, std::ios::binary);

    if (!file.is_open() || !bin_file.is_open()) {
        std::cerr << "Error opening file" << '\n';
        return;
    }

    std::string s;
    Violation violation;

    while (std::getline(file, s)) {
        violation.SetFieldsByStr(s);
        bin_file.write((char*)&violation, sizeof(Violation));
    }

    file.close();
    bin_file.close();
}

void BinToText(const std::string& file_name, const std::string& bin_file_name) {
    std::ifstream bin_file(bin_file_name, std::ios::binary);
    std::ofstream file(file_name);

    if (!bin_file.is_open() || !file.is_open()) {
        std::cerr << "Error opening file" << '\n';
        return;
    }

    Violation violation;

    while (bin_file.read((char*)&violation, sizeof(Violation))) {
        file << violation.ToString() << '\n';
    }

    bin_file.close();
    file.close();
}

void PrintAllViolationInBin(const std::string& bin_file_name) {
    std::ifstream bin_file(bin_file_name, std::ios::binary);

    if (!bin_file.is_open()) {
        std::cerr << "Error opening file" << '\n';
        return;
    }

    Violation violation;

    while (bin_file.read((char*)&violation, sizeof(Violation))) {
        std::cout << violation.ToString() << '\n';
    }

    bin_file.close();
}

Violation GetViolationByCarNum(const std::string& bin_file_name, const std::string& car_num, bool& SUCCESS_CODE) {
    std::ifstream bin_file(bin_file_name, std::ios::binary);
    SUCCESS_CODE = false;

    if (!bin_file.is_open()) {
        std::cerr << "Error opening file" << '\n';
        return {};
    }

    Violation violation;

    while (bin_file.read((char*)&violation, sizeof(Violation))) {
        if (strcmp(violation.carNumber, car_num.c_str()) == 0) {
            bin_file.close();
            SUCCESS_CODE = true;
            return violation;
        }
    }

    bin_file.close();
    return {};
}

// Теперь возвращает индекс записи, удаленной и измененной на последнюю запись
size_t DeleteViolationByCarNum(const std::string& bin_file_name, const std::string& car_num) {
    std::fstream bin_file(bin_file_name, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);
    if (!bin_file.is_open())
        return -1;

    size_t file_size = fs::file_size(bin_file_name);
    bin_file.seekg(0, std::ios::beg);

    int violations_count = file_size / sizeof(Violation);

    std::streampos last_record_pos = (violations_count - 1) * sizeof(Violation);
    Violation last_violation;
    bin_file.seekg(last_record_pos);
    bin_file.read((char*)&last_violation, sizeof(Violation));

    bool deleted = false;
    std::streampos cur_pos = std::ios::beg;
    Violation violation;

    size_t ind_del = -1;
    bin_file.seekp(std::ios::beg);
    while (cur_pos != file_size) {
        bin_file.read((char*)&violation, sizeof(Violation));

        if (strcmp(violation.carNumber, car_num.c_str()) == 0 && ind_del == -1) {
            bin_file.seekp(cur_pos);
            bin_file.write((char*)&last_violation, sizeof(Violation));
            ind_del = cur_pos / sizeof(Violation);
        }

        cur_pos = bin_file.tellg();
    }

    bin_file.close();
    fs::resize_file(bin_file_name, file_size - sizeof(Violation));
    return ind_del;
}

void SelectionByCarNum(const std::string& bin_file_name, const std::string& new_file_name, const std::string& car_num) {
    std::ifstream bin_file(bin_file_name, std::ios::binary);
    std::ofstream new_bin_file(new_file_name, std::ios::binary);

    if (!bin_file.is_open()) {
        std::cerr << "Error opening file" << '\n';
        return;
    }

    Violation violation;

    while (bin_file.read((char*)&violation, sizeof(Violation))) {
        if (strcmp(violation.carNumber, car_num.c_str()) == 0)
            new_bin_file << violation.ToString() << '\n';
    }

    bin_file.close();
}

void DoubleFine(const std::string& bin_file_name, const std::string& start_date,
                const std::string& end_date, const std::string& article) {

    std::fstream bin_file(bin_file_name, std::ios::binary | std::ios::in | std::ios::out);

    if (!bin_file.is_open()) {
        std::cerr << "Error opening file" << '\n';
        return;
    }

    Violation violation;

    while (bin_file.read((char*)&violation, sizeof(Violation))) {
        if (violation.data >= start_date && violation.data <= end_date && strcmp(violation.article, article.c_str()) == 0) {
            violation.fine *= 2;
            bin_file.seekp(-sizeof(Violation), std::ios::cur);
            bin_file.write((char *) &violation, sizeof(Violation));
        }
    }

    bin_file.close();
}

void PrintBinFileInHex(const std::string& bin_file_name) {
    std::ifstream bin_file(bin_file_name, std::ios::binary);

    if (!bin_file.is_open()) {
        std::cerr << "Error opening file" << '\n';
        return;
    }

    char c;
    int k = 0;
    while (bin_file.get(c)) {
        std::cout << std::hex << std::setw(2) << std::setfill('0')
                  << (static_cast<unsigned int>(c) & 0xFF)
                  << ' ';
        k++;

        if (k % 16 == 0)
            std::cout << '\n';
    }

    bin_file.close();
}

Violation GetViolationByOrdinalNum(const std::string& bin_file_name, const size_t ordinal_num, bool& SUCCESS_CODE) {
    std::fstream bin_file(bin_file_name, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);
    SUCCESS_CODE = false;

    if (!bin_file.is_open()) {
        return {};
    }

    size_t file_size = fs::file_size(bin_file_name);
    bin_file.seekg(0, std::ios::beg);
    int violations_count = file_size / sizeof(Violation);

    if (ordinal_num > violations_count - 1 || ordinal_num < 0) {
        return {};
    }

    std::streampos record_pos = ordinal_num * sizeof(Violation);
    bin_file.seekg(record_pos, std::ios::beg);

    Violation target_violation;
    bin_file.read((char*)&target_violation, sizeof(Violation));

    SUCCESS_CODE = true;
    return target_violation;
}

#endif //CODE_BINFILEWORKER_H
