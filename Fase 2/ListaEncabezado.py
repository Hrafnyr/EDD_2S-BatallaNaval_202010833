from NodoEncabezado import Nodo_Encabezado


class Lista_Encabezado(): #Clase lista
    def __init__(self, tipo):
        self.primero: Nodo_Encabezado = None
        self.ultimo: Nodo_Encabezado = None
        self.tipo = tipo
        self.size = 0

    def insertar_nodoEncabezado(self, nuevo):
  
        self.size += 1
        if self.primero == None: # Es el primer nodo insertado
            self.primero = nuevo
            self.ultimo = nuevo
        else:
            # ---- Insercion en ORDEN
            if nuevo.id < self.primero.id:
                nuevo.siguiente = self.primero
                self.primero.anterior = nuevo
                self.primero = nuevo
            # -- verificamos si el nuevo es mayor que el ultimo
            elif nuevo.id > self.ultimo.id:
                self.ultimo.siguiente = nuevo
                nuevo.anterior = self.ultimo
                self.ultimo = nuevo
            else:
                # acomodar, entre el primero y el ultimo
                tmp: Nodo_Encabezado = self.primero 
                while tmp != None:
                    if nuevo.id < tmp.id:
                        nuevo.siguiente = tmp
                        nuevo.anterior = tmp.anterior
                        tmp.anterior.siguiente = nuevo
                        tmp.anterior = nuevo
                        break
                    elif nuevo.id > tmp.id:
                        tmp = tmp.siguiente
                    else:
                        break

    def mostrarEncabezados(self):
        tmp = self.primero
        while tmp != None:
            print('Encabezado', self.tipo, tmp.id)
            tmp = tmp.siguiente

    def getEncabezado(self, id) -> Nodo_Encabezado: #esta funcion debe retornar un nodo cabecera
        tmp = self.primero
        while tmp != None:
            if id == tmp.id:
                return tmp
            tmp = tmp.siguiente
        return None
    
    def setEncabezado(self, id):
        tmp = self.primero
        while tmp != None:
            if id == tmp.id:
                self.primero = None
                self.ultimo = None
                self.size-=1
            tmp = tmp.siguiente
        return None