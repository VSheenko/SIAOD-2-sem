#include "BinFileWorker.h"


BinFileWorker *BinFileWorker::CreateInstance(const fs::path& txt_file_path, const fs::path& bin_file_path) {
    if (!fs::exists(txt_file_path))
        return nullptr;

    if (!fs::exists(bin_file_path))
        return nullptr;

    return new BinFileWorker(txt_file_path, bin_file_path);
}

BinFileWorker *BinFileWorker::CreateInstance(const fs::path &txt_file_path) {
    if (!fs::exists(txt_file_path))
        return nullptr;

    fs::path bin_file = txt_file_path.parent_path() / (txt_file_path.stem().string() + ".bin");
    std::ofstream file(bin_file);

    if (!file.is_open())
        return nullptr;
    file.close();

    return new BinFileWorker(txt_file_path, bin_file);
}

BinFileWorker::BinFileWorker(const fs::path &txt_file_path, const fs::path &bin_file_path) {
    this->txt_file_path = txt_file_path;
    this->bin_file_path = bin_file_path;

    TranslateToBin();

    tree = new SplayTree();
    InitTreeByBin();
}

BinFileWorker::~BinFileWorker() {
    delete tree;
}

void BinFileWorker::TranslateToBin() {
    std::fstream txt_file(txt_file_path, std::ios::in);
    std::fstream bin_file(bin_file_path, std::ios::out | std::ios::binary);

    if (!txt_file.is_open() || !bin_file.is_open())
        throw std::runtime_error("TranslateToBin-> Can't open file");

    std::string s;
    ViolationRecord violation{};

    while (std::getline(txt_file, s)) {
        violation.SetFieldsByStr(s);

        if (!violation.Validate())
            throw std::runtime_error("TranslateToBin-> Invalid record: " + s);

        bin_file.write((char*)&violation, sizeof(ViolationRecord));
    }

    txt_file.close();
    bin_file.close();
}

void BinFileWorker::TranslateToTxt() {
    std::fstream txt_file(txt_file_path, std::ios::out);
    std::fstream bin_file(bin_file_path, std::ios::in | std::ios::binary);

    if (!txt_file.is_open() || !bin_file.is_open())
        throw std::runtime_error("TranslateToTxt-> Can't open file");

    ViolationRecord violation{};

    while (bin_file.read((char*)&violation, sizeof(ViolationRecord))) {
        txt_file << violation.ToString() << std::endl;
    }

    bin_file.close();
    txt_file.close();
}

void BinFileWorker::InitTreeByBin() {
    if (!tree)
        throw std::runtime_error("InitTreeByBin-> Tree is not initialized");

    std::fstream bin_file(bin_file_path, std::ios::in | std::ios::binary);
    if (!bin_file.is_open())
        throw std::runtime_error("InitTreeByBin-> Can't open file");

    ViolationRecord violation{};
    size_t ind = 0;

    while (bin_file.read((char*)&violation, sizeof(ViolationRecord))) {
        tree->Insert(violation.carNumber, ind++);
    }

    bin_file.close();
}

void BinFileWorker::PrintTree() {
    tree->PrintTree();
}

bool BinFileWorker::GetRecordByInd(size_t index, ViolationRecord &record) {
    std::fstream bin_file(bin_file_path, std::ios::binary | std::ios::in | std::ios::out | std::ios::ate);

    if (!bin_file.is_open()) {
        return false;
    }

    size_t file_size = fs::file_size(bin_file_path);
    bin_file.seekg(0, std::ios::beg);
    int violations_count = file_size / sizeof(ViolationRecord);

    if (index > violations_count - 1) {
        return false;
    }

    std::streampos record_pos = index * sizeof(ViolationRecord);
    bin_file.seekg(record_pos, std::ios::beg);

    bin_file.read((char*)&record, sizeof(ViolationRecord));
    return true;
}

bool BinFileWorker::FindRecord(const std::string &car_number, ViolationRecord &record) {
    if (!tree)
        throw std::runtime_error("FindRecord-> Tree is not initialized");

    size_t index;
    if (!tree->Find(car_number, index))
        return false;

    return GetRecordByInd(index, record);
}

void BinFileWorker::RemoveFromTree(const std::string &key) {
    if (!tree)
        throw std::runtime_error("RemoveFromTree-> Tree is not initialized");

    tree->Remove(key);
}

int BinFileWorker::GetRotations() {
    return tree->rotations;
}
