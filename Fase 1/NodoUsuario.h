#include <string>
#include <iostream>
using namespace std;


class Usuario{  
    public: 
        string nombre;
        string password;
        string monedas;
        string edad;

        //Defina apuntadores Lista doble -> anterior y siguiente siguiente
        Usuario* anterior;
        Usuario* siguiente;

        Usuario();
        Usuario(string nombre,string password,string monedas,string edad);
};

//Constructores

Usuario::Usuario() {    //Inicialización
    this->nombre = "";
    this->password = "";
    this->monedas = "";
    this->edad = "";
    this->anterior=NULL;
    this->siguiente=NULL;
}

Usuario::Usuario(string name,string pass,string mon,string ed) { //asignación
    this->nombre = name;
    this->password = pass;
    this->monedas = mon;
    this->edad = ed;
    this->anterior=NULL;
    this->siguiente=NULL;
}
