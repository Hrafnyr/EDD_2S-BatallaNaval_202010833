
#include <cstdlib>

#include "arbolB.h"
#include <unistd.h>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    ArbolB pruebas;

    string nombre = "us1";
    string pass = "pas1";
    string  edad = "20";
    string mon = "15";
    string u = "4";
    int t;

    
    pruebas.insertarUser(nombre,pass,mon,edad);

    
    nombre = "us2";
    pass = "pas2";
    pruebas.insertarUser(nombre,pass,mon,edad);
    

    nombre = "us3";
    pass = "pas3";
    pruebas.insertarUser(nombre,pass,mon,edad);


    nombre = "us4";
    pass = "pas4";
    pruebas.insertarUser(nombre,pass,mon,edad);

    nombre = "us5";
    pass = "pas5";
    pruebas.insertarUser(nombre,pass,mon,edad);

    nombre = "us3";
    pass = "pas3";
    pruebas.Grafo();
    t = pruebas.login(nombre,pass);
    cout<<to_string(t)<<endl;

    return 0;
}

