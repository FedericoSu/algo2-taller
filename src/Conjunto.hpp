#include <stack>
#include "Conjunto.h"

using namespace std;

template <class T>
Conjunto<T>::Conjunto() {
    cantNodos_ = 0;
    _raiz = nullptr;
}

template <class T>
Conjunto<T>::~Conjunto() {
    int foo = cantNodos_;
    vector<Nodo*> vectNod;
    vectNod.reserve(foo);
    MorrisTraversal(vectNod);
    for (int i = 0; i < foo; ++i) {
        remover(vectNod[i]->valor);
    }
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    bool pert = false;
    if (cantNodos_ > 0){
        Nodo* detector = _raiz;
        bool stop = false;
        while(!stop){
            if(clave == detector->valor){
                stop = true;
                pert = true;
            } else {
                if (clave < detector->valor){
                    if (detector->izq == nullptr){stop = true;} else {detector = detector->izq;}
                }
                if (clave > detector->valor){
                    if (detector->der == nullptr){stop = true;} else {detector = detector->der;}
                }
            }
        }
    }
    return pert;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if (!pertenece(clave)) {
        Nodo* nuevo_Nodo = new Nodo(clave);
        if(cardinal() == 0){
            _raiz = nuevo_Nodo;
        } else {
            Nodo* detector = _raiz;
            bool stop = false;
            while(!stop){
                if (clave < detector->valor){
                    if (detector->izq == nullptr){
                        detector->izq = nuevo_Nodo;
                        stop = true;
                    } else {detector = detector->izq;}
                }
                if (clave > detector->valor){
                    if (detector->der == nullptr){
                        detector->der = nuevo_Nodo;
                        stop = true;
                    } else {detector = detector->der;}
                }
            }
        }
        cantNodos_++;
    }
}




template <class T>
void Conjunto<T>::remover(const T& clave) {
    if (pertenece(clave)) { // me aseguro que lo que quiero borrar existe
        if(cardinal() == 1){
            delete _raiz;
            _raiz = nullptr;
        } else {
            eliminacion(nullptr, 2, _raiz, clave);
        }
        cantNodos_--;
    }
}

template <class T>
void Conjunto<T>::eliminacion(Nodo* padre, int lado, Nodo* actual, T clave){
    if (clave == actual->valor){// encontre el nodo a borrar
        if(actual->izq == nullptr && actual->der == nullptr){// si el nodo a borrar es una hoja...
            delete actual;
            if (lado == 0){
                padre->izq= nullptr;
            } else {
                padre->der = nullptr;
            }
        } else {// si el nodo a borrar NO es una hoja...
            if (actual->der != nullptr){
                actual->valor = minimoParticular(actual->der);
                eliminacion(actual, 1, actual->der, actual->valor);
            } else {
                actual->valor = maximoParticular(actual->izq);
                eliminacion(actual, 0, actual->izq, actual->valor);
            }
        }
    } else {// si no lo encontre, sigo buscando
        if (clave < actual->valor){
            eliminacion(actual, 0, actual->izq, clave);// sigo por izq
        } else {
            eliminacion(actual, 1, actual->der, clave);// sigo por der
        }
    }
}


template <class T>
const T& Conjunto<T>::siguiente(const T& elem){
    vector<Nodo*> vect;
    vect.reserve(cantNodos_);
    MorrisTraversal(vect);
    bool out = false;
    int i = 0;
    while(i < cantNodos_ && !out){
        if(elem == vect[i]->valor){
            out = true;
        }
        i++;
    }
    return vect[i]->valor;
}

template <class T>
void Conjunto<T>::MorrisTraversal(vector<Conjunto<T>::Nodo*>& v){
    Nodo *pre;
    if (_raiz == nullptr){return;}
    Nodo *current = _raiz;
    while (current != nullptr) {
        if (current->izq == nullptr) {
            v.push_back(current);
            current = current->der;
        } else {
            pre = current->izq;
            while (pre->der != nullptr && pre->der != current){
                pre = pre->der;
            }
            if (pre->der == nullptr) {
                pre->der = current;
                current = current->izq;
            } else {
                pre->der = nullptr;
                v.push_back(current);
                current = current->der;
            }
        }
    }
}


template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo* detector = _raiz;
    bool stop = false;
    while(!stop){
        if (detector->izq == nullptr) {
            stop = true;
        } else {
            detector = detector->izq;
        }
    }
    return detector->valor;
}



template <class T>
T& Conjunto<T>::minimoParticular(Nodo* actual){
        Nodo* detector = actual;
        bool stop = false;
        while(!stop){
            if (detector->izq == nullptr) {
                stop = true;
            } else {
                detector = detector->izq;
            }
        }
        return detector->valor;
}


template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo* detector = _raiz;
    bool stop = false;
    while(!stop){
        if (detector->der == nullptr) {
            stop = true;
        } else {
            detector = detector->der;
        }
    }
    return detector->valor;
}

template <class T>
T& Conjunto<T>::maximoParticular(Nodo* actual){
    Nodo* detector = actual;
    bool stop = false;
    while(!stop){
        if (detector->der == nullptr) {
            stop = true;
        } else {
            detector = detector->der;
        }
    }
    return detector->valor;
}


template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return cantNodos_;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    // OPCIONAL
    assert(false);
}

