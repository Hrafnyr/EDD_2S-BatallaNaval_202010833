#include <string>
#include <iostream>
#include "ListaArticulos.h"
using namespace std;


class nodoCategoria{
    public:
        string categoria; //Nombre categoria
        listaArticulos* elementos; //Categoría tendrá un apuntador a su lista de elementos
        
        nodoCategoria* siguiente;

        nodoCategoria();
        nodoCategoria(string categoria);
};

nodoCategoria::nodoCategoria() {    //Inicialización
    this->categoria = "";
    this->elementos= new listaArticulos();
    this->siguiente=NULL;
}

nodoCategoria::nodoCategoria(string nuevaCategoria) { //asignación
    this->categoria = nuevaCategoria;
    this->elementos= new listaArticulos();
    this->siguiente=NULL;
}
