#include "Secuencia.h"
#include "Genoma.h"
#include <fstream>
#include <sstream>
#include <iostream>

Secuencia::Secuencia() {}

Secuencia::Secuencia(std::string n, std::list<char> b, int a, bool c)
    : nombreS(n), bases(b), anchoBase(a), completa(c) {}

void Secuencia::CantidadBases(const Secuencia &c)
{

    if (c.completa)
    {
        std::cout << "Secuencia " << c.nombreS << " contiene " << c.bases.size() << " bases " << std::endl;
    }
    else
    {
        int n = 0;
        for (char base : c.bases)
        {
            if (base != '-')
                n++;
        }
        std::cout << "Secuencia " << c.nombreS << " contiene al menos " << n << " bases " << std::endl;
    }
}
