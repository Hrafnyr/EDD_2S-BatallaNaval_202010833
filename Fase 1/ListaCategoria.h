
#include <iostream>
#include <string>
#include "NodoCategoria.h"
//#include "ListaArticulos.h"


using namespace std;

class listaCategoria{
    private:            
        nodoCategoria* primero;   
    public:

        void insertarInicio(string& nombreCate);
        void mostrarLista();
        void generarReporte();
        void insertarNuevoArticulo(string& nombreCate, string& id,string& nom,string& price,string&src); 
        bool verificarExistencia(string&); //Verifica si la categoría está guardada o no
        string getDatos();

        //gets
        string getNombre(string&,string&);
        string getPrecio(string&,string&);

        listaCategoria();

};

listaCategoria::listaCategoria(){ //constructor, apuntar por defecto a null
    this->primero=NULL; 
}

string listaCategoria::getNombre(string& cate, string& id){
    nodoCategoria* actual = new nodoCategoria(); //Auxiliar
    actual = primero;

    if (primero!=NULL){
        while (actual!=NULL){
            
            if (actual->categoria==cate)
            {
                return actual->elementos->getName(id);
            }
            

			actual = actual->siguiente;
        }
        
    }

    return ""; //vacio
}

string listaCategoria::getPrecio(string& cate, string& id){
    nodoCategoria* actual = new nodoCategoria(); //Auxiliar
    actual = primero;

    if (primero!=NULL){
        while (actual!=NULL){
            
            if (actual->categoria==cate)
            {
                return actual->elementos->getPrice(id);
            }
            

			actual = actual->siguiente;
        }
        
    }

    return "1000000"; //vacio
}

void listaCategoria::insertarInicio(string& nombreCate){
    
    nodoCategoria* nuevo = new nodoCategoria();//Nuevo nodo

    //Asignar valores
    nuevo->categoria = nombreCate;

    if (primero==NULL)
    {
        primero=nuevo;
    }else{
        if (verificarExistencia(nombreCate)!=true) 
        {
            nuevo->siguiente=primero;
            primero=nuevo;
        }
    }    
};

//Modificar para entregar un JSON
string listaCategoria::getDatos()
{
    nodoCategoria* actual = new nodoCategoria(); //Auxiliar
    actual = primero;
    string out = "";
    string art = "";

    if (primero!=NULL){
        while (actual!=NULL){
            
            out += "\"" + actual->categoria + "\":[";

            //concatenar los elementos de cada categoria
            out += actual->elementos->getArticulos();

            out += "]";

            if (actual->siguiente!=NULL)
            {
                out+= ",\n";
            }

			actual = actual->siguiente;
        }
        return "{\"categorias\":\n{\n"+out+"\n}\n}";
    }

    return "{\"categorias\":[]}"; //vacio
}

void listaCategoria::mostrarLista(){
    nodoCategoria* actual = new nodoCategoria(); //Auxiliar

    actual = primero;

    if (primero!=NULL){
        while (actual!=NULL){

            cout<<"Categoria: "<<actual->categoria<<endl;
            actual->elementos->mostrarLista();
            actual = actual->siguiente;
        }
    }else{
        cout<<"No hay datos"<<endl;
    }
};

bool listaCategoria::verificarExistencia(string& categoriaB){
    nodoCategoria* actual = new nodoCategoria(); //Auxiliar

    actual = primero;

    while (actual!=NULL){

        if (actual->categoria!=categoriaB)
        {
            actual = actual->siguiente;
        }else{
            return true;
        }
    }
    return false;
};

void listaCategoria::insertarNuevoArticulo(string& nombreCate, string& id,string& nom,string& price, string& src){
    nodoCategoria* actual = new nodoCategoria(); //Auxiliar

    actual = primero;
    
    while (actual!=NULL){

        if (actual->categoria!=nombreCate)
        {
            actual = actual->siguiente;
        }else{
            actual->elementos->insertarInicio(id,nom,price,src);
            break;
        }
    }

};

void listaCategoria::generarReporte(){
    system("cls");
    nodoCategoria* actual = new nodoCategoria(); //Auxiliar
    actual = primero;

    int contCate = 0;

    string datos;
    string cabecera="",NCategoria="",listaN="";
    string apuntador="";

    cabecera+="digraph G {\nrankdir=TB;";
    cabecera+="\ngraph [fontsize=15 fontname=\"Verdana\" compound=true];\n";
    cabecera+="node[shape=box fontsize=12 fillcolor=\"darkseagreen1\" style=\"filled\"];";
    cabecera+="\nsubgraph cluster_0{\nlabel=\"Articulos\";\ncolor=darkslategrey;\n";
    
    apuntador+="\n{rank=same\n";

    if (primero!=NULL){
        while (actual!=NULL){
            //Nodos categoria
            NCategoria+="NodoC"+to_string(contCate)+"[label=\""+actual->categoria+"\"];\n";

            

            //Se genera y guardan los nodos anidados
            listaN+=actual->elementos->generarReporte(contCate);
            
            //Apuntadores
            if (actual->siguiente!=NULL)
            {
                apuntador+="NodoC"+to_string(contCate)+"-> NodoC"+to_string(contCate+1)+";\n";
                contCate++;
            }
            actual = actual->siguiente;
        }
        //Unión de strings
        apuntador+="\n}\n";
        datos = cabecera+NCategoria+apuntador+listaN+"\n}\n}\n";

        //Generar archivo
        try {
            string path = "Articulos";

            ofstream file;
            file.open(path + "Reporte.dot",std::ios::out);

            if(file.fail()){
                exit(1);
            }

            file<<datos;
            file.close();
            string command = "dot -Tpng " + path + "Reporte.dot -o  " + path + "Reporte.png";
            system(command.c_str());
            system(("ArticulosReporte.png"));//Abrir archivo
        }catch (exception e){
            cout << "Error detectado, no se pudo generar el Reporte solicitado";
        }
        cout<<"--> Reporte generado\n";
    }else{
        cout<<"No hay datos"<<endl;
    }
}