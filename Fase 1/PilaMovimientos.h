
#include <iostream>
#include <string>
#include "NodoMovimiento.h" //Llamada al archivo nodo.h 

using namespace std;

class pila{
    private:   
        NodoDisparo* primero;
        NodoDisparo* ultimo;    
    public:
        void push(string&,string&); //ultimo en entrar primero en salir 1,2,3,4->NULL
        string mostrarPila(int&,int&,int&); 
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

string pila::mostrarPila(int& cont_U, int& cont_J, int& cM){
    NodoDisparo* actual = new NodoDisparo(); //Auxiliar
    actual = primero;
    string Nodo="",apunt="";
    int contM=1;

    apunt+="{\nrank=same\n";

    if (primero!=NULL){
        while (actual!=NULL){

            //nodos de la pila
            Nodo+="Nodo"+to_string(cont_U)+to_string(cont_J)+"_J"+to_string(cont_J)+"_"+to_string(contM);
            Nodo+="[label=\"X: "+actual->X+"\\nY: "+actual->Y+"\"];\n";

            //Apuntadores
            if (actual->siguiente!=NULL)
            {
                apunt+="Nodo"+to_string(cont_U)+to_string(cont_J)+"_J"+to_string(cont_J)+"_"+to_string(contM)+" -> "+"Nodo"+to_string(cont_U)+to_string(cont_J)+"_J"+to_string(cont_J)+"_"+to_string(contM+1)+";\n";
                contM++;
            }

            actual = actual->siguiente;
        }
        apunt+="}\n";
        cM=contM;
        return Nodo+apunt;
    }
    return "";
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
