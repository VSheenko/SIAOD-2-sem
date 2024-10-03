#include "FileWorker.h"
#include <filesystem>
#include "BinFileWorker.h"

namespace fs = std::filesystem;


int main() {
    std::string s_file_name = "Z:\\MIREA\\SIAOD2\\5_2\\code\\cmake-build-debug\\z2_text";

    TextToBin(s_file_name, "file.bin");
    DeleteViolationByCarNum("file.bin", "Mп456OR77");
    BinToText("file_new.txt", "file.bin");
//    PrintAllViolationInBin("file.bin");
}
