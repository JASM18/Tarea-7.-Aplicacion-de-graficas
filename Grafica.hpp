/**
 * \file Grafica.hpp
 * \brief Este archivo contiene la definici&oacute;n de la clase Grafica para representar una gr&aacute;fica ponderada y calcular su &aacute;rbol de m&iacute;nima expansi&oacute;n.
 * \author S&aacute;nchez Montoy, Jes&uacute;s Axel
 * \author Portugal Arreola, Marian Bethsab&eacute;
 * \date 22/04/2026
 * \code{.cpp}
#include <iostream>
#include "Grafica.hpp"

using namespace std;

int main(){

    try {
        Grafica G;

        cout << "-> Construyendo la gr\240fica G..." << endl;
        G.AgregarNodo("A");
        G.AgregarNodo("B");
        G.AgregarNodo("C");
        G.AgregarNodo("D");
        G.AgregarNodo("E");

        cout << "Agregando aristas con pesos..." << endl;
        G.AgregarArista("A", "B", 2);
        G.AgregarArista("A", "C", 3);
        G.AgregarArista("B", "C", 1);
        G.AgregarArista("B", "D", 4);
        G.AgregarArista("C", "D", 5);
        G.AgregarArista("C", "E", 6);
        G.AgregarArista("D", "E", 7);

        cout << "Gr\240fica G:\n" << G << endl;

        cout << "N\243mero de nodos: " << G.ObtenerNumNodos() << endl;
        cout << "N\243mero de aristas: " << G.ObtenerNumAristas() << endl;
        cout << "Grado del nodo C: " << G.ObtenerGradoDeNodo("C") << endl;
        cout << "\250Es conexa?: " << (G.EsConexo() ? "S\241" : "No") << endl;

        cout << "\n-> Aplicando el algoritmo de prim (\265rbol de m\241nima expansi\242n)..." << endl;
        if (G.EsConexo()) {
            Grafica AME = G.ObtenerArbolMinExp();
            cout << "Gr\240fica AME:\n" << AME << endl;
            cout << "Costo total de aristas en MST: " << AME.ObtenerNumAristas() << " aristas." << endl;
        }else{
            cout << "La gr\240fica no es conexa, no se puede aplicar Prim." << endl;
        }

        cout << "\n-> Eliminando aristas y nodos..." << endl;
        cout << "Eliminando arista B-C (peso 1)..." << endl;
        G.EliminarArista("B", "C");

        cout << "Eliminando nodo D..." << endl;
        G.EliminarNodo("D");

        cout << "Gr\240fica despu\202s de borrar:\n" << G << endl;

        cout << "Vaciando la gr\240fica..." << endl;
        G.Vaciar();

        cout << "\250Est\240 vac\241a?: " << (G.EstaVacia() ? "S\241" : "No") << endl;


    } catch (const Grafica::GraficaNoMemoria& e) {
        cerr << "Error de memoria: " << e.what() << endl;
    } catch (const exception& e) {
        cerr << "Error inesperado: " << e.what() << endl;
    }

    system("pause");
    return 0;
}
 * \endcode
 */

#ifndef GRAFICA_HPP
#define GRAFICA_HPP

#include <string>
#include <exception>

using std::string;

/**
 * \brief Clase que representa una gr&aacute;fica ponderada mediante listas de adyacencia.
 */
class Grafica {

    /** \brief Sobrecarga del operador de inserci&oacute;n para imprimir la gr&aacute;fica.
     * \param salida Flujo de salida.
     * \param g Referencia constante a la gr&aacute;fica a imprimir.
     * \return Referencia al flujo de salida modificado.
     */
    friend std::ostream & operator <<(std::ostream & salida, const Grafica &g);

public:

    /** \brief Constructor por default que inicializa la gr&aacute;fica vac&iacute;a.
     */
    Grafica();

    /** \brief Destructor que libera la memoria de todos los nodos y aristas de la gr&aacute;fica.
     */
    ~Grafica();

    /** \brief Constructor de copias.
     * \param grafica Referencia a la gr&aacute;fica que se copiar&aacute;.
     */
    Grafica(const Grafica& grafica);

    /** \brief Operador de asignaci&oacute;n sobrecargado.
     * \param grafica Referencia a la gr&aacute;fica original.
     * \return Referencia a la gr&aacute;fica actual.
     */
    Grafica& operator=(const Grafica& grafica);

    /** \brief Agrega un nuevo nodo a la gr&aacute;fica, pero si ya existe, no hace nada.
     * \param nombre Cadena de caracteres con el nombre del nodo.
     * \return void
     * \throw GraficaNoMemoria Lanza excepci&oacute;n si falla la asignaci&oacute;n de memoria.
     */
    void AgregarNodo(string nombre);

    /** \brief Conecta dos nodos existentes mediante una arista con un peso espec&iacute;fico.
     * \param origen Nombre del nodo de origen.
     * \param destino Nombre del nodo de destino.
     * \param peso Valor que tienen las aristas.
     * \return void
     * \throw GraficaNoMemoria Lanza excepci&oacute;n si falla la asignaci&oacute;n de memoria.
     */
    void AgregarArista(string origen, string destino, float peso);

    /** \brief Elimina un nodo de la gr&aacute;fica y todas las aristas conectadas a &eacute;l.
     * \param nombre Nombre del nodo a eliminar.
     * \return true si el nodo fue eliminado con &eacute;xito, false si no exist&iacute;a.
     */
    bool EliminarNodo(string nombre);

    /** \brief Elimina la arista entre dos nodos de la gr&aacute;fica.
     * \param origen Nombre del nodo de origen.
     * \param destino Nombre del nodo de destino.
     * \return true si la arista se elimin&oacute; correctamente, false si no exist&iacute;a.
     */
    bool EliminarArista(string origen, string destino);

    /** \brief Devuelve la cantidad de aristas conectadas a un nodo espec&iacute;fico.
     * \param nombre Nombre del nodo del que se quiere saber su grado.
     * \return N&uacute;mero que representa el grado del nodo, o -1 si el nodo no existe.
     */
    int ObtenerGradoDeNodo(string nombre) const;

    /** \brief Consulta el n&uacute;mero total de nodos en la gr&aacute;fica.
     * \return Cantidad actual de nodos.
     */
    int ObtenerNumNodos() const;

    /** \brief Consulta el n&uacute;mero total de aristas en la gr&aacute;fica.
     * \return Cantidad actual de aristas.
     */
    int ObtenerNumAristas() const;

    /** \brief Verifica si la gr&aacute;fica se encuentra vac&iacute;a.
     * \return true si no hay nodos, false en otro caso.
     */
    bool EstaVacia() const;

    /** \brief Determina si la gr&aacute;fica es conexa.
     * \return true si es conexa, false si hay nodos o subgr&aacute;ficas aisladas.
     */
    bool EsConexo() const;

    /** \brief Elimina todas las aristas de un nodo.
     * \param nodo Nombre del nodo que se va a vaciar.
     * \return void
     */
    void VaciarNodo(string nodo);

    /** \brief Vac&iacute;a la gr&aacute;fica, borrando nodos y aristas.
     * \return void
     */
    void Vaciar();

    /** \brief Busca si un nodo existe dentro de la estructura de la gr&aacute;fica.
     * \param nombre Nombre del nodo a buscar.
     * \return true si existe, false si no.
     */
    bool BuscarNodo(string nombre) const;

    /** \brief Verifica si existe una arista entre dos nodos.
     * \param origen Nombre del primer nodo.
     * \param destino Nombre del segundo nodo.
     * \return true si la arista existe, false de lo contrario.
     */
    bool BuscarArista(string origen, string destino) const;

    /** \brief Imprime los nodos y sus listas de adyacencia.
     * \return void
     */
    void Imprimir() const;

    /** \brief Usa el algoritmo de Prim para encontrar y devolver un &aacute;rbol de m&iacute;nima expansi&oacute;n.
     * \return Un objeto de tipo Grafica que representa el &aacute;rbol generador de peso m&iacute;nimo.
     *         Si la gr&aacute;fica no es conexa, el &aacute;rbol quedar&aacute; incompleto o vac&iacute;o.
     */
    Grafica ObtenerArbolMinExp() const;

    /**
     * \brief Descripci&oacute;n de la clase: Excepci&oacute;n lanzada cuando ocurren fallos de memoria din&aacute;mica.
     */
    class GraficaNoMemoria : public std::exception {
    public:
        /** \brief Constructor por defecto de la excepci&oacute;n GraficaNoMemoria.
         */
        GraficaNoMemoria() throw();

        /** \brief Devuelve una descripci&oacute;n del error cuando no haya memoria disponible.
         * \return Cadena de caracteres con el mensaje de error.
         */
        virtual const char *what() const throw();
    };

private:
    int numNodos;           ///< Cantidad total de nodos en la gr&aacute;fica.
    int numAristas;         ///< Cantidad total de aristas en la gr&aacute;fica.

    struct Arista;          // Declaraci&oacute; para su uso en Nodo.

    /**
     * \brief Estructura interna que representa un v&eacute;rtice de la gr&aacute;fica y su lista de adyacencia.
     */
    struct Nodo {
        string Nombre;      ///< Nombre &uacute;nico del nodo.
        int grado;          ///< Cantidad de aristas conectadas al nodo.

        Arista *primero;    ///< Puntero a la primera arista de la lista de adyacencia del nodo.
        Arista *ultima;     ///< Puntero a la &uacute;ltima arista de la lista de adyacencia del nodo.

        Nodo *siguiente;    ///< Puntero al siguiente nodo en la lista principal de la gr&aacute;fica.

        /** \brief Constructor de la estructura Nodo.
         * \param nom Nombre o identificador del nodo.
         * \param sig Puntero al nodo siguiente en la lista.
         */
        Nodo(string nom, Nodo *sig = nullptr);
    };

    /**
     * \brief Estructura interna que representa una arista ponderada entre dos nodos.
     */
    struct Arista {
        Nodo *adyacente;    ///< Puntero al nodo destino con el cual se establece la arista.
        Arista *siguiente;  ///< Puntero a la siguiente arista en la lista de adyacencia.
        float peso;         ///< Costo, distancia o peso de recorrer esta arista.

        /** \brief Constructor de la estructura Arista.
         * \param ady Puntero al nodo destino.
         * \param sig Puntero a la siguiente arista de la lista.
         * \param p Peso num&eacute;rico de la arista.
         */
        Arista(Nodo* ady, Arista* sig = nullptr, float p = 0);
    };

    Nodo *primero;          ///< Puntero al primer nodo de la lista general de la gr&aacute;fica.
    Nodo *ultimo;           ///< Puntero al &uacute;ltimo nodo de la lista general de la gr&aacute;fica.

    /** \brief M&eacute;todo auxiliar que localiza en memoria un nodo seg&uacute;n su nombre.
     * \param nombre Nombre del nodo a buscar.
     * \return Puntero al objeto Nodo, o nullptr si no fue encontrado.
     */
    Nodo* obtenerDireccDeUnNodo(string nombre) const;
};

#endif // GRAFICA_HPP
