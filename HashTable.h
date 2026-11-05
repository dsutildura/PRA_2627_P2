#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"
#include "../../practica1/PRA_2627_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {
    private:
        int n; // Número de elementos almacenados
        int max; // Tamaño de la tabla hash (capacidad)
        ListLinked<TableEntry<V>>* table; // Array de punteros a ListLinked

        // Función Hash
        int h(std::string key) {
            int suma = 0;
            for (size_t i = 0; i < key.length(); i++) {
                suma += int(key.at(i));
            }
            return suma % max;
        }

    public:
        // Constructor
        HashTable(int size) {
            n = 0;
            max = size;
            table = new ListLinked<TableEntry<V>>[max];
        }

        // Destructor
        ~HashTable() override {
            delete[] table;
        }

        // Métodos de la interfaz Dict
        void insert(std::string key, V value) override {
            int pos = h(key);
            TableEntry<V> entry(key, value);
            
            // Comprobamos si la clave ya existe usando el método search de la lista
            // Como TableEntry sobrecarga ==, buscará por clave.
            int index = table[pos].search(entry); 
            if (index != -1) {
                throw std::runtime_error("Key '" + key + "' already exists!");
            }
            
            table[pos].prepend(entry); // O insert(0, entry) dependiendo de tu ListLinked
            n++;
        }

        V search(std::string key) override {
            int pos = h(key);
            TableEntry<V> temp(key); // Entrada temporal para buscar
            
            int index = table[pos].search(temp);
            if (index == -1) {
                throw std::runtime_error("Key '" + key + "' not found!");
            }
            
            // Extraer el valor. get(index) asumiendo que tu ListLinked tiene este método.
            return table[pos].get(index).value;
        }

        V remove(std::string key) override {
            int pos = h(key);
            TableEntry<V> temp(key);
            
            int index = table[pos].search(temp);
            if (index == -1) {
                throw std::runtime_error("Key '" + key + "' not found!");
            }
            
            V deletedValue = table[pos].get(index).value;
            table[pos].remove(index);
            n--;
            
            return deletedValue;
        }

        int entries() override {
            return n;
        }

        // Métodos específicos de HashTable
        int capacity() {
            return max;
        }

        V operator[](std::string key) {
            return search(key); // Reutilizamos search que ya lanza std::runtime_error si no existe
        }

        friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
            out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]" << std::endl;
            out << "==============" << std::endl;
            for (int i = 0; i < th.max; i++) {
                out << "== Cubeta " << i << " ==" << std::endl;
                out << "List => [";
                if (th.table[i].size() > 0) {
                    out << std::endl;
                    for (int j = 0; j < th.table[i].size(); j++) {
                        out << "  " << th.table[i].get(j) << std::endl;
                    }
                }
                out << "]" << std::endl;
            }
            out << "==============" << std::endl;
            return out;
        }
};

#endif
