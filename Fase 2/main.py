
import json
import random
import time
from PyQt5 import QtWidgets, uic, QtGui,QtTest
from PyQt5.QtWidgets import QMessageBox, QInputDialog
from storeC import MainWindow
import os
import sys
import requests
from matriz import MatrizDispersa

#Varibles globales
#Matriz computadora
class mt:
    def __init__(self,capa):
        self.matriz = MatrizDispersa(capa)
        self.NombreJugada = ""
    
    def putSizeT(self,size):
        self.matriz.sizeT = size
    
    def insert(self, f,c,cr):
        self.matriz.insert(f,c,cr)

    def generarPosicionesAleatorias(self):
        self.matriz.generarPosicionesAleatorias()
    
    def graficarNeato(self,n1,n2):
        self.matriz.graficarNeato(n1,n2)
    
    def insertarMovimiento(self,f,c):
        return self.matriz.insertarMovimiento(f,c)
    
    def verificarGanar(self):
        return self.matriz.verificarPartidaGanada(self.matriz.sizeT)
    
    def verificarAciertos(self):
        self.matriz.verificarAciertos()
    
    def reestablecer(self,fila,columna):
        self.matriz.reestablecer(fila,columna)
    
    def eliminar(self): 
        self.matriz.eliminacionPorFilas(self.matriz.sizeT)
        self.matriz.errores = 0
        self.matriz.cantP = 0
        self.matriz.cantS = 0
        self.matriz.cantD = 0
        self.matriz.cantB = 0
        self.matriz.CarateresDisparados.clear()

#Matriz jugador principal
class partidaPrincipal:
    def __init__(self,capa):
        self.matriz = MatrizDispersa(capa)
        self.NombreJugada = ""
        self.turno = False
    
    def putSizeT(self,size):
        self.matriz.sizeT = size
    
    def insert(self, f,c,cr):
        self.matriz.insert(f,c,cr)

    def generarPosicionesAleatorias(self):
        self.matriz.generarPosicionesAleatorias()
    
    def graficarNeato(self,n1,n2):
        self.matriz.graficarNeato(n1,n2)
    
    def insertarMovimiento(self,f,c):
        return self.matriz.insertarMovimiento(f,c)
    
    def verificarGanar(self):
        return self.matriz.verificarPartidaGanada(self.matriz.sizeT)
    
    def verificarAciertos(self):
        self.matriz.verificarAciertos()
    
    def reestablecer(self,fila,columna):
        self.matriz.reestablecer(fila,columna)
    
    def eliminar(self): 
        self.matriz.eliminacionPorFilas(self.matriz.sizeT)
        self.matriz.errores = 0
        self.matriz.cantP = 0
        self.matriz.cantS = 0
        self.matriz.cantD = 0
        self.matriz.cantB = 0
        self.matriz.CarateresDisparados.clear()

class jInvitado: #Clase para la matriz del jugador invitado
    def __init__(self,capa):
        self.matriz = MatrizDispersa(capa)
        self.NombreJugada = ""
        self.turno = False
        self.movimientos = []
    
    def putSizeT(self,size):
        self.matriz.sizeT = size
    
    def insert(self, f,c,cr):
        self.matriz.insert(f,c,cr)

    def generarPosicionesAleatorias(self):
        self.matriz.generarPosicionesAleatorias()
    
    def graficarNeato(self,n1,n2):
        self.matriz.graficarNeato(n1,n2)
    
    def insertarMovimiento(self,f,c):
        return self.matriz.insertarMovimiento(f,c)
    
    def verificarGanar(self):
        return self.matriz.verificarPartidaGanada(self.matriz.sizeT)
    
    def verificarAciertos(self):
        self.matriz.verificarAciertos()
    
    def reestablecer(self,fila,columna):
        self.matriz.reestablecer(fila,columna)
    
    def eliminar(self): 
        self.matriz.eliminacionPorFilas(self.matriz.sizeT)
        self.matriz.errores = 0
        self.matriz.cantP = 0
        self.matriz.cantS = 0
        self.matriz.cantD = 0
        self.matriz.cantB = 0
        self.matriz.CarateresDisparados.clear()
        self.movimientos.clear()

class tutorialM:
    def __init__(self):
        self.matrizTutorial = MatrizDispersa(0)
        self.NombreJugada = "Tutorial"
    
    def putSizeT(self,size):
        self.matrizTutorial.sizeT = size
    
    def insert(self, f,c,cr):
        self.matrizTutorial.insert(f,c,cr)

    def generarPosicionesAleatorias(self):
        self.matrizTutorial.generarPosicionesAleatorias()
    
    def graficarNeato(self,n1,n2):
        self.matrizTutorial.graficarNeato(n1,n2)
    
    def insertarMovimiento(self,f,c):
        return self.matrizTutorial.insertarMovimiento(f,c)
    
    def verificarGanar(self):
        return self.matrizTutorial.verificarPartidaGanada(self.matriz.sizeT)
    
    def verificarAciertos(self):
        self.matrizTutorial.verificarAciertos()
    
    def reestablecer(self,fila,columna):
        self.matrizTutorial.reestablecer(fila,columna)
    
    def eliminar(self): 
        self.matrizTutorial.eliminacionPorFilas(self.matrizTutorial.sizeT)
        self.matrizTutorial.errores = 0
        self.matrizTutorial.cantP = 0
        self.matrizTutorial.cantS = 0
        self.matrizTutorial.cantD = 0
        self.matrizTutorial.cantB = 0
        self.matrizTutorial.CarateresDisparados.clear()

nameUser = ""
passUser = ""
url_Api = "http://0.0.0.0:8080"
matriz = mt(3)
invitado = jInvitado(2)
jugadorP = partidaPrincipal(1)
tutorialMatriz = tutorialM ()
tipoJuego = ""

#iniciar app
app = QtWidgets.QApplication(sys.argv)

#cargar archivos ui localizados en el directorio actual
loginV = uic.loadUi(os.path.dirname(os.path.abspath(__file__))+"/login.ui")
nuevoV = uic.loadUi(os.path.dirname(os.path.abspath(__file__))+"/nuevaCuenta.ui")
userV = uic.loadUi(os.path.dirname(os.path.abspath(__file__))+"/jugadorV.ui")
editarV = uic.loadUi(os.path.dirname(os.path.abspath(__file__))+"/panelEditar.ui")
adminV = uic.loadUi(os.path.dirname(os.path.abspath(__file__))+"/admin.ui")
tutoV = uic.loadUi(os.path.dirname(os.path.abspath(__file__))+"/tutorial.ui")
tiendaV = MainWindow()
invitadoV = uic.loadUi(os.path.dirname(os.path.abspath(__file__))+"/userInvitado.ui")

#Funciones
def loginAction():
    nameUser = loginV.lineEdit.text()
    passUser = loginV.lineEdit_2.text()

    if len(nameUser)==0 or len(passUser)==0:
        if len(nameUser)==0:
            loginV.label_4.setText("Debe ingresar su nombre")
        elif len(passUser)==0:
            loginV.label_5.setText("Debe ingresar su contraseña")            
    else:
        loginV.label_4.setText("")
        loginV.label_5.setText("")
        #Verificar si es el admin
        if nameUser=="EDD" and passUser=="edd123":
            loginV.hide()
            adminV.show()
        else: 
            obj={'nombre':'{}'.format(nameUser),'pass':'{}'.format(passUser)}
            res = requests.post(f'{url_Api}/Login',json=obj)

            #Verificar respuesta
            jsonResponse = res.json()
            
            if jsonResponse["Message"]=="error":
                QMessageBox.about(loginV,"Alerta","Datos incorrectos")
            else:
                verUsuario(nameUser,passUser)

def eliminarCuenta():
    nameUser = userV.txtUS.text()
    passUser= userV.label_2.text()
    buttonReply = QMessageBox.question(userV, 'Alerta', "¿Desea eliminar su cuenta?", QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
    if buttonReply == QMessageBox.Yes:
        obj={'nombre':'{}'.format(nameUser),'pass':'{}'.format(passUser)}
        res = requests.post(f'{url_Api}/removeUser',json=obj)

        #Verificar respuesta
        jsonResponse = res.json()
        
        if jsonResponse["Message"]=="error":
            QMessageBox.about(loginV,"Alerta","Hubo un error")
        else:
            nameUser = ""
            passUser = ""
            loginV.lineEdit.setText("")
            loginV.lineEdit_2.setText("")
            userV.hide()
            loginV.show()

    else:
        print('No clicked.')

def verUsuario(nameU,passR):
    loginV.hide()
    
    #ocultar menu de juego
    userV.labelF.hide()
    userV.labelC.hide()
    userV.txtFila.hide()
    userV.txtColumna.hide()
    userV.labelWarning.hide()
    userV.btnShoot.hide()

    userV.labelWR.hide()
    userV.btnDeshacer.hide()
    userV.btnAbandonar.hide()

    userV.labelMon.hide()
    userV.labelMON.hide()
    userV.labelV.hide()
    userV.labelVidas.hide()

    userV.label_2.hide()
    userV.label_2.setText(passR)
    userV.txtUS.setText(nameU)
    userV.show()

def nuevaCuenta():
    loginV.hide()
    nuevoV.show()

def getDatosNuevaCuenta():
    newName = nuevoV.lineEdit.text()
    newPass = nuevoV.lineEdit_2.text()
    newEdad = nuevoV.lineEdit_3.text()

    if len(newName)==0 or len(newPass)==0 or len(newEdad)==0:
        if len(newName)==0:
            nuevoV.label_4.setText("Debe ingresar su nombre")
        elif len(newPass)==0:
            nuevoV.label_5.setText("Debe ingresar su contraseña")
        elif len(newEdad)==0:
            nuevoV.label_7.setText("Debe ingresar su edad")

    elif newEdad.isalpha():
            nuevoV.label_7.setText("Debe ingresar un valor numérico")            
    else:
        nuevoV.label_4.setText("")
        nuevoV.label_5.setText("")
        nuevoV.label_7.setText("")

        obj={'nombre':'{}'.format(newName),'pass':'{}'.format(newPass),'edad':'{}'.format(newEdad),'monedas':'0'}
        res = requests.post(f'{url_Api}/newUser',json=obj)

        #Verificar respuesta
        jsonResponse = res.json()
        
        if jsonResponse["Message"]=="error":
            QMessageBox.about(loginV,"Alerta","El nombre ya existe")
        else:
            QMessageBox.about(nuevoV,"Mensaje","Cuenta creada correctamente")
            volverLogin()

def updateData():
    nameUser = userV.txtUS.text()
    passUser= userV.label_2.text()
    newName = editarV.lineEdit.text()
    newPass = editarV.lineEdit_2.text()
    newEdad = editarV.lineEdit_3.text()

    if newEdad.isalpha():
            nuevoV.label_7.setText("Debe ingresar un valor numérico")            
    else:
        editarV.label_4.setText("")
        editarV.label_5.setText("")
        editarV.label_7.setText("")

        obj={'nName':'{}'.format(newName),'nPass':'{}'.format(newPass),'nEdad':'{}'.format(newEdad),'nombre':'{}'.format(nameUser),'password':'{}'.format(passUser)}
        res = requests.post(f'{url_Api}/updateUser',json=obj)

        #Verificar respuesta
        jsonResponse = res.json()
        
        if jsonResponse["Message"]=="error":
            QMessageBox.about(editarV,"Alerta","El nombre ya existe")
        else:
            if len(newName)!=0:
                userV.txtUS.setText(newName)
            if len(newPass)!=0:
                userV.label_2.setText(newPass)
            QMessageBox.about(editarV,"Mensaje","Informacion actualizada correctamente")        

def volverEditar():
    editarV.lineEdit.setText("")
    editarV.lineEdit_2.setText("")
    editarV.lineEdit_3.setText("")
    editarV.hide()
    userV.show()

def editarDatos():
    editarV.show()

def volverLogin():
    nuevoV.lineEdit.setText("")
    nuevoV.lineEdit_2.setText("")
    nuevoV.lineEdit_3.setText("")
    loginV.lineEdit.setText("")
    loginV.lineEdit_2.setText("")
    nuevoV.hide()
    loginV.show()

def logOut():
    buttonReply = QMessageBox.question(userV, 'Alerta', "¿Salir?", QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
    if buttonReply == QMessageBox.Yes:
        loginV.lineEdit.setText("")
        loginV.lineEdit_2.setText("")
        nameUser = ""
        passUser = ""
        userV.hide()
        loginV.show()

    else:
        print('No clicked.')

def logOutAdmin():
    buttonReply = QMessageBox.question(adminV, 'Alerta', "¿Salir?", QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
    if buttonReply == QMessageBox.Yes:
        loginV.lineEdit.setText("")
        loginV.lineEdit_2.setText("")
        adminV.hide()
        loginV.show()

    else:
        print('No clicked.')

def allUsuarios():
    requests.post(f'{url_Api}/AllUsers')

def cargaMasiva():
    #global storeV
    res = requests.post(f'{url_Api}/carga')
    pt = res.json()
    #storeV = MainWindow(pt)
    tiendaV.fillTable(pt)
    QMessageBox.about(adminV,"Mensaje","Carga masiva realizada")

def irTienda():
    monedas = getCoins()
    tiendaV.labelMC.setText(monedas)
    tiendaV.show()

def backtienda():
    tiendaV.txtCategoria.setText("")
    tiendaV.txtID.setText("")
    tiendaV.hide()

def salir():
    exit()

def comprar():
    nameUser = userV.txtUS.text()
    passUser= userV.label_2.text()
    categ = tiendaV.txtCategoria.text()
    idAr = tiendaV.txtID.text()
    

    if (len(categ)==0 or len(idAr)==0):
        tiendaV.labelWarning.setText("Debe llenar ambos campos")
    else:
        tiendaV.labelWarning.setText("")
        
        obj={'id':'{}'.format(idAr),'categoria':'{}'.format(categ),'nombre':'{}'.format(nameUser),'password':'{}'.format(passUser)}
        res = requests.post(f'{url_Api}/compra',json=obj)

        #Verificar respuesta
        jsonResponse = res.json()
        
        if jsonResponse["Message"]=="error": QMessageBox.about(tiendaV,"Alerta","Hubo un error")
        elif jsonResponse["Message"]=="NEC": QMessageBox.about(tiendaV,"Alerta","No tiene dinero suficiente")
        elif jsonResponse["Message"]=="errorID": QMessageBox.about(tiendaV,"Alerta","No se encuentra el ID")
        elif jsonResponse["Message"]=="errorCate": QMessageBox.about(tiendaV,"Alerta","No existe la categoria")
        else:
            QMessageBox.about(tiendaV,"Mensaje","compra realizada")
            tiendaV.txtCategoria.setText("")
            tiendaV.txtID.setText("")   
            monedas = getCoins()
            tiendaV.labelMC.setText(monedas)

def verCompras():
    nameUser = userV.txtUS.text()
    passUser= userV.label_2.text()
          
    obj={'nombre':'{}'.format(nameUser),'pass':'{}'.format(passUser)}
    res = requests.post(f'{url_Api}/verAVL',json=obj)

    #Verificar respuesta
    jsonResponse = res.json()
    
    if jsonResponse["Message"]=="error":
        QMessageBox.about(tiendaV,"Alerta","Hubo un error")

def getCoins():
    nameUser = userV.txtUS.text()
    passUser= userV.label_2.text()

    obj={'nombre':'{}'.format(nameUser),'pass':'{}'.format(passUser)}
    res = requests.post(f'{url_Api}/getCoins',json=obj)

    #Verificar respuesta
    jsonResponse = res.json()
    
    return jsonResponse["Coins"]

def setCoins(cant):
    nameUser = userV.txtUS.text()
    passUser= userV.label_2.text()
    

    obj={'nombre':'{}'.format(nameUser),'pass':'{}'.format(passUser),'cant':'{}'.format(cant)}
    requests.post(f'{url_Api}/setCoins',json=obj)

#JUGAR

def generarTurno():
    t = random.randint(1,2)
    return t

def prueba():
    size,ok = QInputDialog.getText(userV,"Tamaño del tablero","Ingrese el tamaño del tablero (10 minimo)")
    
    if ok:

        if int(str(size))<10:
            QMessageBox.about(userV,"Alerta","Debe ingresar un valor mayor o igual a 10")
        else:
            #Preguntamos la modalidad
            box = QMessageBox()
            box.setIcon(QMessageBox.Question)
            box.setWindowTitle('Tipo de juego')
            box.setText('Elija una opcion')
            box.setStandardButtons(QMessageBox.Yes|QMessageBox.No)
            buttonY = box.button(QMessageBox.Yes)
            buttonY.setText('1 jugador')
            buttonN = box.button(QMessageBox.No)
            buttonN.setText('1 VS 1')
            box.exec_()

            if box.clickedButton() == buttonY: #1 jugador
                global tipoJuego
                tipoJuego = "1"
                name2,ok2 = QInputDialog.getText(userV,"Nombre de la jugada","Ingrese el nombre de la jugada")
                if ok2:

                    #Guardamos la jugada
                    nameUser = userV.txtUS.text()
                    passUser= userV.label_2.text()

                    matriz.NombreJugada=name2 #Se guarda en la clase para acceder desde cualquier parte
                
                    obj={'nombre':'{}'.format(nameUser),'pass':'{}'.format(passUser),'jugada':'{}'.format(str(name2))}
                    res = requests.post(f'{url_Api}/newJugada',json=obj)

                    #Verificar respuesta
                    jsonResponse = res.json()
                    if jsonResponse["Message"]!="OK":
                        QMessageBox.about(userV,"Alerta","Hubo un error")

                    #mostar componentes 
                    userV.labelF.show()
                    userV.labelC.show()
                    userV.txtFila.show()
                    userV.txtColumna.show()
                    userV.btnShoot.show()
                    userV.btnDeshacer.show()
                    userV.labelMon.show()
                    monedas = getCoins()
                    userV.labelMON.setText(monedas)
                    userV.labelMON.show()
                    userV.labelV.show()
                    userV.labelVidas.show()
                    userV.btnAbandonar.show()

                    #generar matriz y mostrar tablero
                    generarMatriz1(int(str(size)))
                    getImage()
                else:
                    print("canceled")        

            #Si es de 2 jugadores creamos el tablero 1 y 2
            if box.clickedButton() == buttonN:
                tipoJuego = "2"

                
                name2,ok2 = QInputDialog.getText(userV,"Nombre de la jugada","Ingrese el nombre de la jugada")
                if ok2:

                    #Guardamos la jugada
                    nameUser = userV.txtUS.text()
                    passUser= userV.label_2.text()

                    jugadorP.NombreJugada=name2 #Se guarda en la clase para acceder desde cualquier parte
                    invitado.NombreJugada=name2

                    obj={'nombre':'{}'.format(nameUser),'pass':'{}'.format(passUser),'jugada':'{}'.format(str(name2))}
                    res = requests.post(f'{url_Api}/newJugada',json=obj)

                    #Verificar respuesta
                    jsonResponse = res.json()
                    if jsonResponse["Message"]!="OK":
                        QMessageBox.about(userV,"Alerta","Hubo un error")

                    #mostar componentes 
                    userV.labelF.show()
                    userV.labelC.show()
                    userV.txtFila.show()
                    userV.txtColumna.show()
                    userV.btnShoot.show()
                    userV.btnDeshacer.show()
                    userV.labelMon.show()
                    monedas = getCoins()
                    userV.labelMON.setText(monedas)
                    userV.labelMON.show()
                    userV.labelV.show()
                    userV.labelVidas.show()
                    userV.btnAbandonar.show()

                    #generar matriz y mostrar tablero
                    generarMatrizPrincipal(int(str(size)))
                    getImage()
                    elegirPosiciones(int(str(size)))

                    generarMatrizInvitado(int(str(size)))
                    getImageInvitado()
                    invitadoV.show()  

                    #decidir turno inicial
                    turnoI = generarTurno()

                    if turnoI == 1: 
                        jugadorP.turno=True #Si es true puede lanzar
                        QMessageBox.about(userV,"Mensaje","Inicia el primer tiro")
                    else:           
                        invitado.turno=True
                        QMessageBox.about(invitadoV,"Mensaje","Inicia el primer tiro")

                else:
                    print("canceled")        
               
    else:
        print("canceled")

def generarMatriz1(size):
    matriz.putSizeT(size)    
    for i in range(1,size+1):
        for j in range(1,size+1):
            matriz.insert(i,j," ")
    matriz.generarPosicionesAleatorias()
    matriz.graficarNeato("Partida",matriz.NombreJugada)

def generarMatrizPrincipal(size):
    jugadorP.putSizeT(size)    
    for i in range(1,size+1):
        for j in range(1,size+1):
            jugadorP.insert(i,j," ")
    jugadorP.graficarNeato("Partida",jugadorP.NombreJugada)

def generarMatrizInvitado(size):
    invitado.putSizeT(size)    
    for i in range(1,size+1):
        for j in range(1,size+1):
            invitado.insert(i,j," ")
    invitado.generarPosicionesAleatorias()
    invitado.graficarNeato("Invitado",invitado.NombreJugada)

def getImage():
    userV.label_3.setPixmap(QtGui.QPixmap("matriz_Partida.png"))

def getImageInvitado():
    invitadoV.label_3.setPixmap(QtGui.QPixmap("matriz_Invitado.png"))

def getImageBack():
    #ocultar menu de juego
    userV.labelF.hide()
    userV.labelC.hide()
    userV.txtFila.hide()
    userV.txtColumna.hide()
    userV.labelWarning.hide()
    userV.btnShoot.hide()

    userV.labelWR.hide()
    userV.btnDeshacer.hide()
    userV.btnAbandonar.hide()

    userV.labelMon.hide()
    userV.labelMON.hide()
    userV.labelV.hide()
    userV.labelVidas.setText("3")
    userV.labelVidas.hide()

    #mostrar barco de fondo
    userV.label_3.setPixmap(QtGui.QPixmap("imagenBarco.jpg"))

def makeMove():
    if tipoJuego == "1":
        fila = userV.txtFila.text()
        columna = userV.txtColumna.text()

        vidas = int(userV.labelVidas.text())
        
        if fila.isalpha() or columna.isalpha():
            userV.labelWarning.setText("Ingrese valores numericos")
            userV.labelWarning.show()
        elif len(fila)==0 or len(columna)==0:
            userV.labelWarning.setText("Debe llenar ambos campos")
            userV.labelWarning.show()
        else:
            userV.labelWarning.setText(" ")
            response = matriz.insertarMovimiento(int(fila),int(columna))
            
            #obtenemos datos del usuario
            nameUser = userV.txtUS.text()
            passUser= userV.label_2.text()

            #Guardamos el movimiento en la cola
            obj={'nombre':'{}'.format(nameUser),'pass':'{}'.format(passUser),'jugada':'{}'.format(matriz.NombreJugada),'x':'{}'.format(fila),'y':'{}'.format(columna)}
            resC = requests.post(f'{url_Api}/newMov',json=obj)

            #Verificar respuesta
            jsonResponse = resC.json()
            if jsonResponse["Message"]!="OK":
                QMessageBox.about(userV,"Alerta","Hubo un error")

            if response == "nExist":  
                userV.labelWarning.setText("No existe la fila")
                userV.labelWarning.show()

            elif response == "Disparo":
                setCoins("20")
                monedas = getCoins()

                userV.labelMON.setText(monedas)
                userV.labelWarning.setText("")
                userV.label
                QMessageBox.about(userV,"Felicidades","Disparo correcto, ganas 20 tokens")
                matriz.graficarNeato("Partida",matriz.NombreJugada)
                getImage()

            elif response == "Fallo":

                userV.labelWarning.setText("")
                QMessageBox.about(userV,"¡Oh no!","Ha fallado el disparo, pierde una vida")

                #pierde una vida
                vidas-=1
                userV.labelVidas.setText(str(vidas))

                matriz.graficarNeato("Partida",matriz.NombreJugada)
                getImage()

            elif response == "NAC":
                userV.labelWarning.show()
                userV.labelWarning.setText("No se encuentra")

        #Verificamos si quedan vidas
        if vidas == 0:
            QMessageBox.about(userV,"¡Oh no!","Has Perdido la partida")

            #Mostramos sus resultados
            matriz.verificarAciertos()
            mensaje = " "
            mensaje += "Errores: {}\n\n".format(matriz.matriz.errores)
            mensaje += "Barcos destruidos: \nPortaviones: {}\n\nSubmarinos: {}\n\nDestructores: {}\n\nBuques: {}".format(matriz.matriz.cantP,matriz.matriz.cantS,matriz.matriz.cantD,matriz.matriz.cantB)
            QMessageBox.about(userV,"Resultados",mensaje)


            #preguntamos
            terminate = QMessageBox.question(userV, 'Mensaje', "¿Volver a jugar con la configuracion actual?", QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
            if terminate == QMessageBox.Yes:
                name2,ok2 = QInputDialog.getText(userV,"Nombre de la jugada","Ingrese el nombre de la jugada")
                if ok2:

                    #Guardamos la jugada
                    nameUser = userV.txtUS.text()
                    passUser= userV.label_2.text()

                    matriz.NombreJugada=name2 #Se guarda en la clase para acceder desde cualquier parte

                    obj={'nombre':'{}'.format(nameUser),'pass':'{}'.format(passUser),'jugada':'{}'.format(str(name2))}
                    res = requests.post(f'{url_Api}/newJugada',json=obj)

                    #Verificar respuesta
                    jsonResponse = res.json()
                    if jsonResponse["Message"]!="OK":
                        QMessageBox.about(userV,"Alerta","Hubo un error")

                    aux = matriz.matriz.sizeT

                    #resetear
                    resetGame()
                    monedas = getCoins()
                    userV.labelMON.setText(monedas)
                    userV.labelVidas.setText("3")
                    invitadoV.labelVidas.setText("3")

                    #generar matriz y mostrar tablero
                    matriz.putSizeT(aux)
                    generarMatriz1(int(str(aux)))
                    getImage()

            else:
                getImageBack()
                resetGame()
                userV.labelVidas.setText("3")
                invitadoV.labelVidas.setText("3")

        #verificamos si ha ganado
        partida = matriz.verificarGanar()
        if partida == "terminado":
            QMessageBox.about(userV,"¡Felicidades!","Has Ganado la partida")

            #Mostramos sus resultados
            matriz.verificarAciertos()
            mensaje = " "
            mensaje += "Errores: {}\n\n".format(matriz.matriz.errores)
            mensaje += "Barcos destruidos: \nPortaviones: {}\n\nSubmarinos: {}\n\nDestructores: {}\n\nBuques: {}".format(matriz.matriz.cantP,matriz.matriz.cantS,matriz.matriz.cantD,matriz.matriz.cantB)
            QMessageBox.about(userV,"Resultados",mensaje)
            
            #preguntamos
            terminate = QMessageBox.question(userV, 'Mensaje', "¿Volver a jugar con la configuracion actual?", QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
            if terminate == QMessageBox.Yes:
                name2,ok2 = QInputDialog.getText(userV,"Nombre de la jugada","Ingrese el nombre de la jugada")
                if ok2:

                    #Guardamos la jugada
                    nameUser = userV.txtUS.text()
                    passUser= userV.label_2.text()

                    matriz.NombreJugada=name2 #Se guarda en la clase para acceder desde cualquier parte

                    obj={'nombre':'{}'.format(nameUser),'pass':'{}'.format(passUser),'jugada':'{}'.format(str(name2))}
                    res = requests.post(f'{url_Api}/newJugada',json=obj)

                    #Verificar respuesta
                    jsonResponse = res.json()
                    if jsonResponse["Message"]!="OK":
                        QMessageBox.about(userV,"Alerta","Hubo un error")

                    aux = matriz.matriz.sizeT

                    #resetear
                    resetGame()
                    monedas = getCoins()
                    userV.labelMON.setText(monedas)
                    userV.labelVidas.setText("3")
                    invitadoV.labelVidas.setText("3")
                    #generar matriz y mostrar tablero
                    matriz.putSizeT(aux)
                    generarMatriz1(int(str(aux)))
                    getImage()

            else:
                getImageBack()
                resetGame()
                userV.labelVidas.setText("3")
                invitadoV.labelVidas.setText("3")

    elif tipoJuego=="2":
        if jugadorP.turno==True:
            fila = userV.txtFila.text()
            columna = userV.txtColumna.text()

            vidas = int(userV.labelVidas.text())
        
            if fila.isalpha() or columna.isalpha():
                userV.labelWarning.setText("Ingrese valores numericos")
                userV.labelWarning.show()
            elif len(fila)==0 or len(columna)==0:
                userV.labelWarning.setText("Debe llenar ambos campos")
                userV.labelWarning.show()
            else:
                userV.labelWarning.setText(" ")
                response = invitado.insertarMovimiento(int(fila),int(columna))
                
                #obtenemos datos del usuario
                nameUser = userV.txtUS.text()
                passUser= userV.label_2.text()

                #Guardamos el movimiento en la cola
                obj={'nombre':'{}'.format(nameUser),'pass':'{}'.format(passUser),'jugada':'{}'.format(jugadorP.NombreJugada),'x':'{}'.format(fila),'y':'{}'.format(columna)}
                resC = requests.post(f'{url_Api}/newMov',json=obj)

                #Verificar respuesta
                jsonResponse = resC.json()
                if jsonResponse["Message"]!="OK":
                    QMessageBox.about(userV,"Alerta","Hubo un error")

                if response == "nExist":  
                    userV.labelWarning.setText("No existe la fila")
                    userV.labelWarning.show()

                elif response == "Disparo":
                    invitado.turno=True
                    jugadorP.turno=False
                    setCoins("20")
                    monedas = getCoins()

                    userV.labelMON.setText(monedas)
                    userV.labelWarning.setText("")
                    userV.label
                    QMessageBox.about(userV,"Felicidades","Disparo correcto, ganas 20 tokens")
                    invitado.graficarNeato("Invitado",invitado.NombreJugada)
                    getImageInvitado()

                elif response == "Fallo":
                    invitado.turno=True
                    jugadorP.turno=False
                    userV.labelWarning.setText("")
                    QMessageBox.about(userV,"¡Oh no!","Ha fallado el disparo, pierde una vida")

                    #pierde una vida
                    vidas-=1
                    userV.labelVidas.setText(str(vidas))

                    invitado.graficarNeato("Invitado",invitado.NombreJugada)
                    getImageInvitado()

                elif response == "NAC":
                    userV.labelWarning.show()
                    userV.labelWarning.setText("No se encuentra")

            #Verificamos si quedan vidas
            if vidas == 0:
                QMessageBox.about(userV,"¡Oh no!","Has Perdido la partida")

                #Mostramos resultados del invitado
                jugadorP.verificarAciertos()
                mensaje = " "
                mensaje += "Errores: {}\n\n".format(jugadorP.matriz.errores)
                mensaje += "Barcos destruidos: \nPortaviones: {}\n\nSubmarinos: {}\n\nDestructores: {}\n\nBuques: {}".format(jugadorP.matriz.cantP,jugadorP.matriz.cantS,jugadorP.matriz.cantD,jugadorP.matriz.cantB)
                QMessageBox.about(invitadoV,"Resultados",mensaje)

                #Mostramos resultados del jugador
                invitado.verificarAciertos()
                mensaje = " "
                mensaje += "Errores: {}\n\n".format(invitado.matriz.errores)
                mensaje += "Barcos destruidos: \nPortaviones: {}\n\nSubmarinos: {}\n\nDestructores: {}\n\nBuques: {}".format(invitado.matriz.cantP,invitado.matriz.cantS,invitado.matriz.cantD,invitado.matriz.cantB)
                QMessageBox.about(userV,"Resultados",mensaje)

                #Preguntamos si quiere lista o el grafo
                box = QMessageBox()
                box.setIcon(QMessageBox.Question)
                box.setWindowTitle('Ver imagen')
                box.setText('Elija una opcion')
                box.setStandardButtons(QMessageBox.Yes|QMessageBox.No)
                buttonY = box.button(QMessageBox.Yes)
                buttonY.setText('Lista Adyacencia')
                buttonN = box.button(QMessageBox.No)
                buttonN.setText('Grafo Adyacencia')
                box.exec_()

                if box.clickedButton() == buttonY: invitado.matriz.verListaAdyacencia()
                if box.clickedButton() == buttonN: invitado.matriz.grafoAdyacencia()

                #preguntamos al jugador principal
                terminate = QMessageBox.question(userV, 'Mensaje', "¿Volver a jugar con la configuracion actual?", QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
                if terminate == QMessageBox.Yes:
                    name2,ok2 = QInputDialog.getText(userV,"Nombre de la jugada","Ingrese el nombre de la jugada")
                    if ok2:

                        #Guardamos la jugada
                        nameUser = userV.txtUS.text()
                        passUser= userV.label_2.text()

                        jugadorP.NombreJugada=name2 #Se guarda en la clase para acceder desde cualquier parte
                        invitado.NombreJugada=name2

                        obj={'nombre':'{}'.format(nameUser),'pass':'{}'.format(passUser),'jugada':'{}'.format(str(name2))}
                        res = requests.post(f'{url_Api}/newJugada',json=obj)

                        #Verificar respuesta
                        jsonResponse = res.json()
                        if jsonResponse["Message"]!="OK":
                            QMessageBox.about(userV,"Alerta","Hubo un error")

                        aux = jugadorP.matriz.sizeT

                        #resetear
                        resetGameJ1()
                        resetGameJ2()
                        monedas = getCoins()
                        userV.labelMON.setText(monedas)
                        userV.labelVidas.setText("3")
                        invitadoV.labelVidas.setText("3")
                        #generar matriz y mostrar tablero
                        jugadorP.putSizeT(aux)
                        invitado.putSizeT(aux)
                        generarMatrizPrincipal(int(str(aux)))
                        generarMatrizInvitado(int(str(aux)))
                        getImage()
                        getImageInvitado()

                else:
                    invitadoV.hide()
                    getImageBack()
                    resetGameJ2()
                    resetGameJ1()

            #verificamos si ha ganado
            partida = invitado.verificarGanar()
            if partida == "terminado":
                QMessageBox.about(userV,"¡Felicidades!","Has Ganado la partida")

                #Mostramos resultados del invitado
                jugadorP.verificarAciertos()
                mensaje = " "
                mensaje += "Errores: {}\n\n".format(jugadorP.matriz.errores)
                mensaje += "Barcos destruidos: \nPortaviones: {}\n\nSubmarinos: {}\n\nDestructores: {}\n\nBuques: {}".format(jugadorP.matriz.cantP,jugadorP.matriz.cantS,jugadorP.matriz.cantD,jugadorP.matriz.cantB)
                QMessageBox.about(invitadoV,"Resultados",mensaje)

                #Mostramos resultados del jugador
                invitado.verificarAciertos()
                mensaje = " "
                mensaje += "Errores: {}\n\n".format(invitado.matriz.errores)
                mensaje += "Barcos destruidos: \nPortaviones: {}\n\nSubmarinos: {}\n\nDestructores: {}\n\nBuques: {}".format(invitado.matriz.cantP,invitado.matriz.cantS,invitado.matriz.cantD,invitado.matriz.cantB)
                QMessageBox.about(userV,"Resultados",mensaje)

                #Preguntamos si quiere lista o el grafo
                box = QMessageBox()
                box.setIcon(QMessageBox.Question)
                box.setWindowTitle('Ver imagen')
                box.setText('Elija una opcion')
                box.setStandardButtons(QMessageBox.Yes|QMessageBox.No)
                buttonY = box.button(QMessageBox.Yes)
                buttonY.setText('Lista Adyacencia')
                buttonN = box.button(QMessageBox.No)
                buttonN.setText('Grafo Adyacencia')
                box.exec_()

                if box.clickedButton() == buttonY: invitado.matriz.verListaAdyacencia()
                if box.clickedButton() == buttonN: invitado.matriz.grafoAdyacencia()

                #preguntamos al jugador principal
                terminate = QMessageBox.question(userV, 'Mensaje', "¿Volver a jugar con la configuracion actual?", QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
                if terminate == QMessageBox.Yes:
                    name2,ok2 = QInputDialog.getText(userV,"Nombre de la jugada","Ingrese el nombre de la jugada")
                    if ok2:

                        #Guardamos la jugada
                        nameUser = userV.txtUS.text()
                        passUser= userV.label_2.text()

                        jugadorP.NombreJugada=name2 #Se guarda en la clase para acceder desde cualquier parte
                        invitado.NombreJugada=name2

                        obj={'nombre':'{}'.format(nameUser),'pass':'{}'.format(passUser),'jugada':'{}'.format(str(name2))}
                        res = requests.post(f'{url_Api}/newJugada',json=obj)

                        #Verificar respuesta
                        jsonResponse = res.json()
                        if jsonResponse["Message"]!="OK":
                            QMessageBox.about(userV,"Alerta","Hubo un error")

                        aux = jugadorP.matriz.sizeT

                        #resetear
                        resetGameJ1()
                        resetGameJ2()
                        monedas = getCoins()
                        userV.labelMON.setText(monedas)
                        userV.labelVidas.setText("3")
                        invitadoV.labelVidas.setText("3")
                        #generar matriz y mostrar tablero
                        jugadorP.putSizeT(aux)
                        invitado.putSizeT(aux)
                        generarMatrizPrincipal(int(str(aux)))
                        generarMatrizInvitado(int(str(aux)))
                        getImage()
                        getImageInvitado()

                else:
                    invitadoV.hide()
                    getImageBack()
                    resetGameJ2()
                    resetGameJ1()
        else:
            QMessageBox.about(userV,"Mensaje","Todavia no es su turno")

def deshacer():
    if tipoJuego=="1":
        #obtenemos datos del usuario
        nameUser = userV.txtUS.text()
        passUser= userV.label_2.text()

        #Validamos que pueda retroceder
        obj={'nombre':'{}'.format(nameUser),'password':'{}'.format(passUser)}
        res = requests.post(f'{url_Api}/restarMP',json=obj)

        #Verificar respuesta
        jsonResponse = res.json()
        
        if jsonResponse["Message"]=="NEC":
            userV.labelWR.setText("No tienes monedas suficientes")
            userV.labelWR.show()
        else:
            monedas = getCoins()
            userV.labelMON.setText(monedas)
            userV.labelWR.setText("")

            #Guardamos el movimiento en la cola
            obj={'nombre':'{}'.format(nameUser),'pass':'{}'.format(passUser),'jugada':'{}'.format(matriz.NombreJugada)}
            resC = requests.post(f'{url_Api}/lastMove',json=obj)

            #Verificar respuesta
            jsonResponse = resC.json()
            print(jsonResponse)
            #Validar si hay datos en pila para evitar error
            if jsonResponse["X"]!="NA" and jsonResponse["Y"]!="NA":
                userV.labelWR.hide()

                #Reestablecemos tablero
                matriz.reestablecer(int(jsonResponse["X"]),int(jsonResponse["Y"]))
                print("cargando...")
                #Repintamos y mostramos
                matriz.graficarNeato("Partida",matriz.NombreJugada)
                getImage()

                #Eliminamos de la pila
                res2 = requests.post(f'{url_Api}/eliminarLastMove',json=obj)
            
                #Verificar respuesta
                respuesta = res2.json()
                if respuesta["Message"]!="OK":
                    QMessageBox.about(userV,"Alerta","Hubo un error")
            else:
                userV.labelWR.setText("No hay movimientos")
                userV.labelWR.show()
    
    elif tipoJuego=="2":
        #obtenemos datos del usuario
        nameUser = userV.txtUS.text()
        passUser= userV.label_2.text()

        #Validamos que pueda retroceder
        obj={'nombre':'{}'.format(nameUser),'password':'{}'.format(passUser)}
        res = requests.post(f'{url_Api}/restarMP',json=obj)

        #Verificar respuesta
        jsonResponse = res.json()
        
        if jsonResponse["Message"]=="NEC":
            userV.labelWR.setText("No tienes monedas suficientes")
            userV.labelWR.show()
        else:
            monedas = getCoins()
            userV.labelMON.setText(monedas)
            userV.labelWR.setText("")

            #Guardamos el movimiento en la cola
            obj={'nombre':'{}'.format(nameUser),'pass':'{}'.format(passUser),'jugada':'{}'.format(jugadorP.NombreJugada)}
            resC = requests.post(f'{url_Api}/lastMove',json=obj)

            #Verificar respuesta
            jsonResponse = resC.json()
            print(jsonResponse)
            #Validar si hay datos en pila para evitar error
            if jsonResponse["X"]!="NA" and jsonResponse["Y"]!="NA":
                userV.labelWR.hide()

                #Reestablecemos tablero
                invitado.reestablecer(int(jsonResponse["X"]),int(jsonResponse["Y"]))
                print("cargando...")
                #Repintamos y mostramos
                invitado.graficarNeato("Invitado",jugadorP.NombreJugada)
                getImageInvitado()

                #Eliminamos de la pila
                res2 = requests.post(f'{url_Api}/eliminarLastMove',json=obj)
            
                #Verificar respuesta
                respuesta = res2.json()
                if respuesta["Message"]!="OK":
                    QMessageBox.about(userV,"Alerta","Hubo un error")
            else:
                userV.labelWR.setText("No hay movimientos")
                userV.labelWR.show()

def abandonar():
    if tipoJuego=="1":
        buttonReply = QMessageBox.question(userV, 'Alerta', "¿Abandonar? Costo: 20 tokens", QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
        if buttonReply == QMessageBox.Yes:
            
            #obtenemos datos del usuario
            nameUser = userV.txtUS.text()
            passUser= userV.label_2.text()

            #Validamos que pueda abandonar
            obj={'nombre':'{}'.format(nameUser),'password':'{}'.format(passUser)}
            res = requests.post(f'{url_Api}/Abandonar',json=obj)

            #Verificar respuesta
            jsonResponse = res.json()
            
            if jsonResponse["Message"]=="NEC":
                QMessageBox.about(userV,"Alerta","No tiene monedas suficientes")
            else:
                
                getImageBack()
                resetGame()
                userV.labelVidas.setText("3")
                invitadoV.labelVidas.setText("3")
        else:
            print('No clicked.')
    elif tipoJuego=="2":
        buttonReply = QMessageBox.question(userV, 'Alerta', "¿Abandonar? Costo: 20 tokens", QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
        if buttonReply == QMessageBox.Yes:
            
            #obtenemos datos del usuario
            nameUser = userV.txtUS.text()
            passUser= userV.label_2.text()

            #Validamos que pueda abandonar
            obj={'nombre':'{}'.format(nameUser),'password':'{}'.format(passUser)}
            res = requests.post(f'{url_Api}/Abandonar',json=obj)

            #Verificar respuesta
            jsonResponse = res.json()
            
            if jsonResponse["Message"]=="NEC":
                QMessageBox.about(userV,"Alerta","No tiene monedas suficientes")
            else:
                
                getImageBack()
                resetGameJ1()
                resetGameJ2()
                invitadoV.hide()
                userV.labelVidas.setText("3")
                invitadoV.labelVidas.setText("3")
        else:
            print('No clicked.')

def elegirPosiciones(size):
        #primero obtenemos la configuaricon de barcos
        config = jugadorP.matriz.getShips(size)

        #obtenemos cantidad de barcos individuales
        p = int(config["p"])
        s = int(config["s"])
        d = int(config["d"])
        b = int(config["b"])

        #construir portaviones
        aux1 = 0
        while aux1 < p :
            fila,ok = QInputDialog.getText(userV,"Fila","Ingrese la fila")
            if ok:
                columna,ok2 = QInputDialog.getText(userV,"Columna","Ingrese la columna")
                if ok2:
        
                    #Buscamos coordenada y ubicamos el objeto
                    porta = jugadorP.matriz.ubicarPortavion(int(str(fila)),int(str(columna)))
                
                    if porta != None:
                        #aumentamos contador de objetos ubicados
                        aux1+=1
                        jugadorP.matriz.graficarNeato("Partida",jugadorP.NombreJugada)
                        getImage()
                    else:
                        QMessageBox.about(userV,"Alerta","Entrada no valida")

        #construir submarinos
        aux2 = 0
        while aux2 < s :
            fila,ok = QInputDialog.getText(userV,"Fila","Ingrese la fila")
            if ok:
                columna,ok2 = QInputDialog.getText(userV,"Columna","Ingrese la columna")
                if ok2:
        
                    #Buscamos coordenada y ubicamos el objeto
                    porta = jugadorP.matriz.ubicarSubmarino(int(str(fila)),int(str(columna)))
                
                    if porta != None:
                        #aumentamos contador de objetos ubicados
                        aux2+=1
                        jugadorP.matriz.graficarNeato("Partida",jugadorP.NombreJugada)
                        getImage()
                    else:
                        QMessageBox.about(userV,"Alerta","Entrada no valida")
        
        #construir Destructores
        aux3 = 0
        while aux3 < d :
            fila,ok = QInputDialog.getText(userV,"Fila","Ingrese la fila")
            if ok:
                columna,ok2 = QInputDialog.getText(userV,"Columna","Ingrese la columna")
                if ok2:
        
                    #Buscamos coordenada y ubicamos el objeto
                    porta = jugadorP.matriz.ubicarDestructor(int(str(fila)),int(str(columna)))
                
                    if porta != None:
                        #aumentamos contador de objetos ubicados
                        aux3+=1
                        jugadorP.matriz.graficarNeato("Partida",jugadorP.NombreJugada)
                        getImage()
                    else:
                        QMessageBox.about(userV,"Alerta","Entrada no valida")
        
        #construir Buques
        aux4 = 0
        while aux4 < b :
            fila,ok = QInputDialog.getText(userV,"Fila","Ingrese la fila")
            if ok:
                columna,ok2 = QInputDialog.getText(userV,"Columna","Ingrese la columna")
                if ok2:
        
                    #Buscamos coordenada y ubicamos el objeto
                    porta = jugadorP.matriz.ubicarBuque(int(str(fila)),int(str(columna)))
                
                    if porta != None:
                        #aumentamos contador de objetos ubicados
                        aux4+=1
                        jugadorP.matriz.graficarNeato("Partida",jugadorP.NombreJugada)
                        getImage()
                    else:
                        QMessageBox.about(userV,"Alerta","Entrada no valida")

#invitado
def makeMoveInv():
    if invitado.turno == True:
        fila = invitadoV.txtFila.text()
        columna = invitadoV.txtColumna.text()

        vidas = int(invitadoV.labelVidas.text())
        
        if fila.isalpha() or columna.isalpha():
            invitadoV.labelWarning.setText("Ingrese valores numericos")
            invitadoV.labelWarning.show()
        elif len(fila)==0 or len(columna)==0:
            invitadoV.labelWarning.setText("Debe llenar ambos campos")
            invitadoV.labelWarning.show()
        else:
            invitadoV.labelWarning.setText(" ")
            response = jugadorP.insertarMovimiento(int(fila),int(columna)) #Se realiza el disparo hacia el tablero principal
            coordenadas = [int(fila),int(columna)]
            invitado.movimientos.append(coordenadas)

            if response == "nExist":  
                invitadoV.labelWarning.setText("No existe la fila")
                invitadoV.labelWarning.show()

            #si acierta o falla es turno del siguiente jugador
            elif response == "Disparo":
                invitado.turno=False
                jugadorP.turno=True
                QMessageBox.about(invitadoV,"Felicidades","Disparo correcto")
                jugadorP.graficarNeato("Partida",jugadorP.NombreJugada)
                getImage()


            elif response == "Fallo":
                invitado.turno=False
                jugadorP.turno=True
                invitadoV.labelWarning.setText("")
                QMessageBox.about(invitadoV,"¡Oh no!","Ha fallado el disparo, pierde una vida")

                #pierde una vida
                vidas-=1
                invitadoV.labelVidas.setText(str(vidas))

                jugadorP.graficarNeato("Partida",jugadorP.NombreJugada)
                getImage()

            elif response == "NAC":
                invitadoV.labelWarning.show()
                invitadoV.labelWarning.setText("No se encuentra")

        #Verificamos si quedan vidas
        if vidas == 0:
            QMessageBox.about(invitadoV,"¡Oh no!","Has Perdido la partida")

            #Mostramos resultados del invitado
            jugadorP.verificarAciertos()
            mensaje = " "
            mensaje += "Errores: {}\n\n".format(jugadorP.matriz.errores)
            mensaje += "Barcos destruidos: \nPortaviones: {}\n\nSubmarinos: {}\n\nDestructores: {}\n\nBuques: {}".format(jugadorP.matriz.cantP,jugadorP.matriz.cantS,jugadorP.matriz.cantD,jugadorP.matriz.cantB)
            QMessageBox.about(invitadoV,"Resultados",mensaje)

            #Mostramos resultados del jugador
            invitado.verificarAciertos()
            mensaje = " "
            mensaje += "Errores: {}\n\n".format(invitado.matriz.errores)
            mensaje += "Barcos destruidos: \nPortaviones: {}\n\nSubmarinos: {}\n\nDestructores: {}\n\nBuques: {}".format(invitado.matriz.cantP,invitado.matriz.cantS,invitado.matriz.cantD,invitado.matriz.cantB)
            QMessageBox.about(userV,"Resultados",mensaje)

            #Preguntamos si quiere lista o el grafo
            box = QMessageBox()
            box.setIcon(QMessageBox.Question)
            box.setWindowTitle('Ver imagen')
            box.setText('Elija una opcion')
            box.setStandardButtons(QMessageBox.Yes|QMessageBox.No)
            buttonY = box.button(QMessageBox.Yes)
            buttonY.setText('Lista Adyacencia')
            buttonN = box.button(QMessageBox.No)
            buttonN.setText('Grafo Adyacencia')
            box.exec_()

            if box.clickedButton() == buttonY: invitado.matriz.verListaAdyacencia()
            if box.clickedButton() == buttonN: invitado.matriz.grafoAdyacencia()

            #preguntamos al jugador principal
            terminate = QMessageBox.question(userV, 'Mensaje', "¿Volver a jugar con la configuracion actual?", QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
            if terminate == QMessageBox.Yes:
                name2,ok2 = QInputDialog.getText(userV,"Nombre de la jugada","Ingrese el nombre de la jugada")
                if ok2:

                    #Guardamos la jugada
                    nameUser = userV.txtUS.text()
                    passUser= userV.label_2.text()

                    jugadorP.NombreJugada=name2 #Se guarda en la clase para acceder desde cualquier parte
                    invitado.NombreJugada=name2

                    obj={'nombre':'{}'.format(nameUser),'pass':'{}'.format(passUser),'jugada':'{}'.format(str(name2))}
                    res = requests.post(f'{url_Api}/newJugada',json=obj)

                    #Verificar respuesta
                    jsonResponse = res.json()
                    if jsonResponse["Message"]!="OK":
                        QMessageBox.about(userV,"Alerta","Hubo un error")

                    aux = jugadorP.matriz.sizeT

                    #resetear
                    resetGameJ1()
                    resetGameJ2()
                    monedas = getCoins()
                    userV.labelMON.setText(monedas)
                    userV.labelVidas.setText("3")
                    invitadoV.labelVidas.setText("3")
                    #generar matriz y mostrar tablero
                    jugadorP.putSizeT(aux)
                    invitado.putSizeT(aux)
                    generarMatrizPrincipal(int(str(aux)))
                    generarMatrizInvitado(int(str(aux)))
                    getImage()
                    getImageInvitado()

            else:
                invitadoV.hide()
                getImageBack()
                resetGameJ2()
                resetGameJ1()
                userV.labelVidas.setText("3")
                invitadoV.labelVidas.setText("3")

        #verificamos si ha ganado
        partida = jugadorP.verificarGanar()
        if partida == "terminado":
            QMessageBox.about(userV,"¡Felicidades!","Has Ganado la partida")

            #Mostramos resultados del invitado
            jugadorP.verificarAciertos()
            mensaje = " "
            mensaje += "Errores: {}\n\n".format(jugadorP.matriz.errores)
            mensaje += "Barcos destruidos: \nPortaviones: {}\n\nSubmarinos: {}\n\nDestructores: {}\n\nBuques: {}".format(jugadorP.matriz.cantP,jugadorP.matriz.cantS,jugadorP.matriz.cantD,jugadorP.matriz.cantB)
            QMessageBox.about(invitadoV,"Resultados",mensaje)

            #Mostramos resultados del jugador
            invitado.verificarAciertos()
            mensaje = " "
            mensaje += "Errores: {}\n\n".format(invitado.matriz.errores)
            mensaje += "Barcos destruidos: \nPortaviones: {}\n\nSubmarinos: {}\n\nDestructores: {}\n\nBuques: {}".format(invitado.matriz.cantP,invitado.matriz.cantS,invitado.matriz.cantD,invitado.matriz.cantB)
            QMessageBox.about(userV,"Resultados",mensaje)

            #Preguntamos si quiere lista o el grafo
            box = QMessageBox()
            box.setIcon(QMessageBox.Question)
            box.setWindowTitle('Ver imagen')
            box.setText('Elija una opcion')
            box.setStandardButtons(QMessageBox.Yes|QMessageBox.No)
            buttonY = box.button(QMessageBox.Yes)
            buttonY.setText('Lista Adyacencia')
            buttonN = box.button(QMessageBox.No)
            buttonN.setText('Grafo Adyacencia')
            box.exec_()

            if box.clickedButton() == buttonY: invitado.matriz.verListaAdyacencia()
            if box.clickedButton() == buttonN: invitado.matriz.grafoAdyacencia()

            #preguntamos al jugador principal
            terminate = QMessageBox.question(userV, 'Mensaje', "¿Volver a jugar con la configuracion actual?", QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
            if terminate == QMessageBox.Yes:
                name2,ok2 = QInputDialog.getText(userV,"Nombre de la jugada","Ingrese el nombre de la jugada")
                if ok2:

                    #Guardamos la jugada
                    nameUser = userV.txtUS.text()
                    passUser= userV.label_2.text()

                    jugadorP.NombreJugada=name2 #Se guarda en la clase para acceder desde cualquier parte
                    invitado.NombreJugada=name2

                    obj={'nombre':'{}'.format(nameUser),'pass':'{}'.format(passUser),'jugada':'{}'.format(str(name2))}
                    res = requests.post(f'{url_Api}/newJugada',json=obj)

                    #Verificar respuesta
                    jsonResponse = res.json()
                    if jsonResponse["Message"]!="OK":
                        QMessageBox.about(userV,"Alerta","Hubo un error")

                    aux = jugadorP.matriz.sizeT

                    #resetear
                    resetGameJ1()
                    resetGameJ2()
                    monedas = getCoins()
                    userV.labelMON.setText(monedas)
                    userV.labelVidas.setText("3")
                    invitadoV.labelVidas.setText("3")
                    #generar matriz y mostrar tablero
                    jugadorP.putSizeT(aux)
                    invitado.putSizeT(aux)
                    generarMatrizPrincipal(int(str(aux)))
                    generarMatrizInvitado(int(str(aux)))
                    getImage()
                    getImageInvitado()

            else:
                invitadoV.hide()
                getImageBack()
                resetGameJ2()
                resetGameJ1()
                userV.labelVidas.setText("3")
                invitadoV.labelVidas.setText("3")
    else:
        QMessageBox.about(invitadoV,"Mensaje","Todavia no es su turno")

def resetGame():         
    matriz.eliminar()

def resetGameJ1():         
    #eliminamos la matriz
    jugadorP.eliminar()

def resetGameJ2():         
    #eliminamos la matriz
    invitado.eliminar()
    
#Tutorial
def getTutorial():
    res = requests.post(f'{url_Api}/tutorial')

    #Verificar respuesta
    jsonResponse = res.json()

    #generar matriz y mostrar tablero
    showTutorial()
    generarMatrizTutorial(int(jsonResponse["ancho"]))
    getImageTutorial()
    

    #iniciar reproduccion, se recorren los movimientos
    for d in jsonResponse["Movimientos"]:
        QtTest.QTest.qWait(1500)
        tutorialMatriz.insertarMovimiento(int(d["X"]),int(d["Y"]))
        tutorialMatriz.graficarNeato("Tutorial",tutorialMatriz.NombreJugada)
        getImageTutorial()

        QtTest.QTest.qWait(1500)

    tutoV.hide()
    tutorialMatriz.eliminar()

def showTutorial():
    tutoV.show()

def getImageTutorial():
    tutoV.labelTutorial.setPixmap(QtGui.QPixmap("matriz_Tutorial.png"))

def generarMatrizTutorial(size):
    tutorialMatriz.putSizeT(size)    
    for i in range(1,size+1):
        for j in range(1,size+1):
            tutorialMatriz.insert(i,j," ")
    tutorialMatriz.generarPosicionesAleatorias()
    tutorialMatriz.graficarNeato("Tutorial",tutorialMatriz.NombreJugada)


#Principal - insercion se hace en la matriz invitado
#Invitado - insercion se hace en la principal

#------------ Botones
#Login
loginV.pushButton.clicked.connect(loginAction)
loginV.pushButton_2.clicked.connect(salir)
loginV.pushButton_3.clicked.connect(nuevaCuenta)

#Cuenta nueva
nuevoV.pushButton.clicked.connect(getDatosNuevaCuenta)
nuevoV.pushButton_2.clicked.connect(volverLogin)

#Ventana user
userV.pushButton.clicked.connect(editarDatos)
userV.pushButton_2.clicked.connect(eliminarCuenta)
userV.btnCerrarS.clicked.connect(logOut)
userV.pushButton_5.clicked.connect(irTienda)
userV.btnDeshacer.clicked.connect(deshacer)
userV.btnShoot.clicked.connect(makeMove)
userV.btnAbandonar.clicked.connect(abandonar)
userV.btnTutorial.clicked.connect(getTutorial)
userV.pushButton_4.clicked.connect(prueba)

#Ventana invitado
invitadoV.btnShoot.clicked.connect(makeMoveInv)

#Tienda
tiendaV.btnAVL.clicked.connect(verCompras)
tiendaV.btnBack.clicked.connect(backtienda)
tiendaV.btnComprar.clicked.connect(comprar)

#Editar datos
editarV.btnBack.clicked.connect(volverEditar)
editarV.btnSave.clicked.connect(updateData)

#Admin
adminV.btnCerrar.clicked.connect(logOutAdmin)
adminV.btnUsers.clicked.connect(allUsuarios)
adminV.btnCarga.clicked.connect(cargaMasiva)

#Ejecutar principal
loginV.show()

app.exec()
