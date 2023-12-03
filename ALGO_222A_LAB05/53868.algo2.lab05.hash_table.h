//
// Created by Владимир Марянчук on 26/11/2023.
//

#ifndef ALGO_222A_LAB05_HASH_TABLE_H
#define ALGO_222A_LAB05_HASH_TABLE_H

#endif //ALGO_222A_LAB05_HASH_TABLE_H

#define BASE 31

#include <iostream>
#include "53868.algo2.lab02.dynamic_array.h"
#include "53868.algo2.lab01.list.h"

struct item {
    std::string key;
    int value;
};

class hash_table {
private:
    dynamic_array<List<item> > *table;
    int max_length = 0;
    int size = 0;

    int get_max_length() {
        return table->get_size();
    }

    int hash_code(const std::string& key) {
        long int hash = 0;
        for (int i = 0, j = key.length(); i < key.length() & j > 0; ++i, j--) {
            int temp = (char) key[i];
            hash += temp * ::pow(BASE, j - 1);
        }
        return abs(hash % this->max_length);
    }

    void resize() {
        dynamic_array<List<item> > *new_table = new dynamic_array<List<item >>();
        this->size = 0;
        this->max_length = this->table->get_size();

        for (int i = 0; i < this->max_length; ++i) {
            List<item> new_list = *new List<item>;
            new_table->push(new_list);
        }

        for (int i = 0; i < this->table->get_size(); ++i) {
            for (int j = 0; j < this->table->operator[](i).length(); ++j) {
                item tmp_item = this->table->operator[](i).get(j);

                int hash = hash_code(tmp_item.key);
                new_table->operator[](hash).addFront(tmp_item);

                size++;
            }
        }

        delete this->table;
        this->table = new_table;
    }

    void fill_table() {
        for (int i = 0; i < this->table->get_size(); i++) {
            List<item> new_list = *new List<item>;
            this->table->push(new_list);
        }
    }


public:
    hash_table() : table(new dynamic_array<List<item>>()), max_length(get_max_length()) {
        fill_table();
    }

    hash_table(string key, int value) {
        this->table = new dynamic_array<List<item >>();
        this->max_length = this->get_max_length();
        fill_table();
        insert(key, value);
    }

    void insert(const std::string& key, int value) {
        if (max_length < size) {
            List<item> new_list;
            new_list.addFront({key, value});
            this->table->push(new_list);
            resize();
        } else {
            int hash = hash_code(key);
            this->table->operator[](hash).addFront({key, value});
            size++;
        }
    }

    void to_string() {
        cout << "hash table: ";
        cout << "\n\tcurrent_size: " << size;
        cout << "\n\tmax_size: " << max_length;
        cout << "\n\ttable:\n\t{";

        int non_null_lists = 0;
        int list_max_size = 0;
        int list_min_size = size;

        for (int i = 0; i < this->table->get_length(); i++) {
            auto row = this->table->operator[](i);
            if (row.length() > 0) {
                non_null_lists++;
                list_max_size = (row.length() > list_max_size) ? row.length() : list_max_size;
                list_min_size = (row.length() < list_min_size) ? row.length() : list_min_size;

                ::printf("\n\t\t%d: ", i);
                for (int j = 0; j < row.length(); j++) {
                    std::cout << row.get(j).key << " -> " << row.get(j).value;
                }
                ::printf(";");
            }
        }
        double avg_size = (non_null_lists > 0) ? size / static_cast<double>(non_null_lists) : 0;
        cout << "\n\t}";
        cout << "\n\tstats:";
        cout << "\n\t\tlist min size: " << list_min_size;
        cout << "\n\t\tlist max size: " << list_max_size;
        cout << "\n\t\tnon-null lists: " << non_null_lists;
        cout << "\n\t\tlist avg size: " << avg_size;
    }


    int search(std::string key) {
        int hash = hash_code(key);
        try {
            if (hash > max_length) { throw 1; }

            List<item> tmp_list = this->table->operator[](hash);
            for (int i = 0; i < tmp_list.length(); ++i) {
                item tmp_item = tmp_list.get(i);
                if (tmp_item.key == key) return tmp_item.value;
            }
            throw 1;
        } catch (int err) {
//            std::cerr << "Incorrect key";
            return -1;
        }
    }

    void delete_item(std::string key) {
        int hash = hash_code(key);
        try {
            if (hash > max_length) { throw 1; }
            for (int i = 0; i < this->table->get_length(); i++) {
                auto row = this->table->operator[](i);
                if (row.length() > 0) {
                    for (int j = 0; j < row.length(); j++) {
                        if (row.get(j).key == key) {
                            row.remove(j);
                            return;
                        }
                    }
                }
                throw 1;
            }
        } catch (int err) {
            std::cerr << "Incorrect key";
        }
    }

    void clear() {
        if (size == 0) return;
        for (int i = 0; i < this->table->get_length(); i++) {
            this->table->operator[](i).clear();
        }
    }

    virtual ~hash_table() {
        clear();
    }
};
