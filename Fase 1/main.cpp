#include <iostream>
#include <string>
#include "ListaUsuarios.h"

using namespace std;

//Declaraciones globales
listaUsuarios usuario_;


//Prototipos
void menuUsuario(string&,string&);

int main(){

    //Menú principal
    char op;
    char e;
    bool flag = true;

    //Nuevo usuario
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
            break;
        case '2': 
            
            system("cls");
            cin.ignore();
            cout<<"----- Crear cuenta -----\n";
            cout<<"Ingrese su nombre de usuario:\n";
            getline(cin,name);
            cout<<"Password:\n";
            getline(cin,pass);
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
            getline(cin,logPass);

            log=usuario_.login(logName,logPass);
            
            if (log==1)
            {
                menuUsuario(logName,logPass);

            }else if (log==0)
            {
                cout<<"Usuario no encontrado\n";
                cout<<"->Verifique sus datos o cree una cuenta nueva\n";
            }else if (log==3)
            {
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
                cout<<"->Cancelado\n";
            }
            break;    
        default:
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
                cout<<"->Eliminando..."<<endl;
                flag = false;
                
                logName="";
                logPass="";
                usuario_.eliminarCuenta(logName,logPass);

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