
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
        void insertarJugada(string&,string&,string&);
        void nuevoMovimiento(string&,string&,string&,string&,string&);
        void mostrarUsuarios(); 
        void mostrarJugadasUsuario(string&,string&);
        int login(string&,string&);
        void modificarInformacion(string&,string&);

        void eliminarCuenta(string&,string&);
        string getMonedas(string& name, string& pass);

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

void listaUsuarios::modificarInformacion(string& name, string& pass){
    
    Usuario* actual = new Usuario(); //Auxiliar

    actual = primero;
    bool encontrado = false;

    string nName="";
    string nEdad="";
    string nPass="";
    char opMod;    


    cout<<"-------- Editar informacion --------\n";
    cout<<"1. Editar nombre\n";
    cout<<"2. Editar edad\n";
    cout<<"3. Editar password\n";
    cout<<"4. Regresar\n";
    cout<<"--> Ingrese el numero de opcion: ";
    cin>>opMod;


    if (primero!=NULL){
        do{
			
			if(actual->nombre==name && actual->password==pass){
				//Modificación de información
                switch (opMod)
                {
                case '1':
                    cin.ignore();
                    cout<<"--> Ingrese el nuevo nombre: ";
                    getline(cin,nName);

                    actual->nombre=nName;
                    name = nName;
                    cout<<"Informacion modificada\n";
                    break;

                case '2':
                    cin.ignore();
                    cout<<"--> Ingrese nueva edad: ";
                    getline(cin,nEdad);
                    actual->edad=nEdad;
                    cout<<"Informacion modificada\n";
                    break;
                
                case '3':
                    cin.ignore();
                    cout<<"--> Ingrese nueva password: ";
                    getline(cin,nPass);
                    actual->password=nPass;
                    pass=nPass;
                    cout<<"Informacion modificada\n";
                    break;
                
                case '4':
                    cout<<"-->Regresando...";
                    break;
                
                default:
                    break;
                }

				encontrado = true;		
			}
			
			actual = actual->siguiente;
		}while(actual!=primero && encontrado != true);

        if (encontrado==false)
        {
            cout<<"No se encuentra el usuario\n";
        }
    }else{
        cout<<"No hay datos\n";
    }
}

int listaUsuarios::login(string& name, string& pass){
    Usuario* actual = new Usuario(); //Auxiliar

    actual = primero;
    bool encontrado = false;

    if (primero!=NULL){
        do{
			
			if(actual->nombre==name && actual->password==pass){
				
				encontrado = true;		
			}
			
			actual = actual->siguiente;
		}while(actual!=primero && encontrado != true);

        if (encontrado==false)
        {
            return 0;
        }else{
           return 1;
        }
    }
    return 3;
}   

void listaUsuarios::mostrarJugadasUsuario(string& name, string& pass){
    Usuario* actual = new Usuario(); //Auxiliar

    actual = primero;
    bool encontrado = false;

    if (primero!=NULL){
        do{
			
			if(actual->nombre==name && actual->password==pass){
				
				encontrado = true;
                actual->jugadas->mostrarLista();		
			}
			
			actual = actual->siguiente;
		}while(actual!=primero && encontrado != true);

        if (encontrado==false)
        {
            "No existe esa jugada con ese nombre";
        }
    }
}   

void listaUsuarios::eliminarCuenta(string& nameBuscar,string& passB){
    
    Usuario* actual = new Usuario();
    actual = primero;
    Usuario* aux = new Usuario();
    aux = NULL;

    bool encontrado = false;
    
    if(primero!=NULL){
        do{
            if((actual->nombre==nameBuscar)&&(actual->password==passB)){
                cout<<"\n Eliminando cuenta...\n";

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
                cout<<"\n Cuenta Eliminada \n";
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

string listaUsuarios::getMonedas(string& name, string& pass){
    Usuario* actual = new Usuario(); //Auxiliar

    actual = primero;
    bool encontrado = false;

    if (primero!=NULL){
        do{
			
			if(actual->nombre==name && actual->password==pass){
				
				encontrado = true;
                return actual->monedas;		
			}
			
			actual = actual->siguiente;
		}while(actual!=primero && encontrado != true);

        if (encontrado==false)
        {
            return "0";
        }
    }
    return "0";
}    

void listaUsuarios::insertarJugada(string& name, string& pass,string& nomJ){
    Usuario* actual = new Usuario(); //Auxiliar

    actual = primero;
    
    while (actual!=NULL){

        if (actual->nombre!=name && actual->password!=pass)
        {
            actual = actual->siguiente;
        }else{

            actual->jugadas->nuevaJugada(nomJ);
            break;
        }
    }

};

void listaUsuarios::nuevoMovimiento(string& name, string& pass,string& nomJ,string& X, string& Y){
    Usuario* actual = new Usuario(); //Auxiliar
    Usuario* aux = new Usuario();

    actual = primero;
    
    while (actual!=NULL){

        if (actual->nombre!=name && actual->password!=pass)
        {
            actual = actual->siguiente;
        }else{
            actual->jugadas->nuevoMovimiento(nomJ,X,Y);
            break;
        }
    }

};


/* void listaUsuarios::eliminarLista(){
         while (primero != NULL)
     {
         Nodo *actual = new Nodo(); //Nodo actual y el que se debe eliminar al final
         actual = ultimo;

         if (primero == ultimo) //Si solo hay uno
         {
             primero = NULL;
             ultimo = NULL;
         }else{
             ultimo = ultimo->anterior;
         }
         delete actual;
     }    

     cout<<"Datos eliminados correctamente"<<endl;
     size_ = 0;
    
 };*/
