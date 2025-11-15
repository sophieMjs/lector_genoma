#ifndef GENOMA_H
#define GENOMA_H

#include <string>
#include <list>
#include "Secuencia.h"
#include "ArbolHuffman.h"

class Genoma
{
public:
    std::list<Secuencia> secuencias;

    Genoma();
    Genoma(std::list<Secuencia> secuencias);

    void AgregarSecuencia(const Secuencia &s);
    void SecuenciasCargadas();
    void BuscarSecuencia(std::string n);
    void ExisteSub(std::string sb);
    void Enmascarar(std::string sbs);
    void sumarFrecuencia(char base, int &a, int &c, int &g, int &t, int &u, int &menos, int &r, int &y, int &m, int &k, int &ss, int &w, int &b, int &d, int &h, int &v, int &n);
    void Frecuencia(Secuencia s);
    void Codificar(const std::string &nombreArchivo);
    void Decodificar(const std::string &nombreArchivo);
};

#endif
