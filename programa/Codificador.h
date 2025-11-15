#ifndef CODIFICADOR_H
#define CODIFICADOR_H

#include <string>
#include <vector>
#include <map>
#include "Nodo.h"

class Codificador
{
public:
    std::vector<unsigned char> codificar(std::string texto, std::map<char, std::string> &tablaDeCodigos);

    std::string decodificar(std::vector<unsigned char> &datos, long long longitudOriginal, Nodo *raiz);
};

#endif
