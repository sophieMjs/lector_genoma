#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <string>
#include <list>
#include "Secuencia.h"

class Secuencia
{
public:
    std::string nombreS;
    std::list<char> bases;
    int anchoBase;
    bool completa;

    Secuencia();
    Secuencia(std::string nombreS, std::list<char> bases, int anchoBase, bool completa);
    void CantidadBases(const Secuencia &c);
};

#endif
