#include <iostream>
#include "BinFileWorker.h"


int main() {
    BinFileWorker *worker = BinFileWorker::CreateInstance("example.txt");
    int mode;

    std::cout << "1. Insert to tree\n"
                 "2. Find In Tree\n" <<
                 "3. Remove from tree\n" <<
                 "4. Print tree\n" <<
                 "5. Exit\n";
    std::cin >> mode;

    size_t ind;
    std::string key;
    while (mode != 5) {
        switch (mode) {
            case 1:
                std::cout << "Enter key and ind: ";
                std::cin >> key >> ind;
                worker->AddToTree(key, ind);
                break;
            case 2:
                std::cout << "Enter key: ";
                std::cin >> key;
                ViolationRecord r;
                if (worker->FindRecord(key, r))
                    std::cout << "Found: " << r.ToString() << std::endl;
                else
                    std::cout << "Not found" << std::endl;
                break;
            case 3:
                std::cout << "Enter key: ";
                std::cin >> key;
                worker->RemoveInTree(key);
                break;
            case 4:
                worker->PrintTree();
                break;
            default:
                std::cout << "Invalid mode" << std::endl;
                break;
        }

        std::cout << "1. Insert to tree\n"
                     "2. FindInTree\n" <<
                     "3. Remove from tree\n" <<
                     "4. Print tree\n" <<
                     "5. Exit\n";
        std::cin >> mode;
    }
}
