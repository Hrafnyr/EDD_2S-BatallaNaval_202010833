
from PyQt5 import QtWidgets, uic, QtGui
from PyQt5.QtWidgets import QMessageBox, QInputDialog
from storeC import MainWindow
import os
import sys
import requests
from matriz import MatrizDispersa

#Varibles globales
nameUser = ""
passUser = ""
url_Api = "http://0.0.0.0:8080"

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
            elif len(newPass)!=0:
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
        else:
            QMessageBox.about(tiendaV,"Mensaje","compra realizada")
            tiendaV.txtCategoria.setText("")
            tiendaV.txtID.setText("")   

def verCompras():
    nameUser = userV.txtUS.text()
    passUser= userV.label_2.text()
          
    obj={'nombre':'{}'.format(nameUser),'pass':'{}'.format(passUser)}
    res = requests.post(f'{url_Api}/verAVL',json=obj)

    #Verificar respuesta
    jsonResponse = res.json()
    
    if jsonResponse["Message"]=="error":
        QMessageBox.about(tiendaV,"Alerta","Hubo un error")


#JUGAR

def prueba():
    size,ok = QInputDialog.getText(userV,"Tamaño del tablero","Ingrese el tamaño del tablero (10 minimo)")
    
    if ok:

        if int(str(size))<10:
            QMessageBox.about(userV,"Alerta","Debe ingresar un valor mayor o igual a 10")
        else:
            generarMatriz1(int(str(size)))
            getImage()
    else:
        print("canceled")

def generarMatriz1(size):
    matriz = MatrizDispersa(1)

    for i in range(1,size+1):
        for j in range(1,size+1):
            matriz.insert(i,j," ")

    matriz.graficarNeato("Partida","Partida")

def getImage():
    userV.label_3.setPixmap(QtGui.QPixmap("matriz_Partida.png"))

def getships(size):
    tot = ((size-1)//10)+1
    p = tot
    s = p+p
    d = s+p
    b = d+p
    return {'p':p,'s':s,'d':d,'b':b} # retorna un json con la cantidad de barcos 

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
