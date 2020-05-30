#include "Lista.h"

Lista::Lista()  {
    longitud_ = 0;
    header = nullptr;
    tailer = nullptr;
}

Lista::Lista(const Lista& l) : Lista() {
    *this = l;
}

Lista::~Lista() {
    int foo = longitud_;
    for (int i = 0; i < foo; ++i) {
        eliminar(0);
    }
}

Lista& Lista::operator=(const Lista& aCopiar) {
    int foo = this->longitud_;
    for (int i = 0; i < foo; ++i) {
        eliminar(0);
    }
    for (Nat i = 0; i < aCopiar.longitud_; ++i) {
       agregarAtras(aCopiar.iesimo(i));
    }
    return *this;
}

void Lista::agregarAdelante(const int& elem) {
    Nodo* new_node = new Nodo(elem);
    if (longitud() == 0){
        header = new_node;
        tailer = new_node;
    } else {
        new_node->prev = nullptr;
        new_node->next = header;

        header->prev = new_node;
        header = new_node;
    }
    longitud_++;
}

void Lista::agregarAtras(const int& elem) {
    Nodo* new_node = new Nodo(elem);
    if (longitud() == 0){
        tailer = new_node;
        header = new_node;
    } else {
        new_node->next = nullptr;
        new_node->prev = tailer;

        tailer->next = new_node;
        tailer = new_node;
    }
    longitud_++;
}

void Lista::eliminar(Nat i) {
    eliminarNodo(buscarIesimo_(i));
}

Lista::Nodo * Lista::buscarIesimo_(Nat i) {
    Nodo* buscador = header;
    for (int j = 0; j < i; ++j) {
        buscador = buscador->next;
    }
    return buscador;
}

void Lista::eliminarNodo(Nodo* n) {
    if(n->prev == nullptr){
        if (n->next != nullptr){
            (n->next)->prev = nullptr;
            header = n->next;
        } // caso si es solo header
    }
    if(n->next == nullptr){
        if(n->prev != nullptr){
            (n->prev)->next = nullptr;
            tailer = n->prev;
        } // caso si es solo tailer
    }
    if(n->prev != nullptr && n->next != nullptr){
        (n->next)->prev = n->prev;
        (n->prev)->next = n->next;
    }
    delete(n);
    longitud_--;
}

int Lista::longitud() const {
    return longitud_;
}

const int& Lista::iesimo(Nat i) const {
    Nodo* detective1 = header;
    bool vdv = false;
    for (int j = 0; j <= i && !vdv; ++j) {
        if(j==i){
            vdv = true;
        }
        if (!vdv){
            detective1 = detective1->next;
        }
    }
    return detective1->valor;
    //assert(false);
}

int& Lista::iesimo(Nat i) {
    // Completar (hint: es igual a la anterior...)
    Nodo* detective1 = header;
    bool vdv = false;
    for (int j = 0; j <= i && !vdv; ++j) {
        if(j==i){
            vdv = true;
        }
        if (!vdv){
            detective1 = detective1->next;
        }
    }
    return detective1->valor;
    //assert(false);
}

void Lista::mostrar(ostream& o) {
    // Completar OPCIONAL??
}
