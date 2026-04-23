/**
* \file CapturaSegura.tpp
 * \brief Implementaci&oacute;n de la plantilla de captura segura.
 */

#include <iostream>
#include <limits>

template <typename T>
void CapturarNumero(T &num, const char solicitud[])
{
    std::cout << solicitud;
    std::cin >> num;
    while(std::cin.fail()){
        std::cout << "Error: no es un n\243mero\n"; // \243 = ú
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<int>::max(),'\n');
        std::cout << solicitud;
        std::cin >> num;
    }
}