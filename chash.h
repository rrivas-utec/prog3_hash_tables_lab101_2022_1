//
// Created by rudri on 6/23/2022.
//

#ifndef PROG3_HASH_TABLES_LAB101_2022_1_CHASH_H
#define PROG3_HASH_TABLES_LAB101_2022_1_CHASH_H

#include <functional>
#include <forward_list>

// template de funcion hash
template<typename T>
size_t hash_function(T key, size_t m) {
    std::hash<T> pre_hash_fun;
    auto numeric_key = pre_hash_fun(key);
    return numeric_key % m;
}

// tipos de apoyo
template <typename KeyType, typename ValueType>
using item_t = std::pair<KeyType, ValueType>;

template <typename KeyType, typename ValueType>
using chain_t = std::forward_list<item_t<KeyType, ValueType>>;

template <typename KeyType, typename ValueType>
class close_hash_table {
    size_t m = 0;
    chain_t<KeyType, ValueType>* table = nullptr;
public:
    explicit close_hash_table(size_t m): m(m) {
        table = new chain_t<KeyType, ValueType>[m];
    }
    ~close_hash_table() {
        delete [] table;
    }

    close_hash_table(const close_hash_table<KeyType, ValueType> &other): m(other.m) {
        table = new chain_t<KeyType, ValueType>[m];
        copy(other.table, other.table + m, table);
    }

    close_hash_table<KeyType, ValueType>& operator=(const close_hash_table<KeyType, ValueType> &other) {
        if (&other == this) return *this;
        delete [] table;
        m = other.m;
        table = new chain_t<KeyType, ValueType>[m];
        copy(other.table, other.table + m, table);
        return *this;
    }

    // Inserción
    std::pair<item_t<KeyType, ValueType>*, bool> insert(const item_t<KeyType, ValueType>& item) {
        // Buscar el slot
        auto index_slot = hash_function(item.first, m);
        // Obtenemos la referencia a la cadena dentro de ese slot;
        auto& chain = table[index_slot];
        // Buscar el key dentro la cadena
        auto it = std::find_if(begin(chain), end(chain), [item](const auto& current){
            return item.first == current.first;
        });
        // Retornar el par ordenado
        if (it == end(chain)) {
            chain.push_front(item);
            return {&chain.front(), true};
        }
        return {nullptr, false};
    }

    // Búsqueda
    std::pair<item_t<KeyType, ValueType>*, bool> find(const KeyType& key) {
        // Buscar el slot
        auto index_slot = hash_function(key, m);
        // Obtenemos la referencia a la cadena dentro de ese slot;
        auto& chain = table[index_slot];
        // Buscar el key
        auto it = std::find_if(begin(chain), end(chain), [key](const auto& current){
            return key == current.first;
        });
        // Si lo encuentra
        if (it != end(chain)) {
            return {&(*it), true};
        }
        return {nullptr, false};
    }

    // Borrado
    bool remove(const KeyType& key) {
        // Buscar el slot
        auto index_slot = hash_function(key, m);
        // Obtenemos la referencia a la cadena dentro de ese slot;
        auto& chain = table[index_slot];
        // Remover el valor
        auto old_size = std::distance(begin(chain), end(chain));
        chain.remove_if([key](const auto& current){
            return key == current.first;
        });
        auto new_size = std::distance(begin(chain), end(chain));
        return new_size < old_size;
    }
};

#endif //PROG3_HASH_TABLES_LAB101_2022_1_CHASH_H
