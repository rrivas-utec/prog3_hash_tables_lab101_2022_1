#include <iostream>
#include <functional>
#include "chash.h"
#include "ohash.h"
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
    close_hash_table<string, int> ch(10);

    auto [item_1, inserted_1] = ch.insert({"A", 1});
    if (inserted_1)
        cout << "Valor insertado: {" << item_1->first << ", " << item_1->second << "}\n";
    else
        cout << "No inserto\n";

    auto [item_2, inserted_2] = ch.insert({"A", 20});
    if (inserted_2)
        cout << "Valor insertado: {" << item_2->first << ", " << item_2->second << "}\n";
    else
        cout << "No inserto\n";

    ch.insert({"B", 2});
    ch.insert({"C", 3});

    auto [item_3, found_3] = ch.find("B");
    if (found_3)
        cout << "Valor Encontrado: {" << item_3->first << ", " << item_3->second << "}\n";
    else
        cout << "No Encontrado\n";

    auto removed = ch.remove("Z");
    if (removed)
        cout << "Removido\n";
    else
        cout << "No Removido\n";

    removed = ch.remove("B");
    if (removed)
        cout << "Removido\n";
    else
        cout << "No Removido\n";
}

void ejemplo_open_hash() {
    open_hash_table<string, int> oh(10);

    auto result = oh.insert({"A", 1});
    if (result.second)
        cout << "Valor insertado: {" << result.first->first << ", " << result.first->second << "}\n";
    else
        cout << "No inserto\n";

    result = oh.insert({"A", 20});
    if (result.second)
        cout << "Valor insertado: {" << result.first->first << ", " << result.first->second << "}\n";
    else
        cout << "No inserto\n";

    result = oh.insert({"B", 2});
    if (result.second)
        cout << "Valor insertado: {" << result.first->first << ", " << result.first->second << "}\n";
    else
        cout << "No inserto\n";

    result = oh.insert({"C", 3});
    if (result.second)
        cout << "Valor insertado: {" << result.first->first << ", " << result.first->second << "}\n";
    else
        cout << "No inserto\n";

    result = oh.find("B");
    if (result.second)
        cout << "Valor Encontrado: {" << result.first->first << ", " << result.first->second << "}\n";
    else
        cout << "No Encontrado\n";

    auto removed = oh.remove("Z");
    if (removed)
        cout << "Removido\n";
    else
        cout << "No Removido\n";

    removed = oh.remove("B");
    if (removed)
        cout << "Removido\n";
    else
        cout << "No Removido\n";

    result = oh.find("B");
    if (result.second)
        cout << "Valor Encontrado: {" << result.first->first << ", " << result.first->second << "}\n";
    else
        cout << "No Encontrado\n";
}

int main() {
//    ejemplo_hash();
    ejemplo_close_hash();
    std::cout << "---\n";
    ejemplo_open_hash();
    return 0;
}
