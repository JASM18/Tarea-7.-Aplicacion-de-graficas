#ifndef GRAFICA_HPP
#define GRAFICA_HPP

#include <string>
#include <exception>

using std::string;

//si intentamos agregar un vertice o una arista repetidos, no se agrega

//para eliminar, primero se birran las arisras y luego el nodo

class Grafica {
    friend std::ostream & operator <<(std::ostream & salida, const Grafica &g);
public:

    Grafica();
    ~Grafica();
    Grafica(const Grafica& grafica);
    Grafica& operator=(const Grafica& grafica);

    void AgregarNodo(string nombre); // LISTO
    void AgregarArista(string origen, string destino, float peso); // LISTO

    bool EliminarNodo(string nombre); // LISTO
    bool EliminarArista(string origen, string destino); // LISTO

    int ObtenerGradoDeNodo(string nombre) const; //LISTO
    int ObtenerNumNodos() const; // LISTO
    int ObtenerNumAristas() const; // LISTO

    bool EstaVacia() const; // LISTO

    bool EsConexo() const; //LISTO

    void VaciarNodo(string nodo); // LISTO
    void Vaciar(); // LISTO

    bool BuscarNodo(string nombre) const; // LISTO
    bool BuscarArista(string origen, string destino) const; // LISTO

    void Imprimir() const;

    Grafica ObtenerArbolMinExp() const;

    class GraficaNoMemoria : public std::exception {
    public:
        GraficaNoMemoria() throw();

        virtual const char *what() const throw();
    };

private:
    int numNodos;
    int numAristas;

    struct Arista;

    struct Nodo {

        string Nombre;
        int grado;

        Arista *primero;
        Arista *ultima;

        Nodo *siguiente;

        Nodo(string nom, Nodo *sig = nullptr);
    };

    struct Arista {

        Nodo *adyacente;

        Arista *siguiente;
        float peso;

        Arista(Nodo* ady, Arista* sig = nullptr, float p = 0);
    };

    Nodo *primero;
    Nodo *ultimo;

    Nodo* obtenerDireccDeUnNodo(string nombre) const; // LISTO
};

#endif // GRAFICA_HPP
