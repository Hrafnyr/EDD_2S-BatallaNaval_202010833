
#include <iostream>
#include "NodoUsuario.h" 

using namespace std;

//Declaramos clase lista
class listaUsuarios{
    private:            
        Usuario* primero;
        Usuario* ultimo;    
        int size_ = 0;  
    public:
        void insertarNuevo(string&,string&,string&,string&);
        void mostrarUsuarios(); 

        void modificarInformacion(string&,string&,string&);

        void eliminarCuenta(string&,string&);

        //Falta ordenar por edad

        //void eliminarLista(); 
        listaUsuarios();
        
};

listaUsuarios::listaUsuarios(){ //constructor, apuntar por defecto a null
    this->primero=NULL; 
    this->ultimo=NULL;
}

void listaUsuarios::insertarNuevo(string& nickname, string& pass, string& mon, string& ed){
    
    Usuario* nuevo = new Usuario();//Nuevo nodo

    //Asignar valores
    nuevo->nombre = nickname;
    nuevo->password = pass;
    nuevo->monedas = mon;
    nuevo->edad = ed;
    size_++;

    //Manejo de apuntadores
    if (primero == NULL)
    {
        primero = nuevo;
        ultimo = nuevo;
        primero->siguiente = primero;
        primero->anterior = ultimo;
    }
    else{
        ultimo->siguiente = nuevo; //Siguiente del ultimo es nuevo
        nuevo->anterior = ultimo; //El anterior del nuevo ahora apunta al ultimo
    
        nuevo->siguiente = primero; //Conectamos el siguiente del nuevo al primero
        ultimo = nuevo; //ahora el ultimo es nuevo
        primero->anterior = ultimo; //Conectamos el anterior del primero al ultimo
    }

};

//Metodo de prueba para verifica la correcta insercion de usuarios
void listaUsuarios::mostrarUsuarios(){
    Usuario* actual = new Usuario(); //Auxiliar

    actual = primero;

    if (primero!=NULL){
        do
        {
            cout<<"-------------------"<<endl;
            cout<<actual->nombre<<endl;
            cout<<actual->password<<endl;
            cout<<actual->monedas<<endl;
            cout<<actual->edad<<endl;
            cout<<"-------------------"<<endl;

            actual = actual->siguiente;
        } while (actual!=primero);
        
    }else{
        cout<<"No hay datos"<<endl;
    }

};

void listaUsuarios::eliminarCuenta(string& nameBuscar,string& passB){
    
    Usuario* actual = new Usuario();
    actual = primero;
    Usuario* aux = new Usuario();
    aux = NULL;

    bool encontrado = false;
    
    if(primero!=NULL){
        do{
            if((actual->nombre==nameBuscar)&&(actual->password==passB)){
                cout<<"\n Eliminando:"<<actual->nombre<<"\n";

                //Si solo hay un nodo
                if ((actual==primero)&&(primero==ultimo))
                {
                    primero = NULL;
                    ultimo = NULL;
                }else if (actual==primero){ //Si está al principio
                    primero = primero->siguiente; //Primero es igual al siguiente
                    primero->anterior=ultimo; //Se conetca primero y ultimo
                    ultimo->siguiente = primero; 
                }else if(actual==ultimo){
                    ultimo = aux; //En ese punto aux contiene el anterior del ultimo
                    ultimo->siguiente = primero; //ultimo ya es el anterior y apunta a primero
                    primero->anterior = ultimo; //Se redirecciona el anterior del primero 
                }else{
                    aux->siguiente = actual->siguiente; //Si no el nodo está en medio de la lista
                    actual->siguiente->anterior = aux;
                }
                size_--;
                cout<<"\n Nodo Eliminado \n";
                encontrado=true;
            }
            aux = actual; //Aux almacena el anterior del actual
            actual = actual->siguiente; //Pasa al siguiente nodo
        }while((actual!=primero) && (encontrado!= true));

        if (!encontrado){
            cout<<"\n Nodo no encontrado \n";
        }
    }else{
        cout<<"\n La lista se Encuentra Vacia \n";

    }

};

// void listaUsuarios::eliminarLista(){
    
//     while (primero != NULL)
//     {
//         Nodo *actual = new Nodo(); //Nodo actual y el que se debe eliminar al final
//         actual = ultimo;

//         if (primero == ultimo) //Si solo hay uno
//         {
//             primero = NULL;
//             ultimo = NULL;
//         }else{
//             ultimo = ultimo->anterior;
//         }
//         delete actual;
//     }    

//     cout<<"Datos eliminados correctamente"<<endl;
//     size_ = 0;
    
// };
