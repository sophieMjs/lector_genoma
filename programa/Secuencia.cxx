#include "Secuencia.h"
#include "Genoma.h"
#include <fstream>
#include <sstream>
#include <iostream>     
#include <vector>
#include <map>
#include <cmath>

Secuencia::Secuencia() {}

Secuencia::Secuencia(std::string n, std::list<char> b, int a, bool c)
    : nombreS(n), bases(b), anchoBase(a), completa(c) {
        ConstruirMatrizYGrafo();
    }

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

void Secuencia::ConstruirMatrizYGrafo() {
    if (bases.empty() || anchoBase == 0)return;

    matrizBases.clear();
    std::vector<char>filaActual;
    int contador = 0;

    for (char base : bases) {
        filaActual.push_back(base);
        contador++;
        if(contador == anchoBase){
            matrizBases.push_back(filaActual);
            filaActual.clear();
            contador = 0;
        }
    }

    if(!filaActual.empty()){
        matrizBases.push_back(filaActual);
    }

    int filas = GetFilas();
    if(filas==0)return;
    int columnas = GetColumnas();
    int totalVertices = filas * columnas; 
    
    totalVertices = 0;
    for(const auto& fila : matrizBases) {
        totalVertices += fila.size();
    }
    
    adj.clear();
    adj.resize(totalVertices);

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < matrizBases[i].size(); ++j) {
            
            int indiceOrigen = GetIndiceVertice(i, j);
            char charOrigen = matrizBases[i][j];

            int dx[] = {-1, 1, 0, 0};
            int dy[] = {0, 0, -1, 1};

            for (int k = 0; k < 4; ++k) {
                int ni = i + dx[k];
                int nj = j + dy[k];

                // Validar límites
                if (ni >= 0 && ni < filas && nj >= 0 && nj < matrizBases[ni].size()) {
                    
                    int indiceDestino = GetIndiceVertice(ni, nj);
                    char charDestino = matrizBases[ni][nj];

                    // Calcular peso
                    double peso = 1.0 / (1.0 + std::abs(static_cast<int>(charOrigen) - static_cast<int>(charDestino)));

                    // Añadir arista
                    adj[indiceOrigen].push_back(Arista{peso, indiceDestino});
                }
            }
        }
    }
}

int Secuencia::GetFilas() const {
    return matrizBases.size();
}

int Secuencia::GetColumnas() const {
    return anchoBase;
}

char Secuencia::GetBaseAt(int i, int j) const {
    if (i >= 0 && i < matrizBases.size() && j >= 0 && j < matrizBases[i].size()) {
        return matrizBases[i][j];
    }
    return '\0';
}

int Secuencia::GetIndiceVertice(int i, int j) const {
    int indice = 0;
    for(int fila = 0; fila < i; ++fila) {
        indice += matrizBases[fila].size();
    }
    indice += j;
    return indice;
}

std::pair<int, int> Secuencia::GetCoordsVertice(int indice) const {
    // Mapeo 1D a 2D
    int contador = 0;
    for (int i = 0; i < matrizBases.size(); ++i) {
        for (int j = 0; j < matrizBases[i].size(); ++j) {
            if (contador == indice) {
                return {i, j};
            }
            contador++;
        }
    }
    return {-1, -1};
}
