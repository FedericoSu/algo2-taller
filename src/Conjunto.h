#ifndef CONJUNTO_H_
#define CONJUNTO_H_

#include <assert.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Nodo;

template <class T>
class Conjunto
{
    public:
        // Constructor. Genera un conjunto vacío.
        Conjunto();

        // Destructor. Debe dejar limpia la memoria.
        ~Conjunto();

        // Inserta un elemento en el conjunto. Si este ya existe,
        // el conjunto no se modifica.
        void insertar(const T&);

        // Decide si un elemento pertenece al conjunto o no.
        bool pertenece(const T&) const;

        // Borra un elemento del conjunto. Si este no existe,
        // el conjunto no se modifica.
        void remover(const T&);

        void eliminacion(Nodo* padre, int lado, Nodo* actual, T valor);

        // Siguiente elemento al recibido por párametro, en orden.
        const T& siguiente(const T& elem);

        // Devuelve el mínimo elemento del conjunto según <.
        const T& minimo() const;

        T& minimoParticular(Nodo* actual);

        // Devuelve el máximo elemento del conjunto según <.
        const T& maximo() const;

        T& maximoParticular(Nodo* actual);

        // Devuelve la cantidad de elementos que tiene el conjunto.
        unsigned int cardinal() const;

        // Muestra el conjunto.
        void mostrar(std::ostream&) const;
    private:
        struct Nodo{
            Nodo(const T& v) : valor(v){
                izq = nullptr;
                der = nullptr;
            };
            T valor;
            Nodo* izq;
            Nodo* der;
        };
        Nodo *_raiz;
        unsigned int cantNodos_;
        void eliminacion(Nodo* padre, int lado, Nodo* actual, T valor);
        T& minimoParticular(Nodo* actual);
        T& maximoParticular(Nodo* actual);
        void MorrisTraversal(vector<Conjunto<T>::Nodo*> &v);
};

template<class T>
std::ostream& operator<<(std::ostream& os, const Conjunto<T>& c) {
	 c.mostrar(os);
	 return os;
}

#include "Conjunto.hpp"

#endif // CONJUNTO_H_
