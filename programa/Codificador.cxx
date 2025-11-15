#include "Codificador.h"
#include <iostream>

std::vector<unsigned char> Codificador::codificar(std::string texto, std::map<char, std::string> &tablaDeCodigos)
{
    std::string bitsgigantes;
    // convierte todo el texto en una lista 0 y 1
    for (char caracter : texto)
    {
        bitsgigantes += tablaDeCodigos[caracter];
    }

    std::vector<unsigned char> resultado;
    unsigned char byteActual = 0;
    int contadorBits = 0;

    // Recorre los bits y los pone en paquetes de 8
    for (char bit : bitsgigantes)
    {
        // Mueve los bits del byte a la izquierda para hacer espacio
        byteActual = byteActual << 1; // CON IA

        // Si el bit es 1, enciéndelo en la última posición
        if (bit == '1')
        {
            byteActual = byteActual | 1; // CON IA
        }

        contadorBits++;

        // Si ya llenamos un byte, lo guarda y empieza uno nuevo
        if (contadorBits == 8)
        {
            resultado.push_back(byteActual);
            contadorBits = 0;
            byteActual = 0;
        }
    }

    // Si quedaron bits sueltos al final, guarda el ultimo byte parcial
    if (contadorBits > 0)
    {
        byteActual = byteActual << (8 - contadorBits); // Mueve los bits al principio del byte CON IA
        resultado.push_back(byteActual);
    }

    return resultado;
}

std::string Codificador::decodificar(std::vector<unsigned char> &datos, long long longitudOriginal, Nodo *raiz)
{
    std::string resultado;
    Nodo *nodoActual = raiz;

    // Recorre cada byte de los datos codificados
    for (unsigned char byte : datos)
    {
        // Dentro de cada byte lee cada uno de sus 8 bits
        for (int i = 7; i >= 0; i--)
        {
            // Revisa si el bit en la posición 'i' es un 1) o un 0)
            char bit = (byte >> i) & 1; // CON IA

            // Avanza en el arbol, si el bit es 0 a la izquierda y si es 1 a la derecha
            if (bit == 0)
            {
                nodoActual = nodoActual->izquierdo;
            }
            else
            {
                nodoActual = nodoActual->derecho;
            }

            // Si llegamos a una hoja encontramos su símbolo
            if (nodoActual->esHoja())
            {
                resultado += nodoActual->simbolo;
                nodoActual = raiz; // Volvemos a la raiz para buscar el siguiente
            }

            if (resultado.length() == longitudOriginal)
            {
                return resultado;
            }
        }
    }

    return resultado;
}
