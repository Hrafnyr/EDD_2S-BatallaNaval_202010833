#include <string>
#include <iostream>
#include "PilaMovimientos.h"
using namespace std;


class nodoJugada{
    public:
        string nombreJugada; //Nombre categoria
        pila* coordenadas; //Jugada tendrá un apuntador a una pila de movimientos
        
        nodoJugada* siguiente;

        nodoJugada();
        nodoJugada(string nombreJugada);
};

nodoJugada::nodoJugada() {    //Inicialización
    this->nombreJugada = "";
    this->coordenadas= new pila();
    this->siguiente=NULL;
}

nodoJugada::nodoJugada(string nuevaJugada) { //asignación
    this->nombreJugada = nuevaJugada;
    this->coordenadas= new pila();
    this->siguiente=NULL;
}
