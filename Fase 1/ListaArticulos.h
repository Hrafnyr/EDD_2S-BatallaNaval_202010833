
#include <iostream>
#include <string>
#include "NodoArticulos.h" 

using namespace std;

//Declaramos clase lista
class listaArticulos{
    //private:            
         
    public:
        nodoArticulos* primero;  
        void insertarInicio(string&,string&,string&,string&);
        void mostrarLista();
        string generarReporte(int&); 

        // void eliminarnodoArticulos(int&); 
        // void eliminarLista();

        listaArticulos();
};

listaArticulos::listaArticulos(){
    this->primero=NULL;
}

void listaArticulos::insertarInicio(string& id,string& nombre,string& precio, string& src){
    
    nodoArticulos* nuevo = new nodoArticulos();//Nuevo nodoArticulos
    
    //Asignar valores
    nuevo->Id = id;
    nuevo->nombre = nombre;
    nuevo->precio = precio;
    nuevo->src = src;
    
    //Manejo de apuntadores
    if (this->primero==NULL)
    {
        primero = nuevo;
    }
    else{
        nuevo->siguiente = primero;
        primero = nuevo;
    }
};

void listaArticulos::mostrarLista(){
    nodoArticulos* actual = new nodoArticulos(); //Auxiliar

    actual = primero;
    cout
        << left
        << setw(10)
        << "Id"
        << left
        << setw(50)
        << "Nombre"
        << left
        << setw(10)
        << "Precio"
        << endl;

    if (primero!=NULL){
        while (actual!=NULL){
            cout
            << left
            << setw(10)
            << actual->Id
            << left
            << setw(50)
            << actual->nombre
            << left
            << setw(10)
            << actual->precio
            << endl;

            actual = actual->siguiente;
        }
    }else{
        cout<<"No hay datos"<<endl;
    }
};

string listaArticulos::generarReporte(int& contCate){
    nodoArticulos* actual = new nodoArticulos(); //Auxiliar
    actual = primero;

    int contAux = 0;
    int aux=0;

    string nodo;
    string NodoR="",ApuntadorR="";

    if (primero!=NULL){
        while (actual!=NULL){

            NodoR+="NodoC"+to_string(contCate)+"_"+to_string(contAux)+"[label=";
            NodoR+="\"ID: "+actual->Id+"\\nNombre: "+actual->nombre+"\\nPrecio: "+actual->precio+"\" fillcolor=\"lemonchiffon\"];\n";

            //Apuntador
            if(actual->siguiente!=NULL){
                if (aux==0)
                {
                    ApuntadorR+="NodoC"+to_string(contCate)+" -> NodoC"+to_string(contCate)+"_"+to_string(contAux)+";\n";
                    aux = 1;
                }
                
                ApuntadorR+="NodoC"+to_string(contCate)+"_"+to_string(contAux)+" -> NodoC"+to_string(contCate)+"_"+to_string(contAux+1)+";\n";
            }
            else{
                if (aux==0)
                {
                   ApuntadorR+="NodoC"+to_string(contCate)+" -> NodoC"+to_string(contCate)+"_"+to_string(contAux)+";\n";
                }
        
            }
            actual = actual->siguiente;
            contAux++;
        }
    }else{
        return "";
    }

    return NodoR+ApuntadorR;
} 

/*
void listaArticulos::eliminarLista(){
    
    while (primero != NULL)
    {
        nodoArticulos *actual = new nodoArticulos(); //nodoArticulos auxiliar

        actual = primero; //Nos posicionamos en la cabecera

        primero = actual->siguiente; //Pasamos al siguiente nodoArticulos hasta llegar a null

        delete actual; //Liberamos
    }

    cout<<"Datos eliminados correctamente"<<endl;
    size_ = 0;
    
}*/