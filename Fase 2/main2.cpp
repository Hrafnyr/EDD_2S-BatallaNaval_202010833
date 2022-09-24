#include <crow.h>
#include <iostream>
#include <string>
#include <fstream>
#include "../Fase 1/sha256.h"
#include "../Fase 1/json/json.h" //Permite manipular JSON
#include "../Fase 1/jsoncpp.cpp"
#include "../Fase 1/ListaUsuarios.h" //Llamada a lista de usuarios
#include "../Fase 1/ColaTutorial.h" //Llamada a la cola del tutorial
#include "../Fase 1/ListaCategoria.h"
#include "../Fase 1/arbolB.h"
using namespace std;

//Variables globales
listaUsuarios usuarioV;
ArbolB arbol;
cola tutorial;
listaCategoria categoria_;

void cargaMasiva();

int main(int argc, char **argv){
    //creando usuario admin
    string nameAdmin = "EDD";
    string passAdmin = "edd123";
    string edadAdmin = "50";
    string monedasAdmin = "0";
    arbol.insertarUser(nameAdmin,passAdmin,monedasAdmin,edadAdmin);

    //Creando app
    crow::SimpleApp app;


    //Creacion de rutas
    CROW_ROUTE(app, "/")([](){
        return "hello world";
    });

    //Carga masiva
    CROW_ROUTE(app, "/carga").methods(crow::HTTPMethod::POST)
    ([&](const crow::request& req)
    {
        cargaMasiva();
        return crow::response(200, "OK");
    });

    //Mostrar usuarios
    CROW_ROUTE(app, "/AllUsers").methods(crow::HTTPMethod::POST)
    ([&](const crow::request& req)
    {
        arbol.Grafo();
        return crow::response(200, "added");
    });

    //Insertar
    CROW_ROUTE(app, "/newUser").methods(crow::HTTPMethod::POST)
    ([&](const crow::request& req)
    {
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Invalid body");
        std::string nombre, pass, edad,mon,res;
        try {
            nombre = body["nombre"].s();
            pass = body["pass"].s();
            edad = body["edad"].s();
            mon = body["monedas"].s();
        } catch (const std::runtime_error &err) {
            return crow::response(400, "Invalid body");
        }

        try {
            
            int resP = arbol.verificarNickname(nombre);
            if (resP==0)
            {
                //cifrar contraseña
                res = SHA256::cifrar(pass);

                arbol.insertarUser(nombre,res,mon,edad); //insercion en arbol si el name no existe
                return crow::response(200,"{\"Message\":\"OK\"}");
               
            }
            else if (resP==1)
            {
                return crow::response(200,"{\"Message\":\"error\"}");
            }
            

        } catch (const std::runtime_error &ex) {
            return crow::response(500, "Internal Server Error");
        }

        return crow::response(200, "added");
    });

    //Actualizar
    CROW_ROUTE(app, "/updateUser").methods(crow::HTTPMethod::POST)
    ([&](const crow::request& req)
    {
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Invalid body");
        std::string newNombre, newPass, newEdad,res, user, pass,pass1,pass2;
        try {
            newNombre = body["nName"].s();
            newPass = body["nPass"].s();
            newEdad = body["nEdad"].s();
            user= body["nombre"].s();
            pass = body["password"].s();
        } catch (const std::runtime_error &err) {
            return crow::response(400, "Invalid body");
        }

        try {
            
            int resP = arbol.verificarNickname(newNombre);
            if (resP==0)
            {
                //cifrar contraseña
                if (newPass.empty()!=true)
                {
                    pass2= SHA256::cifrar(newPass);
                }
                pass1 = SHA256::cifrar(pass) ;       

                int i = arbol.actualizar(user,pass1,newNombre,pass2,newEdad);
                if (i==1)
                {
                    return crow::response(200,"{\"Message\":\"OK\"}");
                }
                else{
                     return crow::response(200,"{\"Message\":\"error\"}");
                }   
            }
            else if (resP==1)
            {
                return crow::response(200,"{\"Message\":\"error\"}");
            }
            

        } catch (const std::runtime_error &ex) {
            return crow::response(500, "Internal Server Error");
        }

        return crow::response(200, "added");
    });

    //Login
    CROW_ROUTE(app, "/Login").methods(crow::HTTPMethod::POST)
    ([&](const crow::request& req)
    {
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Invalid body");
        std::string nombre, pass,vr;
        int resp;
        try {
            nombre = body["nombre"].s();
            pass = body["pass"].s();
        } catch (const std::runtime_error &err) {
            return crow::response(400, "Invalid body");
        }

        try {
            vr = SHA256::cifrar(pass);
            resp = arbol.login(nombre,vr);
            if (resp==0)
            {
               return crow::response(200,"{\"Message\":\"error\"}");
            }
            else if (resp==1)
            {
                 return crow::response(200,"{\"Message\":\"OK\"}");
            }

        } catch (const std::runtime_error &ex) {
            return crow::response(500, "Internal Server Error");
        }

        return crow::response(200, "Blog added");
    });

    //eliminar
    CROW_ROUTE(app, "/removeUser").methods(crow::HTTPMethod::POST)
    ([&](const crow::request& req)
    {
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Invalid body");
        std::string nombre, pass,vr;
        int resp;
        try {
            nombre = body["nombre"].s();
            pass = body["pass"].s();
        } catch (const std::runtime_error &err) {
            return crow::response(400, "Invalid body");
        }

        try {
            vr = SHA256::cifrar(pass);
            resp = arbol.eliminar(nombre,vr);
            if (resp==0)
            {
               return crow::response(200,"{\"Message\":\"error\"}");
            }
            else if (resp==1)
            {
                 return crow::response(200,"{\"Message\":\"OK\"}");
            }

        } catch (const std::runtime_error &ex) {
            return crow::response(500, "Internal Server Error");
        }

        return crow::response(200, "Blog added");
    });

    //inicializacion
    app.port(8080).multithreaded().run();

    return 0;
}

void cargaMasiva(){
    //variables usuarios
    string nombre,pass,mon,ed;
    string auxPass;
    int verificador;

    //variables tutorial
    string ancho,alto,cX,cY;

    //variables articulos
    string categoria,id,nom,precio,src;
    ifstream file("../Fase 1/carga.json"); //fstream para obtener el puntero del archivo
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