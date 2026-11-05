#ifndef DICT_H
#define DICT_H

#include <string>
#include <stdexcept>

template <typename V> 
class Dict {
    public:
        // Destructor virtual (buena práctica para interfaces)
        virtual ~Dict() = default;

        // Inserta el par key->value en el diccionario. 
        // Lanza una excepción std::runtime_error si key ya existe.
        virtual void insert(std::string key, V value) = 0;

        // Busca el valor correspondiente a key. 
        // Lanza una excepción std::runtime_error si no se encuentra.
        virtual V search(std::string key) = 0;

        // Elimina el par key->value si se encuentra en el diccionario. 
        // Lanza una excepción std::runtime_error si no se encuentra.
        virtual V remove(std::string key) = 0;

        // Devuelve el número de elementos que tiene el Diccionario.
        virtual int entries() = 0;
};

#endif
