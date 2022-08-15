#include <iostream>
#include <string>
#include "ListaUsuarios.h"

using namespace std;

//Llamada a listaUsuarios
listaUsuarios usuario_;


int main(){

    //Menú principal
    char op;
    char e;
    bool flag = true;

    //Nuevo usuario
    string name,pass,ed,mon;

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

            //Nuevo usuario
            usuario_.insertarNuevo(name,pass,mon="0",ed);
            usuario_.mostrarUsuarios(); //Metodo de prueba para ver la correcta insercion
            break;
        case '3':
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