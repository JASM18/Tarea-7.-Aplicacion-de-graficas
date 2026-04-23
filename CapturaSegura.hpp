/**
* \file CapturaSegura.hpp
 * \brief Plantilla para la validaci&oacute;n de entrada de datos num&eacute;ricos.
 * \date 10/02/2026
 */

#ifndef CAPTURASEGURA_HPP_INCLUDED
#define CAPTURASEGURA_HPP_INCLUDED

/**
 * \brief Captura de forma segura un n&uacute;mero desde la entrada est&aacute;ndar.
 *
 * Verifica que el dato ingresado corresponda al tipo esperado. Si falla,
 * limpia el buffer y solicita el dato nuevamente.
 *
 * \tparam T Tipo de dato num&eacute;rico a capturar (int, float, double).
 * \param num Referencia a la variable donde se almacenar&aacute; el n&uacute;mero.
 * \param solicitud Mensaje que se mostrar&aacute; al usuario solicitando el dato.
 */
template <typename T>
void CapturarNumero(T &num, const char solicitud[]);

#include "CapturaSegura.tpp"

#endif // CAPTURASEGURA_HPP_INCLUDED