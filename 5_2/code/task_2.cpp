#include "BinFileWorker.h"


int main() {
    std::string bin_file_name;
    std::string text_file_name;

    std::cout << "Enter the name of the binary file: ";
    std::cin >> bin_file_name;
    std::cout << "Enter the name of the text file: ";
    std::cin >> text_file_name;

    int mode = 0;

    std::cout << "1. Convert text to binary\n"
                 "2. Convert binary to text\n"
                 "3. Print all violations in binary\n"
                 "4. Get violation by number\n"
                 "5. Delete violation by number\n"
                 "6. Doubling fines for violations by date and article\n"
                 "7. Create selection violations by car number\n"
                 "8. Exit\n";

    std::cout << "Enter the mode: ";
    std::cin >> mode;
    while (mode != 8) {
        std::string num;
        switch (mode) {
            case 1:
                TextToBin(text_file_name, bin_file_name);
                break;
            case 2:
                BinToText(text_file_name, bin_file_name);
                break;
            case 3:
                PrintAllViolationInBin(bin_file_name);
                break;
            case 4: {
                std::cout << "Enter the number of the violation: ";
                int ord_num;
                std::cin >> ord_num;

                bool code = false;
                std::string s = GetViolationByOrdinalNum(bin_file_name, ord_num, code);

                if (code)
                    std::cout << s << '\n';
                else
                    std::cerr << "No such violation\n";

                break;
            }
            case 5: {
                std::cout << "Enter the number of the violation: ";
                std::cin >> num;
                DeleteViolationByCarNum(bin_file_name, num);
                break;
            }
            case 6: {
                std::string start_date;
                std::string end_date;
                std::string article;

                std::cout << "Enter the start date: ";
                std::cin >> start_date;
                std::cout << "Enter the end date: ";
                std::cin >> end_date;
                std::cout << "Enter the article: ";

                std::cin >> std::ws;
                std::getline(std::cin, article);

                DoubleFine(bin_file_name, start_date, end_date, article);
                break;
            }
            case 7: {
                std::string file_name;

                std::cout << "Enter the car number: ";
                std::cin >> num;

                std::cout << "Enter the name of the new file: ";
                std::cin >> file_name;

                SelectionByCarNum(bin_file_name, file_name, num);
                break;
            }
            default:
                std::cout << "Invalid mode\n";
                break;
        }
        std::cout << "\nEnter the mode: ";
        std::cin >> mode;
    }
}
