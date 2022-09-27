
#include <iostream>
#include <fstream>
using namespace std;


class AVL;

// Clase compra de Arbol AVL:
class compra {
  public:
    // Constructor:
    compra(
        string idC,
        string cate,
        string prec,
        string nom, 
        compra *pad=NULL, 
        compra *izq=NULL, 
        compra *der=NULL
        ):
            id(idC),
            categoria(cate),
            precio(prec),
            nombre(nom), 
            padre(pad), 
            izquierdo(izq), 
            derecho(der), 
            FE(0) 
            {}

    // Miembros:
    string id;
    string categoria;
    string precio;
    string nombre;
    int FE;              //Factor de equilibrio: Altura derecha - Altura izquierda
    
    //Apuntadires     
    compra *izquierdo;
    compra *derecho;
    compra *padre;
    friend class AVL;   //clase amiga para que tenga acceso a sus miembros
}; 

class AVL {
  private:
   enum {IZQUIERDO, DERECHO}; //Enumeracion para hijos del mismo tipo

   // Punteros de la lista, para cabeza y compra actual:
   compra *raiz;
   compra *actual;
   int contador;
   int altura;

  public:

   // Constructor y destructor
   AVL() : raiz(NULL), actual(NULL) {}
   ~AVL() { Podar(raiz); }

   void Insertar(string idC,string cate,string prec,string nom);
   void Borrar(string id);
   bool Buscar(string id);
   bool Vacio(compra *r) { return r==NULL; }
   bool EsHoja(compra *r) { return !r->derecho && !r->izquierdo; }
   int Numerocompras(); // Contar número de Nodos:
   int AlturaArbol();
   int Altura(string id); // Calcular altura de un dato:
   string &ValorActual() { return actual->id; } // Devolver referencia al dato del nodo actual:
   void Raiz() { actual = raiz; } // Moverse al nodo raiz:
   void graficar();
   string getCodigoGraphviz();
   string getCodigoInterno(compra*);

   //metodo de recorrer
    void InOrden(); //void (*func)(string&, int) , compra *compra=NULL, bool r=true
    void auxInOrden(compra *nodo);
  private:

   // Funciones de equilibrado:
   void Equilibrar(compra *compra, int, bool);
   void RSI(compra* compra); //->simple izquierda
   void RSD(compra* compra); //->simple derecha
   void RDI(compra* compra); //->doble izquierda
   void RDD(compra* compra); //->doble derecha


   // otras funciones
   void Podar(compra* &);
   void auxContador(compra*);
   void auxAltura(compra*, int);
};

// Funcion para borrar todos los nodos a partir de uno e incluido el mismo
void AVL::Podar(compra* &compra)
{
   // Algoritmo recursivo, recorrido en postorden
   if(compra) {
      Podar(compra->izquierdo); // Podar izquierdo
      Podar(compra->derecho);   // Podar derecho
      delete compra;            // Eliminar compra
      compra = NULL;
   }
}

void AVL::Insertar(string idC,string cate,string prec,string nom){
    compra *padre = NULL;

    cout << "Insertar: " << idC << endl;
    actual = raiz;

    // Buscar el dato en el árbol, manteniendo un puntero al nodo padre
    while(!Vacio(actual) && idC != actual->id) {
      padre = actual;
      if(stoi(idC) > stoi(actual->id)) 
        actual = actual->derecho;
      else if(stoi(idC) < stoi(actual->id)) 
        actual = actual->izquierdo;
    }

    if(!Vacio(actual)) // Si se ha encontrado el elemento, regresar sin insertar porque no se acepta valores repetidos
        return; 

    if(Vacio(padre))  // Si el arbol no tiene datos el nuevo nodo será la raìz
        raiz = new compra(idC,cate,prec,nom); 

    else if(stoi(idC) < stoi(padre->id)) {    // Si el dato es menor que el que contiene el nodo padre, va a rama izquierda
        padre->izquierdo = new compra(idC,cate,prec,nom, padre);
        Equilibrar(padre, IZQUIERDO, true);
    }
    else if(stoi(idC) > stoi(padre->id)) { // Si el dato es mayor que el que contiene el nodo padre, va a la derecha
        padre->derecho =  new compra(idC,cate,prec,nom, padre);
        Equilibrar(padre, DERECHO, true);
    }
}

// Equilibrar partiendo del Nodo nuevo
void AVL::Equilibrar(compra *compra, int rama, bool nuevo)
{
    bool salir = false;

    // Recorrer camino inverso actualizando valores de FE
    while(compra && !salir) {

        if(nuevo)
            if(rama == IZQUIERDO) compra->FE--; // Depende de si añadimos ...
            else                  compra->FE++;
        else
            if(rama == IZQUIERDO) compra->FE++; // ... o borramos
            else                  compra->FE--;

        if(compra->FE == 0) 
            salir = true; // La altura de las ramas no ha variado entonces salir

        else if(compra->FE == -2) { // Rotar a derechas y salir:
            if(compra->izquierdo->FE == 1) 
                RDD(compra); // Rotación doble
            else 
                RSD(compra); // Rotación simple
            salir = true;
        }

        else if(compra->FE == 2) {  // Rotar a izquierdas y salir:
            if(compra->derecho->FE == -1) 
                RDI(compra); // Rotación doble
            else 
                RSI(compra); // Rotación simple
            salir = true;
        }

        if(compra->padre) 
            if(compra->padre->derecho == compra) 
                rama = DERECHO; 
            else 
                rama = IZQUIERDO;
        compra = compra->padre; // Calcular FE, siguiente nodo del camino.
   }   
}

// Rotación doble a derechas
void AVL::RDD(compra* nodo)
{
   cout << "RDD" << endl;
   compra *Padre = nodo->padre;
   compra *P = nodo;
   compra *Q = P->izquierdo;
   compra *R = Q->derecho;
   compra *B = R->izquierdo;
   compra *C = R->derecho;

    if(Padre) 
        if(Padre->derecho == nodo) 
            Padre->derecho = R;
        else 
            Padre->izquierdo = R;
    else 
        raiz = R;

   // Reconstruir árbol:
   Q->derecho = B;
   P->izquierdo = C;
   R->izquierdo = Q;
   R->derecho = P;
   
   // Reasignar padres:
   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) B->padre = Q;
   if(C) C->padre = P;

   // Ajustar valores de FE:
   switch(R->FE) {
      case -1: Q->FE = 0; P->FE = 1; break;
      case 0:  Q->FE = 0; P->FE = 0; break;
      case 1:  Q->FE = -1; P->FE = 0; break;
   }
   R->FE = 0;
}

// Rotación doble a izquierdas
void AVL::RDI(compra* nodo)
{
    cout << "RDI" << endl;
    compra *Padre = nodo->padre;
    compra *P = nodo;
    compra *Q = P->derecho;
    compra *R = Q->izquierdo;
    compra *B = R->izquierdo;
    compra *C = R->derecho;

    if(Padre)
        if(Padre->derecho == nodo) 
            Padre->derecho = R;
        else 
            Padre->izquierdo = R;
    else raiz = R;

   // Reconstruir árbol:
   P->derecho = B;
   Q->izquierdo = C;
   R->izquierdo = P;
   R->derecho = Q;
   
   // Reasignar padres:
   R->padre = Padre;
   P->padre = Q->padre = R;
   if(B) B->padre = P;
   if(C) C->padre = Q;

   // Ajustar valores de FE:
   switch(R->FE) {
      case -1: P->FE = 0; Q->FE = 1; break;
      case 0:  P->FE = 0; Q->FE = 0; break;
      case 1:  P->FE = -1; Q->FE = 0; break;
   }
   R->FE = 0;
}

// Rotación simple a derechas
void AVL::RSD(compra* nodo)
{
    cout << "RSD" << endl;
    compra *Padre = nodo->padre;
    compra *P = nodo;
    compra *Q = P->izquierdo;
    compra *B = Q->derecho;

    if(Padre) 
        if(Padre->derecho == P) 
            Padre->derecho = Q;
        else 
            Padre->izquierdo = Q;
    else raiz = Q;

    // Reconstruir árbol:
    P->izquierdo = B;
    Q->derecho = P;
    
    // Reasignar padres:
    P->padre = Q;
    if(B) B->padre = P;
    Q->padre = Padre;

    // Ajustar valores de FE:
    P->FE = 0;
    Q->FE = 0;
}

// Rotación simple a izquierdas
void AVL::RSI(compra* nodo)
{
    cout << "RSI" << endl;
    compra *Padre = nodo->padre;
    compra *P = nodo;
    compra *Q = P->derecho;
    compra *B = Q->izquierdo;

    if(Padre) 
        if(Padre->derecho == P) 
        Padre->derecho = Q;
        else 
        Padre->izquierdo = Q;
    else raiz = Q;

    // Reconstruir árbol:
    P->derecho = B;
    Q->izquierdo = P;
    
    // Reasignar padres:
    P->padre = Q;
    if(B) B->padre = P;
    Q->padre = Padre;
    
    // Ajustar valores de FE:
    P->FE = 0;
    Q->FE = 0;
}

// Eliminar un elemento de un árbol AVL
void AVL::Borrar(string idB)
{
   compra *padre = NULL;
   compra *nodo;
   string aux, aux1,aux2, aux3;

   actual = raiz;
   // Mientras el valor esté en el árbol
    while(!Vacio(actual)) {
        if(idB == actual->id) { // Si el valor está en el nodo actual
            if(EsHoja(actual)) { // Si es hoja se borra

                if(padre) // Si tiene padre (no es el nodo raiz) -> se anula el puntero que le hace referencia
                if(padre->derecho == actual) padre->derecho = NULL;
                else if(padre->izquierdo == actual) padre->izquierdo = NULL;
                delete actual; // Borrar el nodo
                actual = NULL;
                
                /*  El nodo padre del actual puede ser ahora un nodo hoja, por lo tanto su
                    FE es cero, pero debemos seguir el camino a partir de su padre, si existe.*/
                if((padre->derecho == actual && padre->FE == 1) || (padre->izquierdo == actual && padre->FE == -1)) {
                    padre->FE = 0;
                    actual = padre;
                    padre = actual->padre;
                }
                if(padre)
                if(padre->derecho == actual) Equilibrar(padre, DERECHO, false);
                else                         Equilibrar(padre, IZQUIERDO, false);
                return;
            }
            else { // Si el valor está en el nodo actual, pero no es hoja -> Buscar nodo
                padre = actual;
                
                if(actual->derecho) { // Buscar nodo más izquierdo de rama derecha
                    nodo = actual->derecho;
                    while(nodo->izquierdo) {
                        padre = nodo;
                        nodo = nodo->izquierdo;
                    }
                }
                else { // O buscar nodo más derecho de rama izquierda
                    nodo = actual->izquierdo;
                    while(nodo->derecho) {
                        padre = nodo;
                        nodo = nodo->derecho;
                    }
                }
                
                //Guardar datos en auxiliares
                aux  = actual->id;
                aux1 = actual->categoria;
                aux2 = actual->precio;
                aux3 = actual->nombre;

                //Reasignar datos
                actual->id          = nodo->id;
                actual->categoria   = nodo->categoria;
                actual->precio      = nodo->precio;
                actual->nombre      = nodo->nombre;

                //itercambiar datos
                nodo->id            = aux;   
                nodo->categoria     = aux1;
                nodo->precio        = aux2;
                nodo->nombre        = aux3;

                actual = nodo;
            }
        }
        else { //Seguir buscando
            padre = actual;
            if(stoi(idB) > stoi(actual->id)) actual = actual->derecho;
            else if(stoi(idB) < stoi(actual->id)) actual = actual->izquierdo;
        }
    }
}

// Recorrido de árbol en inorden, aplicamos la función func, que tien el prototipo: void func(int&, int);
void AVL::InOrden()
{   cout << "InOrden: ";
    auxInOrden(raiz);
}

void AVL::auxInOrden(compra *nodo)
{
    if (nodo == NULL) return;
       else
            auxInOrden(nodo->izquierdo) ;
            cout << "Id"+nodo->id+" - nombre: "+nodo->nombre<<endl;
            auxInOrden(nodo->derecho);
    
}

// Buscar un valor en el árbol
bool AVL::Buscar(string ID)
{
   actual = raiz;

   // Todavía puede aparecer, ya que quedan nodos por mirar
    while(!Vacio(actual)) {
        if(ID == actual->id) return true; // dato encontrado
        else if(stoi(ID) > stoi(actual->id)) actual = actual->derecho; // Seguir
        else if(stoi(ID) < stoi(actual->id)) actual = actual->izquierdo;
    }
    return false; // No está en árbol
}

// Calcular la altura del compra que contiene el dato dat
int AVL::Altura(string id)
{
   int altura = 0;
   actual = raiz;

   // Todavía puede aparecer, ya que quedan compras por mirar
   while(!Vacio(actual)) {
      if(id == actual->id) return altura; // dato encontrado
      else {
         altura++; // Incrementamos la altura, seguimos buscando
         if(stoi(id) > stoi(actual->id)) actual = actual->derecho;
         else if(stoi(id) < stoi(actual->id)) actual = actual->izquierdo;
      }
   }
   return -1; // No está en árbol
}

// Contar el número de nodos
int AVL::Numerocompras()
{
   contador = 0;
   auxContador(raiz); // FUnción auxiliar
   return contador;
}

// Función auxiliar para contar nodos. Función recursiva de recorrido en preorden, el proceso es aumentar el contador
void AVL::auxContador(compra *nodo)
{
   contador++; 
   // Continuar recorrido
   if(nodo->izquierdo) auxContador(nodo->izquierdo);
   if(nodo->derecho)   auxContador(nodo->derecho);
}

// Calcular la altura del árbol, que es la altura del nodo de mayor altura.
int AVL::AlturaArbol()
{
   altura = 0;

   auxAltura(raiz, 0); // Función auxiliar
   return altura;
}

// Recorrido en postorden, actualziar la altura sólo en nodos hojas de mayor altura de la máxima actual
void AVL::auxAltura(compra *nodo, int a)
{
   // Recorrido postorden
   if(nodo->izquierdo) auxAltura(nodo->izquierdo, a+1);
   if(nodo->derecho)   auxAltura(nodo->derecho, a+1);
   
    /*  Si es un nodo hoja, y su altura es mayor que la actual del
        árbol, actualizamos la altura actual del árbol*/
   if(EsHoja(nodo) && a > altura) altura = a;
}

void AVL::graficar() {
    string path = "Arbol";
    try {
        

        ofstream file;
        file.open(path + "AVL.dot",std::ios::out);
        file << getCodigoGraphviz();
        file.close();            
    }catch (exception e){
        cout << "Error detectado, no se pudo generar el Reporte solicitado";
    }
                        
    try{
        string command = "dot -Tpng " + path + "AVL.dot -o  " + path + "AVL.png";
        string command2 = "shotwell ArbolAVL.png";
        system(command.c_str());
        system(command2.c_str());//Abrir archivo
    } catch (exception e) {
        cout<<"Error al generar la imagen para el archivo aux_grafico.dot"<<endl;
    }            
}
    
string AVL::getCodigoGraphviz() {
    
    return "digraph grafica{\nrankdir=TB;\nnode [shape = record, style=filled, fillcolor=seashell2];\n"+getCodigoInterno(raiz)+"}\n";
}

string AVL::getCodigoInterno(compra* nodo) {
    string etiqueta;
    string aux;

    //FALTA IMPRIMIR TODOS LOS DATOS
    if(nodo->izquierdo==NULL && nodo->derecho==NULL){
        aux="ID: "+nodo->id+"\\nNombre:"+nodo->nombre+"\\nPrecio:"+nodo->precio+"\\nCategoria:"+nodo->categoria;
        etiqueta="nodo"+nodo->id+" [ label =\""+aux+"\"];\n";
    }else{
        aux="ID: "+nodo->id+"\\nNombre:"+nodo->nombre+"\\nPrecio:"+nodo->precio+"\\nCategoria:"+nodo->categoria;
        etiqueta="nodo"+nodo->id+" [ label =\"<C0>|"+aux+"|<C1>\"];\n";
    }
    if(nodo->izquierdo!=NULL){
        etiqueta=etiqueta + getCodigoInterno(nodo->izquierdo) +
            "nodo"+nodo->id+":C0->nodo"+nodo->izquierdo->id+"\n";
    }
    if(nodo->derecho!=NULL){
        etiqueta = etiqueta+getCodigoInterno(nodo->derecho)
        +"nodo"+nodo->id+":C1->nodo"+nodo->derecho->id+"\n";                    
    }
    return etiqueta;
}        

