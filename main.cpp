#include <iostream>
#include <functional>
#include "chash.h"
using namespace std;

void ejemplo_hash() {
    std::hash<int> hi;
    std::hash<string> hs;
    std::hash<bool> hb;

    cout << hi(123) << endl;
    cout << hi(234) << endl;
    cout << hs("Hola Mundo") << endl;
    cout << hs("Hola Mundi") << endl;
    cout << hb(true) << endl;
    cout << hb(false) << endl;
}

void ejemplo_close_hash() {
    close_hash_table<string, int> ht(10);

    auto [item_1, inserted_1] = ht.insert({"A", 1});
    if (inserted_1)
        cout << "Valor insertado: {" << item_1->first << ", " << item_1->second << "}\n";
    else
        cout << "No inserto\n";

    auto [item_2, inserted_2] = ht.insert({"A", 20});
    if (inserted_2)
        cout << "Valor insertado: {" << item_2->first << ", " << item_2->second << "}\n";
    else
        cout << "No inserto\n";

    ht.insert({"B", 2});
    ht.insert({"C", 3});

    auto [item_3, found_3] = ht.find("B");
    if (found_3)
        cout << "Valor Encontrado: {" << item_3->first << ", " << item_3->second << "}\n";
    else
        cout << "No Encontrado\n";

    auto removed = ht.remove("Z");
    if (removed)
        cout << "Removido\n";
    else
        cout << "No Removido\n";

    removed = ht.remove("B");
    if (removed)
        cout << "Removido\n";
    else
        cout << "No Removido\n";

}

int main() {
//    ejemplo_hash();
    ejemplo_close_hash();
    return 0;
}
