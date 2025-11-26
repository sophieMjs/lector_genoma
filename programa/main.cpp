#include <iostream>
#include <sstream>
#include <string>
#include "Comando.h"
#include "Genoma.h"
#include "ArchivoFasta.h"

int main()
{
    std::cout << "=== Proyecto Genoma ===" << std::endl;
    std::cout << "Escribe un comando o ayuda para ver los comandos" << std::endl;

    Comando cmd;
    Genoma genoma;
    ArchivoFasta arch;
    std::string entrada;

    std::cout << "$ ";
    std::getline(std::cin, entrada);
    while (entrada != "salir")
    {

        if (entrada == "ayuda")
        {
            cmd.MontarAyuda();
        }
        else if (entrada == "ayuda comandos")
        {
            std::cout << "Ingresa el comando del cual deseas conocer información." << std::endl
                      << "$ ";
            std::getline(std::cin, entrada);
            cmd.AyudasPorComando(entrada);
        }
        else if (entrada == "salir")
        {

            std::cout << "Finalizando programa..." << std::endl;
        }
        else if (entrada.find("cargar") == 0)
        {
            std::stringstream ss(entrada);
            std::string comando, archivo;
            ss >> comando >> archivo;
            ArchivoFasta af(archivo);
            genoma = af.CargarArchivo();
        }

        else if (entrada == "listar_secuencias")
        {
            genoma.SecuenciasCargadas();
        }
        else if (entrada.find("histograma") == 0)
        {
            std::stringstream ss(entrada);
            std::string comando, nombreSecuencia;
            ss >> comando >> nombreSecuencia;
            genoma.BuscarSecuencia(nombreSecuencia);
        }
        else if (entrada.find("es_subsecuencia") == 0)
        {
            std::stringstream ss(entrada);
            std::string comando, subSec;
            ss >> comando >> subSec;
            genoma.ExisteSub(subSec);
        }

        else if (entrada.find("enmascarar") == 0)
        {
            std::stringstream ss(entrada);
            std::string comando, subSec;
            ss >> comando >> subSec;
            genoma.Enmascarar(subSec);
        }
        else if (entrada.find("guardar") == 0)
        {
            std::stringstream ss(entrada);
            std::string comando, archivo;
            ss >> comando >> archivo;
            ArchivoFasta af(archivo);
            af.GuardarArchivo(genoma);
        }

        else if (entrada.find("codificar") == 0)
        {
            std::stringstream ss(entrada);
            std::string comando, archivo;
            ss >> comando >> archivo;
            genoma.Codificar(archivo);
        }
        else if (entrada.find("decodificar") == 0)
        {
            std::stringstream ss(entrada);
            std::string comando, archivo;
            ss >> comando >> archivo;
            genoma.Decodificar(archivo);
        }
        else if(entrada.find("ruta_mas_corta")==0){
             std::stringstream ss(entrada);
            std::string comando, archivo;
            ss >> comando >> archivo;
        }
        else if(entrada.find("base_remota")==0){
             std::stringstream ss(entrada);
            std::string comando, archivo;
            ss >> comando >> archivo;
        }
        
        

        std::cout << "$ ";
        std::getline(std::cin, entrada);
    }

    return 0;
}
