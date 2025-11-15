#ifndef ARBOLHUFFMAN_H
#define ARBOLHUFFMAN_H

#include "Nodo.h"
#include <string>
#include <map>
#include <list>

class ArbolHuffman
{
public:
    Nodo *raiz;

    ArbolHuffman();
    ~ArbolHuffman();

    void construirDesdeFrecuencias(std::map<char, long long> frecuencias);

    // Genera el diccionario de códigos ( A, 01)
    void generarCodigos(std::map<char, std::string> &tablaDeCodigos);

private:
    // Funcion auxiliar recursiva para generar codigos
    void generarCodigosRec(Nodo *nodo, std::string codigoActual, std::map<char, std::string> &tablaDeCodigos);

    // Funcion auxiliar para borrar el arbol y liberar memoria
    void destruirArbol(Nodo *nodo);
};

#endif
