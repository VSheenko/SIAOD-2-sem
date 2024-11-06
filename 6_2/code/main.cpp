#include <iostream>
#include "BST.h"

int main() {
    BST tree;
    BST tree2;
    bool isFirst = true;

    std::cout << "Cureent tree: " << (isFirst ? "\"tree\"" : "\"tree2\"") << '\n' <<
                 "1. InsertElem\n" <<
                 "2. InitTree\n" <<
                 "3. PrintTree\n" <<
                 "4. SpecCount\n" <<
                 "5. IsDegenerate\n" <<
                 "6. Copy to other tree\n" <<
                 "7. Swap tree\n" <<
                 "8. Exit\n";

    int mode;
    std::cin >> mode;
    while (mode != 8) {
        switch (mode) {
            case 1: {
                std::cout << "Enter string (key): ";
                std::string str;
                std::cin >> str;

                if (isFirst)
                    tree.InsertElem(str);
                else
                    tree2.InsertElem(str);

                break;
            }
            case 2: {
                std::cout << "Enter number of elements: ";
                int n;
                std::cin >> n;
                std::vector<std::string> elems(n);
                std::cout << "Enter elements: ";
                for (int i = 0; i < n; i++)
                    std::cin >> elems[i];

                if (isFirst)
                    tree.InitTree(elems);
                else
                    tree2.InitTree(elems);

                break;
            }
            case 3: {
                if (isFirst)
                    tree.PrintTree();
                else
                    tree2.PrintTree();

                break;
            }
            case 4: {
                if (isFirst)
                    std::cout << tree.SpecCount(3) << '\n';
                else
                    std::cout << tree2.SpecCount(3) << '\n';

                break;
            }
            case 5: {
                if (isFirst)
                    std::cout << std::boolalpha << tree.IsDegenerate() << '\n';
                else
                    std::cout << std::boolalpha << tree2.IsDegenerate() << '\n';

                break;
            }
            case 6: {
                if (isFirst)
                    tree2.CopyTree(tree);
                else
                    tree.CopyTree(tree2);

                break;
            }
            case 7: {
                isFirst = !isFirst;
                std::cout << "Cureent tree: " << (isFirst ? "\"tree\"" : "\"tree2\"") << '\n' <<
                          "1. InsertElem\n" <<
                          "2. InitTree\n" <<
                          "3. PrintTree\n" <<
                          "4. SpecCount\n" <<
                          "5. IsDegenerate\n" <<
                          "6. Copy to other tree\n" <<
                          "7. Swap tree\n" <<
                          "8. Exit\n";
                break;
            }
            default:
                std::cout << "Invalid mode\n";
        }

        std::cout << "Enter mode: ";
        std::cin >> mode;
    }
}
