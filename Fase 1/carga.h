#include <iostream>
#include <string>
#include <fstream>
#include "sha256.h" //Permite cifrar contraseñas
#include "json/json.h" //Permite manipular JSON
#include "jsoncpp.cpp"
#include "ListaUsuarios.h" //Llamada a lista de usuarios
#include "ColaTutorial.h" //Llamada a la cola del tutorial
#include "ListaCategoria.h"
#include "arbolB.h"
using namespace std;

class Carga{
    public:
        listaUsuarios usuario_;
        ArbolB arbol;
        cola tutorial;
        listaCategoria categoria_;
        void cargaJSON();
};

void Carga::cargaJSON(){
    //variables usuarios
    string nombre,pass,mon,ed;
    string auxPass;
    int verificador;

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
        verificador = arbol.verificarNickname(nombre);
        if (verificador==0)
        {
            auxPass = datos["usuarios"][i]["password"].asString();
            //Cifrar contraseña
            pass = SHA256::cifrar(auxPass);

            mon = datos["usuarios"][i]["monedas"].asString();
            ed = datos["usuarios"][i]["edad"].asString();
            
            //Guardando usuarios
            arbol.insertarUser(nombre,pass,mon,ed);
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
