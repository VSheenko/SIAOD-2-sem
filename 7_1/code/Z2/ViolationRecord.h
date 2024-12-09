
#ifndef CODE_VIOLATIONRECORD_H
#define CODE_VIOLATIONRECORD_H

#include <vector>
#include <string>
#include <cstring>

inline std::vector<std::string> Split(std::string s, const std::string& separator) {
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

struct ViolationRecord {
    char carNumber[16];
    char name[32];
    char model[32];
    char data[32];
    char place[32];
    char article[32];
    short fine;

    ViolationRecord() = default;
    bool SetFieldsByStr(const std::string& s) {
        std::vector<std::string> tokens = Split(s, ";");

        if (tokens.size() != 7) {
            return false;
        }

        strcpy(carNumber, tokens[0].c_str());
        strcpy(name, tokens[1].c_str());
        strcpy(model, tokens[2].c_str());
        strcpy(data, tokens[3].c_str());
        strcpy(place, tokens[4].c_str());
        strcpy(article, tokens[5].c_str());
        fine = std::stoi(tokens[6]);

        return true;
    }

    std::string ToString() {
        std::string res;

        res = carNumber + std::string(";") + name + std::string(";") + model + std::string(";") +
              data + std::string(";") + place + std::string(";") + article + std::string(";") +
              std::to_string(fine) + std::string(";");

        return res;
    }

    bool Validate() {
        return carNumber[0] != '\0' && name[0] != '\0' && model[0] != '\0' && data[0] != '\0' &&
               place[0] != '\0' && article[0] != '\0' && fine != 0;
    }
};

#endif //CODE_VIOLATIONRECORD_H
