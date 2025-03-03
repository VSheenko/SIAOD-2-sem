#ifndef CODE_BINFILEWORKER_H
#define CODE_BINFILEWORKER_H

#include <fstream>
#include <filesystem>
#include "ViolationRecord.h"
#include "SplayTree.h"

namespace fs = std::filesystem;

class BinFileWorker {
private:
    fs::path bin_file_path;
    fs::path txt_file_path;

    SplayTree* tree = nullptr;

    BinFileWorker(const fs::path& txt_file_path, const fs::path& bin_file_path);
public:
    static BinFileWorker* CreateInstance(const fs::path& txt_file_path, const fs::path& bin_file_path);
    static BinFileWorker* CreateInstance(const fs::path& txt_file_path);
    ~BinFileWorker();

    void RemoveFromTree(const std::string& key);
    void TranslateToBin();
    void TranslateToTxt();
    void InitTreeByBin();
    void PrintTree();
    bool GetRecordByInd(size_t index, ViolationRecord& record);
    bool FindRecord(const std::string& car_number, ViolationRecord& record);
    int GetRotations();
    void PrintBin();
};


#endif //CODE_BINFILEWORKER_H
