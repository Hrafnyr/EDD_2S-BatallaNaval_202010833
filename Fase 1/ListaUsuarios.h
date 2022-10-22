#include <fstream>
#include "NodoUsuario.h" 
#include <string>
#include "arbolB.h"
using namespace std;

//Declaramos clase lista
class listaUsuarios{
    private:            
        Usuario* primero;
        Usuario* ultimo;    
        int contID = 1000; //contador auxiliar para nuevo usuario
        int size_ = 0;

    public:
        ArbolB* arbol;
        void insertarNuevo(string&,string&,string&,string&,string&);
        void insertarJugada(string&,string&,string&);
        void nuevoMovimiento(string&,string&,string&,string&,string&);
        string verUltimoMovimiento(string&,string&,string&);
        void eliminarUltimoMovimiento(string&,string&,string&);
        void ReporteUsuarios(); 
        int login(string&,string&);
        int modificarInformacion(string&,string&,string&,string&,string&);
        void sumarPunto(string&,string&,string&);
        void restarMonedas(string&,string&,string&);
        int verificarNombre(string&);
        void reporteJugadas();
        string getDatos();
        
        int nuevaCompra(string&,string&,string&,string&);

        int eliminarCuenta(string&,string&);
        string getMonedas(string& name, string& pass);
        string getID(string&, string&);

        //void eliminarLista(); 
        
        
        //metodos con arbol
        void graficarArbol();
        void insertarAB(string&, string&,string&, string&, string&);
        void modificarAB(string&, string&,string&, string&, string&);
        void reInsercion();

        int verAVL(string&, string&);


        listaUsuarios();
};

listaUsuarios::listaUsuarios(){ //constructor, apuntar por defecto a null
    this->primero=NULL; 
    this->ultimo=NULL;
    this->arbol=new ArbolB();
}

void listaUsuarios::graficarArbol(){
    arbol->Grafo();
}

void listaUsuarios::insertarAB(string& id, string& nickname, string& pass, string& mon, string& ed){
    arbol->insertarUser(id, nickname, pass, mon, ed);
}

void listaUsuarios::modificarAB(string& name, string& pass, string& name2, string& pass2, string& edad2){
    arbol->actualizar(name,pass,name2,pass2,edad2);
}

void listaUsuarios::insertarNuevo(string& id, string& nickname, string& pass, string& mon, string& ed){
    
    Usuario* nuevo = new Usuario();//Nuevo nodo
    string aux;

    if (id.empty()==true)
    {
        aux = to_string(contID);
        contID++;
    }
    else{
        aux = id;
    }
    insertarAB(aux,nickname,pass,mon,ed);

    nuevo->id = aux;
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

string listaUsuarios::getDatos()
{
    Usuario* actual = new Usuario(); //Auxiliar
    actual = primero;
    string out = "";
    if (primero!=NULL){
        do{
			out += "{\"nick\": \"" + actual->nombre + "\",\"password\":\""+actual->password+"\"}";
			actual = actual->siguiente;

            if (actual != primero)
            {      
                out += ",";
            }
            
		}while(actual!=primero);

        return "[\n " + out + "\n]";
       
    }
    return "[\n]";
};

int listaUsuarios::verAVL(string& name, string& pass){
    Usuario* actual = new Usuario(); //Auxiliar

    actual = primero;
    bool encontrado = false;

    if (primero!=NULL){
        do{
			
			if(actual->nombre==name && actual->password==pass){
				actual->compras->graficar();
				encontrado = true;
                return 1;		
			}
			
			actual = actual->siguiente;
		}while(actual!=primero && encontrado != true);
    }

    return 0;
} 

int listaUsuarios::nuevaCompra(string& name,string& pass,string& idC,string& nombre){
    Usuario* actual = new Usuario(); //Auxiliar

    actual = primero;
    bool encontrado = false;

    if (primero!=NULL){
        do{
			
			if(actual->nombre==name && actual->password==pass){
				
                //agregar compra
                actual->compras->Insertar(idC,nombre);

				encontrado = true;
                return 1;		
			}
			
			actual = actual->siguiente;
		}while(actual!=primero && encontrado != true);
    }
    return 0;
}

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

            std::ofstream file;

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

int listaUsuarios::modificarInformacion(string& name, string& pass,string& name2,string& pass2,string& edad2){
    
    Usuario* actual = new Usuario(); //Auxiliar

    actual = primero;
    bool encontrado = false;
    bool flag4=false;

    modificarAB(name,pass,name2,pass2,edad2);

    /*
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
    cin>>opMod;*/

    if (primero!=NULL){
        do{
			
			if(actual->nombre==name && actual->password==pass){

				/*//Modificación de información
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
                }*/
                
                
                //Validar campos para actualizar
                if (name2.empty()!=true)
                {
                    actual->nombre=name2;
                }
                
                if (pass2.empty()!=true)
                {
                    actual->password=pass2;
                }

                if (edad2.empty()!=true)
                {
                    actual->edad=edad2;
                }
                cout<<"Actualizado en lista"<<endl;
                encontrado = true;
                return 1;	
			}
			
			actual = actual->siguiente;
		}while(actual!=primero && encontrado != true);

        if (encontrado==false)
        {
            cout<<"No se encuentra el usuario\n";
            return 0;
        }
    }
    return 0;
}

int listaUsuarios::login(string& name, string& pass){
    Usuario* actual = new Usuario(); //Auxiliar

    actual = primero;
    bool encontrado = false;

    if (primero!=NULL){
        do{
			
			if(actual->nombre==name && actual->password==pass){
				
				encontrado = true;
                return 1;		
			}
			
			actual = actual->siguiente;
		}while(actual!=primero && encontrado != true);
    }

    return 0;
} 

int listaUsuarios::verificarNombre(string& name){
    Usuario* actual = new Usuario(); //Auxiliar

    actual = primero;
    bool encontrado = false;

    if (primero!=NULL){
        do{
			
			if(actual->nombre==name){
				encontrado = true;
                return 1;		
			}
			
			actual = actual->siguiente;
		}while(actual!=primero && encontrado != true);
    }
    return 0;
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

int listaUsuarios::eliminarCuenta(string& nameBuscar,string& passB){
    
    Usuario* actual = new Usuario();
    actual = primero;
    Usuario* aux = new Usuario();
    aux = NULL;

    bool encontrado = false;

    string prueba;

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

                //crear el arbol desde cero
                reInsercion();

                encontrado=true;
                return 1;
            }
            aux = actual; //Aux almacena el anterior del actual
            actual = actual->siguiente; //Pasa al siguiente nodo
        }while((actual!=primero) && (encontrado!= true));

        if (!encontrado){
            cout<<"\n Nodo no encontrado \n";
            return 0;
        }
    }
    return 0;
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

string listaUsuarios::getID(string& name, string& pass){
    Usuario* actual = new Usuario(); //Auxiliar

    actual = primero;
    bool encontrado = false;

    if (primero!=NULL){
        do{
			
			if(actual->nombre==name && actual->password==pass){
				
				encontrado = true;
                return actual->id;		
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

void listaUsuarios::sumarPunto(string& name, string& pass, string& cant){
    Usuario* actual = new Usuario(); //Auxiliar

    actual = primero;
    bool encontrado = false;
    string mon_ = getMonedas(name,pass);
    int aux = stoi(mon_);
    int sum = stoi(cant);
    int tot = aux+sum;

    if (primero!=NULL){
        do{
			
			if(actual->nombre==name && actual->password==pass){
				
				encontrado = true;
                actual->monedas=to_string(tot);		
			}
			
			actual = actual->siguiente;
		}while(actual!=primero && encontrado != true);

    }  
}

void listaUsuarios::restarMonedas(string& name, string& pass, string& cant){
    Usuario* actual = new Usuario(); //Auxiliar

    actual = primero;
    bool encontrado = false;
    string mon_ = getMonedas(name,pass);
    int aux = stoi(mon_);
    int cant2 = stoi(cant);
    int tot = aux-cant2;

    if (primero!=NULL){
        do{
			
			if(actual->nombre==name && actual->password==pass){
				
				encontrado = true;
                actual->monedas=to_string(tot);		
			}
			
			actual = actual->siguiente;
		}while(actual!=primero && encontrado != true);

    }  
}

void listaUsuarios::nuevoMovimiento(string& name, string& pass,string& nomJ,string& X, string& Y){
    Usuario* actual = new Usuario(); //Auxiliar
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

string listaUsuarios::verUltimoMovimiento(string& name, string& pass,string& nomJ){
    Usuario* actual = new Usuario(); //Auxiliar
    string mov = " ";
    actual = primero;
    
    while (actual!=NULL){

        if (actual->nombre!=name && actual->password!=pass)
        {
            actual = actual->siguiente;
        }else{
            mov = actual->jugadas->verTop(nomJ);
            break;
        }
    }
    return mov;

};

void listaUsuarios::eliminarUltimoMovimiento(string& name, string& pass,string& nomJ){
    Usuario* actual = new Usuario(); //Auxiliar
    actual = primero;
    
    while (actual!=NULL){

        if (actual->nombre!=name && actual->password!=pass)
        {
            actual = actual->siguiente;
        }else{
            actual->jugadas->eliminarTop(nomJ);
            break;
        }
    }

};

void listaUsuarios::reInsercion(){
    
    //borrar arbol
    ArbolB* nuevo = new ArbolB();
    arbol = nuevo;

    Usuario* actual = new Usuario(); //Auxiliar
    actual = primero;
    string id,name,pass,mon,ed;
    if (primero!=NULL){
        do{

            id = actual->id;
            name = actual->nombre;
            pass = actual->password;
            mon = actual->monedas;
            ed = actual->edad;
			insertarAB(id,name,pass,mon,ed);   

            actual = actual->siguiente;         

		}while(actual!=primero);
       
    }
}

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
