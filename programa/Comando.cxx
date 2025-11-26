#include "Comando.h"
#include <iostream>

Comando::Comando() {}

void Comando::MontarAyuda()
{
    std::cout << "1- cargar //nombre_archivo\n"
              << "2- listar_secuencias\n"
              << "3- histograma //nombre_secuencia\n"
              << "4- es_subsecuencia //subsecuencia\n"
              << "5- enmascarar //subsecuencia\n"
              << "6- guardar //nombre_para_guardar_archivo\n"
              << "7- codificar //nombre_para_guardar_archivo\n"
              << "8- decodificar //nombre_archivo_a_decodificar\n"
              << "9- ruta_mas_corta //descripcion_secuencia i j x y\n"
              << "10- base_remota //descripcion_secuencia i j\n"
              << "11- salir" << std::endl;
    std::cout << "Para recibir ayuda sobre algun comando en especifico escribe: ayuda comandos" << std::endl;
}

void Comando::AyudasPorComando(std::string comandoAuxilio)
{
    comando = comandoAuxilio;
    if (comando == "cargar")
        std::cout << "Se encarga de leer el archivo FASTA indicado y carga todas las secuencias dentro del genoma activo." << std::endl;
    else if (comando == "listar_secuencias")
        std::cout << "Muestra un resumen de cada secuencia: su nombre, cantidad de bases y si está completa o no." << std::endl;
    else if (comando == "histograma")
        std::cout << "Calcula la frecuencia de las bases principales (A, C, G, T, U) ." << std::endl;
    else if (comando == "es_subsecuencia")
        std::cout << "Revisa si la subsecuencia dada aparece en alguna secuencia del genoma, e indica cuántas veces se repite." << std::endl;
    else if (comando == "enmascarar")
        std::cout << "Busca todas las apariciones de la subsecuencia en el genoma y las enmascara con 'X' " << std::endl;
    else if (comando == "guardar")
        std::cout << "Guarda el genoma activo (todas las secuencias en memoria, con sus posibles modificaciones) en un archivo FASTA de salida." << std::endl;
    else if (comando == "codificar")
        std::cout << "codifica el genoma cargado en un archivo .fabin, debe escribir el nombre del archivo para guardar (sin el .fabin)" << std::endl;
    else if (comando == "decodificar")
        std::cout << "decodifica un archivo .fabin y lo carga en memoria, debe escribir el nombre del archivo .fabin a decodificar (sin el .fabin)" << std::endl;
    else if (comando == "ruta_mas_corta")
        std::cout << "Calcula e imprime la ruta de costo mínimo (usando grafos) entre la base en la posición [i,j] y la base en [x,y] dentro de la secuencia indicada." << std::endl;
    else if (comando == "base_remota")
        std::cout << "Busca la ubicación de la misma base (letra idéntica) más lejana dentro de la matriz de la secuencia, partiendo de la posición [i,j]." << std::endl;
    else if (comando == "salir")
        std::cout << "Para salir del programa." << std::endl;
}
