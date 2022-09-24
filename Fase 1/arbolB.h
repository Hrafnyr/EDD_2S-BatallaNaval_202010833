#include <unistd.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include "NodoUserAB.h"
#include <iostream>

class ArbolB{
    private:
        int orden_arbol = 5;
        UsuarioB* raiz;
        int contID = 0;
    public:
        void insertarUser(string&,string&,string&,string&);
        pair<UsuarioB*, pair<bool, bool>> insertarCrearRama(UsuarioB* nodo, UsuarioB* rama);
        UsuarioB* dividir(UsuarioB* rama);
        pair<UsuarioB*, bool>  insertarEnRama(UsuarioB* primero, UsuarioB* nuevo);
        bool esHoja(UsuarioB* primero);
        int contador(UsuarioB* primero);
        void Grafo();
        string GrafoArbolAbb(UsuarioB*rama);
        string GrafoRamas(UsuarioB*rama);
        string GrafoConexionRamas(UsuarioB*rama);

        int login(string& , string& );
        int loginA(UsuarioB*,string& , string& );
        int loginB(UsuarioB*,string& , string& );

        int verificarNickname(string&);
        int verificarNicknameA(UsuarioB*,string&);
        int verificarNicknameB(UsuarioB*,string&);

        int actualizar(string&,string&,string&,string&,string&);
        int actualizarA(UsuarioB*,string&,string&,string&,string&,string&);
        int actualizarB(UsuarioB*,string&,string&,string&,string&,string&);

        int eliminar(string& , string& );
        int eliminarA(UsuarioB*,string& , string& );
        int eliminarB(UsuarioB*,string& , string& );

        ArbolB();
};

ArbolB:: ArbolB(){
    this->raiz=NULL;
}

void ArbolB::insertarUser(string& nombre,string& pass, string& mon, string& edad) {
    UsuarioB* nodo = new UsuarioB();
    nodo->contID = to_string(contID);
    nodo->nombre=nombre;
    nodo->password=pass;
    nodo->monedas=mon;
    nodo->edad=edad;

    contID+=1;
    if (raiz == NULL) {
        raiz = nodo;
    } else {
        pair < UsuarioB*, pair<bool, bool>> ret = insertarCrearRama(nodo, raiz);
        UsuarioB* obj = ret.first;
        if ((ret.second.first || ret.second.second) && obj != NULL) {//si se divide la rama o se inserta al inicio, la raiz cambia
            cout << "se cambia de rama principal ID:" << obj->contID << "\n";
            raiz = obj;
        }
    }
}

pair<UsuarioB*, pair<bool, bool>> ArbolB::insertarCrearRama(UsuarioB* nodo, UsuarioB* rama) {
    pair < UsuarioB*, pair<bool, bool>> ResultadoRama;
    ResultadoRama.first = NULL; //nodo Inicial de la rama
    ResultadoRama.second.first = false; //indica si se dividio la rama
    ResultadoRama.second.second = false; //indica si se modifica el inicio de la rama
    if (esHoja(rama)) {//si el nodo es hoja se inseta directamente dentro de ella
        pair < UsuarioB*, bool> resultado = insertarEnRama(rama, nodo); //insertamos el nuevo elemento dentro de la rama actual
        ResultadoRama.first = resultado.first; //posee la rama con el valor ya insertado
        ResultadoRama.second.second = resultado.second; //posee el resultado de si se modifico el inicio en el insert anterior
        if (contador(resultado.first) == orden_arbol) {//si la rama posee mas elementos de los permitidos se divide
            cout << "La rama debe dividirse\n";
            ResultadoRama.first = dividir(resultado.first); //dividimos la rama y obtenemos una nueva rama con sus respectivos apuntadores
            ResultadoRama.second.first = true; //identificar que la rama se dividio
        }
    } else {//si el nodo es rama se debe buscar la posicion donde insertarlo
        UsuarioB*temp = rama;
        do {
            if (stoi(nodo->contID) == stoi(temp->contID)) {//valor ya insertado, no se permiten repeditos
                cout << "insertarCrearRama(), El ID " << nodo->contID << " ya existe\n";
                return ResultadoRama;
            } else if (stoi(nodo->contID) < stoi(temp->contID)) {
                pair < UsuarioB*, pair<bool, bool>> ResultadoInsert = insertarCrearRama(nodo, temp->izquierda);
                if (ResultadoInsert.second.second && ResultadoInsert.first != NULL) {//si se modifico el inicio de la rama
                    ResultadoRama.second.second = true;
                    temp->izquierda = ResultadoInsert.first;
                }
                if (ResultadoInsert.second.first) {//se dividio la subrama
                    pair < UsuarioB*, bool> auxInsert = insertarEnRama(rama, ResultadoInsert.first);
                    rama = auxInsert.first;
                    if (auxInsert.second) {
                        ResultadoRama.first = rama;
                    }
                    if (contador(rama) == orden_arbol) {
                        ResultadoRama.first = dividir(rama);
                        ResultadoRama.second.first = true;
                    }
                }
                return ResultadoRama;
            } else if (temp->siguiente == NULL) {
                pair < UsuarioB*, pair<bool, bool>> ResultadoInsert = insertarCrearRama(nodo, temp->derecha);
                if (ResultadoInsert.second.second && ResultadoInsert.first != NULL) {//si se modifico el inicio de la rama
                    ResultadoRama.second.second = true;
                    temp->derecha = ResultadoInsert.first;
                }
                if (ResultadoInsert.second.first) {//se dividio la subrama
                    pair < UsuarioB*, bool> auxInsert = insertarEnRama(rama, ResultadoInsert.first);
                    rama = auxInsert.first;
                    if (auxInsert.second) {
                        ResultadoRama.first = rama;
                    }
                    if (contador(rama) == orden_arbol) {
                        ResultadoRama.first = dividir(rama);
                        ResultadoRama.second.first = true;
                    }
                }
                return ResultadoRama;
            }
            temp = temp->siguiente;
        } while (temp != NULL);
    }
    return ResultadoRama;
}

UsuarioB* ArbolB::dividir(UsuarioB* rama) {
    
    UsuarioB*temp = NULL;
    UsuarioB*Nuevo = NULL;
    UsuarioB*aux = rama;

    UsuarioB*rderecha = NULL;
    UsuarioB*rizquierda = NULL;

    int cont = 0;
    while (aux != NULL) {
        cont++;
        //implementacion para dividir unicamente ramas de 4 nodos
        if (cont < 3) {
            
            temp = new UsuarioB();

            temp->contID=aux->contID;
            temp->nombre=aux->nombre;
            temp->password=aux->password;
            temp->monedas=aux->monedas;
            temp->edad=aux->edad;

            temp->izquierda = aux->izquierda;
            if (cont == 2) {
                temp->derecha = aux->siguiente->izquierda;
            } else {
                temp->derecha = aux->derecha;
            }
            rizquierda = insertarEnRama(rizquierda, temp).first;
        } else if (cont == 3) {
            
            Nuevo = new UsuarioB();
            Nuevo->contID=aux->contID;
            Nuevo->nombre=aux->nombre;
            Nuevo->password=aux->password;
            Nuevo->monedas=aux->monedas;
            Nuevo->edad=aux->edad;

        } else {
           
            temp = new UsuarioB();
            temp->contID=aux->contID;
            temp->nombre=aux->nombre;
            temp->password=aux->password;
            temp->monedas=aux->monedas;
            temp->edad=aux->edad;

            temp->izquierda = aux->izquierda;
            temp->derecha = aux->derecha;
            rderecha = insertarEnRama(rderecha, temp).first;
        }
        aux = aux->siguiente;
    }
    Nuevo->derecha = rderecha;
    Nuevo->izquierda = rizquierda;
    return Nuevo;
}

pair<UsuarioB*, bool> ArbolB::insertarEnRama(UsuarioB* primero, UsuarioB* nuevo) {
    pair < UsuarioB*, bool> ret;
    ret.second = false;
    if (primero == NULL) {
        //primero en la lista
        ret.second = true;
        primero = nuevo;
    } else {
        //recorrer e insertar
        UsuarioB* aux = primero;
        while (aux != NULL) {
            if (stoi(aux->contID) == stoi(nuevo->contID)) {//------------->ya existe en el arbol
                cout << "insertarEnRama(), El ID " << nuevo->contID << " ya existe\n";
                break;
            } else {
                if (stoi(aux->contID) > stoi(nuevo->contID)) {
                    if (aux == primero) {//------------->insertar al inicio
                        aux->anterior = nuevo;
                        nuevo->siguiente = aux;
                        //ramas del nodo
                        aux->izquierda = nuevo->derecha;
                        nuevo->derecha = NULL;
                        ret.second = true;
                        primero = nuevo;
                        break;
                    } else {//------------->insertar en medio;
                        nuevo->siguiente = aux;
                        //ramas del nodo
                        aux->izquierda = nuevo->derecha;
                        nuevo->derecha = NULL;

                        nuevo->anterior = aux->anterior;
                        aux->anterior->siguiente = nuevo;
                        aux->anterior = nuevo;
                        break;
                    }
                } else if (aux->siguiente == NULL) {//------------->insertar al final
                    aux->siguiente = nuevo;
                    nuevo->anterior = aux;
                    break;
                }
            }
            aux = aux->siguiente;
        }

    }
    ret.first = primero;

    return ret;
}

/*
 * Metodo para verificar si es hoja
 * Un nodo hoja no pose apuntadores a otros nodos hacia izquierda o derecha
 */
bool ArbolB::esHoja(UsuarioB* primero) {
    UsuarioB* aux = primero;
    while (aux != NULL) {
        cout << "[" << aux->contID << "]->";
        if (aux->izquierda != NULL || aux->derecha != NULL) {
            return false;
        }
        aux = aux->siguiente;
    }
    cout << "Null\n";
    return true;
}

/*Metodo para contar los elementos de una rama*/
int ArbolB::contador(UsuarioB* primero) {
    int contador = 0;
    UsuarioB* aux = primero;
    while (aux != NULL) {
        contador++;
        aux = aux->siguiente;
    }
    return contador;
}

//================================Grafo solo del arbol b=====================

void ArbolB::Grafo() {
    string dotFull = "";
    //escribir dot

    dotFull += "digraph G {\n";
    dotFull += "node[shape=record]\n";
    dotFull += "\t\t//Agregar Nodos Rama\n";
    dotFull += GrafoArbolAbb(raiz);
    //agregar conexiones de ramas
    dotFull += "\t\t//Agregar conexiones\n";
    dotFull += GrafoConexionRamas(raiz);

    dotFull += "}";

    //Generar archivo
        try {
            string path = "Arbol";

            ofstream file;
            file.open(path + "Usuarios.dot",std::ios::out);
            file << dotFull;
            file.close();


            if(file.fail()){
                exit(1);
            }

            string command = "dot -Tpng " + path + "Usuarios.dot -o  " + path + "Usuarios.png";
            system(command.c_str());
            system(("ArbolUsuarios.png"));//Abrir archivo
        }catch (exception e){
            cout << "Error detectado, no se pudo generar el Reporte solicitado";
        }
}

string ArbolB::GrafoArbolAbb(UsuarioB* rama) {
    string dot = "";
    if (rama != NULL) {
        //agrear rama actual
        dot += GrafoRamas(rama);
        //agregar las ramas siguientes recursivamente
        UsuarioB*aux = rama;
        while (aux != NULL) {
            if (aux->izquierda != NULL) {
                dot += GrafoArbolAbb(aux->izquierda);
            }
            if (aux->siguiente == NULL) {
                if (aux->derecha != NULL) {
                    dot += GrafoArbolAbb(aux->derecha);
                }
            }
            aux = aux->siguiente;
        }
    }
    return dot;
}

string ArbolB::GrafoRamas(UsuarioB*rama) {
    string dot = "";
    string auxS="";
    stringstream auxTXT;
    if (rama != NULL) {
        //============================================agregar rama=================================
        UsuarioB*aux = rama;
        auxTXT.str("");
        auxTXT << rama;
        dot = dot + "R" + auxTXT.str() + "[label=\"";
        int r = 1;
        while (aux != NULL) {
            if (aux->izquierda != NULL) {
                dot = dot + "<C" + to_string(r) + ">|";
                r++;
            }
            if (aux->siguiente != NULL) {
                auxS+=aux->contID+"\\nUsuario: "+aux->nombre+"\\nPassword: "+aux->password+"\\nMonedas: "+aux->monedas+"\\nEdad: "+aux->edad;
                dot = dot + auxS + "|";
                auxS="";
            } else {
                auxS+=aux->contID+"\\nUsuario: "+aux->nombre+"\\nPassword: "+aux->password+"\\nMonedas: "+aux->monedas+"\\nEdad: "+aux->edad;
                dot = dot + auxS;
                auxS="";
                if (aux->derecha != NULL) {
                    dot = dot + "|<C" + to_string(r) + ">";
                }
            }
            aux = aux->siguiente;
        }
        dot = dot + "\"];\n";
    }
    return dot;
}

string ArbolB::GrafoConexionRamas(UsuarioB*rama) {
    string dot = "";
    stringstream auxTXT;
    if (rama != NULL) {
        //============================================agregar rama=================================
        UsuarioB*aux = rama;
        auxTXT << rama;
        string actual = "R" + auxTXT.str();
        int r = 1;
        while (aux != NULL) {
            if (aux->izquierda != NULL) {
                auxTXT.str("");
                auxTXT << aux->izquierda;
                dot += actual + ":C" + to_string(r) + "->" + "R" + auxTXT.str() + ";\n";
                r++;
                dot += GrafoConexionRamas(aux->izquierda);
            }
            if (aux->siguiente == NULL) {
                if (aux->derecha != NULL) {
                    auxTXT.str("");
                    auxTXT << aux->derecha;
                    dot += actual + ":C" + to_string(r) + "->" + "R" + auxTXT.str() + ";\n";
                    r++;
                    dot += GrafoConexionRamas(aux->derecha);
                }
            }
            aux = aux->siguiente;
        }
    }
    return dot;
}

int ArbolB::login(string& nick, string& pass) {
    cout<<"inicio\n";
    int r = loginA(raiz,nick, pass);
    return r;
    
}

int ArbolB::loginA(UsuarioB* rama,string& nick, string& pass){
    if (rama != NULL) {
        //ver rama actual
        int x = loginB(rama, nick, pass);
        if (x==1)
        {
            return 1;
        }else{
            //agregar las ramas siguientes recursivamente
            UsuarioB*aux = rama;
            while (aux != NULL) {
                if (aux->izquierda != NULL) {
                    int a = loginA(aux->izquierda,nick, pass);
                    return a;
                }
                if (aux->siguiente == NULL) {
                    if (aux->derecha != NULL) {
                        int b = loginA(aux->derecha,nick, pass);
                        return b;
                    }
                }
            aux = aux->siguiente;
            }
        }
    }
    return 0;
}

int  ArbolB::loginB(UsuarioB* rama,string& nick, string& pass){
    string auxS="";
    bool encontrado = false;
    if (rama != NULL) {
        UsuarioB*aux = rama;
        while (aux != NULL && encontrado==false) {
            if (aux->izquierda != NULL) {
                auxS+="a";
            }
            if (aux->siguiente != NULL) {

                if (aux->nombre==nick && aux->password==pass)
                {
                    cout<<"Usuario: "+aux->nombre<<"\n";
                    cout<<"Password: "+aux->password<<"\n";
                    cout<<"Edad: "+aux->edad<<"\n";
                    cout<<"Monedas: "+aux->monedas<<"\n";
                    cout<<"------------------------------\n";
                    encontrado = true;
                    return 1;
                }
                
                
            } else {
                if (aux->nombre==nick && aux->password==pass)
                {
                    cout<<"Usuario: "+aux->nombre<<"\n";
                    cout<<"Password: "+aux->password<<"\n";
                    cout<<"Edad: "+aux->edad<<"\n";
                    cout<<"Monedas: "+aux->monedas<<"\n";
                    cout<<"------------------------------\n";
                    encontrado = true;
                    return 1;
                }
                if (aux->derecha != NULL) {
                    auxS+="a";
                }
            }
            aux = aux->siguiente;
        }
    }
    return 0;
}

int ArbolB::verificarNickname(string& nick){
    int r = verificarNicknameA(raiz,nick);
    return r;
}

int ArbolB::verificarNicknameA(UsuarioB* rama,string& nick){
     if (rama != NULL) {
        //ver rama actual
        int x = verificarNicknameB(rama, nick);
        if (x==1)
        {
            return 1;
        }else{
            //agregar las ramas siguientes recursivamente
            UsuarioB*aux = rama;
            while (aux != NULL) {
                if (aux->izquierda != NULL) {
                    int a = verificarNicknameA(aux->izquierda,nick);
                    return a;
                }
                if (aux->siguiente == NULL) {
                    if (aux->derecha != NULL) {
                        int b = verificarNicknameA(aux->derecha,nick);
                        return b;
                    }
                }
            aux = aux->siguiente;
            }
        }
    }
    return 0;
}

int ArbolB::verificarNicknameB(UsuarioB* rama,string& nick){
    string auxS="";
    bool encontrado = false;
    if (rama != NULL) {
        UsuarioB*aux = rama;
        while (aux != NULL && encontrado==false) {
            if (aux->izquierda != NULL) {
                auxS+="a";
            }
            if (aux->siguiente != NULL) {

                if (aux->nombre==nick)
                {
                    cout<<"Usuario: "+aux->nombre<<"\n";
                    cout<<"------------------------------\n";
                    encontrado = true;
                    return 1;
                }
                
                
            } else {
                if (aux->nombre==nick)
                {
                    cout<<"Usuario: "+aux->nombre<<"\n";
                    cout<<"------------------------------\n";
                    encontrado = true;
                    return 1;
                }
                if (aux->derecha != NULL) {
                    auxS+="a";
                }
            }
            aux = aux->siguiente;
        }
    }
    return 0;
}

int ArbolB::actualizar(string& nick, string& pass,string& newName,string& passN,string& newEdad) {
    cout<<"Actualizar\n";
    int r = actualizarA(raiz,nick, pass,newName,passN,newEdad);
    return r;
    
}

int ArbolB::actualizarA(UsuarioB* rama,string& nick, string& pass, string& newName,string& passN,string& newEdad){
    if (rama != NULL) {
        //ver rama actual
        int x = actualizarB(rama, nick, pass, newName,passN,newEdad);
        if (x==1)
        {
            return 1;
        }else{
            //agregar las ramas siguientes recursivamente
            UsuarioB*aux = rama;
            while (aux != NULL) {
                if (aux->izquierda != NULL) {
                    int a = actualizarA(aux->izquierda,nick, pass,newName,passN,newEdad);
                    return a;
                }
                if (aux->siguiente == NULL) {
                    if (aux->derecha != NULL) {
                        int b = actualizarA(aux->derecha,nick, pass,newName,passN,newEdad);
                        return b;
                    }
                }
            aux = aux->siguiente;
            }
        }
    }
    return 0;
}

int  ArbolB::actualizarB(UsuarioB* rama,string& nick, string& pass, string& newName,string& passN,string& newEdad){
    string auxS="";
    bool encontrado = false;
    if (rama != NULL) {
        UsuarioB*aux = rama;
        while (aux != NULL && encontrado==false) {
            if (aux->izquierda != NULL) {
                auxS+="a";
            }
            if (aux->siguiente != NULL) {

                if (aux->nombre==nick && aux->password==pass)
                {
                    cout<<"incio de actualizar"<<endl;
                    //Validar campos para actualizar
                    if (newName.empty()!=true)
                    {
                        aux->nombre=newName;
                    }
                    
                    if (passN.empty()!=true)
                    {
                        aux->password=passN;
                    }

                    if (newEdad.empty()!=true)
                    {
                        aux->edad=newEdad;
                    }
                    cout<<"Actualizado"<<endl;
                    encontrado = true;
                    return 1;
                }
                
                
            } else {
                if (aux->nombre==nick && aux->password==pass)
                {
                    //Validar campos para actualizar
                    if (newName.empty()!=true)
                    {
                        aux->nombre=newName;
                    }
                    
                    if (passN.empty()!=true)
                    {
                        aux->password=passN;
                    }

                    if (newEdad.empty()!=true)
                    {
                        aux->edad=newEdad;
                    }
                    encontrado = true;
                    return 1;
                }
                if (aux->derecha != NULL) {
                    auxS+="a";
                }
            }
            aux = aux->siguiente;
        }
    }
    return 0;
}

int ArbolB::eliminar(string& nick, string& pass) {
    int r = eliminarA(raiz,nick, pass);
    return r;
    
}

int ArbolB::eliminarA(UsuarioB* rama,string& nick, string& pass){
    if (rama != NULL) {
        //ver rama actual
        int x = eliminarB(rama, nick, pass);
        if (x==1)
        {
            return 1;
        }else{
            //agregar las ramas siguientes recursivamente
            UsuarioB*aux = rama;
            while (aux != NULL) {
                if (aux->izquierda != NULL) {
                    int a = eliminarA(aux->izquierda,nick, pass);
                    return a;
                }
                if (aux->siguiente == NULL) {
                    if (aux->derecha != NULL) {
                        int b = eliminarA(aux->derecha,nick, pass);
                        return b;
                    }
                }
            aux = aux->siguiente;
            }
        }
    }
    return 0;
}

int  ArbolB::eliminarB(UsuarioB* rama,string& nick, string& pass){
    string auxS="";
    bool encontrado = false;
    if (rama != NULL) {
        UsuarioB*aux = rama;
        while (aux != NULL && encontrado==false) {
            if (aux->izquierda != NULL) {
                auxS+="a";
            }
            if (aux->siguiente != NULL) {

                if (aux->nombre==nick && aux->password==pass)
                {
                    aux->nombre=" ";
                    aux->password=" ";
                    aux->monedas=" ";
                    aux->edad= " ";
                    cout<<"---------> Eliminado \n";
                    encontrado = true;
                    return 1;
                }
                
                
            } else {
                if (aux->nombre==nick && aux->password==pass)
                {
                    aux->nombre=" ";
                    aux->password=" ";
                    aux->monedas=" ";
                    aux->edad= " ";
                    cout<<"---------> Eliminado \n";
                    encontrado = true;
                    return 1;
                }
                if (aux->derecha != NULL) {
                    auxS+="a";
                }
            }
            aux = aux->siguiente;
        }
    }
    return 0;
}

