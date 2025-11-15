#ifndef COMANDO_H
#define COMANDO_H

#include <string>
#include <list>
#include "Genoma.h"

class Comando
{
public:
    // Constructor
    std::string comando;
    Comando();
    void AyudasPorComando(std::string comandoAuxilio);
    void MontarAyuda();
};

#endif
