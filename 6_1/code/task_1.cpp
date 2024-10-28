#include "task_1.h"
#include <vector>
#include <variant>

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
            {"N038EK34", "Korolev V.V.", "Mazda 6", "10.05.2024", "ul. Tolstogo, d. 15", "12.6 p.1", 2312},
            {"P743YA23", "Volkov S.A.", "Ford Explorer", "27.11.2024", "ul. Parkovaya, d. 28", "12.16 p.3", 939},
            {"S990RG77", "Ivanov I.I.", "Toyota Land Cruiser", "21.07.2024", "ul. Chekhova, d. 15", "12.5 p.3", 2990},
            {"D370JF50", "Matveev A.I.", "Audi A6", "03.11.2024", "ul. Zhukova, d. 8", "12.5 p.2", 524},
            {"K810RX23", "Mikhailov E.E.", "Volkswagen Polo", "29.07.2024", "ul. Shkolnaya, d. 19", "12.9 p.1", 3432 },
            {"K079CD50", "Grishin S.G.", "Honda Accord", "22.02.2024", "ul. Tsvetochnaya, d. 17", "12.9 p.2", 1050},
            {"J997UO50", "Matveev A.I.", "Chevrolet Cruze", "16.08.2024", "ul. Shkolnaya, d. 4", "12.19 p.3", 702},
            {"K711DK23", "Popov I.I.", "Kia Rio", "29.11.2024", "ul. Solnechnaya, d. 8", "12.15 p.4", 1792},
            {"T735YE50", "Vinogradov E.E.", "BMW X3", "28.08.2024", "ul. Molodezhnaya, d. 26", "12.9 p.2", 3446},
            {"B597LW61", "Loginov O.N.", "Lada XRay", "13.03.2024", "ul. Gagarina, d. 27", "12.15 p.4", 3110},
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
    std::cout << FindElem(h, "H654TM77") <<'\n' << '\n';

    DeleteElem(h, "C789KN77");
    PrintHashTable(h);

    std::cout << FindElem(h, "P743YA23") << '\n' << '\n'; // Поиск после удаленного элемента
}