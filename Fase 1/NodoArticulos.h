#include <string>
#include <iostream>
using namespace std;


class nodoArticulos{  //Puede cambiar el nombre
    public: //Defina atributos publicos tipo nombre;
        string Id;
        string nombre;
        string precio;
        string src;

        //Defina apuntadores Lista simple -> siguiente
        nodoArticulos* siguiente;

        nodoArticulos();
        nodoArticulos(string Id,string nombre,string precio,string src);
};

//Constructores

nodoArticulos::nodoArticulos() {    //Inicialización
    this->Id = "";
    this->nombre="";
    this->precio="";
    this->src="";
    this->siguiente=NULL;
}

nodoArticulos::nodoArticulos(string nuevoID,string nuevoNombre, string nuevoPrecio, string Nsrc) { //asignación
    this->Id = nuevoID;
    this->nombre=nuevoNombre;
    this->precio=nuevoPrecio;
    this->src=Nsrc;
    this->siguiente=NULL;
}
