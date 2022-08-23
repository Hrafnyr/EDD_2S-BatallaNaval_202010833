
#include <iostream>
#include "NodoUsuario.h" 
#include <string>
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
        void ReporteUsuarios(); 
        int login(string&,string&);
        void modificarInformacion(string&,string&);
        void sumarPunto(string&,string&);
        bool verificarNombre(string&);
        void reporteJugadas();

        void eliminarCuenta(string&,string&);
        string getMonedas(string& name, string& pass);

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

//Metodo de reporte
void listaUsuarios::ReporteUsuarios(){
    Usuario* actual = new Usuario(); //Auxiliar
    actual = primero;

    string cabecera="",apuntador="",Nodo="",apUnion="";
    int contU = 1;

    cabecera+="digraph G {\nrankdir=LR;\ngraph [fontsize=15 fontname=\"Verdana\"];\n";
    cabecera+="node[shape=box fontsize=12 fillcolor=\"darkseagreen1\" style=\"filled\"];\nlabel=\"Usuarios\";\n";

    if (primero!=NULL){        
        do
        {
            //Si solo hay un nodo se referencia a sí mismo
            //Creacion de nodos
            Nodo+="NodoU"+to_string(contU)+"[label=\"Nombre: "+actual->nombre+"\\n";
            Nodo+="Contraseña: "+actual->password+"\\n";
            Nodo+="Monedas: "+actual->monedas+"\\n";
            Nodo+="Edad: "+actual->edad+"\"];\n";

            //Apuntadores
            if (actual->siguiente!=primero)
            {
                apuntador+="NodoU"+to_string(contU)+"-> NodoU"+to_string(contU+1)+";\n";//->
                apuntador+="NodoU"+to_string(contU+1)+"-> NodoU"+to_string(contU)+";\n";//<-
                contU++;
            }
            
            actual = actual->siguiente;
        } while (actual!=primero);
        
        //Union
        apUnion+="NodoU1:s -> NodoU"+to_string(contU)+";\n";
        apUnion+="NodoU"+to_string(contU)+":n -> NodoU1;}\n";

        //Unir todo
        cabecera+=Nodo+apuntador+apUnion;

        //Generar archivo
        try {
            string path = "Usuarios";

            ofstream file;
            file.open(path + "Reporte.dot",std::ios::out);

            if(file.fail()){
                exit(1);
            }

            file<<cabecera;
            file.close();
            string command = "dot -Tpng " + path + "Reporte.dot -o  " + path + "Reporte.png";
            system(command.c_str());
            system(("UsuariosReporte.png")); //abrir archivo
        }catch (exception e){
            cout << "Error detectado, no se pudo generar el Reporte solicitado";
        }
        cout<<"--> Reporte generado\n";

    }else{
        cout<<"No hay datos"<<endl;
    }

};

void listaUsuarios::modificarInformacion(string& name, string& pass){
    
    Usuario* actual = new Usuario(); //Auxiliar

    actual = primero;
    bool encontrado = false;
    bool flag4=false;

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
                    do
                    {
                        cout<<"Ingrese su nombre de usuario:\n";
                        getline(cin,nName);

                        flag4=verificarNombre(nName);

                        if (flag4==true)
                        {
                            cout<<"El nombre ya existe\n";
                        }

                    } while (flag4==true);

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
                    cout<<"-->Regresando...\n";
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

bool listaUsuarios::verificarNombre(string& name){
    Usuario* actual = new Usuario(); //Auxiliar

    actual = primero;
    bool encontrado = false;

    if (primero!=NULL){
        do{
			
			if(actual->nombre==name){
				encontrado = true;
                return true;		
			}
			
			actual = actual->siguiente;
		}while(actual!=primero && encontrado != true);
    }
    return false;
}   

void listaUsuarios::reporteJugadas(){
    Usuario* actual = new Usuario(); //Auxiliar
    actual = primero;

    string cabecera="",subGU="", jugada="";
    int contUser = 0;
    //cabecera
    cabecera+="digraph G {\nrankdir=LR;\ngraph [fontsize=15 fontname=\"Verdana\" compound=true];\n";
    cabecera+="node[shape=box fontsize=12 fillcolor=\"darkseagreen1\" style=\"filled\"];\n";

    if (primero!=NULL){
        do{
			//Cada usuario será un subgrafo
            subGU+="subgraph cluster_"+to_string(contUser)+"{\nlabel=\"Usuario: "+actual->nombre+"\";\n";
            subGU+="style=filled;\ncolor=aliceblue;\n";

            //Llamada a las jugadas de usuario -> lista jugadas
            jugada = actual->jugadas->reporte(contUser);	

            subGU+=jugada+"}\n";
            contUser++;
			actual = actual->siguiente;
		}while(actual!=primero);

        //Unir todo
        cabecera+=subGU+"}\n";

        //Generar archivo
        try {
            string path = "Pilas";

            ofstream file;
            file.open(path + "Reporte.dot",std::ios::out);

            if(file.fail()){
                exit(1);
            }

            file<<cabecera;
            file.close();
            string command = "dot -Tpng " + path + "Reporte.dot -o  " + path + "Reporte.png";
            system(command.c_str());
            system(("PilasReporte.png"));//Abrir archivo
        }catch (exception e){
            cout << "Error detectado, no se pudo generar el Reporte solicitado";
        }
        cout<<"--> Reporte generado\n";

    }else{
        cout<<"No hay datos\n";
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

void listaUsuarios::sumarPunto(string& name, string& pass){
    Usuario* actual = new Usuario(); //Auxiliar

    actual = primero;
    bool encontrado = false;
    string mon_ = getMonedas(name,pass);
    int aux = stoi(mon_);

    if (primero!=NULL){
        do{
			
			if(actual->nombre==name && actual->password==pass){
				
				encontrado = true;
                aux++;
                actual->monedas=to_string(aux);		
			}
			
			actual = actual->siguiente;
		}while(actual!=primero && encontrado != true);

    }  
}

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
