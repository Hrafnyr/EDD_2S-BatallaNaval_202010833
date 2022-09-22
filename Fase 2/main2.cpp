#include <crow.h>
#include "../Fase 1/ListaUsuarios.h"


//Variables globales
listaUsuarios usuarioV;

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
            mon = "0";
        } catch (const std::runtime_error &err) {
            return crow::response(400, "Invalid body");
        }

        try {
            res = "{\"nombre\":\""+nombre+"\",\"PASS\":\""+pass+"\",\"EDAD\":\""+edad+"\"}";
            return crow::response(200,res);

        } catch (const std::runtime_error &ex) {
            return crow::response(500, "Internal Server Error");
        }

        return crow::response(200, "Blog added");
    });

    //inicializacion
    app.port(8080).multithreaded().run();

    return 0;
}
