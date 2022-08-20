
#include <iostream>
#include <string>
#include "NodoCategoria.h"
//#include "ListaArticulos.h"


using namespace std;

class listaCategoria{
    private:            
        nodoCategoria* primero;   
    public:

        void insertarInicio(string& nombreCate);
        void mostrarLista();
        void insertarNuevoArticulo(string& nombreCate, string& id,string& nom,string& price,string&src); 
        bool verificarExistencia(string&); //Verifica si la categoría está guardada o no
        listaCategoria();

};

listaCategoria::listaCategoria(){ //constructor, apuntar por defecto a null
    this->primero=NULL; 
}

void listaCategoria::insertarInicio(string& nombreCate){
    
    nodoCategoria* nuevo = new nodoCategoria();//Nuevo nodo

    //Asignar valores
    nuevo->categoria = nombreCate;

    if (primero==NULL)
    {
        primero=nuevo;
    }else{
        if (verificarExistencia(nombreCate)!=true) 
        {
            nuevo->siguiente=primero;
            primero=nuevo;
        }
    }    
};

void listaCategoria::mostrarLista(){
    nodoCategoria* actual = new nodoCategoria(); //Auxiliar

    actual = primero;

    if (primero!=NULL){
        while (actual!=NULL){

            cout<<"Categoria: "<<actual->categoria<<endl;
            actual->elementos->mostrarLista();
            actual = actual->siguiente;
        }
    }else{
        cout<<"No hay datos"<<endl;
    }
};

bool listaCategoria::verificarExistencia(string& categoriaB){
    nodoCategoria* actual = new nodoCategoria(); //Auxiliar

    actual = primero;

    while (actual!=NULL){

        if (actual->categoria!=categoriaB)
        {
            actual = actual->siguiente;
        }else{
            return true;
        }
    }
    return false;
};

void listaCategoria::insertarNuevoArticulo(string& nombreCate, string& id,string& nom,string& price, string& src){
    nodoCategoria* actual = new nodoCategoria(); //Auxiliar

    actual = primero;
    
    while (actual!=NULL){

        if (actual->categoria!=nombreCate)
        {
            actual = actual->siguiente;
        }else{
            actual->elementos->insertarInicio(id,nom,price,src);
            break;
        }
    }

};
