
from curses.ascii import NUL
from PyQt5 import QtWidgets, uic
from PyQt5.QtWidgets import QMessageBox
import os
import sys
import requests

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
    requests.post(f'{url_Api}/carga')
    QMessageBox.about(adminV,"Mensaje","Carga masiva realizada")

def salir():
    exit()



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
