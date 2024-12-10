#ifndef CODE_BINFILEWORKER_H
#define CODE_BINFILEWORKER_H

#include <fstream>
#include <filesystem>
#include "ViolationRecord.h"
#include "BinarySearchTree.h"

namespace fs = std::filesystem;

class BinFileWorker {
private:
    fs::path bin_file_path;
    fs::path txt_file_path;

    BinFileWorker(const fs::path& txt_file_path, const fs::path& bin_file_path);

public:
    BinarySearchTree* tree = nullptr;
    static BinFileWorker* CreateInstance(const fs::path& txt_file_path, const fs::path& bin_file_path);
    static BinFileWorker* CreateInstance(const fs::path& txt_file_path);
    ~BinFileWorker();

    void TranslateToBin();
    void TranslateToTxt();
    void InitTreeByBin();
    void PrintTree();
    bool GetRecordByInd(size_t index, ViolationRecord& record);
    bool FindRecord(const std::string& car_number, ViolationRecord& record);
    void PrintBin();
    void RemoveInTree(const std::string& car_number) const;
    int FindInTree(const std::string& car_number) const;
    void AddToTree(std::string key, size_t ind);
};


#endif //CODE_BINFILEWORKER_H
