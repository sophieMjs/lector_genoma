#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <string>
#include <list>
#include "Secuencia.h"
#include <vector>
#include <map>

struct Arista{
    double peso;
    int vecino;
};

class Secuencia
{
public:
    std::string nombreS;
    std::list<char> bases;
    int anchoBase;
    bool completa;
    std::vector<std::vector<char>> matrizBases;
    std::vector<std::list<Arista>> adj;


    void ConstruirMatrizYGrafo();
    int GetFilas() const;
    int GetColumnas() const;
    char GetBaseAt(int i, int j) const;
    int GetIndiceVertice(int i, int j) const;
    std::pair<int, int> GetCoordsVertice(int indice) const;

    Secuencia();
    Secuencia(std::string nombreS, std::list<char> bases, int anchoBase, bool completa);
    void CantidadBases(const Secuencia &c);
};

#endif
