#include "Nodo.h"

Nodo::Nodo(char sim, long long freq)
{
    simbolo = sim;
    frecuencia = freq;
    izquierdo = nullptr;
    derecho = nullptr;
}

Nodo::Nodo(Nodo *izq, Nodo *der)
{
    simbolo = 0;
    frecuencia = izq->frecuencia + der->frecuencia; // La frecuencia es la suma de sus hijos
    izquierdo = izq;
    derecho = der;
}

bool Nodo::esHoja()
{
    return izquierdo == nullptr && derecho == nullptr;
}
