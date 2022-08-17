#include <string>
#include <iostream>
using namespace std;


class nodoTutorial{  
    public:
        string ancho;
        string alto;
        string cX;
        string cY;

        //Defina apuntadores Lista doble -> anterior y siguiente siguiente
        nodoTutorial* anterior;
        nodoTutorial* siguiente;

        nodoTutorial();
        nodoTutorial(string ancho,string alto,string cX,string cY);
};

//Constructores

nodoTutorial::nodoTutorial() {    //Inicialización
    this->ancho = "";
    this->alto = "";
    this->cX = "";
    this->cY = "";
    this->anterior=NULL;
    this->siguiente=NULL;
}

nodoTutorial::nodoTutorial(string anchoN,string altoN,string cXN,string cYN) { //asignación
    this->ancho = anchoN;
    this->alto = altoN;
    this->cX = cXN;
    this->cY = cYN;
    this->anterior=NULL;
    this->siguiente=NULL;
}
