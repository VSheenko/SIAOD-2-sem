#include <iostream>
#include "BinFileWorker.h"


int main() {
    BinFileWorker *worker = BinFileWorker::CreateInstance("example.txt");

    ViolationRecord record{};
    worker->FindRecord("B597LW61", record);
    std::cout << record.ToString() << std::endl;

    delete worker;
}
