
#include <iostream>
#include "NodoMovimiento.h" //Llamada al archivo nodo.h 

using namespace std;

class pila{
    private:   
        NodoDisparo* primero;
        NodoDisparo* ultimo;    
    public:
        void push(string&,string&); //ultimo en entrar primero en salir 1,2,3,4->NULL
        void mostrarPila(); 
        void pop(); //elimina el ultimo elemento apilado
        void top(); //Devuelve el ultimo elemento apilado
        //void eliminarPila();
        pila();
};

pila::pila(){ //constructor, apuntar por defecto a null
    this->primero=NULL; 
    this->ultimo=NULL;
}

void pila::push(string& nX,string& nY){
    
    NodoDisparo* nuevo = new NodoDisparo();//Nuevo nodo

    //Asignar valores
    nuevo->X = nX;
    nuevo->Y = nY;

    //Manejo de apuntadores
    if (primero == NULL)
    {
        primero = nuevo;
        primero->siguiente = NULL;
    }
    else{
        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;
        nuevo->siguiente = NULL;
    }
    ultimo = nuevo;
};

void pila::mostrarPila(){
    NodoDisparo* actual = new NodoDisparo(); //Auxiliar

    actual = primero;

    if (primero!=NULL){
        while (actual!=NULL){

            cout<<"Coordenadas: ("<<actual->X<<","<<actual->Y<<")"<<endl;
            
            actual = actual->siguiente;
        }
    }else{
        cout<<"No hay datos"<<endl;
    }
};

void pila::top(){
    NodoDisparo* temporal = new NodoDisparo(); //Auxiliar

    temporal = primero;

    if (primero!=NULL){
        while (temporal->siguiente!=NULL){
            temporal = temporal->siguiente;
        }
    }
    else{
        cout<<"No hay datos"<<endl;
    }
    cout<<temporal->X<<","<<temporal->Y;
}

void pila::pop(){
    
    NodoDisparo *actual = new NodoDisparo(); //Nodo actual y el que se debe eliminar al final
    actual = ultimo;

    if (actual->anterior != NULL)
    {
        ultimo = actual->anterior;
        actual->anterior->siguiente = NULL;
    }
    else{
        primero = NULL;
        ultimo = NULL;
    }

    delete actual;
    
};

/*void pila::eliminarPila(){
    
    while (primero != NULL)
    {
        NodoDisparo *actual = new NodoDisparo(); //Nodo actual y el que se debe eliminar al final
        actual = ultimo;

        if (actual->anterior != NULL)
        {
            ultimo = actual->anterior;
            actual->anterior->siguiente = NULL;
        }
        else{
            primero = NULL;
            ultimo = NULL;
        }

        delete actual;
    }

    cout<<"Datos eliminados correctamente"<<endl;
    
}*/
