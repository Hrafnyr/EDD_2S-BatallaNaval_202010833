from PyQt5 import QtWidgets, uic, QtCore
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QMessageBox
from PyQt5 import QtGui
import os
import sys

#Varibles globales
nameUser = ""
passUser = ""

#iniciar app
app = QtWidgets.QApplication(sys.argv)

#cargar archivos ui localizados en el directorio actual
loginV = uic.loadUi(os.path.dirname(os.path.abspath(__file__))+"\\login.ui")
nuevoV = uic.loadUi(os.path.dirname(os.path.abspath(__file__))+"\\nuevaCuenta.ui")
userV = uic.loadUi(os.path.dirname(os.path.abspath(__file__))+"\\jugadorV.ui")

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

def verUsuario(nameU):
    loginV.hide()
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


def volverLogin():
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
userV.btnCerrarS.clicked.connect(logOut)

#Ejecutar principal
loginV.show()

app.exec()
