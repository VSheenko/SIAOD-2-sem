#include "FileWorker.h"
#include <filesystem>

void input_open (std::ifstream& in_file, const std::string& file_name) {
    in_file = std::ifstream(file_name);

    if (!in_file.is_open()) {
        std::cerr << "File not opened\n";
        exit(1);
    }

}

void output_open (std::ofstream& out_file, const std::string& file_name, std::ios::openmode mode) {
    out_file = std::ofstream(file_name, mode);

    if (!out_file.is_open()) {
        std::cerr << "File not opened\n";
        exit(1);
    }
}

int main () {
    std::string file_name;
    std::cout << "Enter the name of the file: ";
    std::cin >> file_name;

    if (!(std::filesystem::exists(file_name))) {
        std::cerr << "File not found\n";
        return 1;
    }

    int mode = 0;
    std::cout << "1. Print all content\n"
                 "2. Append content\n"
                 "3. Get number by ordinal\n"
                 "4. Count numbers\n"
                 "5. Partition and merge content\n"
                 "6. Exit\n";

    std::cout << "Enter the mode: ";
    std::cin >> mode;
    while (mode != 6) {
        switch (mode) {
            case 1: {
                std::ifstream in_file;
                input_open(in_file, file_name);
                PrintFileContent(in_file);

                std::cout << "std::ios::good ==> " << in_file.good() << '\n';
                in_file.close();
                break;
            }
            case 2: {
                std::ofstream out_file;
                output_open(out_file, file_name, std::ios::app);

                std::string num;
                std::cout << "Enter the number: ";
                std::cin >> num;

                AppendContentToFile(out_file, num);

                std::cout << "std::ios::good ==>" << out_file.good() << '\n';
                out_file.close();
                break;
            }
            case 3: {
                int ordinal_num;
                std::cout << "Enter the ordinal number: ";
                std::cin >> ordinal_num;

                std::ifstream in_file;
                input_open(in_file, file_name);

                bool SUCCESS_CODE = true;
                int res = GetNumByOrdinal(in_file, ordinal_num, SUCCESS_CODE);

                if (SUCCESS_CODE) {
                    std::cout << "Number: " << res << '\n';
                } else {
                    std::cerr << "Number not found\n";
                }

                std::cout << "std::ios::good ==>" << in_file.good() << '\n';
                in_file.close();
                break;
            }
            case 4: {
                std::ifstream in_file;
                input_open(in_file, file_name);

                std::cout << "Count: " << CountNum(in_file) << '\n';
                std::cout << "std::ios::good ==>" << in_file.good() << '\n';
                in_file.close();
                break;
            }
            case 5: {
                std::ifstream in_file;
                input_open(in_file, file_name);
                Partition(in_file);
                std::cout << "1, std::ios::good ==>" << in_file.good() << '\n';
                in_file.close();

                std::ofstream out_file;
                output_open(out_file, file_name, std::ios::out);
                Merge(out_file);
                std::cout << "2, std::ios::good ==>" << out_file.good() << '\n';
                out_file.close();
                break;
            }
        }
        std::cout << "\nEnter the mode: ";
        std::cin >> mode;
    }
}