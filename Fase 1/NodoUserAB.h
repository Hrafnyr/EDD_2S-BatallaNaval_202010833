#include <stddef.h>
#include <iostream>
using namespace std;


class UsuarioB{  
    public: 
        string contID;
        string nombre;
        string password;
        string monedas;
        string edad;

        //Pendiente: listaJugadas* jugadas;

        UsuarioB* anterior;
        UsuarioB* siguiente;
        UsuarioB* derecha;
        UsuarioB* izquierda;

        UsuarioB();
        UsuarioB(string contID,string nombre,string password,string monedas,string edad);
};

//Constructores

UsuarioB::UsuarioB() {    //Inicialización
    this->contID="";
    this->nombre = "";
    this->password = "";
    this->monedas = "";
    this->edad = "";
    //this->jugadas = new listaJugadas();

    //apuntador de rama
    this->anterior=NULL;
    this->siguiente=NULL;

    //apuntador rama siguiente
    this->derecha=NULL;
    this->izquierda=NULL;

}

UsuarioB::UsuarioB(string cont, string name,string pass,string mon,string ed) { //asignación
    this->contID=cont;
    this->nombre = name;
    this->password = pass;
    this->monedas = mon;
    this->edad = ed;
    //this->jugadas = new listaJugadas();
    this->anterior=NULL;
    this->siguiente=NULL;
    this->derecha=NULL;
    this->izquierda=NULL;
}
