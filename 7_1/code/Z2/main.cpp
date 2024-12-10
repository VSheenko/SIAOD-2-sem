#include "BinFileWorker.h"
#include <iostream>

int main() {
    BinFileWorker *worker = BinFileWorker::CreateInstance("example.txt");
    int mode;

    std::cout << "1. FindInTree\n" <<
                 "2. Remove\n" <<
                 "3. Print\n" <<
                 "4. Get rotations\n" <<
                 "5. Exit\n";
    std::cin >> mode;

    size_t ind;
    std::string key;
    while (mode != 5) {
        switch (mode) {
            case 1:
                std::cout << "Enter key: ";
                std::cin >> key;
                ViolationRecord r;
                if (worker->FindRecord(key, r))
                    std::cout << "Found: " << r.ToString() << std::endl;
                else
                    std::cout << "Not found" << std::endl;
                break;
            case 2:
                std::cout << "Enter key: ";
                std::cin >> key;
                worker->RemoveFromTree(key);
                break;
            case 3:
                worker->PrintTree();
                break;
            case 4:
                std::cout << "Rotations: " << worker->GetRotations() << std::endl;
                break;
            default:
                std::cout << "Invalid mode" << std::endl;
                break;
        }

        std::cout << "1. FindInTree\n" <<
                  "2. Remove\n" <<
                  "3. Print\n" <<
                  "4. Get rotations\n" <<
                  "5. Exit\n";
        std::cin >> mode;


    }
}
