
#include <iostream>
#include <string>
#include "NodoJugada.h"

using namespace std;

class listaJugadas{
    private:            
        nodoJugada* primero;   
    public:

        void nuevaJugada(string& nombre);
        void mostrarLista();
        void nuevoMovimiento(string& nombre,string&X,string&Y);
        listaJugadas();

};

listaJugadas::listaJugadas(){ //constructor, apuntar por defecto a null
    this->primero=NULL; 
}

void listaJugadas::nuevaJugada(string& nombre){
    
    nodoJugada* nuevo = new nodoJugada();//Nuevo nodo

    //Asignar valores
    nuevo->nombreJugada = nombre;

    if (primero==NULL)
    {
        primero=nuevo;
    }else{
        nuevo->siguiente=primero;
        primero=nuevo;
    }    
};

void listaJugadas::mostrarLista(){
    nodoJugada* actual = new nodoJugada(); //Auxiliar

    actual = primero;

    if (primero!=NULL){
        while (actual!=NULL){

            cout<<"Nombre Jugada: "<<actual->nombreJugada<<endl;
            actual->coordenadas->mostrarPila();
            actual = actual->siguiente;
        }
    }else{
        cout<<"No hay datos"<<endl;
    }
};

void listaJugadas::nuevoMovimiento(string& nombre,string& X, string& Y){
    nodoJugada* actual = new nodoJugada(); //Auxiliar

    actual = primero;
    
    while (actual!=NULL){

        if (actual->nombreJugada!=nombre)
        {
            actual = actual->siguiente;
        }else{
            actual->coordenadas->push(X,Y);
            break;
        }
    }

};
