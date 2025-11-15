#ifndef ARCHIVOFASTA_H
#define ARCHIVOFASTA_H
#include "Genoma.h"
#include <string>
#include <list>

class ArchivoFasta
{
public:
    std::string nombreArchivo;
    ArchivoFasta();
    ArchivoFasta(std::string nombreArchivo);
    Genoma CargarArchivo();
    void GuardarArchivo(const Genoma &g);
};

#endif
