#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

template <typename V> 
class TableEntry {
    public:
        // Atributos
        std::string key;
        V value;

        // Constructores
        TableEntry() : key(""), value(V()) {} // V() inicializa el valor por defecto según el tipo
        
        TableEntry(std::string key) : key(key), value(V()) {}
        
        TableEntry(std::string key, V value) : key(key), value(value) {}

        // Sobrecarga global del operador == (solo compara claves)
        friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2) {
            return te1.key == te2.key;
        }

        // Sobrecarga global del operador != (solo compara claves)
        friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2) {
            return te1.key != te2.key;
        }

        // Sobrecarga global del operador << 
        friend std::ostream& operator<<(std::ostream &out, const TableEntry<V> &te) {
            out << "('" << te.key << "' => " << te.value << ")";
            return out;
        }
};

#endif
