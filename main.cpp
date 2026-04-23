/**
 * \file main.cpp
 * \brief Este archivo contiene la ejecuci&oacute;n principal y el men&uacute; interactivo para probar la clase Grafica y el algoritmo de Prim.
 * \author S&aacute;nchez Montoy, Jes&uacute;s Axel
 * \author Portugal Arreola, Marian Bethsab&eacute;
 * \date 22/04/2026
 */

#include <iostream>

#include "CapturaSegura.hpp"
#include "Grafica.hpp"

using namespace std;

/**
 * \brief Opciones del men&uacute; principal para la gr&aacute;fica.
 */
enum Opciones_principales {
    AGREGARNODO = 1,    ///< Agrega un nuevo nodo a la gr&aacute;fica.
    AGREGARARISTA,      ///< Crea una arista ponderada entre dos nodos.
    ELIMINARNODO,       ///< Borra un nodo y sus aristas adyacentes.
    ELIMINARARISTA,     ///< Borra la arista entre dos nodos.
    GRADONODO,          ///< Muestra la cantidad de aristas de un nodo.
    NUMNODOS,           ///< Muestra el total de nodos de la gr&aacute;fica (orden).
    NUMARISTAS,         ///< Muestra el total de aristas de la gr&aacute;fica (tama&ntilde;o).
    ESTAVACIA,          ///< Indica si la gr&aacute;fica no tiene nodos.
    CONEXO,             ///< Indica si la gr&aacute;fica es conexa.
    VACIARNODO,         ///< Elimina todas las conexiones de un nodo espec&iacute;fico.
    VACIAR,             ///< Elimina todos los nodos y aristas de la gr&aacute;fica.
    BUSCARNODO,         ///< Verifica si un nodo existe.
    BUSCARARISTA,       ///< Verifica si una arista existe.
    IMPRIMIR,           ///< Imprime la lista de adyacencia de la gr&aacute;fica.
    ARBOLMINEXP,        ///< Calcula e imprime el &aacute;rbol de m&iacute;nima expansi&oacute;n usando Prim.
    SALIR               ///< Termina la ejecuci&oacute;n del programa.
};

int main()
{
    int opcion = -1;
    Grafica G;

    string nodo1, nodo2;
    int peso;

    do{
        cout << "==================================" << endl;
        cout << "Tarea 7. Aplicaci\242n de gr\240ficas" << endl;
        cout << "==================================" << endl << endl;

        cout << "--- GR\265FICA ACTUAL ---" << endl;
        G.Imprimir();
        cout << "----------------------" << endl << endl;

        cout << "Opciones:" << endl;
        cout << "\t" << AGREGARNODO << ") Agregar un nodo." << endl;
        cout << "\t" << AGREGARARISTA << ") Agregar una arista (con peso)." << endl;
        cout << "\t" << ELIMINARNODO << ") Eliminar un nodo." << endl;
        cout << "\t" << ELIMINARARISTA << ") Eliminar una arista." << endl;
        cout << "\t" << GRADONODO << ") Obtener el grado de un nodo." << endl;
        cout << "\t" << NUMNODOS << ") Obtener n\243mero total de nodos (Orden)." << endl;
        cout << "\t" << NUMARISTAS << ") Obtener n\243mero total de aristas (Tama\244o)." << endl;
        cout << "\t" << ESTAVACIA << ") Saber si la gr\240fica est\240 vac\241a." << endl;
        cout << "\t" << CONEXO << ") Saber si la gr\240fica es conexa." << endl;
        cout << "\t" << VACIARNODO << ") Vaciar un nodo (eliminar todas sus aristas)." << endl;
        cout << "\t" << VACIAR << ") Vaciar toda la gr\240fica." << endl;
        cout << "\t" << BUSCARNODO << ") Buscar un nodo." << endl;
        cout << "\t" << BUSCARARISTA << ") Buscar una arista." << endl;
        cout << "\t" << IMPRIMIR << ") Imprimir lista de adyacencia." << endl;
        cout << "\t" << ARBOLMINEXP << ") Generar \265rbol de M\241nima Expansi\242n (Prim)." << endl;
        cout << "\t" << SALIR << ") Salir del programa." << endl;

        do{
            CapturarNumero(opcion, "Elige una opci\242n: ");
        }while(opcion > SALIR || opcion < AGREGARNODO);

        if(opcion == SALIR) continue;

        try{
            cout << "- - - - -" << endl;
            switch(opcion){
                case AGREGARNODO:
                    cout << "Nombre del nuevo nodo: ";
                    cin >> nodo1;
                    G.AgregarNodo(nodo1);
                    cout << "Nodo agregado (si no exist\241a)." << endl;
                break;

                case AGREGARARISTA:
                    if(G.ObtenerNumNodos() < 2){
                        cout << "No hay v\202rtices suficientes para agregar una arista." << endl;
                    }else{
                        cout << "Nodo origen: ";
                        cin >> nodo1;
                        cout << "Nodo destino: ";
                        cin >> nodo2;
                        CapturarNumero(peso, "Peso de la arista: ");
                        G.AgregarArista(nodo1, nodo2, peso);
                        cout << "Arista agregada." << endl;
                    }
                break;

                case ELIMINARNODO:
                    cout << "Nombre del nodo a eliminar: ";
                    cin >> nodo1;
                    if (G.EliminarNodo(nodo1)) cout << "Nodo eliminado correctamente." << endl;
                    else cout << "El nodo no existe." << endl;
                break;

                case ELIMINARARISTA:
                    cout << "Nodo origen: ";
                    cin >> nodo1;
                    cout << "Nodo destino: ";
                    cin >> nodo2;
                    if (G.EliminarArista(nodo1, nodo2)) cout << "Arista eliminada." << endl;
                    else cout << "La arista no existe." << endl;
                break;

                case GRADONODO:
                    cout << "Nombre del nodo: ";
                    cin >> nodo1;
                    peso = G.ObtenerGradoDeNodo(nodo1); // re utilizando variable xd
                    if (peso != -1) cout << "El grado del nodo " << nodo1 << " es: " << peso << endl;
                    else cout << "El nodo no existe." << endl;
                break;

                case NUMNODOS:
                    cout << "La gr\240fica tiene " << G.ObtenerNumNodos() << " nodos." << endl;
                break;

                case NUMARISTAS:
                    cout << "La gr\240fica tiene " << G.ObtenerNumAristas() << " aristas." << endl;
                break;

                case ESTAVACIA:
                    if (G.EstaVacia()) cout << "La gr240fica esta vac\241a." << endl;
                    else cout << "La gr\240fica NO esta vac\241a." << endl;
                break;

                case CONEXO:
                    if (G.EsConexo()) cout << "La gr\240fica es conexa." << endl;
                    else cout << "La gr\240fica NO es conexa." << endl;
                break;

                case VACIARNODO:
                    cout << "Nombre del nodo a vaciar: ";
                    cin >> nodo1;
                    G.VaciarNodo(nodo1);
                    cout << "Se han eliminado todas las aristas conectadas a " << nodo1 << "." << endl;
                break;

                case VACIAR:
                    G.Vaciar();
                    cout << "La gr\240fica ha sido vaciada por completo." << endl;
                break;

                case BUSCARNODO:
                    cout << "Nombre del nodo a buscar: ";
                    cin >> nodo1;
                    if (G.BuscarNodo(nodo1)) cout << "El nodo S\326 existe." << endl;
                    else cout << "El nodo NO existe." << endl;
                break;

                case BUSCARARISTA:
                    cout << "Nodo origen: ";
                    cin >> nodo1;
                    cout << "Nodo destino: ";
                    cin >> nodo2;
                    if (G.BuscarArista(nodo1, nodo2)) cout << "La arista S\326 existe." << endl;
                    else cout << "La arista NO existe." << endl;
                    break;

                case IMPRIMIR:
                    cout << "Lista de adyacencia:" << endl;
                    G.Imprimir();
                break;

                case ARBOLMINEXP:
                    cout << "Generando \265rbol de M\241nima Expansi\242n..." << endl;
                    if (!G.EsConexo()) {
                        cout << "Error: La gr\240fica original debe ser conexa para generar el \240rbol de Prim." << endl;
                    }else{
                        Grafica arbolPrim = G.ObtenerArbolMinExp();
                        cout << "\n--- \265RBOL DE M\326NIMA EXPANSI\340N ---" << endl;
                        arbolPrim.Imprimir();
                    }
                break;
            }

        }catch(const char* mensaje){
            cerr << "Error: " << mensaje << endl;
        }catch(const exception &error){
            cerr << "Error: " << error.what() << endl;
        }catch(...){
            cerr << "El programa tuvo un error inesperado." << endl;
        }

        cout << endl;
        system ("pause");
        system("CLS");
    }while(opcion != SALIR);

    cout << "\nEl programa ha terminado." << endl;

    system("pause");
    return 0;
}
