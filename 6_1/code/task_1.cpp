#include "task_1.h"
#include <vector>
#include <variant>

template<class T>
using decay_t = std::decay<T>::type;


int main() {

    HashTable h;



    std::vector<std::vector<std::variant<std::string, int>>> data {
            {"A123BC77", "Ivanov I.I.", "Toyota Camry", "15.09.2024", "ul. Lenina, d. 12", "12.9 ch.2", 500},
            {"B456OR77", "Petrov P.P.", "Hyundai Solaris", "18.09.2024", "pr. Mira, d. 8", "12.16 ch.3", 1000},
            {"C789KN77", "Smirnov A.A.", "Kia Rio", "20.09.2024", "ul. Pushkina, d. 5", "12.5 ch.1", 1500},
            {"D321OR99", "Sidorov V.V.", "Ford Focus", "12.09.2024", "ul. Gagarina, d. 7", "12.8 ch.2", 2000},
            {"E654TR77", "Kuznetsov N.N.", "Nissan Qashqai", "14.09.2024", "pr. Lomonosova, d. 22", "12.15 ch.4", 700},
            {"F987KR77", "Fedorov A.S.", "Mazda 3", "16.09.2024", "ul. Chaykovskogo, d. 9", "12.19 ch.1", 1200},
            {"G432NC77", "Morozov D.M.", "Volkswagen Polo", "19.09.2024", "pr. Sakharova, d. 4", "12.16 ch.1", 500},
            {"H654TM77", "Vasiliev I.V", "Skoda Octavia", "13.09.2024", "ul. Tolstogo, d. 10", "12.9 ch.2", 2500},
            {"K987RP77", "Nikolaev S.S", "Renault Duster", "17.09.2024", "ul. Chekhova, d. 15", "12.5 ch.2", 1800},
            {"L123BC77", "Zaitsev M.M.", "Lada Vesta", "21.09.2024", "ul. Gorkogo, d. 11", "12.6 ch.1", 900},
    };


    for (int i = 0; i < data.size(); i++) {
       InsertElem(h, std::visit([](auto&& arg) -> std::string {
            if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, int>) {
                return std::to_string(arg);
            } else {
                return arg;
            }
        }, data[i][0]), i);
    }

    PrintHashTable(h);

    DeleteElem(h, "D321OR99");

    std::cout << '\n';
    PrintHashTable(h);

    std::cout << FindElem(h, "H654TM77") <<'\n';
}