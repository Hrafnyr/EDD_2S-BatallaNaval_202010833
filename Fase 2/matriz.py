from NodoEncabezado import Nodo_Encabezado
from ListaEncabezado import Lista_Encabezado
import os
import random

class Nodo_Interno(): # Nodos ortogonales/celda
    def __init__(self, x, y, caracter):# 'caracter' puede ser cualquier valor
        self.caracter = caracter
        self.coordenadaX = x  # fila
        self.coordenadaY = y  # columna

        #apuntadores
        self.arriba = None
        self.abajo = None
        self.derecha = None  # self.siguiente
        self.izquierda = None  # self.anterior
    
    def setArriba(self, arriba): self.arriba = arriba
    
    def getArriba(self): return self.arriba
    
    def setAbajo(self, abajo): self.abajo = abajo

    def getAbajo(self): return self.abajo

    def setDerecha(self, derecha): self.derecha = derecha

    def getDerecha(self): return self.derecha

    def setIzquierda(self, izquierda): self.izquierda = izquierda

    def getIzquierda(self): return self.izquierda

    def setCaracter(self,nuevoCaracter): self.caracter = nuevoCaracter

class MatrizDispersa():
    def __init__(self, capa):
        self.capa = capa
        self.filas = Lista_Encabezado('fila') # Encabezados  X
        self.columnas = Lista_Encabezado('columna') # Encabezados  Y
        self.sizeT = 0
        self.CarateresDisparados = []

    def putSizeT(self,size):
        self.sizeT = size

    # (filas = x, columnas = y)
    def insert(self, pos_x, pos_y, caracter):
        nuevo = Nodo_Interno(pos_x, pos_y, caracter) # se crea nodo interno
        # verifica si hay nodos
        nodo_X = self.filas.getEncabezado(pos_x)
        nodo_Y = self.columnas.getEncabezado(pos_y)

        if nodo_X == None: 
             # --- si nodo_X es nulo, quiere decir que no existe encabezado fila pos_x, por lo tanto hay que crearlo
            nodo_X = Nodo_Encabezado(pos_x)
            self.filas.insertar_nodoEncabezado(nodo_X)

        if nodo_Y == None: 
            # --- si nodo_Y es nulo, quiere decir que no existe encabezado columna pos_y, por lo tanto hay que crearlo
            nodo_Y = Nodo_Encabezado(pos_y)
            self.columnas.insertar_nodoEncabezado(nodo_Y)

        # ----- INSERTAR NUEVO EN FILA
        if nodo_X.acceso == None: # -- comprobamos que el nodo_x no esta apuntando hacia ningun nodoInterno
            nodo_X.acceso = nuevo
        else: # -- si esta apuntando, validamos si la posicion de la columna del NUEVO nodoInterno es menor a la posicion de la columna del acceso 
            if nuevo.coordenadaY < nodo_X.acceso.coordenadaY: # F1 --->  NI 1,1     NI 1,3
                nuevo.derecha = nodo_X.acceso              
                nodo_X.acceso.izquierda = nuevo
                nodo_X.acceso = nuevo
            else:
                #de no cumplirse debemos movernos de izquierda a derecha buscando donde posicionar el NUEVO nodoInterno
                tmp : Nodo_Interno = nodo_X.acceso     # nodo_X:F1 --->      NI 1,2; NI 1,3; NI 1,5;
                while tmp != None:                      #NI 1,6
                    if nuevo.coordenadaY < tmp.coordenadaY:
                        nuevo.derecha = tmp
                        nuevo.izquierda = tmp.izquierda
                        tmp.izquierda.derecha = nuevo
                        tmp.izquierda = nuevo
                        break
                    elif nuevo.coordenadaX == tmp.coordenadaX and nuevo.coordenadaY == tmp.coordenadaY: #validamos que no haya repetidas
                        break
                    else:
                        if tmp.derecha == None:
                            tmp.derecha = nuevo
                            nuevo.izquierda = tmp
                            break
                        else:
                            tmp = tmp.derecha 

        # ----- INSERTAR NUEVO EN COLUMNA
        if nodo_Y.acceso == None:  # -- comprobamos que el nodo_y no esta apuntando hacia ningun nodoCelda
            nodo_Y.acceso = nuevo
        else: # -- si esta apuntando, validamos si la posicion de la fila del NUEVO nodoCelda es menor a la posicion de la fila del acceso 
            if nuevo.coordenadaX < nodo_Y.acceso.coordenadaX:
                nuevo.abajo = nodo_Y.acceso
                nodo_Y.acceso.arriba = nuevo
                nodo_Y.acceso = nuevo
            else:
                # de no cumplirse, debemos movernos de arriba hacia abajo buscando donde posicionar el NUEVO
                tmp2 : Nodo_Interno = nodo_Y.acceso
                while tmp2 != None:
                    if nuevo.coordenadaX < tmp2.coordenadaX:
                        nuevo.abajo = tmp2
                        nuevo.arriba = tmp2.arriba
                        tmp2.arriba.abajo = nuevo
                        tmp2.arriba = nuevo
                        break;
                    elif nuevo.coordenadaX == tmp2.coordenadaX and nuevo.coordenadaY == tmp2.coordenadaY: #validamos que no haya repetidas
                        break;
                    else:
                        if tmp2.abajo == None:
                            tmp2.abajo = nuevo
                            nuevo.arriba = tmp2
                            break
                        else:
                            tmp2 = tmp2.abajo

    def eliminacionPorFilas(self,filas):  #Recorre filas, hacia la derecha, limpia la matriz para reutilizarla de nuevo
        f = 1
        f2 = int(filas)+1

        while f < f2:
            inicio : Nodo_Encabezado = self.filas.getEncabezado(f)
            if inicio == None:
                print('----> Vaciando')
                return None
            else:    
                tmp : Nodo_Interno = inicio.getAcceso()
                while tmp != None:
                    self.filas.setEncabezado(f)
                    self.columnas.setEncabezado(f)
                    inicio.setAcceso(None)
                    tmp = tmp.getDerecha()
            f+=1

    def insertarMovimiento(self,fila,columna):
        inicio : Nodo_Encabezado = self.filas.getEncabezado(fila) #Se obtiene la cabecera con la fila
        if inicio == None:
            print('Esa coordenada de fila no existe')
            return "nExist"
            
        tmp : Nodo_Interno = inicio.getAcceso() #Verifica el acceso
        verificador = False
        while tmp != None:

            if tmp.coordenadaX == fila and tmp.coordenadaY == columna: #Ubica el punto
                verificador = True
                #primero validamos que no haya barco
                if tmp.caracter == "P" or tmp.caracter == "S" or tmp.caracter == "D" or tmp.caracter == "B":
                    #Se agrega para su posterior reestablecimiento
                    self.CarateresDisparados.append(tmp.caracter)
                    
                    tmp.caracter = "x"
                    return "Disparo"
                else:
                    if tmp.caracter == " ":
                        #Se agrega para su posterior reestablecimiento
                        self.CarateresDisparados.append(tmp.caracter)

                        tmp.caracter = "X"
                    return "Fallo"


            tmp = tmp.getDerecha()

        if verificador == False:
            print('Coordenada no encontrada')

        return "NAC"

    def ubicarPortavion(self,fila, columna): #Se solicita el punto de entrada  
      
        inicio : Nodo_Encabezado = self.filas.getEncabezado(fila) #Se obtiene la cabecera con la fila
        if inicio == None:
            print('Esa coordenada de fila no existe')
            return None
            
        tmp : Nodo_Interno = inicio.getAcceso() #Verifica el acceso
        verificador = False
        while tmp != None:
            if tmp.coordenadaX == fila and tmp.coordenadaY == columna: #Ubica el punto

                #primero validamos que no haya barco
                if tmp.caracter == " ":
                    
                    #Luego miramos caminos disponibles partiendo de la actual: arriba, abajo, izquierda, derecha
                    arriba      = []
                    abajo       = []
                    izquierda   = []
                    derecha     = []

                    aux1 = tmp
                    aux2 = tmp
                    aux3 = tmp
                    aux4 = tmp

                    #arriba
                    while len(arriba) < 4 and aux1!=None:

                        if aux1.caracter == " ":
                            cr = [aux1.coordenadaX,aux1.coordenadaY]
                            arriba.append(cr)
                        
                        aux1 = aux1.arriba

                    #print("Arriba: ",arriba)
                    if len(arriba)==4:
                        #recorremos las posiciones y pintamosabajo
                        for p in arriba:
                            self.pintarPortavion(p[0],p[1])
                    
                        del arriba
                        return "OK"

                    else:
                        #abajo
                        while len(abajo) < 4 and aux2!=None:

                            if aux2.caracter == " ":
                                cr = [aux2.coordenadaX,aux2.coordenadaY]
                                abajo.append(cr)
                            
                            aux2 = aux2.abajo
                        #print("Abajo: ",abajo)
                        if len(abajo)==4:
                            #recorremos las posiciones y pintamos
                            for p in abajo:
                                self.pintarPortavion(p[0],p[1])
                            
                            del abajo
                            return "OK"
                        else: 

                            #izquierda
                            while len(izquierda) < 4 and aux3!=None:

                                if aux3.caracter == " ":
                                    cr = [aux3.coordenadaX,aux3.coordenadaY]
                                    izquierda.append(cr)
                                
                                aux3 = aux3.izquierda
                            #print("izquierda :", izquierda)
                            if len(izquierda)==4:
                                #recorremos las posiciones y pintamos
                                for p in izquierda:
                                    self.pintarPortavion(p[0],p[1])
                                
                                del izquierda
                                return "OK"
                            else:
                                #print("derecha: ",derecha)
                                #derecha
                                while len(derecha) <4 and aux4!=None:

                                    if aux4.caracter == " ":
                                        cr = [aux4.coordenadaX,aux4.coordenadaY]
                                        derecha.append(cr)
                                    
                                    aux4 = aux4.derecha 

                                if len(derecha)==4:
                                    #recorremos las posiciones y pintamos
                                    for p in derecha:
                                        self.pintarPortavion(p[0],p[1])
                                    del derecha 
                                    return "OK"                                        

                else:
                    #print("ya hay un objeto en la coordenada") #si no retornamos none y pedimos otro punto
                    return None

                verificador = True

            tmp = tmp.getDerecha()

        if verificador == False:
            print('Coordenada no encontrada')

        return None

    def pintarPortavion(self,fila, columna): #Se solicita el punto de entrada  
      
        inicio : Nodo_Encabezado = self.filas.getEncabezado(fila) #Se obtiene la cabecera con la fila
        if inicio == None:
            print('Esa coordenada de fila no existe')
            return None
            
        tmp : Nodo_Interno = inicio.getAcceso() #Verifica el acceso
        verificador = False
        while tmp != None:
            if tmp.coordenadaX == fila and tmp.coordenadaY == columna: #Ubica el punto

                #primero validamos que no haya barco
                tmp.caracter = "P"
                verificador = True
                return "OK"

            tmp = tmp.getDerecha()

        if verificador == False:
            print('Coordenada no encontrada')

        return None

    def ubicarSubmarino(self,fila, columna): #Se solicita el punto de entrada  
      
        inicio : Nodo_Encabezado = self.filas.getEncabezado(fila) #Se obtiene la cabecera con la fila
        if inicio == None:
            print('Esa coordenada de fila no existe')
            return None
            
        tmp : Nodo_Interno = inicio.getAcceso() #Verifica el acceso
        verificador = False
        while tmp != None:
            if tmp.coordenadaX == fila and tmp.coordenadaY == columna: #Ubica el punto

                #primero validamos que no haya barco
                if tmp.caracter == " ":
                    
                    #Luego miramos caminos disponibles partiendo de la actual: arriba, abajo, izquierda, derecha
                    arriba      = []
                    abajo       = []
                    izquierda   = []
                    derecha     = []

                    aux1 = tmp
                    aux2 = tmp
                    aux3 = tmp
                    aux4 = tmp

                    #arriba
                    while len(arriba) < 3 and aux1!=None:

                        if aux1.caracter == " ":
                            cr = [aux1.coordenadaX,aux1.coordenadaY]
                            arriba.append(cr)
                        else: break
                        aux1 = aux1.arriba

                    #print("Arriba: ",arriba)
                    if len(arriba)==3:
                        #recorremos las posiciones y pintamosabajo
                        for p in arriba:
                            self.pintarSubmarino(p[0],p[1])
                    
                        del arriba
                        return "OK"

                    else:
                        #abajo
                        while len(abajo) < 3 and aux2!=None:

                            if aux2.caracter == " ":
                                cr = [aux2.coordenadaX,aux2.coordenadaY]
                                abajo.append(cr)
                            else: break
                            aux2 = aux2.abajo
                        #print("Abajo: ",abajo)
                        if len(abajo)==3:
                            #recorremos las posiciones y pintamos
                            for p in abajo:
                                self.pintarSubmarino(p[0],p[1])
                            
                            del abajo
                            return "OK"
                        else: 

                            #izquierda
                            while len(izquierda) < 3 and aux3!=None:

                                if aux3.caracter == " ":
                                    cr = [aux3.coordenadaX,aux3.coordenadaY]
                                    izquierda.append(cr)
                                else: break
                                aux3 = aux3.izquierda
                            #print("izquierda :", izquierda)
                            if len(izquierda)==3:
                                #recorremos las posiciones y pintamos
                                for p in izquierda:
                                    self.pintarSubmarino(p[0],p[1])
                                
                                del izquierda
                                return "OK"
                            else:
                                #print("derecha: ",derecha)
                                #derecha
                                while len(derecha) < 3 and aux4!=None:

                                    if aux4.caracter == " ":
                                        cr = [aux4.coordenadaX,aux4.coordenadaY]
                                        derecha.append(cr)
                                    else: break
                                    aux4 = aux4.derecha 

                                if len(derecha)==3:
                                    #recorremos las posiciones y pintamos
                                    for p in derecha:
                                        self.pintarSubmarino(p[0],p[1])
                                    del derecha 
                                    return "OK"                                        

                else:
                    print("ya hay un objeto en la coordenada") #si no retornamos none y pedimos otro punto
                    return None

                verificador = True

            tmp = tmp.getDerecha()

        if verificador == False:
            print('Coordenada no encontrada')

        return None

    def pintarSubmarino(self,fila, columna): #Se solicita el punto de entrada  
      
        inicio : Nodo_Encabezado = self.filas.getEncabezado(fila) #Se obtiene la cabecera con la fila
        if inicio == None:
            print('Esa coordenada de fila no existe')
            return None
            
        tmp : Nodo_Interno = inicio.getAcceso() #Verifica el acceso
        verificador = False
        while tmp != None:
            if tmp.coordenadaX == fila and tmp.coordenadaY == columna: #Ubica el punto

                #primero validamos que no haya barco
                tmp.caracter = "S"
                verificador = True
                return "OK"

            tmp = tmp.getDerecha()

        if verificador == False:
            print('Coordenada no encontrada')

        return None

    def ubicarDestructor(self,fila, columna): #Se solicita el punto de entrada  
      
        inicio : Nodo_Encabezado = self.filas.getEncabezado(fila) #Se obtiene la cabecera con la fila
        if inicio == None:
            print('Esa coordenada de fila no existe')
            return None
            
        tmp : Nodo_Interno = inicio.getAcceso() #Verifica el acceso
        verificador = False
        while tmp != None:
            if tmp.coordenadaX == fila and tmp.coordenadaY == columna: #Ubica el punto

                #primero validamos que no haya barco
                if tmp.caracter == " ":
                    
                    #Luego miramos caminos disponibles partiendo de la actual: arriba, abajo, izquierda, derecha
                    arriba      = []
                    abajo       = []
                    izquierda   = []
                    derecha     = []

                    aux1 = tmp
                    aux2 = tmp
                    aux3 = tmp
                    aux4 = tmp

                    #arriba
                    while len(arriba) < 2 and aux1!=None:

                        if aux1.caracter == " ":
                            cr = [aux1.coordenadaX,aux1.coordenadaY]
                            arriba.append(cr)
                        else: break
                        aux1 = aux1.arriba

                    #print("Arriba: ",arriba)
                    if len(arriba)==2:
                        #recorremos las posiciones y pintamosabajo
                        for p in arriba:
                            self.pintarDestructor(p[0],p[1])
                    
                        del arriba
                        return "OK"

                    else:
                        #abajo
                        while len(abajo) < 2 and aux2!=None:

                            if aux2.caracter == " ":
                                cr = [aux2.coordenadaX,aux2.coordenadaY]
                                abajo.append(cr)
                            else: break
                            aux2 = aux2.abajo
                        #print("Abajo: ",abajo)
                        if len(abajo)==2:
                            #recorremos las posiciones y pintamos
                            for p in abajo:
                                self.pintarDestructor(p[0],p[1])
                            
                            del abajo
                            return "OK"
                        else: 

                            #izquierda
                            while len(izquierda) < 2 and aux3!=None:

                                if aux3.caracter == " ":
                                    cr = [aux3.coordenadaX,aux3.coordenadaY]
                                    izquierda.append(cr)
                                else: break
                                aux3 = aux3.izquierda
                            #print("izquierda :", izquierda)
                            if len(izquierda)==2:
                                #recorremos las posiciones y pintamos
                                for p in izquierda:
                                    self.pintarDestructor(p[0],p[1])
                                
                                del izquierda
                                return "OK"
                            else:
                                #print("derecha: ",derecha)
                                #derecha
                                while len(derecha) < 2 and aux4!=None:

                                    if aux4.caracter == " ":
                                        cr = [aux4.coordenadaX,aux4.coordenadaY]
                                        derecha.append(cr)
                                    else: break
                                    aux4 = aux4.derecha 

                                if len(derecha)==2:
                                    #recorremos las posiciones y pintamos
                                    for p in derecha:
                                        self.pintarDestructor(p[0],p[1])
                                    del derecha 
                                    return "OK"                                        

                else:
                    print("ya hay un objeto en la coordenada") #si no retornamos none y pedimos otro punto
                    return None

                verificador = True

            tmp = tmp.getDerecha()

        if verificador == False:
            print('Coordenada no encontrada')

        return None

    def pintarDestructor(self,fila, columna): #Se solicita el punto de entrada  
      
        inicio : Nodo_Encabezado = self.filas.getEncabezado(fila) #Se obtiene la cabecera con la fila
        if inicio == None:
            print('Esa coordenada de fila no existe')
            return None
            
        tmp : Nodo_Interno = inicio.getAcceso() #Verifica el acceso
        verificador = False
        while tmp != None:
            if tmp.coordenadaX == fila and tmp.coordenadaY == columna: #Ubica el punto

                #primero validamos que no haya barco
                tmp.caracter = "D"
                verificador = True
                return "OK"

            tmp = tmp.getDerecha()

        if verificador == False:
            print('Coordenada no encontrada')

        return None

    def ubicarBuque(self,fila, columna): #Se solicita el punto de entrada  
      
        inicio : Nodo_Encabezado = self.filas.getEncabezado(fila) #Se obtiene la cabecera con la fila
        if inicio == None:
            print('Esa coordenada de fila no existe')
            return None
            
        tmp : Nodo_Interno = inicio.getAcceso() #Verifica el acceso
        verificador = False
        while tmp != None:
            if tmp.coordenadaX == fila and tmp.coordenadaY == columna: #Ubica el punto

                #primero validamos que no haya barco
                if tmp.caracter == " ":
                    
                    #Luego miramos caminos disponibles partiendo de la actual: arriba, abajo, izquierda, derecha
                    arriba      = []
                    abajo       = []
                    izquierda   = []
                    derecha     = []

                    aux1 = tmp
                    aux2 = tmp
                    aux3 = tmp
                    aux4 = tmp

                    #arriba
                    while len(arriba) < 1 and aux1!=None:

                        if aux1.caracter == " ":
                            cr = [aux1.coordenadaX,aux1.coordenadaY]
                            arriba.append(cr)
                        else: break
                        aux1 = aux1.arriba

                    #print("Arriba: ",arriba)
                    if len(arriba)==1:
                        #recorremos las posiciones y pintamosabajo
                        for p in arriba:
                            self.pintarBuque(p[0],p[1])
                    
                        del arriba
                        return "OK"

                    else:
                        #abajo
                        while len(abajo) < 1 and aux2!=None:

                            if aux2.caracter == " ":
                                cr = [aux2.coordenadaX,aux2.coordenadaY]
                                abajo.append(cr)
                            else: break
                            aux2 = aux2.abajo
                        #print("Abajo: ",abajo)
                        if len(abajo)==1:
                            #recorremos las posiciones y pintamos
                            for p in abajo:
                                self.pintarBuque(p[0],p[1])
                            
                            del abajo
                            return "OK"
                        else: 

                            #izquierda
                            while len(izquierda) < 1 and aux3!=None:

                                if aux3.caracter == " ":
                                    cr = [aux3.coordenadaX,aux3.coordenadaY]
                                    izquierda.append(cr)
                                else: break
                                aux3 = aux3.izquierda
                            #print("izquierda :", izquierda)
                            if len(izquierda)==1:
                                #recorremos las posiciones y pintamos
                                for p in izquierda:
                                    self.pintarBuque(p[0],p[1])
                                
                                del izquierda
                                return "OK"
                            else:
                                #print("derecha: ",derecha)
                                #derecha
                                while len(derecha) < 1 and aux4!=None:

                                    if aux4.caracter == " ":
                                        cr = [aux4.coordenadaX,aux4.coordenadaY]
                                        derecha.append(cr)
                                    else: break
                                    aux4 = aux4.derecha 

                                if len(derecha)==1:
                                    #recorremos las posiciones y pintamos
                                    for p in derecha:
                                        self.pintarBuque(p[0],p[1])
                                    del derecha 
                                    return "OK"                                        

                else:
                    print("ya hay un objeto en la coordenada") #si no retornamos none y pedimos otro punto
                    return None

                verificador = True

            tmp = tmp.getDerecha()

        if verificador == False:
            print('Coordenada no encontrada')

        return None

    def pintarBuque(self,fila, columna): #Se solicita el punto de entrada  
      
        inicio : Nodo_Encabezado = self.filas.getEncabezado(fila) #Se obtiene la cabecera con la fila
        if inicio == None:
            print('Esa coordenada de fila no existe')
            return None
            
        tmp : Nodo_Interno = inicio.getAcceso() #Verifica el acceso
        verificador = False
        while tmp != None:
            if tmp.coordenadaX == fila and tmp.coordenadaY == columna: #Ubica el punto

                #primero validamos que no haya barco
                tmp.caracter = "B"
                verificador = True
                return "OK"

            tmp = tmp.getDerecha()

        if verificador == False:
            print('Coordenada no encontrada')

        return None

    def getShips(self,size):
        tot = ((size-1)//10)+1
        p = tot
        s = p+p
        d = s+p
        b = d+p
        return {'p':p,'s':s,'d':d,'b':b} # retorna un json con la cantidad de barcos 

    def generarPosicionesAleatorias(self):
        #primero obtenemos la configuaricon de barcos
        config = self.getShips(self.sizeT)

        #obtenemos cantidad de barcos individuales
        p = int(config["p"])
        s = int(config["s"])
        d = int(config["d"])
        b = int(config["b"])

        #construir portaviones
        aux1 = 0
        while aux1 < p :
            #primero generamos una coordenada aleatoria
            tmpF = self.getFila(self.sizeT)
            tmpC = self.getColumna(self.sizeT)
        
            #Buscamos coordenada y ubicamos el objeto
            porta = self.ubicarPortavion(tmpF,tmpC)
           
            if porta != None:
                #aumentamos contador de objetos ubicados
                aux1+=1

        #construir submarinos
        aux2 = 0
        while aux2 < s :
            #primero generamos una coordenada aleatoria
            tmpF = self.getFila(self.sizeT)
            tmpC = self.getColumna(self.sizeT)
        
            #Buscamos coordenada y ubicamos el objeto
            porta = self.ubicarSubmarino(tmpF,tmpC)
            
            if porta != None:
                #aumentamos contador de objetos ubicados
                aux2+=1
        
        #construir Destructores
        aux3 = 0
        while aux3 < d :
            #primero generamos una coordenada aleatoria
            tmpF = self.getFila(self.sizeT)
            tmpC = self.getColumna(self.sizeT)
        
            #Buscamos coordenada y ubicamos el objeto
            porta = self.ubicarDestructor(tmpF,tmpC)
            
            if porta != None:
                #aumentamos contador de objetos ubicados
                aux3+=1
        
        #construir Buques
        aux4 = 0
        while aux4 < b :
            #primero generamos una coordenada aleatoria
            tmpF = self.getFila(self.sizeT)
            tmpC = self.getColumna(self.sizeT)
        
            #Buscamos coordenada y ubicamos el objeto
            porta = self.ubicarBuque(tmpF,tmpC)
            
            if porta != None:
                #aumentamos contador de objetos ubicados
                aux4+=1

    def getFila(self,size):
        x = random.randint(1,size)
        return x
    
    def getColumna(self,size):
        y = random.randint(1,size)
        return y

    def graficarNeato(self, nombre,name1):
        contenido = '''digraph G{
    node[shape=box, width=0.7, height=0.7, fontname="Arial", fillcolor="white", style=filled]
    edge[style = "bold"]
    node[label = "Mapa:''' + str(self.capa) +'''" fillcolor="darkolivegreen1" pos = "-1,1!"]raiz;'''
        contenido += '''label = "{}" \nfontname="Arial Black" \nfontsize="25pt" \n
                    \n'''.format('\n'+name1)

        # --graficar nodos ENCABEZADO
        # --graficar nodos fila
        pivote = self.filas.primero
        posx = 0
        while pivote != None:
            contenido += '\n\tnode[label = "F{}" fillcolor="azure3" pos="-1,-{}!" shape=box]x{};'.format(pivote.id, 
            posx, pivote.id)
            pivote = pivote.siguiente
            posx += 1
        pivote = self.filas.primero
       
        # --graficar nodos columna
        pivotey = self.columnas.primero
        posy = 0
        while pivotey != None:
            contenido += '\n\tnode[label = "C{}" fillcolor="azure3" pos = "{},1!" shape=box]y{};'.format(pivotey.id, 
            posy, pivotey.id)
            pivotey = pivotey.siguiente
            posy += 1
        pivotey = self.columnas.primero

        #Grafica de nodos celda, segun el contenido
        pivote = self.filas.primero
        posx = 0
        while pivote != None:
            pivote_celda : Nodo_Interno = pivote.acceso
            while pivote_celda != None:
                # --- buscamos posy
                pivotey = self.columnas.primero
                posy_celda = 0
                while pivotey != None:
                    if pivotey.id == pivote_celda.coordenadaY: break
                    posy_celda += 1
                    pivotey = pivotey.siguiente

                #Aqui se puede colorear la celda segun sea su contenido    
                if pivote_celda.caracter == 'P':
                    contenido += '\n\tnode[label=" " fillcolor="Maroon" pos="{},-{}!" shape=box]i{}_{};'.format( #pos="{},-{}!"
                        posy_celda, posx, pivote_celda.coordenadaX, pivote_celda.coordenadaY
                    )
                elif pivote_celda.caracter == 'S':
                    contenido += '\n\tnode[label=" " fillcolor="Navy" pos="{},-{}!" shape=box]i{}_{};'.format( #pos="{},-{}!"
                        posy_celda, posx, pivote_celda.coordenadaX, pivote_celda.coordenadaY
                    )
                elif pivote_celda.caracter == 'D':
                    contenido += '\n\tnode[label=" " fillcolor="Gray" pos="{},-{}!" shape=box]i{}_{};'.format( #pos="{},-{}!"
                        posy_celda, posx, pivote_celda.coordenadaX, pivote_celda.coordenadaY
                    )
                elif pivote_celda.caracter == 'B':
                    contenido += '\n\tnode[label=" " fillcolor="Teal" pos="{},-{}!" shape=box]i{}_{};'.format( #pos="{},-{}!"
                        posy_celda, posx, pivote_celda.coordenadaX, pivote_celda.coordenadaY
                    )
                elif pivote_celda.caracter == 'x':
                    contenido += '\n\tnode[label="x" fillcolor="red" pos="{},-{}!" shape=box]i{}_{};'.format( #pos="{},-{}!"
                        posy_celda, posx, pivote_celda.coordenadaX, pivote_celda.coordenadaY
                    )
                elif pivote_celda.caracter == 'X':
                    contenido += '\n\tnode[label="X" fillcolor="yellow" pos="{},-{}!" shape=box]i{}_{};'.format( #pos="{},-{}!"
                        posy_celda, posx, pivote_celda.coordenadaX, pivote_celda.coordenadaY
                    )
                else:
                    contenido += '\n\tnode[label=" " fillcolor="white" pos="{},-{}!" shape=box]i{}_{};'.format( # pos="{},-{}!"
                        posy_celda, posx, pivote_celda.coordenadaX, pivote_celda.coordenadaY
                    ) 
                pivote_celda = pivote_celda.derecha
            
            pivote_celda = pivote.acceso
            
            pivote = pivote.siguiente
            posx += 1
        
        pivote = self.columnas.primero
                
        contenido += '\n}'


        #--- se genera DOT y se procede a ecjetuar el comando
        dot = "matriz_{}_dot.dot".format(nombre)
        archivo = open(dot,'w', encoding='utf-8')
        archivo.write(contenido)
        archivo.close()

        result = "matriz_{}.png".format(nombre)
        os.system("neato -Tpng " + dot + " -o " + result)
        #os.system("shotwell "+result)

    def verificarPartidaGanada(self,filas): #Este metodo recorre la matriz
        f = 1
        f2 = int(filas)+1
        verificador = False

        while f < f2:
            inicio : Nodo_Encabezado = self.filas.getEncabezado(f)
            if inicio == None:
                return None
            else:    
                tmp : Nodo_Interno = inicio.getAcceso()
                while tmp != None:

                    #Si encuentra simbolos de naves entonces no se ha terminado la partida
                    if tmp.caracter == "P" or tmp.caracter == "S" or tmp.caracter == "D" or tmp.caracter == "B":
                        verificador = True

                    tmp = tmp.getDerecha()
            f+=1


        if verificador == False: #si no se encontraon simbolos de nava entonces termina la partida
            return "terminado"
        else: return "continuar"
            
    def reestablecer(self,fila,columna):
        
        inicio : Nodo_Encabezado = self.filas.getEncabezado(fila) #Se obtiene la cabecera con la fila
        if inicio == None:
            print('Esa coordenada de fila no existe')
            return "nExist"
            
        tmp : Nodo_Interno = inicio.getAcceso() #Verifica el acceso
        verificador = False
        while tmp != None:

            if tmp.coordenadaX == fila and tmp.coordenadaY == columna: #Ubica el punto
                verificador = True
                #Reestablecemos
                last = self.CarateresDisparados.pop()
                
                tmp.caracter = last
                
                return "OK"


            tmp = tmp.getDerecha()

        if verificador == False:
            print('Coordenada no encontrada')

        return "NAC"    
##############
#pruebas
# matriz = MatrizDispersa(1,10)

# for i in range(1,11):
#     for j in range(1,11):
#         matriz.insert(i,j," ")
# matriz.generarPosicionesAleatorias()

# matriz.insertarMovimiento(1,5)
# matriz.insertarMovimiento(5,5)
# matriz.insertarMovimiento(6,2)
# matriz.insertarMovimiento(7,1)

# matriz.graficarNeato("datos","datos")