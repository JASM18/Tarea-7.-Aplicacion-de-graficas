/**
 * \file Grafica.cpp
 * \brief Este archivo contiene la implementaci&oacute;n de los m&eacute;todos de la clase Grafica.
 * \author S&aacute;nchez Montoy, Jes&uacute;s Axel
 * \author Portugal Arreola, Marian Bethsab&eacute;
 * \date 22/04/2026
 */

#include "Grafica.hpp"

#include <iostream>

using std::cout;
using std::endl;
using std::string;

//***********************************
// CONSTRUCTORES
//***********************************

Grafica::Grafica()
{
    numAristas = 0;
    numNodos = 0;

    primero = nullptr;
    ultimo = nullptr;
}

//***********************************

Grafica::~Grafica()
{
    Vaciar();
}

//***********************************

Grafica::Grafica(const Grafica& grafica)
{
    numNodos = 0;
    numAristas = 0;
    primero = nullptr;
    ultimo = nullptr;

    *this = grafica;
}

//***********************************

Grafica& Grafica::operator=(const Grafica& grafica)
{
    if(this == &grafica) return *this;

    Vaciar();

    Nodo *visitado = grafica.primero;

    while(visitado != nullptr){
        AgregarNodo(visitado->Nombre);
        visitado = visitado->siguiente;
    }

    //aristas
    visitado = grafica.primero;

    while(visitado != nullptr){
        Arista *aristaVis = visitado->primero;
        while(aristaVis != nullptr){

            AgregarArista(visitado->Nombre, aristaVis->adyacente->Nombre, aristaVis->peso);
            aristaVis = aristaVis->siguiente;
        }
        visitado = visitado->siguiente;
    }

    return *this;
}

//***********************************
// MÉTODOS PUBLICOS
//***********************************

void Grafica::AgregarNodo(string nombre)
{
    if(BuscarNodo(nombre)) return;

    try{
        Nodo *nuevo = new Nodo(nombre);
        nuevo->grado = 0;
        nuevo->primero = nullptr;
        nuevo->ultima = nullptr;
        nuevo->siguiente = nullptr;

        if(EstaVacia()){
            primero = nuevo;
            ultimo = nuevo;
        }else{
            ultimo->siguiente = nuevo;
            ultimo = nuevo;

        }

        ++numNodos;
    }catch(std::bad_alloc&){
        throw GraficaNoMemoria();
    }
}

//***********************************

void Grafica::AgregarArista(string origen, string destino, float peso)
{
    // Condiciones:
    // 1. Eviar ciclos (que el origen sea igual al destino)
    // 2. Que la arista que se desee construir ya exista
    // 3. que el nombre de origen o destino no exista

    if(origen == destino) return; // se evitan ciclos

    if(BuscarArista(origen, destino)) return; // Ya existe la arista

    Nodo *nodoOrigen = obtenerDireccDeUnNodo(origen);
    Nodo *nodoDestino = obtenerDireccDeUnNodo(destino);


    if(nodoOrigen == nullptr || nodoDestino == nullptr) return; // Alguno de los dos nodos no existe

    // Se cumplen todas las condiciones para que la arista exista
    // -> Crear la conexion del origen al destino y del destino al origen

    try{
        Arista* nuevaAristaOrigDest = new Arista(nodoDestino, nullptr, peso);

        if(nodoOrigen->primero == nullptr){ // No hay aristas!

            nodoOrigen->primero = nuevaAristaOrigDest;
            nodoOrigen->ultima = nuevaAristaOrigDest;
        }else{
            nodoOrigen->ultima->siguiente = nuevaAristaOrigDest;
            nodoOrigen->ultima = nuevaAristaOrigDest;
        }

        ++nodoOrigen->grado;

        Arista* nuevaAristaDestOrig = new Arista(nodoOrigen, nullptr, peso);

        if(nodoDestino->primero == nullptr){ // No hay aristas!

            nodoDestino->primero = nuevaAristaDestOrig;
            nodoDestino->ultima = nuevaAristaDestOrig;
        }else{
            nodoDestino->ultima->siguiente = nuevaAristaDestOrig;
            nodoDestino->ultima = nuevaAristaDestOrig;
        }

        ++nodoDestino->grado;

        ++numAristas;
    }catch(const std::bad_alloc&){
        throw GraficaNoMemoria();
    }
}

//***********************************

bool Grafica::EliminarNodo(string nombre)
{
    Nodo *porBorrar = obtenerDireccDeUnNodo(nombre);
    if(porBorrar == nullptr) return false;

    VaciarNodo(nombre);

    Nodo *actual = primero;
    Nodo *anterior = nullptr;

    while(actual != nullptr && actual != porBorrar){
        anterior = actual;
        actual = actual->siguiente;
    }

    if(anterior == nullptr){
        primero = actual->siguiente;
    }else{
        anterior->siguiente = actual->siguiente;
    }

    if(actual == ultimo){
        ultimo = anterior;
    }

    delete actual;
    numNodos--;
    return true;
}

//***********************************

bool Grafica::EliminarArista(string origen, string destino)
{
    if(!BuscarArista(origen, destino)) return false;

    Nodo *nodoOrigen = obtenerDireccDeUnNodo(origen);
    Nodo *nodoDestino = obtenerDireccDeUnNodo(destino);

    //Se elimina el nodo de destino

    Arista *actual = nodoOrigen->primero;
    Arista *anterior = nullptr;
    while(actual != nullptr && actual->adyacente != nodoDestino){
        anterior = actual;
        actual = actual->siguiente;
    }

    if(actual != nullptr){
        if(anterior == nullptr) nodoOrigen->primero = actual->siguiente;
        else anterior->siguiente = actual->siguiente;

        if(actual == nodoOrigen->ultima) nodoOrigen->ultima = anterior;

        delete actual;
        nodoOrigen->grado--;
    }

    // Se elimina el nodo de origen
    actual = nodoDestino->primero;
    anterior = nullptr;
    while(actual != nullptr && actual->adyacente != nodoOrigen){
        anterior = actual;
        actual = actual->siguiente;
    }

    if(actual != nullptr){
        if(anterior == nullptr) nodoDestino->primero = actual->siguiente;
        else anterior->siguiente = actual->siguiente;

        if(actual == nodoDestino->ultima) nodoDestino->ultima = anterior;

        delete actual;
        nodoDestino->grado--;
    }

    --numAristas;
    return true;
}

//***********************************

int Grafica::ObtenerGradoDeNodo(string nombre) const
{
    Nodo *n = obtenerDireccDeUnNodo(nombre);
    if(n != nullptr){
        return n->grado;
    }
    return -1; // Si el nodo no existe
}

//***********************************

int Grafica::ObtenerNumNodos() const
{
    return numNodos;
}

//***********************************

int Grafica::ObtenerNumAristas() const
{
    return numAristas;
}

//***********************************

bool Grafica::EstaVacia() const
{
    return primero == nullptr;
}

//***********************************

bool Grafica::EsConexo() const
{
    if (EstaVacia()) return false;
    if (numNodos == 1) return true;

    Nodo** cola = new Nodo*[numNodos];
    Nodo** nodosVisitados = new Nodo*[numNodos];

    int numVisitados = 0;
    int inicioCola = 0, finCola = 0;

    cola[finCola++] = primero;
    nodosVisitados[numVisitados++] = primero;

    while(inicioCola < finCola){
        Nodo* actual = cola[inicioCola++];

        // Se checa todos los vecinos de este nodo
        Arista* arista = actual->primero;
        while(arista != nullptr){
            Nodo* ady = arista->adyacente;

            // Verificamos si ya lo visitamos antes
            bool visitado = false;
            for(int i = 0; i < numVisitados; ++i){
                if(nodosVisitados[i] == ady){
                    visitado = true;
                    break;
                }
            }

            // Si es nuevo, lo metemos a la cola
            if(!visitado){
                nodosVisitados[numVisitados++] = ady;
                cola[finCola++] = ady;
            }
            arista = arista->siguiente;
        }
    }

    // Si pudimos visitar todos los nodos, la grafica es conexa
    bool conexo = (numVisitados == numNodos);

    delete[] cola;
    delete[] nodosVisitados;

    return conexo;
}

//***********************************

void Grafica::VaciarNodo(string nodo)
{
    Nodo *nodoActual = obtenerDireccDeUnNodo(nodo);
    if(nodoActual == nullptr) return;

    while(nodoActual->primero != nullptr){
        string destino = nodoActual->primero->adyacente->Nombre;
        EliminarArista(nodo, destino);
    }
}

//***********************************

void Grafica::Vaciar()
{
    while(primero != nullptr){
        EliminarNodo(primero->Nombre);
    }
}

//***********************************

bool Grafica::BuscarNodo(string nombre) const
{
    return obtenerDireccDeUnNodo(nombre) != nullptr;
}

//***********************************

bool Grafica::BuscarArista(string origen, string destino) const
{
    Nodo *nodoOrigen = obtenerDireccDeUnNodo(origen); // Encontramos la direccion del nodo de origen

    if(nodoOrigen == nullptr) return false;

    Arista* aristaVisitada = nodoOrigen->primero; // Puntero para checar todas sus aristas

    while(aristaVisitada != nullptr){

        if(aristaVisitada->adyacente->Nombre == destino){ // Si el nombre del nodo que conecta la arista es igual al nombre del destino, significa que se encontro la arista deseada
            return true;
        }
        aristaVisitada = aristaVisitada->siguiente;
    }

    return false;
}

//***********************************

void Grafica::Imprimir() const
{
    if(EstaVacia()){
        cout << "La grafica esta vac\241a." << endl;
        return;
    }

    Nodo *visitado = primero;

    while(visitado != nullptr){
        cout << "[" << visitado->Nombre << "]: ";

        Arista *aristaVis = visitado->primero;
        if(aristaVis == nullptr){
            cout << "No tiene aristas.";
        }

        while(aristaVis != nullptr){
            cout << "(" << aristaVis->adyacente->Nombre << "), ";
            aristaVis = aristaVis->siguiente;
        }

        cout << "\b\b " << endl;
        visitado = visitado->siguiente;
    }

}

//***********************************

Grafica Grafica::ObtenerArbolMinExp() const
{
    Grafica T;
    if (EstaVacia()) return T;

    T.AgregarNodo(primero->Nombre);

    while (numNodos > T.ObtenerNumNodos()){
        Nodo *visitado = primero;

        float menorpeso = 999999999.0;
        string nomOrigen = "";
        string nomDestino = "";

        // recorremos todos los nodos de G
        while (visitado != nullptr){

            //buscamos si visitado ya está en T para poder usar las aristas de T
            if (T.BuscarNodo(visitado->Nombre)){

                Arista *visitadoArista = visitado->primero;

                while (visitadoArista != nullptr){
                    if (!T.BuscarNodo(visitadoArista->adyacente->Nombre)){
                        if (visitadoArista->peso < menorpeso){
                            menorpeso = visitadoArista->peso;
                            nomOrigen = visitado->Nombre;
                            nomDestino = visitadoArista->adyacente->Nombre;
                        }
                    }
                    visitadoArista = visitadoArista->siguiente;
                }
            }
            visitado = visitado->siguiente;
        }

        if (nomOrigen != ""){
            T.AgregarNodo(nomDestino);
            T.AgregarArista(nomOrigen, nomDestino, menorpeso);
        }else{
            break;
        }
    }

    return T;
}

//***********************************
// EXCEPCIONES
//***********************************

Grafica::GraficaNoMemoria::GraficaNoMemoria() throw() {}

//***********************************

const char *Grafica::GraficaNoMemoria::what() const throw()
{
    return "No hay memoria disponible.";
}

//***********************************
// CONSTRUCTORES DE CLASES AUXILIARES
//***********************************

Grafica::Nodo::Nodo(string nom, Nodo *sig /*= nullptr*/) : Nombre(nom), siguiente(sig) {};

//***********************************

Grafica::Arista::Arista(Nodo* ady, Arista* sig /*= nullptr*/, float p /* = 0 */) : adyacente(ady), siguiente(sig), peso(p) {};

//***********************************
// Métodos privados de la clase
//***********************************

Grafica::Nodo* Grafica::obtenerDireccDeUnNodo(string nombre) const
{
    Nodo* visitado = primero;

    while(visitado != nullptr){ // Se recorre toda la lista de nodos en el grafo

        if(visitado->Nombre == nombre) return visitado; // Si el nodo que visitamos, su nombre es igual al nombre que buscamos, regresamos su direccion
        visitado = visitado->siguiente;
    }

    return nullptr;
}

//**********************************
// Flujos sobrecargados de entrada y salida
//**********************************

std::ostream & operator<<(std::ostream & salida, const Grafica &g)
{
    g.Imprimir();
    return salida;
}
