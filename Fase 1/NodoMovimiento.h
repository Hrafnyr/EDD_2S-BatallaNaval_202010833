#include <string>
#include <iostream>
using namespace std;

class NodoDisparo{  
    public: 
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
