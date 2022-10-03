
#include <iostream>
#include <string>
#include "NodoJugada.h"

using namespace std;

class listaJugadas{
    private:            
        nodoJugada* primero;   
    public:

        void nuevaJugada(string& nombre);
        string reporte(int& contU);
        void nuevoMovimiento(string& nombre,string&X,string&Y);
        string verTop(string& nombre);
        void eliminarTop(string& nombre);
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
    cout<<"Se creo la jugada"<<endl;
};

string listaJugadas::reporte(int& contU){
    nodoJugada* actual = new nodoJugada(); //Auxiliar
    actual = primero;

    string c1="",pila="",apt="";
    int contJ=1;
    int contM = 0;

    if (primero!=NULL){
        while (actual!=NULL){
            
            //Cabecera del subgrafo jugada
            c1+="subgraph cluster_"+to_string(contU)+to_string(contJ)+"{\nlabel=\"Jugada: "+actual->nombreJugada+"\";\ncolor=lightyellow;\n";

            //Se llama a los nodos de la pila de movimiento
            pila=actual->coordenadas->mostrarPila(contU,contJ,contM);

            c1+=pila+"}\n"; //Se cierra el subgrafo

            //apuntador hacie subgrafos
            if (actual->siguiente!=NULL)
            {
                apt+="Nodo"+to_string(contU)+to_string(contJ)+"_J"+to_string(contJ)+"_1 -> Nodo"+to_string(contU)+to_string(contJ+1)+"_J"+to_string(contJ+1)+"_1 [ltail=cluster_"+to_string(contU)+to_string(contJ)+" lhead=cluster_"+to_string(contU)+to_string(contJ+1)+"];\n";
                contJ++;
            }
    
            actual = actual->siguiente;
        }
        return c1+apt; 
    }
    return "";
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
            cout<<"Se agregò el movimiento"<<endl;
            break;
        }
    }

};

string listaJugadas::verTop(string& nombre){
    nodoJugada* actual = new nodoJugada(); //Auxiliar
    string tot = " ";
    actual = primero;
    
    while (actual!=NULL){

        if (actual->nombreJugada!=nombre)
        {
            actual = actual->siguiente;
        }else{
            tot = actual->coordenadas->top();
            return tot;
            break;
        }
    }

    return " ";
};

void listaJugadas::eliminarTop(string& nombre){
    nodoJugada* actual = new nodoJugada(); //Auxiliar

    actual = primero;
    
    while (actual!=NULL){

        if (actual->nombreJugada!=nombre)
        {
            actual = actual->siguiente;
        }else{
            actual->coordenadas->pop();
            break;
        }
    }

};
