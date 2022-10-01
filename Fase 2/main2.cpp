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
using namespace std;

//CREAR METODO DE AGREGAR COMPRA, METODO PARA CREAR EL ARBOL DE USUARIOS DESDE LISTA USUARIOS

//Variables globales
listaUsuarios usuarioV;
cola tutorial;
listaCategoria categoria_;

void cargaMasiva();

int main(int argc, char **argv){
    //creando usuario admin
    string id = "";
    string nameAdmin = "EDD";
    string passAdmin = "edd123";
    string edadAdmin = "50";
    string monedasAdmin = "0";
    usuarioV.insertarNuevo(id,nameAdmin,passAdmin,monedasAdmin,edadAdmin);

    //Creando app
    crow::SimpleApp app;


    //Creacion de rutas
    CROW_ROUTE(app, "/")([](){
        crow::json::wvalue x({{"message","Hello"}});
        return x;
    });

    //Carga masiva
    CROW_ROUTE(app, "/carga").methods(crow::HTTPMethod::POST)
    ([&](const crow::request& req)
    {
        cargaMasiva();
        std::string dataTienda;
        dataTienda = categoria_.getDatos();
        crow::json::wvalue x(dataTienda);
        return x;
    });

    //Mostrar usuarios
    CROW_ROUTE(app, "/AllUsers").methods(crow::HTTPMethod::POST)
    ([&](const crow::request& req)
    {
        usuarioV.graficarArbol();
        return crow::response(200, "added");
    });

    //Insertar
    CROW_ROUTE(app, "/newUser").methods(crow::HTTPMethod::POST)
    ([&](const crow::request& req)
    {
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Invalid body");
        std::string nombre, pass, edad,mon,res,id;
        try {
            nombre = body["nombre"].s();
            pass = body["pass"].s();
            edad = body["edad"].s();
            mon = body["monedas"].s();
        } catch (const std::runtime_error &err) {
            return crow::response(400, "Invalid body");
        }

        try {
            
            int resP = usuarioV.verificarNombre(nombre);
            if (resP==0)
            {
                //cifrar contraseña
                res = SHA256::cifrar(pass);
                id = "";
                usuarioV.insertarNuevo(id,nombre,res,mon,edad); 
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
            
            int resP = usuarioV.verificarNombre(newNombre);
            if (resP==0)
            {
                //cifrar contraseña
                if (newPass.empty()!=true)
                {
                    pass2= SHA256::cifrar(newPass);
                }
                pass1 = SHA256::cifrar(pass) ;       

                int i = usuarioV.modificarInformacion(user,pass1,newNombre,pass2,newEdad);
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

    //nuevaCompra
    CROW_ROUTE(app, "/compra").methods(crow::HTTPMethod::POST)
    ([&](const crow::request& req)
    {
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Invalid body");
        std::string idC, cate, price,name, user, pass,pass1,monedas;
        try {
            idC = body["id"].s();
            cate = body["categoria"].s();
            user= body["nombre"].s();
            pass = body["password"].s();
        } catch (const std::runtime_error &err) {
            return crow::response(400, "Invalid body");
        }

        try {
            pass1 = SHA256::cifrar(pass) ; 

            monedas = usuarioV.getMonedas(user,pass1);

            name = categoria_.getNombre(cate,idC);
            price = categoria_.getPrecio(cate,idC);
            

            //verificar que pueda comprar
            if (stoi(monedas) >= stoi(price))
            {
                
                int i = usuarioV.nuevaCompra(user,pass1,idC,cate,price,name);
                if (i==1)
                {
                    usuarioV.restarMonedas(user,pass1,price);
                    return crow::response(200,"{\"Message\":\"OK\"}");
                }
                else{
                        return crow::response(200,"{\"Message\":\"error\"}");
                }   
            }
            else{
                return crow::response(200,"{\"Message\":\"NEC\"}"); //Not enough cash
            }   
                       

        } catch (const std::runtime_error &ex) {
            return crow::response(500, "Internal Server Error");
        }

        return crow::response(200, "added");
    });

     //ver AVL de compras
    CROW_ROUTE(app, "/verAVL").methods(crow::HTTPMethod::POST)
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
            resp = usuarioV.verAVL(nombre,vr);
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
            resp = usuarioV.login(nombre,vr);
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
            resp = usuarioV.eliminarCuenta(nombre,vr);
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

    //GetCoins
    CROW_ROUTE(app, "/getCoins").methods(crow::HTTPMethod::POST)
    ([&](const crow::request& req)
    {
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Invalid body");
        std::string nombre, pass,vr,resp;
        try {
            nombre = body["nombre"].s();
            pass = body["pass"].s();
        } catch (const std::runtime_error &err) {
            return crow::response(400, "Invalid body");
        }

        try {
            vr = SHA256::cifrar(pass);
            resp = usuarioV.getMonedas(nombre,vr);
            return crow::response(200,"{\"Coins\":\""+resp+"\"}");
        } catch (const std::runtime_error &ex) {
            return crow::response(500, "Internal Server Error");
        }

        return crow::response(200, "Blog added");
    });

    //setCoins
    CROW_ROUTE(app, "/setCoins").methods(crow::HTTPMethod::POST)
    ([&](const crow::request& req)
    {
        auto body = crow::json::load(req.body);
        if (!body)
            return crow::response(400, "Invalid body");
        std::string nombre, pass,vr,resp,cant;
        try {
            nombre = body["nombre"].s();
            pass = body["pass"].s();
            cant = body["cant"].s();
        } catch (const std::runtime_error &err) {
            return crow::response(400, "Invalid body");
        }

        try {
            vr = SHA256::cifrar(pass);
            usuarioV.sumarPunto(nombre,vr,cant);
            return crow::response(200,"{\"Message\":\"OK\"}");
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
    string ID,nombre,pass,mon,ed;
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
        ID =  datos["usuarios"][i]["id"].asString();
        nombre = datos["usuarios"][i]["nick"].asString();

        //Validar nombre
        verificador = usuarioV.verificarNombre(nombre);
        if (verificador==0)
        {
            auxPass = datos["usuarios"][i]["password"].asString();
            //Cifrar contraseña
            pass = SHA256::cifrar(auxPass);

            mon = datos["usuarios"][i]["monedas"].asString();
            ed = datos["usuarios"][i]["edad"].asString();
            
            //Guardando usuarios
            usuarioV.insertarNuevo(ID,nombre,pass,mon,ed);
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
