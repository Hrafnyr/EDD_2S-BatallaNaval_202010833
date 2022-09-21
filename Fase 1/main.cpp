#include <iostream>
#include <string>
#include <fstream>
#include "sha256.h" //Permite cifrar contraseñas
#include "json/json.h" //Permite manipular JSON
#include "jsoncpp.cpp"
#include "ListaUsuarios.h" //Llamada a lista de usuarios
#include "ColaTutorial.h" //Llamada a la cola del tutorial
#include "ListaCategoria.h"

using namespace std;


//Declaraciones globales
listaUsuarios usuario_;
cola tutorial;
listaCategoria categoria_;


//Prototipos
void menuUsuario(string&,string&);
void menuReportes();
void cargarJSON();

int main(){
    //Menú principal
    char op;
    char e;
    bool flag = true;
    bool flag4;
    
    //Nuevo usuario
    string auxPass;
    string name,pass,ed,mon;

    //Login
    int log;
    string logName="";
    string logPass="";
    

    system("cls");
    while (flag==true)
    {
        
        cout<<"----------- Menu principal -----------\n";
        cout<<"1. Carga Masiva\n";
        cout<<"2. Registrar Usuario\n";
        cout<<"3. Login\n";
        cout<<"4. Reportes\n";
        cout<<"5. Salir del juego\n";
        cout<<"--------------------------------------\n";
        cout<<"--> Ingrese el numero de opcion: ";
        cin>>op;
        
        switch (op)
        {
        case '1':
            system("cls");
            cargarJSON();
            break;
        case '2': 
            
            system("cls");
            cin.ignore();
            cout<<"----- Crear cuenta -----\n";
            do
            {
                cout<<"Ingrese su nombre de usuario:\n";
                getline(cin,name);

                flag4=usuario_.verificarNombre(name);

                if (flag4==true)
                {
                    cout<<"El nombre ya existe\n";
                }

            } while (flag4==true);
            
            cout<<"Password:\n";
            getline(cin,auxPass);

            //Cifrar contraseña
            pass = SHA256::cifrar(auxPass);

            cout<<"Ingrese su edad:\n";
            getline(cin,ed);

            //Nuevo usuario
            usuario_.insertarNuevo(name,pass,mon="0",ed);
            break;
        case '3':

            cout<<"-------- Login --------\n";
            cin.ignore();
            cout<<"Ingrese su nombre de usuario:\n";
            getline(cin,logName);
            cout<<"Password:\n";
            getline(cin,auxPass);
            logPass = SHA256::cifrar(auxPass);

            log=usuario_.login(logName,logPass);
            
            if (log==1)
            {
                menuUsuario(logName,logPass);

            }else if (log==0)
            {   
                system("cls");
                cout<<"Usuario no encontrado\n";
                cout<<"->Verifique sus datos o cree una cuenta nueva\n";
            }else if (log==3)
            {
                system("cls");
                cout<<"No hay usuarios regristrados\n";
            }
            
            break;
        case '4':
            menuReportes();
            break;
        case '5':
            cout<<"Salir del juego [S/N]\n";
            cout<<"Ingrese S o N: ";
            cin>>e;
            
            if ((e=='s')||(e=='S'))
            {
                
                cout<<"->Saliendo..."<<endl;
                flag = false;
                exit(5);
            }else{
                system("cls");
                cout<<"->Cancelado\n";
            }
            break;    
        default:
            system("cls");
            cout<<"-> Error, debe ingresar el numero de opcion\n";
            break;
        }
    }
    
    return 0;
};

void menuUsuario(string& logName,string& logPass){
    bool flag = true;

    char op;
    char r;
    string auxMonedas;
    string nameJugada,cX,cY;
    bool flag2 = false;

    system("cls");
    while (flag)
    {
        cout<<"----------- Bienvenido "<<logName<<"-----------\n";
        cout<<"a. Editar informacion\n";
        cout<<"b. Eliminar cuenta\n";
        cout<<"c. Ver tutorial\n";
        cout<<"d. Ver articulos de la tienda\n";
        cout<<"e. Realizar movimientos\n";
        cout<<"f. Salir al menu principal\n";
        cout<<"--------------------------------------\n";
        cout<<"--> Ingrese la letra de opcion: ";
        cin>>op;

        switch (op)
        {
        case 'a':
            system("cls");
            usuario_.modificarInformacion(logName,logPass);
            break;
        case 'b':
            cout<<"Desea eliminar su cuenta permanentemente [S/N]\n";
            cout<<"Ingrese S o N: ";
            cin>>r;
            
            if ((r=='s')||(r=='S'))
            {   
                system("cls");
                flag = false;
     
                usuario_.eliminarCuenta(logName,logPass);
                logName="";
                logPass="";

            }else{
                system("cls");
                cout<<"->Cancelado\n";
            }
            break;    
        case 'c':
            tutorial.mostrarTutorial();
            break;
        case 'd':
            system("cls");
            auxMonedas = usuario_.getMonedas(logName,logPass);
            cout<<"Tienda\t\t\tMonedas Disponibles: "<<auxMonedas<<endl;
            categoria_.mostrarLista();
            system("pause");
            break;
        case 'e':
            system("cls");
            cin.ignore();
            cout<<"Ingrese el nombre de la jugada: \n";
            getline(cin,nameJugada);

            //guardar Nodo Jugada
            usuario_.insertarJugada(logName,logPass,nameJugada);
            usuario_.sumarPunto(logName,logPass);

            //Asignando Movimientos a la Pila
            while (flag2==false)
            {
                cout<<"->Ingrese C para terminar\n";
                cout<<"Ingrese coordenada en X:\n";
                getline(cin,cX);

                if (cX=="C"||cX=="c")
                {
                    break;
                }

                cout<<"Ingrese coordenada en Y:\n";
                getline(cin,cY);

                if (cY=="C"||cY=="c")
                {   
                    break;
                }
                //Ingreso de nuevo movimiento
                usuario_.nuevoMovimiento(logName,logPass,nameJugada,cX,cY);   
            }
            break;
        case 'f':
            cout<<"Regresar [S/N]\n";
            cout<<"Ingrese S o N: ";
            cin>>r;
            
            if ((r=='s')||(r=='S'))
            {   
                system("cls");
                cout<<"->Saliendo..."<<endl;
                flag = false;
                
                logName="";
                logPass="";

            }else{
                system("cls");
                cout<<"->Cancelado\n";
            }
            break;    
        default:
            system("cls");
            cout<<"->Error, valor incorrecto ingresado"<<endl;
            break;
        }

    }
    
}

void menuReportes(){
    bool flag=false;
    char op;
    system("cls");
    while (flag==false)
    {
        cout<<"----------- Reportes -----------\n";
        cout<<"1. Reporte de Usuarios\n";
        cout<<"2. Reporte de Articulos\n";
        cout<<"3. Reporte de Tuturial\n";
        cout<<"4. Reporte de jugadas\n";
        cout<<"5. Regresar\n";
        cout<<"--------------------------------------\n";
        cout<<"--> Ingrese el numero de opcion: ";
        cin>>op;

        switch (op)
        {
        case '1':
            usuario_.ReporteUsuarios();
            break;
        case '2':
            categoria_.generarReporte();
            break;
        case '3':
            tutorial.generarReporte();
            break;
        case '4':
            usuario_.reporteJugadas();
            break;
        case '5':
            system("cls");
            cout<<"--> Regresando...\n";
            flag = true;
            break;
        default:
            system("cls");
            cout<<"Error, debe ingresar el numero de opcion\n";
            break;
        }
    }
    
}

void cargarJSON(){
    //variables usuarios
    string nombre,pass,mon,ed;
    string auxPass;
    bool verificador;

    //variables tutorial
    string ancho,alto,cX,cY;

    //variables articulos
    string categoria,id,nom,precio,src;
    ifstream file("carga.json"); //fstream para obtener el puntero del archivo
    Json::Value datos;
    Json::Reader reader; 

    //Con reader parseamos el json
    reader.parse(file,datos);

    //Ahora datos ya contienen la informacion

    //Accediendo a usuarios
    for (int i = 0; i < datos["usuarios"].size(); i++)
    {
        //Accediendo a sus atributos y convirtiendo a string
        nombre = datos["usuarios"][i]["nick"].asString();

        //Validar nombre
        verificador = usuario_.verificarNombre(nombre);
        if (verificador==false)
        {
            auxPass = datos["usuarios"][i]["password"].asString();
            //Cifrar contraseña
            pass = SHA256::cifrar(auxPass);

            mon = datos["usuarios"][i]["monedas"].asString();
            ed = datos["usuarios"][i]["edad"].asString();
            
            //Guardando usuarios
            usuario_.insertarNuevo(nombre,pass,mon,ed);
        }

    }

    //Accediendo a tutorial
    ancho = datos["tutorial"]["ancho"].asString();
    alto = datos["tutorial"]["alto"].asString();
    tutorial.queue(ancho,alto,cX="",cY="");

    //Accediento a movimientos
    for (int i = 0; i < datos["tutorial"]["movimientos"].size(); i++)
    {
        //Accediendo a atributos y convirtiendo a string

        cX = datos["tutorial"]["movimientos"][i]["x"].asString();
        cY = datos["tutorial"]["movimientos"][i]["y"].asString();
        
        //Guardando datos
        tutorial.queue(ancho="",alto="",cX,cY);
    }

    //Articulos
    for (int i = 0; i < datos["articulos"].size(); i++)
    {
        //->primero verificar si la categoria ya se guardo
        categoria = datos["articulos"][i]["categoria"].asString();
        id = datos["articulos"][i]["id"].asString();
        nom = datos["articulos"][i]["nombre"].asString();
        precio = datos["articulos"][i]["precio"].asString();
        src = datos["articulos"][i]["src"].asString();

        categoria_.insertarInicio(categoria);
        categoria_.insertarNuevoArticulo(categoria,id,nom,precio,src);
    }
    cout<<"-> Informacion cargada exitosamente\n";
}
