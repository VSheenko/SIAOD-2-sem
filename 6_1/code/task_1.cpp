#include "task_1.h"
#include <vector>

int main() {
    HashTable h;

    std::vector<ViolationData*> data {
            new ViolationData{"A123BC77", "Ivanov I.I.", "Toyota Camry", "15.09.2024", "ul. Lenina, d. 12", "12.9 ch.2", 500},
            new ViolationData{"B456OR77", "Petrov P.P.", "Hyundai Solaris", "18.09.2024", "pr. Mira, d. 8", "12.16 ch.3", 1000},
            new ViolationData{"C789KN77", "Smirnov A.A.", "Kia Rio", "20.09.2024", "ul. Pushkina, d. 5", "12.5 ch.1", 1500},
            new ViolationData{"D321OR99", "Sidorov V.V.", "Ford Focus", "12.09.2024", "ul. Gagarina, d. 7", "12.8 ch.2", 2000},
            new ViolationData{"E654TR77", "Kuznetsov N.N.", "Nissan Qashqai", "14.09.2024", "pr. Lomonosova, d. 22", "12.15 ch.4", 700},
            new ViolationData{"F987KR77", "Fedorov A.S.", "Mazda 3", "16.09.2024", "ul. Chaykovskogo, d. 9", "12.19 ch.1", 1200},
            new ViolationData{"G432NC77", "Morozov D.M.", "Volkswagen Polo", "19.09.2024", "pr. Sakharova, d. 4", "12.16 ch.1", 500},
            new ViolationData{"H654TM77", "Vasiliev I.V", "Skoda Octavia", "13.09.2024", "ul. Tolstogo, d. 10", "12.9 ch.2", 2500},
            new ViolationData{"K987RP77", "Nikolaev S.S", "Renault Duster", "17.09.2024", "ul. Chekhova, d. 15", "12.5 ch.2", 1800},
            new ViolationData{"L123BC77", "Zaitsev M.M.", "Lada Vesta", "21.09.2024", "ul. Gorkogo, d. 11", "12.6 ch.1", 900},
    };


    for (int i = 0; i < data.size(); i++) {
        InsertElem(h, data[i]);
    }

    PrintHashTable(h);

    DeleteElem(h, "D321OR99");

    std::cout << '\n';
    PrintHashTable(h);
}