
import json
from PyQt5 import QtWidgets, uic, QtGui
from PyQt5.QtWidgets import QMessageBox, QInputDialog
from storeC import MainWindow
import os
import sys
import requests
from matriz import MatrizDispersa

#Varibles globales
class mt:
    def __init__(self,capa):
        self.matriz = MatrizDispersa(capa)
    
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

nameUser = ""
passUser = ""
url_Api = "http://0.0.0.0:8080"
matriz = mt(1)

#iniciar app
app = QtWidgets.QApplication(sys.argv)

#cargar archivos ui localizados en el directorio actual
loginV = uic.loadUi(os.path.dirname(os.path.abspath(__file__))+"/login.ui")
nuevoV = uic.loadUi(os.path.dirname(os.path.abspath(__file__))+"/nuevaCuenta.ui")
userV = uic.loadUi(os.path.dirname(os.path.abspath(__file__))+"/jugadorV.ui")
editarV = uic.loadUi(os.path.dirname(os.path.abspath(__file__))+"/panelEditar.ui")
adminV = uic.loadUi(os.path.dirname(os.path.abspath(__file__))+"/admin.ui")
tiendaV = MainWindow()

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
        
        if jsonResponse["Message"]=="error":
            QMessageBox.about(tiendaV,"Alerta","Hubo un error")
        elif jsonResponse["Message"]=="NEC":
            QMessageBox.about(tiendaV,"Alerta","No tiene dinero suficiente")
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

def prueba():
    size,ok = QInputDialog.getText(userV,"Tamaño del tablero","Ingrese el tamaño del tablero (10 minimo)")
    
    if ok:

        if int(str(size))<10:
            QMessageBox.about(userV,"Alerta","Debe ingresar un valor mayor o igual a 10")
        else:

            #mostar componentes 
            userV.labelF.show()
            userV.labelC.show()
            userV.txtFila.show()
            userV.txtColumna.show()
            userV.btnShoot.show()

            userV.labelMon.show()
            monedas = getCoins()
            userV.labelMON.setText(monedas)
            userV.labelMON.show()
            userV.labelV.show()
            userV.labelVidas.show()

            #generar matriz y mostrar tablero
            generarMatriz1(int(str(size)))
            getImage()
    else:
        print("canceled")

def generarMatriz1(size):
    matriz.putSizeT(size)    
    for i in range(1,size+1):
        for j in range(1,size+1):
            matriz.insert(i,j," ")
    matriz.generarPosicionesAleatorias()
    matriz.graficarNeato("Partida","Partida")

def getImage():
    userV.label_3.setPixmap(QtGui.QPixmap("matriz_Partida.png"))

def getImageBack():
    userV.label_3.setPixmap(QtGui.QPixmap("imagenBarco.jpg"))

def makeMove():
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
            matriz.graficarNeato("Partida","Partida")
            getImage()

        elif response == "Fallo":

            userV.labelWarning.setText("")
            QMessageBox.about(userV,"¡Oh no!","Ha fallado el disparo, pierde una vida")

            #pierde una vida
            vidas-=1
            userV.labelVidas.setText(str(vidas))

            matriz.graficarNeato("Partida","Partida")
            getImage()

        elif response == "NAC":
            userV.labelWarning.show()
            userV.labelWarning.setText("Se encuentra la coordenada")

    if vidas == 0:
        QMessageBox.about(userV,"¡Oh no!","Has Perdido la partida")
        getImageBack()
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

userV.btnShoot.clicked.connect(makeMove)

userV.pushButton_4.clicked.connect(prueba)

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
