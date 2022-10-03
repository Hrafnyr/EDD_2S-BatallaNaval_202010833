#include <string>
#include <iostream>
#include "ListaJugadas.h"
#include "arbolAVL.h"
using namespace std;


class Usuario{  
    public: 
        string id;
        string nombre;
        string password;
        string monedas;
        string edad;

        listaJugadas* jugadas;
        AVL* compras;

        //Defina apuntadores Lista doble -> anterior y siguiente siguiente
        Usuario* anterior;
        Usuario* siguiente;

        Usuario();
        Usuario(string id, string nombre,string password,string monedas,string edad);
};

//Constructores

Usuario::Usuario() {    //Inicialización
    this->id="";
    this->nombre = "";
    this->password = "";
    this->monedas = "";
    this->edad = "";
    this->jugadas = new listaJugadas();
    this->compras = new AVL();
    this->anterior=NULL;
    this->siguiente=NULL;
}

Usuario::Usuario(string idN, string name,string pass,string mon,string ed) { //asignación
    this->id=idN;
    this->nombre = name;
    this->password = pass;
    this->monedas = mon;
    this->edad = ed;
    this->jugadas = new listaJugadas();
    this->compras = new AVL();
    this->anterior=NULL;
    this->siguiente=NULL;
}
