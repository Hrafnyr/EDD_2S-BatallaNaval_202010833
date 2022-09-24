#include <crow.h>
#include "../Fase 1/sha256.h"
#include "../Fase 1/ListaUsuarios.h" //Pendiente 
#include "../Fase 1/arbolB.h"


//Variables globales
listaUsuarios usuarioV;
ArbolB arbol;

int main(int argc, char **argv){

    //Creando app
    crow::SimpleApp app;


    //Creacion de rutas
    CROW_ROUTE(app, "/")([](){
        return "hello world";
    });

    //Mostrar usuarios
    CROW_ROUTE(app, "/AllUsers")
    ([]{
        return usuarioV.getDatos();
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

    //Login
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
