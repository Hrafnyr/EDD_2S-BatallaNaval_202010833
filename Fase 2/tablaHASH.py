
import os
import json

class tbHash:
    def __init__(self):  
        self.contador = 0

        #Tamaño inicial 13
        self.tabla = []
        self.tamañoInicial()
        
    def tamañoInicial(self):
        for i in range(13):
            self.tabla.append(None)

    def insertar(self,nuevo):
        self.contador+=1
        keyNew = str(nuevo[0])+str(len(nuevo[1]))

        indice = self.getKey(int(keyNew))

        #Verificar si llave existe
        if self.llaveExistente(indice) == True:
            print("hay una colision")
            indice = self.colision(int(keyNew))
        
        self.tabla[indice]=nuevo
        
        #Rehash cuando llegue al  80% de capacidad
        if self.contador/len(self.tabla) > 0.80:
            print("se llego al 80%")
            self.tabla = self.rehash()

    def getKey(self, key): #Key:int -> es la llave del ID concatenado con el nombre (tamaño)
        return key % len(self.tabla)

    #Metodo que verifica si hay una llave en la posicion 
    def llaveExistente(self,indice):
        if self.tabla[indice]==None:
                return False
        return True

    #Metodo para resolver colisiones
    def colision(self,key):
        ContColisiones = 0
        flag = True
        
        while flag == True:
            indice = ((key % 3)+1)*ContColisiones
            
            if self.llaveExistente(indice) == False:
                print("sigue la colision")
                flag = False
            
            ContColisiones+=1    
        print("sin colisiones")
        return indice

    def rehash(self):
        #obtener valor de aumento
        aumento = (self.contador*100)//20
        print(aumento)
        aux = []
        #creamos tablas con la nueva posicion
        for i in range(aumento):
            aux.append(None)
        
        for i in range(len(self.tabla)):
            aux[i]=self.tabla[i]
        
        return aux #retornamos la tabla aumentada

    def verTabla(self):
        for i in range(len(self.tabla)):
            print("Posicion :",i," - Data: ",self.tabla[i])
    
    def getJson(self):
        data = "{ \"data\":["
        for i in range(len(self.tabla)):
            if self.tabla[i]!=None:
                data+="{\"indice\":\""+str(i)+"\",\"id\":\""+self.tabla[i][2]+"\",\"nombre\":\""+self.tabla[i][1]+"\"}"
                
                aux = i + 1
                while aux < len(self.tabla):
                    if self.tabla[aux]==None:
                        pass
                    else:
                        data+=","
                        break
                    aux+=1
                       
        
        data+="]}"
        return data
    
    def getGraph(self):
        cabecera = ""

        cabecera+="digraph G {\n"
        cabecera+="node[shape=box fontsize=12 fillcolor=\"darkseagreen1\" style=\"filled\"];\nlabel=\"Carrito\";\n"

        #Se crea un nodo principal cuya etiqueta sera con estructura HTML para la tabla
        cabecera+="nodo [ label = <\n<table border=\"1\">\n<tr>\n"
        cabecera+="<td align=\"text\" bgcolor=\"#f5fca2\">Indice</td>\n"
        cabecera+="<td align=\"text\" bgcolor=\"#cbffd9\">ID</td>\n"
        cabecera+="<td align=\"text\" bgcolor=\"#a8f2f9\">Nombre</td>\n</tr>"

        #Recorrer la tabla y agregar posiciones que tengan informacion
        for i in range(len(self.tabla)):
            if self.tabla[i]!=None:
                #print("Posicion :",i," - Data: ",self.tabla[i])

                #agregar informacion
                cabecera+="<tr>\n"
                cabecera+="<td align=\"text\" bgcolor=\"#f5fca2\">{}<br align=\"left\"/></td>".format(i)
                cabecera+="<td align=\"text\" bgcolor=\"#cbffd9\">{}<br align=\"left\"/></td>".format(self.tabla[i][2])
                cabecera+="<td align=\"text\" bgcolor=\"#a8f2f9\">{}<br align=\"left\"/></td></tr>".format(self.tabla[i][1])

        #Cerrar tabla y grafo
        cabecera+="\n</table>\n>\n]\n}"

        #--- se genera DOT y se procede a ecjetuar el comando
        dot = "hash.dot"
        archivo = open(dot,'w', encoding='utf-8')
        archivo.write(cabecera)
        archivo.close()

        result = "hash.png"
        os.system("dot -Tpng " + dot + " -o " + result)
        os.system("shotwell "+result)

    def vaciarTabla(self):

        self.contador = 0 #Reseteamos el contador

        #Hacemos que la tabla tenga 13 posiciones
        while len(self.tabla)!=13:
            self.tabla.pop()
        
        #Luego seteamos el contenido nuevamente a None
        for i in range(len(self.tabla)):
            self.tabla[i] = None
        
        #Mostramos para confirmar
        print("-> Vaciando")
    
    def eliminarDato(self,indice):
        auxPrecio = self.tabla[indice][3]
        self.tabla[indice]=None
        self.contador-=1
        return auxPrecio

# #pruebas unitarias
# tb = tbHash()
# tb.insertar(["3","5","p1"])
# tb.insertar(["32","53","p23"])
# tb.verTabla()
# aux = tb.getJson()
# print(aux)


