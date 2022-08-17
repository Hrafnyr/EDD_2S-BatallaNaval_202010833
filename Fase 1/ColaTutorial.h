
#include <iostream>
#include "nodoTutorial.h" //Llamada al archivo nodoTutorial.h 

using namespace std;

//Declaramos clase lista
class cola{
    private:            
        nodoTutorial* primero;
        nodoTutorial* ultimo;    
        int size_ = 0;  
    public:
        
        void queue(string&,string&,string&,string&); //Insercion al inicio nodo3->nodo2->nodo1->Null
        void mostrarTutorial();
        void dequeue(); //Elimina el primero en entrar
        void eliminarCola();
        cola();

};

cola::cola(){ 
    this->primero=NULL; 
    this->ultimo=NULL;
}

void cola::queue(string& nuevoAncho,string& nuevoAlto,string& cX,string& cY){
    
    nodoTutorial* nuevo = new nodoTutorial();//Nuevo nodoTutorial

    //Asignar valores
    nuevo->ancho = nuevoAncho;
    nuevo->alto = nuevoAlto;
    nuevo->cX = cX;
    nuevo->cY = cY;
    size_++;

    //Manejo de apuntadores
    if (primero == NULL)
    {
        primero = nuevo;
        ultimo = nuevo;
        nuevo->siguiente = NULL;
    }
    else{
        nuevo->siguiente = primero;
        primero->anterior = nuevo;
        primero = nuevo;
        nuevo->anterior = NULL;
    }
};

//Metodo de prueba para verificar la correcta inserción
void cola::mostrarTutorial(){
    nodoTutorial* actual = new nodoTutorial(); //Auxiliar
    int contAux = 1;
    actual = primero;
    string aux="",aux2="",aux3="";

    system("cls");
    aux+="----- Tutorial -----\n";
    if (primero!=NULL){
        while (actual!=NULL){
            
            if (actual->ancho.empty()!=true && actual->alto.empty()!=true)
            {
                if (contAux==1)
                {
                    aux2+="\n\tTablero:\n\t\tAncho:"+actual->ancho+"\n\t\tAlto: "+actual->alto+"\n";
                    aux2+="\n\tMovimientos:\n\t\t";
                }
                contAux++;
            }
           
            if (actual->cX.empty()!=true && actual->cY.empty()!=true)
            {
               aux3+=" -> ("+actual->cX+","+actual->cY+")";
            }
            
            actual = actual->siguiente;
        }
        cout<<aux+aux2+aux3+"\n\n";
    }else{
        cout<<"No hay datos"<<endl;
    }
    
};

void cola::dequeue(){

    if (primero == NULL)
    {
        cout<<"La lista no tiene datos"<<endl;
    }else if (primero->siguiente==NULL) //Solo hay un nodoTutorial
    {
        primero = NULL;
        ultimo = NULL;
    }else{
        ultimo = ultimo->anterior;
        ultimo->siguiente= NULL;

    }
    size_--;
};

/*void cola::eliminarCola(){
    
    while (primero != NULL)
    {
        nodoTutorial *actual = new nodoTutorial(); //nodoTutorial actual y el que se debe eliminar al final
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
    size_ = 0;
    
};*/
