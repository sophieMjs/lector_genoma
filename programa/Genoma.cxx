#include "Genoma.h"
#include "Secuencia.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "ArbolHuffman.h"
#include "Codificador.h"
#include <map>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>
#include <list>

struct Estado
{
    double costo;
    int indice;
    bool operator<(const Estado &otro) const
    {
        return costo > otro.costo;
    }
};

struct ResultadoDijkstra
{
    std::vector<double> distancias;
    std::vector<int> padres;
};

ResultadoDijkstra EjecutarDijkstra(const Secuencia& sec, int indiceOrigen) {
    int totalVertices = sec.adj.size();
    ResultadoDijkstra res;

    double infinito = 1000000000.0;

    res.distancias.clear();
    res.padres.clear();

    for (int k = 0; k < totalVertices; k++) {
        res.distancias.push_back(infinito);
        res.padres.push_back(-1);
    }

    std::priority_queue<Estado> cola;

    res.distancias[indiceOrigen] = 0.0;
    cola.push({0.0, indiceOrigen});

    while (!cola.empty()) {
        Estado actual = cola.top();
        cola.pop();

        if (actual.costo > res.distancias[actual.indice]) {
            continue;
        }

        std::list<Arista>::const_iterator it;
        for (it = sec.adj[actual.indice].begin(); it != sec.adj[actual.indice].end(); ++it) {
            int vecino = it->vecino;
            double pesoArista = it->peso;
            
            double nuevoCosto = res.distancias[actual.indice] + pesoArista;

            if (nuevoCosto < res.distancias[vecino]) {
                res.distancias[vecino] = nuevoCosto;
                res.padres[vecino] = actual.indice;
                cola.push({nuevoCosto, vecino});
            }
        }
    }
    return res;
}

Genoma::Genoma() {}
Genoma::Genoma(std::list<Secuencia> secuencias) : secuencias(secuencias) {}

void Genoma::AgregarSecuencia(const Secuencia &s)
{
    secuencias.push_back(s);
}

void Genoma::SecuenciasCargadas()
{
    Secuencia c;
    if (secuencias.empty())
    {
        std::cout << "No hay secuencias cargadas en memoria" << std::endl;
    }
    else
    {
        int cantSecuencias = secuencias.size();
        std::cout << "Hay " << cantSecuencias << " secuencias cargadas en memoria." << std::endl;
        for (Secuencia s : secuencias)
        {
            c.CantidadBases(s);
        }
    }
}

void Genoma::BuscarSecuencia(std::string n)
{
    bool encontrado = false;
    for (Secuencia s : secuencias)
    {
        if (s.nombreS == n)
        {
            Frecuencia(s);
            encontrado = true;
        }
    }
    if (!encontrado)
        std::cout << "Secuencia inválida" << std::endl;
}

void Genoma::ExisteSub(std::string sb)
{
    if (secuencias.empty())
    {
        std::cout << "No hay secuencias cargadas en memoria.\n";
        return;
    }

    int x = sb.size();
    int cantVeces = 0;

    for (Secuencia s : secuencias)
    {
        int i = 0;
        int total = 0;
        int ancho = 0;
        for (char c : s.bases)
        {
            ancho++;
            if (c == sb[i])
            {
                total++;
                i++;
                if (total == x)
                {
                    cantVeces++;
                    int next_i = 0;
                    if (c == sb[0])
                    {
                        next_i = 1;
                    }
                    i = next_i;
                    total = next_i;
                }
            }
            else
            {
                int next_i = 0;
                if (c == sb[0])
                {
                    next_i = 1;
                }
                i = next_i;
                total = next_i;
            }
            if (ancho == s.anchoBase)
            {
                total = 0;
                i = 0;
                ancho = 0;
            }
        }
    }

    if (cantVeces == 0)
    {
        std::cout << "La subsecuencia dada no existe dentro de las secuencias cargadas\n";
    }
    else
    {
        std::cout << "La subsecuencia dada se repite " << cantVeces << " veces dentro de las secuencias cargadas en memoria.\n";
    }
}

void Genoma::Enmascarar(std::string sb)
{
    if (secuencias.empty())
    {
        std::cout << "No hay secuencias cargadas en memoria." << std::endl;
        return;
    }

    int x = sb.size();
    bool encontrado = false;
    int cambiadas = 0;
    for (Secuencia &s : secuencias)
    {
        int i = 0;
        int total = 0;
        std::list<char>::iterator it;
        int ancho = 0;
        for (it = s.bases.begin(); it != s.bases.end(); ++it)
        {
            ancho++;
            if (*it == sb[i])
            {
                total++;
                i++;
                if (total == x)
                {
                    cambiadas++;
                    char caracter_original = *it;
                    encontrado = true;
                    std::list<char>::iterator jt = it;
                    for (int j = 0; j < x; j++)
                    {
                        *jt = 'X';
                        --jt;
                    }
                    int next_i = 0;
                    if (caracter_original == sb[0])
                    {
                        next_i = 1;
                    }
                    i = next_i;
                    total = next_i;
                }
            }
            else
            {
                int sig_i = 0;
                if (*it == sb[0])
                {
                    sig_i = 1;
                }
                i = sig_i;
                total = sig_i;
            }
            if (ancho == s.anchoBase)
            {
                total = 0;
                i = 0;
                ancho = 0;
            }
        }
    }

    if (!encontrado)
    {
        std::cout << "La subsecuencia dada no existe dentro de las secuencias cargadas en memoria, por tanto no se enmascara nada." << std::endl;
    }
    else
    {
        std::cout << cambiadas << " subsecuencias han sido enmascaradas dentro de las secuencias cargadas en memoria." << std::endl;
    }
}

void Genoma::sumarFrecuencia(char base, int &a, int &c, int &g, int &t, int &u, int &menos, int &r, int &y, int &m, int &k, int &ss, int &w, int &b, int &d, int &h, int &v, int &n)
{
    if (base == 'A')
    {
        a++;
    }
    else if (base == 'C')
    {
        c++;
    }
    else if (base == 'G')
    {
        g++;
    }
    else if (base == 'T')
    {
        t++;
    }
    else if (base == 'U')
    {
        u++;
    }
    else if (base == '-')
    {
        menos++;
    }
    else if (base == 'R')
    {
        r++;
    }
    else if (base == 'Y')
    {
        y++;
    }
    else if (base == 'M')
    {
        m++;
    }
    else if (base == 'K')
    {
        k++;
    }
    else if (base == 'S')
    {
        ss++;
    }
    else if (base == 'W')
    {
        w++;
    }
    else if (base == 'B')
    {
        b++;
    }
    else if (base == 'D')
    {
        d++;
    }
    else if (base == 'H')
    {
        h++;
    }
    else if (base == 'V')
    {
        v++;
    }
    else if (base == 'N')
    {
        n++;
    }
}

void Genoma::Frecuencia(Secuencia s)
{
    int a = 0, c = 0, g = 0, t = 0, u = 0, menos = 0, r = 0, y = 0, m = 0, k = 0, ss = 0, w = 0, b = 0, d = 0, h = 0, v = 0, n = 0;
    for (char p : s.bases)
    {
        sumarFrecuencia(p, a, c, g, t, u, menos, r, y, m, k, ss, w, b, d, h, v, n);
    }

    std::cout << "Frecuencias:" << std::endl;
    std::cout << "A: " << a << "  "
              << "C: " << c << "  "
              << "G: " << g << "  "
              << "T: " << t << "  "
              << "U: " << u << "  "
              << "-: " << menos << "  "
              << "R: " << r << "  "
              << "Y: " << y << "  "
              << "M: " << m << "  "
              << "K: " << k << "  "
              << "S: " << ss << "  "
              << "W: " << w << "  "
              << "B: " << b << "  "
              << "D: " << d << "  "
              << "H: " << h << "  "
              << "V: " << v << "  "
              << "N: " << n << std::endl;
}

void Genoma::Codificar(const std::string &nombreArchivo)
{
    if (secuencias.empty())
    {
        std::cout << "No hay secuencias cargadas en memoria." << std::endl;
        return;
    }

    std::map<char, long long> frecuencias;
    for (Secuencia s : secuencias)
    {
        for (char base : s.bases)
        {
            frecuencias[base]++;
        }
    }

    ArbolHuffman arbol;
    arbol.construirDesdeFrecuencias(frecuencias);

    std::map<char, std::string> tablaDeCodigos;
    arbol.generarCodigos(tablaDeCodigos);

    std::ofstream archivoSalida("data/" + nombreArchivo + ".fabin", std::ios::binary);
    if (!archivoSalida.is_open())
    {
        std::cerr << "No se pueden guardar las secuencias cargadas en " << nombreArchivo << ".fabin" << std::endl;
        return;
    }

    short n_bases = frecuencias.size();
    archivoSalida.write(reinterpret_cast<char *>(&n_bases), sizeof(short));
    for (auto par : frecuencias)
    {
        archivoSalida.write(&par.first, sizeof(char));
        archivoSalida.write(reinterpret_cast<char *>(&par.second), sizeof(long long));
    }

    int n_secuencias = secuencias.size();
    archivoSalida.write(reinterpret_cast<char *>(&n_secuencias), sizeof(int));

    Codificador codificador;
    for (Secuencia s : secuencias)
    {
        short nombre_len = s.nombreS.length();
        archivoSalida.write(reinterpret_cast<char *>(&nombre_len), sizeof(short));
        archivoSalida.write(s.nombreS.c_str(), nombre_len);

        long long secuencia_len = s.bases.size();
        archivoSalida.write(reinterpret_cast<char *>(&secuencia_len), sizeof(long long));

        short ancho = s.anchoBase;
        archivoSalida.write(reinterpret_cast<char *>(&ancho), sizeof(short));

        std::string secuenciaStr(s.bases.begin(), s.bases.end());
        std::vector<unsigned char> datosCodificados = codificador.codificar(secuenciaStr, tablaDeCodigos);

        long long tamano_codificado = datosCodificados.size();
        archivoSalida.write(reinterpret_cast<char *>(&tamano_codificado), sizeof(long long));
        archivoSalida.write(reinterpret_cast<char *>(datosCodificados.data()), datosCodificados.size());
    }

    archivoSalida.close();
    std::cout << "Secuencias codificadas y almacenadas en " << nombreArchivo << ".fabin" << std::endl;
}

void Genoma::Decodificar(const std::string &nombreArchivo)
{
    std::ifstream archivoEntrada("data/" + nombreArchivo + ".fabin", std::ios::binary);
    if (!archivoEntrada.is_open())
    {
        std::cerr << "No se pueden cargar las secuencias desde " << nombreArchivo << ".fabin" << std::endl;
        return;
    }

    secuencias.clear();

    std::map<char, long long> frecuencias;
    short n_bases;
    archivoEntrada.read(reinterpret_cast<char *>(&n_bases), sizeof(short));

    for (int i = 0; i < n_bases; ++i)
    {
        char base;
        long long freq;
        archivoEntrada.read(&base, sizeof(char));
        archivoEntrada.read(reinterpret_cast<char *>(&freq), sizeof(long long));
        frecuencias[base] = freq;
    }

    ArbolHuffman arbol;
    arbol.construirDesdeFrecuencias(frecuencias);

    int n_secuencias;
    archivoEntrada.read(reinterpret_cast<char *>(&n_secuencias), sizeof(int));

    Codificador decodificador;

    for (int i = 0; i < n_secuencias; ++i)
    {

        short nombre_len;
        archivoEntrada.read(reinterpret_cast<char *>(&nombre_len), sizeof(short));

        std::string nombre_secuencia(nombre_len, '\0');
        archivoEntrada.read(&nombre_secuencia[0], nombre_len);

        long long secuencia_len_original;
        archivoEntrada.read(reinterpret_cast<char *>(&secuencia_len_original), sizeof(long long));

        short ancho;
        archivoEntrada.read(reinterpret_cast<char *>(&ancho), sizeof(short));

        long long tamano_codificado;
        archivoEntrada.read(reinterpret_cast<char *>(&tamano_codificado), sizeof(long long));

        std::vector<unsigned char> datosCodificados(tamano_codificado);
        archivoEntrada.read(reinterpret_cast<char *>(datosCodificados.data()), tamano_codificado);

        std::string secuenciaDecodificada = decodificador.decodificar(datosCodificados, secuencia_len_original, arbol.raiz);

        std::list<char> bases(secuenciaDecodificada.begin(), secuenciaDecodificada.end());

        bool completa = true;
        for (char base : bases)
        {
            if (base == '-')
            {
                completa = false;
                break;
            }
        }

        Secuencia s(nombre_secuencia, bases, ancho, completa);
        AgregarSecuencia(s);
    }

    archivoEntrada.close();
    std::cout << "Secuencias decodificadas desde " << nombreArchivo << ".fabin" << " y cargadas en memoria." << std::endl;
}

void Genoma::RutaMasCorta(std::string nombreSec, int i, int j, int x, int y) {
    Secuencia* sec = nullptr;
    std::list<Secuencia>::iterator it;
    for (it = secuencias.begin(); it != secuencias.end(); ++it) {
        if (it->nombreS == nombreSec) {
            sec = &(*it);
            break;
        }
    }

    if (sec == nullptr) {
        std::cout << "La secuencia " << nombreSec << " no existe." << std::endl;
        return;
    }

    int indiceOrigen = sec->GetIndiceVertice(i, j);
    char baseOrigen = sec->GetBaseAt(i, j);
    
    if (baseOrigen == '\0') { 
        std::cout << "La base en la posicion [" << i << "," << j << "] no existe." << std::endl;
        return;
    }

    int indiceDestino = sec->GetIndiceVertice(x, y);
    char baseDestino = sec->GetBaseAt(x, y);
    if (baseDestino == '\0') {
        std::cout << "La base en la posicion [" << x << "," << y << "] no existe." << std::endl;
        return;
    }

    ResultadoDijkstra resultado = EjecutarDijkstra(*sec, indiceOrigen);

    double costoTotal = resultado.distancias[indiceDestino];

    if (costoTotal >= 1000000000.0) {
         std::cout << "No existe una ruta entre esas bases." << std::endl;
         return;
    }

    std::cout << "Para la secuencia " << nombreSec << ", la ruta mas corta entre" << std::endl;
    std::cout << "la base " << baseOrigen << " en [" << i << "," << j << "] y la base " << baseDestino << " en [" << x << "," << y << "] es:" << std::endl;

    std::list<int> ruta;
    int paso = indiceDestino;
    while (paso != -1) {
        ruta.push_front(paso);
        paso = resultado.padres[paso];
    }
    
    std::list<int>::iterator itRuta;
    for (itRuta = ruta.begin(); itRuta != ruta.end(); ++itRuta) {
        int idx = *itRuta;
        std::pair<int, int> coords = sec->GetCoordsVertice(idx);
        char base = sec->GetBaseAt(coords.first, coords.second);
        std::cout << "-> [" << coords.first << "," << coords.second << "] (" << base << ") " << std::endl;
    }

    std::cout << "El costo total de la ruta es: " << costoTotal << std::endl;
}

void Genoma::BaseRemota(std::string nombreSec, int i, int j) {
    Secuencia* sec = nullptr;
    std::list<Secuencia>::iterator it;
    for (it = secuencias.begin(); it != secuencias.end(); ++it) {
        if (it->nombreS == nombreSec) {
            sec = &(*it);
            break;
        }
    }

    if (sec == nullptr) {
        std::cout << "La secuencia " << nombreSec << " no existe." << std::endl;
        return;
    }

    int indiceOrigen = sec->GetIndiceVertice(i, j);
    char baseOrigen = sec->GetBaseAt(i, j);
    if (baseOrigen == '\0') {
        std::cout << "La base en la posicion [" << i << "," << j << "] no existe." << std::endl;
        return;
    }

    ResultadoDijkstra resultado = EjecutarDijkstra(*sec, indiceOrigen);

    double maxCosto = -1.0;
    int indiceRemoto = -1;

    for (int k = 0; k < sec->adj.size(); ++k) {
        if (k == indiceOrigen) continue;

        std::pair<int, int> coords = sec->GetCoordsVertice(k);
        char baseActual = sec->GetBaseAt(coords.first, coords.second);

        if (baseActual == baseOrigen) {
            double costo = resultado.distancias[k];
            if (costo < 1000000000.0 && costo > maxCosto) {
                maxCosto = costo;
                indiceRemoto = k;
            }
        }
    }

    if (indiceRemoto == -1) {
        std::cout << "No se encontro otra base '" << baseOrigen << "' en la secuencia." << std::endl;
        return;
    }

    std::pair<int, int> coordsRemotas = sec->GetCoordsVertice(indiceRemoto);
    std::cout << "Para la secuencia " << nombreSec << ", la base remota esta ubicada" << std::endl;
    std::cout << "en [" << coordsRemotas.first << "," << coordsRemotas.second << "], y la ruta entre la base en [" << i << "," << j << "] y la base remota en [" << coordsRemotas.first << "," << coordsRemotas.second << "] es:" << std::endl;

    std::list<int> ruta;
    int paso = indiceRemoto;
    while (paso != -1) {
        ruta.push_front(paso);
        paso = resultado.padres[paso];
    }
    
    std::list<int>::iterator itRuta;
    for (itRuta = ruta.begin(); itRuta != ruta.end(); ++itRuta) {
        int idx = *itRuta;
        std::pair<int, int> coords = sec->GetCoordsVertice(idx);
        char base = sec->GetBaseAt(coords.first, coords.second);
        std::cout << "-> [" << coords.first << "," << coords.second << "] (" << base << ") " << std::endl;
    }

    std::cout << "El costo total de la ruta es: " << maxCosto << std::endl;
}