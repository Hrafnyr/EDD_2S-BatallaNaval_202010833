#include <iostream>
#include <string>
#include <fstream>
#include "sha256.h" //Permite cifrar contraseñas
#include "json/json.h" //Permite manipular JSON
#include "jsoncpp.cpp"
#include "ListaUsuarios.h" //Llamada a lista de usuarios

using namespace std;

//Declaraciones globales
listaUsuarios usuario_;


//Prototipos
void menuUsuario(string&,string&);
void cargarJSON();

int main(){

    //Menú principal
    char op;
    char e;
    bool flag = true;

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
            cargarJSON();
            usuario_.mostrarUsuarios(); 
            break;
        case '2': 
            
            system("cls");
            cin.ignore();
            cout<<"----- Crear cuenta -----\n";
            cout<<"Ingrese su nombre de usuario:\n";
            getline(cin,name);
            cout<<"Password:\n";
            getline(cin,auxPass);

            //Cifrar contraseña
            pass = SHA256::cifrar(auxPass);

            cout<<"Ingrese su edad:\n";
            getline(cin,ed);

            //Falta Encriptacion sha256


            //Nuevo usuario
            usuario_.insertarNuevo(name,pass,mon="0",ed);
            usuario_.mostrarUsuarios(); //Metodo de prueba para ver la correcta insercion
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
            
            break;
        case 'd':
            
            break;
        case 'e':
            
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

void cargarJSON(){
    string nombre,pass,mon,ed;
    string auxPass;

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
        auxPass = datos["usuarios"][i]["password"].asString();
        //Cifrar contraseña
        pass = SHA256::cifrar(auxPass);

        mon = datos["usuarios"][i]["monedas"].asString();
        ed = datos["usuarios"][i]["edad"].asString();
        
        //Guardando usuarios
        usuario_.insertarNuevo(nombre,pass,mon,ed);
    }
    
}