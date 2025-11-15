#ifndef NODO_H
#define NODO_H

class Nodo
{
public:
    char simbolo;
    long long frecuencia;
    Nodo *izquierdo;
    Nodo *derecho;

    // Constructor para hojas
    Nodo(char sim, long long freq);

    // Constructor para nodos internos
    Nodo(Nodo *izq, Nodo *der);

    // Funcion para saber si un nodo es una hoja
    bool esHoja();
};

#endif
