#include "ArchivoFasta.h"
#include "Genoma.h"
#include "Secuencia.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cctype>  

ArchivoFasta::ArchivoFasta(std::string nombreAr)
{
     nombreArchivo = "data/" + nombreAr;
}
ArchivoFasta::ArchivoFasta() {}

Genoma ArchivoFasta::CargarArchivo(){
    Genoma genoma;
    std::ifstream file(nombreArchivo+ ".fa"+".txt");
 
    if (!file.is_open())
    {
        std::cerr << nombreArchivo << " No se encuentra o no puede leerse" << std::endl;
    }

    std::string linea;
    std::list <char> secuencia;
    std::string nombreSecuencia;
    int ancho;
    int primeraLinea=0;
    bool completa=true;
    int contarSecuencias=1;
    while (std::getline(file, linea)){
        if (linea.empty())
            continue;
        if (linea[0] == '>'){
            if (!nombreSecuencia.empty()) {
                Secuencia sec(nombreSecuencia, secuencia, ancho, completa);
                genoma.AgregarSecuencia(sec);
                contarSecuencias++;
            }
          
            secuencia.clear();       
            primeraLinea=0;          
            completa=true;           
            nombreSecuencia = linea.substr(1);
	    nombreSecuencia.erase(0, nombreSecuencia.find_first_not_of(" \t\r\n"));
	    nombreSecuencia.erase(nombreSecuencia.find_last_not_of(" \t\r\n") + 1);
        }else {
            linea.erase(std::remove_if(linea.begin(), linea.end(), ::isspace), linea.end());

            for (char c : linea) {
                if(primeraLinea==0) ancho=linea.size();
                if(c=='-')completa=false;
                secuencia.push_back(c);
            }
            primeraLinea++;
        }

    }


    if (!nombreSecuencia.empty()) {
        Secuencia sec(nombreSecuencia, secuencia, ancho, completa);
        genoma.AgregarSecuencia(sec);
    }

    if(contarSecuencias==0){
        std::cout<< nombreArchivo <<" no contiene ninguna secuencia."<<std::endl;
    }else if(contarSecuencias==1){
        std::cout<<"1 secuencia cargada correctamente desde "<<nombreArchivo<<std::endl;
    }else{
    
        std::cout<< contarSecuencias <<" secuencias cargadas correctamente desde "<<nombreArchivo<<std::endl;
    }

    return genoma;
}


void ArchivoFasta::GuardarArchivo(const Genoma& g) {
    
    if (g.secuencias.empty()) {
        std::cout << "No hay secuencias cargadas en memoria." << std::endl;
        return;
    }

    std::ofstream out(nombreArchivo + ".fa");
    if (!out.is_open()) {
        std::cerr << "Error guardando en " << nombreArchivo << std::endl;
        return;
    }

    for (const Secuencia& s : g.secuencias) {
        
        out << ">" << s.nombreS << "\n";

        
        int count = 0;
        for (std::list<char>::const_iterator it = s.bases.begin(); it != s.bases.end(); it++) {
            out << *it;
            count++;
            if (count == s.anchoBase)   {
                out << "\n";
                count = 0;
            }
        }
        out << "\n"; 
    }

    out.close();
    std::cout << "Las secuencias han sido guardadas " << nombreArchivo << ".fa"<< std::endl;
}


