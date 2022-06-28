//
// Created by rudri on 6/24/2022.
//

#ifndef PROG3_HASH_TABLES_LAB101_2022_1_OHASH_H
#define PROG3_HASH_TABLES_LAB101_2022_1_OHASH_H

#include <functional>
#include <vector>
#include <memory>

// Tipo de dato que almacene data en el slot
template <typename KeyType, typename ValueType>
using item_t = std::pair<KeyType, ValueType>;

template <typename KeyType, typename ValueType>
using bucket_t = std::vector<std::shared_ptr<item_t<KeyType, ValueType>>>;

template <typename KeyType, typename ValueType>
class open_hash_table {
    size_t m = 0;
    bucket_t<KeyType, ValueType> table;

    size_t linear_probing(KeyType key, size_t i) {
        std::hash<KeyType> pre_hash_fun;
        return (pre_hash_fun(key) + i) % m;
    }

public:
    explicit open_hash_table(size_t m): m(m), table(m) {}
    // Método de inserción
    std::pair<std::shared_ptr<item_t<KeyType, ValueType>>, bool> insert(const item_t<KeyType, ValueType>& item) {
        size_t i = 0, idx = 0;
        do {
            // Indice initial
            idx = linear_probing(item.first, i++);
            // Definir el limite i
            if (i >= size(table))
                return {nullptr, false};
            // Si encuentra alguno igual
            if (table[idx] && table[idx]->first == item.first)
                return {nullptr, false};
        } while (table[idx]);
        // Si no encuentra valores (Si encontró un slot vacío)
        table[idx] = std::make_shared<item_t<KeyType, ValueType>>(item);
        return {table[idx], true};
    }

    // Método de Búsqueda
    std::pair<std::shared_ptr<item_t<KeyType, ValueType>>, bool> find(const KeyType key) {
        size_t i = 0, idx = 0;
        do {
            // Indice initial
            idx = linear_probing(key, i++);
            // Definir el limite i
            if (i >= size(table))
                return {nullptr, false};
            // Si encuentra alguno igual
            if (table[idx] && table[idx]->first == key)
                return {table[idx], true};
        } while (table[idx]);
        return {nullptr, false};
    }
    // Método de Borrado
    bool remove(const KeyType key) {
        size_t i = 0, idx = 0;
        // Buscar el valor a borrar
        do {
            idx = linear_probing(key, i++);
            // Definir el limite i
            if (i >= size(table))
                return false;
        } while (table[idx] && table[idx]->first != key);
        // Si lo encuentra
        if (table[idx] && table[idx]->first == key)
            table[idx] = nullptr;
        else
            return false;
        // Si lo encuentra, debe reubicar el resto de valores
        auto next_idx = linear_probing(key, i);
        do {
            if (table[next_idx] && next_idx == linear_probing(table[next_idx]->first, i++)) {
                swap(table[idx], table[next_idx]);
                idx = next_idx;
            }
            if (i >= size(table))
                break;
            next_idx = linear_probing(key, i);
        } while (table[next_idx]);
        return true;
    }
};

#endif //PROG3_HASH_TABLES_LAB101_2022_1_OHASH_H
