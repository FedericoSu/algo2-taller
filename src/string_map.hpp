
template <typename T>
string_map<T>::string_map(){
    _size = 0;
    raiz = new Nodo;
    raiz->definicion = nullptr;
}

template <typename T>
string_map<T>::string_map(const string_map<T>& aCopiar) : string_map() { *this = aCopiar; }
// Provisto por la catedra: utiliza el operador asignacion para realizar la copia.

template <typename T>
string_map<T>& string_map<T>::operator=(const string_map<T>& d) {//Busco agarrar la data de d y "copiarla"
    vector<string> estable = this->_claves;
    //ELIMINO DATA VIEJA
    for (int i = 0; i < estable.size(); ++i){
        erase(_claves[i]); // borro lo que haya en el this
    }
    (this->raiz)->definicion = nullptr;
    vector<string> clavesAUbicar = d._claves;
    // REEMPLAZO CON LA DATA NUEVA
    for (int j = 0; j < clavesAUbicar.size(); ++j) {
        insert(make_pair(clavesAUbicar[j], d.at((clavesAUbicar[j]))));
    }
    return *this;
}

template <typename T>
string_map<T>::~string_map(){
    vector<string> clavesABorrar = _claves;
    for (int i = 0; i < clavesABorrar.size(); ++i) {
        erase(clavesABorrar[i]);
    }
    delete raiz;
}

template <typename T>
void string_map<T>::insert(const pair<string, T>& pst){
    int slong = (pst.first).size();

    T* valor = new T(pst.second);

    if (slong == 0) { // Si mi string es "", inserto el "" en la raiz.
        raiz->definicion = valor;
    } else { // Sino voy a ir recorriendo, y si hay un camino previo lo sigo. Caso contrario lo voy armo.
        Nodo *actual = raiz;
        for (int j = 0; j < slong; ++j){
            bool found = false;
            if ((actual->siguientes[int(pst.first[j])]) != nullptr){
                if (j == slong - 1) { // Caso end
                    actual = actual->siguientes[int(pst.first[j])];
                    if(count(pst.first) == 1){delete actual->definicion; actual->definicion = nullptr;}
                    actual->definicion = valor;
                    found = true;
                } else {
                    found = true;
                    actual = actual->siguientes[int(pst.first[j])];
                }
            }
            if (!found) { // Si no estaba en siguientes, agarro y creo un nuevo nodo
                Nodo *newNode = new Nodo;
                actual->siguientes[int(pst.first[j])] = newNode;
                if (j == slong - 1) { // Caso end
                    newNode->definicion = valor;
                } else {
                    newNode->definicion = nullptr;
                    actual = newNode;
                }
            }
        }
    }
    if(count(pst.first) == 0){_size++; _claves.push_back(pst.first);} //Si la palabra no estaba, la sumo y la agrego a mis claves.
}

template <typename T>
T& string_map<T>::operator[](const string& clave){
    // --OPCIONAL--
}


template <typename T>
int string_map<T>::count(const string& clave) const{ // ME DA SI ESTA O NO
   int res = 0;
   for (string i : _claves){
       if(i == clave){res = 1;}
   }
   return res;

}

template <typename T>
const T& string_map<T>::at(const string& clave) const {
    // Pre: La clave esta definida
    T* res = raiz->definicion;
    Nodo* actual = raiz;
    for (int j = 0; j < clave.size(); ++j) {
        if ((actual->siguientes[int(clave[j])]) != nullptr){
            if (j == clave.size() - 1){
                res = (actual->siguientes[int(clave[j])])->definicion;
            } else {
                actual = actual->siguientes[int(clave[j])];
            }
        }
    }
    return *res;
}

template <typename T>
T& string_map<T>::at(const string& clave) {
    // Pre: La clave esta definida
   T* res = raiz->definicion;
   Nodo* actual = raiz;
   for (int j = 0; j < clave.size(); ++j) {
       if ((actual->siguientes[int(clave[j])]) != nullptr){
           if (j == clave.size() - 1){
               res = (actual->siguientes[int(clave[j])])->definicion;
           } else {
               actual = actual->siguientes[int(clave[j])];
           }
       }
   }
   return *res;
}

template <typename T>
void string_map<T>::erase(const string& clave) {
    Nodo* actual = raiz;

    if(clave.size() == 0){ // Si la clave es ""

            delete actual->definicion;
            raiz->definicion = nullptr;
            //No borro el nodo raiz

    } else { // Sino..

            //Busco el ultimo Nodo y la ultBif(ultima bifurcacion)
            //Seteo como mi primera bifurcacion la raiz (Caso Base)
            Nodo* ultBif = raiz;
            int ultBifValor = -1;

            int contDeCaminos = 0;
            for (int j = 0; j < clave.size(); ++j) {
                contDeCaminos = 0;
                if ((actual->siguientes[int(clave[j])]) != nullptr){ //adelanto el actual
                actual = actual->siguientes[int(clave[j])];
                }
                for (int i = 0; i < 256; ++i) { //Chequeo cuantos hijos tiene actual
                    if(actual->siguientes[i] != nullptr){
                        contDeCaminos++;
                    }
                }
                if (contDeCaminos > 1){ // Guardo la ultima Bifurcacion (si la es)
                    ultBif = actual;
                    ultBifValor = j;
                }
            }

        //Chequeo los hijos del UltNodo
        bool tieneHijos = false;
        for (int i = 0; i < 256; ++i) {
            if(actual->siguientes[i] != nullptr){
                tieneHijos = true;
            }
        }

        if(tieneHijos){ //Si el nodo tiene hijos, solo borro el significado

            delete actual->definicion;
            actual->definicion = nullptr;


        } else { // Si no tiene hijos...

            //Borro entre la ultima bif y el actual
            bool fput = true;
            Nodo* adelantado = ultBif; //Dice que no se usa??????
            while(ultBif != actual){
                adelantado = ultBif->siguientes[int(clave[ultBifValor+1])]; // adelanto
                ultBif->siguientes[int(clave[ultBifValor+1])] = nullptr; // lo borro de siguientes
                if(!fput){
                    delete ultBif; //deleteo el nodo
                } else {
                    fput = false;
                }
                ultBif = adelantado;
                if(ultBif == actual){
                    delete ultBif->definicion;
                    delete ultBif;
                }
                ultBifValor++; // Me muevo sobre la clave
            }
        }
    } //end long if

    // Borro el elemento de _claves:
    vector<string> final;
    for (int i = 0; i < _claves.size(); ++i) {
        if(_claves[i] != clave){
            final.push_back(_claves[i]);
        }
    }
    _claves = final;
    _size--;
}

template <typename T>
int string_map<T>::size() const{return _size;}

template <typename T>
bool string_map<T>::empty() const{return (_size == 0);}