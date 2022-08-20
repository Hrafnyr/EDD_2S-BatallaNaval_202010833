#include <string>
#include <iostream>
using namespace std;

//Para la pila se facilita trabaja como lista doble

class NodoDisparo{  //Puede cambiar el nombre
    public: //Defina atributos publicos tipo nombre;
        string X;
        string Y;

        //Defina apuntadores
        NodoDisparo* anterior;
        NodoDisparo* siguiente;

        NodoDisparo();
        NodoDisparo(string X, string Y);
};

//Constructores

NodoDisparo::NodoDisparo() {    //Inicialización
    this->X = "";
    this->Y = "";
    this->anterior=NULL;
    this->siguiente=NULL;
}

NodoDisparo::NodoDisparo(string nX, string nY) { //asignación
    this->X=nX;
    this->Y=nY;
    this->anterior=NULL;
    this->siguiente=NULL;
}
