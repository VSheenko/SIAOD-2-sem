#ifndef CODE_BINFILEWORKER_H
#define CODE_BINFILEWORKER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <cstring>
#include <filesystem>

namespace fs = std::filesystem;

struct Violation{
    std::string carNumber;
    std::string name;
    std::string model;
    std::string data;
    std::string place;
    std::string article;
    int fine;

    void SetFieldsByStr(const std::string& s) {
        std::vector<std::string> tokens = Split(s, ";");

        if (tokens.size() != 7) {
            std::cerr << "Reading Error" << '\n';
            return;
        }

        carNumber = tokens[0];
        name = tokens[1];
        model = tokens[2];
        data = tokens[3];
        place = tokens[4];
        article = tokens[5];
        fine = std::stoi(tokens[6]);
    }

    std::string ToString () {
        std::string res;

        res = carNumber + ";" + name + ";" + model + ";" + data + ";" + place + ";" + article + ";" + std::to_string(fine) + ";";

        return res;
    }

private:
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
};

bool AreExist(const std::vector<std::string>& files_name) {
    for (const auto& file_name : files_name) {
        if (!fs::exists(file_name))
            return false;
    }

    return true;
}

template<typename T>
void ExtractViolationFromBinStream(T& in, Violation& violation) {
    static_assert(
            std::is_same<T, std::stringstream>::value || std::is_same<T, std::fstream>::value,
            "T must be a stringstream or fstream"
    );

    auto readString = [&](std::string& str) {
        unsigned int length;
        in.read(reinterpret_cast<char*>(&length), sizeof(length));

        if (in.eof())
            return;

        str.resize(length);
        in.read(&str[0], length);
    };

    readString(violation.carNumber);
    readString(violation.name);
    readString(violation.model);
    readString(violation.data);
    readString(violation.place);
    readString(violation.article);

    in.read(reinterpret_cast<char*>(&violation.fine), sizeof(violation.fine));
}
template<typename T>
void InsertViolationToBinStream(T& out, Violation& violation) {
    static_assert(
            std::is_same<T, std::stringstream>::value || std::is_same<T, std::fstream>::value,
            "T must be a stringstream or fstream"
    );

    auto writeString = [&](const std::string& str) {
        unsigned int length = str.size();
        out.write(reinterpret_cast<const char*>(&length), sizeof(length)); // Записываем длину
        out.write(str.data(), length); // Записываем данные строки
    };

    writeString(violation.carNumber);
    writeString(violation.name);
    writeString(violation.model);
    writeString(violation.data);
    writeString(violation.place);
    writeString(violation.article);

    out.write(reinterpret_cast<const char*>(&violation.fine), sizeof(violation.fine));
}

void ReplaceViolationInBinStream(std::fstream& out, Violation& violation, std::streampos pos, size_t old_record_size) {
    out.seekp(pos);

    InsertViolationToBinStream(out, violation);
}

void TextToBin(const std::string& s_text_file, const std::string& s_bin_file) {
    std::fstream out(s_bin_file, std::ios::binary | std::ios::out);
    std::fstream in(s_text_file, std::ios::in);

    std::string s;
    Violation violation;
    while (std::getline(in, s)) {
        violation.SetFieldsByStr(s);

        InsertViolationToBinStream(out, violation);
    }

    out.close();
    in.close();
}

void BinToText(const std::string& s_text_file, const std::string& s_bin_file) {
    std::fstream in(s_bin_file, std::ios::binary | std::ios::in);
    std::fstream out(s_text_file, std::ios::out);

    assert("Bin file is not open" && in.is_open() == true);
    assert("Text file is not open" && out.is_open() == true);

    Violation violation;
    while (true) {
        ExtractViolationFromBinStream(in, violation);

        if (in.eof())
            break;

        out << violation.ToString() <<'\n';
    }

    out.close();
    in.close();
}

void PrintAllViolationInBin(const std::string& s_bin_file) {
    std::fstream in(s_bin_file, std::ios::binary | std::ios::in);

    assert("Bin file is not open" && in.is_open() == true);

    Violation violation;
    while (true) {
        ExtractViolationFromBinStream(in, violation);

        if (in.eof())
            break;

        std::cout << violation.ToString() << '\n';
    }

    in.close();
}

// По первому вхождению
Violation GetViolationByNum(const std::string& s_bin_file, int num) {
    std::fstream in(s_bin_file, std::ios::binary | std::ios::in);

    assert("Bin file is not open" && in.is_open());

    int count = 0;
    Violation violation;
    while (true) {
        ExtractViolationFromBinStream(in, violation);

        if (in.eof())
            break;

        if (count == num)
            return violation;

        count++;
    }

    return {};
}

void DeleteViolationByCarNum(const std::string& s_bin_file, const std::string& s_car_num) {
    std::fstream file(s_bin_file, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);
    std::stringstream ss;

    assert("Bin file is not open" && file.is_open());

    size_t file_size = file.tellg();
    file.seekg(0);

    Violation violation;
    Violation last_violation;

    std::streampos pos_to_delete = -1;
    std::streampos last_record_pos = -1;
    std::streampos  cur_pos = std::ios::beg;

    while (cur_pos != file_size) {
        last_record_pos = cur_pos;
        ExtractViolationFromBinStream(file, violation);

        if (violation.carNumber == s_car_num && pos_to_delete == -1)
            pos_to_delete = cur_pos;

        last_violation = violation;
        cur_pos = file.tellg();
    }

    if (pos_to_delete == -1) {
        std::cerr << "Record not found" << '\n';
        return;
    }

    cur_pos = std::ios::beg;
    file.seekg(std::ios::beg);
    while (cur_pos != last_record_pos) {
        ExtractViolationFromBinStream(file, violation);

        if (cur_pos == pos_to_delete)
            InsertViolationToBinStream(ss, last_violation);
        else
            InsertViolationToBinStream(ss, violation);

        cur_pos = file.tellg();
    }

    file.seekp(std::ios::beg);
    file.write(ss.str().c_str(), ss.str().size());
    file.close();
}

void SelectionByCarNum(const std::string& s_source_bin, const std::string& s_new_bin, const std::string& s_car_num) {
    assert("No such file" && AreExist({s_source_bin}));

    std::fstream in(s_source_bin, std::ios::binary | std::ios::in);
    std::fstream out(s_new_bin, std::ios::binary | std::ios::out);

    assert("Source bin file is not open" && in.is_open());
    assert("New bin file is not open" && out.is_open());


    Violation violation;

    while (true) {
        ExtractViolationFromBinStream(in, violation);

        if (in.eof())
            break;

        if (violation.carNumber == s_car_num)
            InsertViolationToBinStream(out, violation);
    };

    in.close();
    out.close();
}

void DoubleFine(const std::string& s_bin_file, const std::string& s_start_date, const std::string& s_end_date, const std::string& article) {
    const std::string temp_file_name = "temp_file.bin";

    assert("No such file" && AreExist({s_bin_file}));

    std::fstream in(s_bin_file, std::ios::binary | std::ios::in);
    std::fstream out(temp_file_name, std::ios::binary | std::ios::out);

    assert("Bin file is not open" && in.is_open());
    assert("Temp Bin file is not open" && out.is_open());

    Violation violation;
    while (true) {
        ExtractViolationFromBinStream(in, violation);

        if (in.eof())
            break;

        if (s_start_date >= violation.data &&  violation.data <= s_end_date && violation.article == article)
            violation.fine *= 2;

        InsertViolationToBinStream(out, violation);
    }

    in.close();
    out.close();

    remove(s_bin_file.c_str());
    rename(temp_file_name.c_str(), s_bin_file.c_str());
}

#endif
