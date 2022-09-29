from NodoEncabezado import Nodo_Encabezado
from ListaEncabezado import Lista_Encabezado
import os

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

    def ubicarCoordenada(self,fila, columna): #Se solicita el punto de entrada para iniciar el camino    
      
        inicio : Nodo_Encabezado = self.filas.getEncabezado(fila) #Se obtiene la cabecera con la fila
        if inicio == None:
            print('Esa coordenada de fila no existe')
            return None
            
        tmp : Nodo_Interno = inicio.getAcceso() #Verifica el acceso
        verificador = False
        while tmp != None:
            if tmp.coordenadaX == fila and tmp.coordenadaY == columna: #Ubica el punto

                print("Encontrado: ",tmp.coordenadaX," - ",tmp.coordenadaY)
                verificador = True

            tmp = tmp.getDerecha()

        if verificador == False:
            print('Coordenada no encontrada')

        return None
          
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
                if pivote_celda.caracter == '*':
                    contenido += '\n\tnode[label="*" fillcolor="black" pos="{},-{}!" shape=box]i{}_{};'.format( #pos="{},-{}!"
                        posy_celda, posx, pivote_celda.coordenadaX, pivote_celda.coordenadaY
                    )
                elif pivote_celda.caracter == 'E':
                    contenido += '\n\tnode[label="E" fillcolor="green" pos="{},-{}!" shape=box]i{}_{};'.format( #pos="{},-{}!"
                        posy_celda, posx, pivote_celda.coordenadaX, pivote_celda.coordenadaY
                    )
                elif pivote_celda.caracter == 'C':
                    contenido += '\n\tnode[label="C" fillcolor="blue" pos="{},-{}!" shape=box]i{}_{};'.format( #pos="{},-{}!"
                        posy_celda, posx, pivote_celda.coordenadaX, pivote_celda.coordenadaY
                    )
                elif pivote_celda.caracter == 'R':
                    contenido += '\n\tnode[label="R" fillcolor="gray" pos="{},-{}!" shape=box]i{}_{};'.format( #pos="{},-{}!"
                        posy_celda, posx, pivote_celda.coordenadaX, pivote_celda.coordenadaY
                    )
                elif pivote_celda.caracter == 'U':
                    contenido += '\n\tnode[label="U" fillcolor="red" pos="{},-{}!" shape=box]i{}_{};'.format( #pos="{},-{}!"
                        posy_celda, posx, pivote_celda.coordenadaX, pivote_celda.coordenadaY
                    )
                elif pivote_celda.caracter == 'T':
                    contenido += '\n\tnode[label="T" fillcolor="yellow" pos="{},-{}!" shape=box]i{}_{};'.format( #pos="{},-{}!"
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



################
#pruebas
# matriz = MatrizDispersa(1)

# for i in range(1,11):
#     for j in range(1,11):
#         matriz.insert(i,j," ")

# matriz.graficarNeato("datos","datos")