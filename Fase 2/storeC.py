
import os
import json
import sys
from PyQt5.uic import loadUi
from PyQt5 import QtWidgets, QtGui
from PyQt5.QtWidgets import QMainWindow,QApplication

class MainWindow(QMainWindow):
    def __init__(self): #,jsonResponse,*args,**kwargs
        super(MainWindow,self).__init__() #*args,**kwargs
        loadUi(os.path.dirname(os.path.abspath(__file__))+"/store.ui",self)
        
        #colocar tamaño por defecto de columnas
        self.tableStore.setColumnWidth(0,200)
        self.tableStore.setColumnWidth(1,150)
        self.tableStore.setColumnWidth(2,175)
        self.tableStore.setColumnWidth(3,125)
        

    def fillTable(self,respuesta):
        data = json.loads(respuesta)
        cont=0
        rows = 0

        #primero saber cuantos elementos hay
        for single in data["categorias"]:
            for info in data["categorias"][single]:
                rows+=1
        #print(rows)
        #Agregar la cantidad de filas
        self.tableStore.setRowCount(rows)
        
        #Agregar datos
        for single in data["categorias"]:
            for info in data["categorias"][single]:
                self.tableStore.setItem(cont,0,QtWidgets.QTableWidgetItem(single))
                self.tableStore.setItem(cont,1,QtWidgets.QTableWidgetItem(info["nombre"]))
                self.tableStore.setItem(cont,2,QtWidgets.QTableWidgetItem(info["id"]))
                self.tableStore.setItem(cont,3,QtWidgets.QTableWidgetItem(info["precio"]))

                #Agregar imagen
                img = self.getImage(info["src"])
                self.tableStore.setCellWidget(cont,4,img)
                cont+=1
        
        #redimensionar
        self.tableStore.verticalHeader().setDefaultSectionSize(80)

    def getImage(self, path):
        image = QtWidgets.QLabel(self.tableStore)
        image.setText
        image.setScaledContents(True)
        pixmap = QtGui.QPixmap(path)
        image.setPixmap(pixmap)
        return image
    
    def getID(self,fila):
        
        data = self.tableStore.item(fila-1,2)
        return data.text()
    
    def getNombre(self,fila):
        
        data = self.tableStore.item(fila-1,1)
        return data.text()
    
    def getPrecio(self,fila):
        
        data = self.tableStore.item(fila-1,3)
        return data.text()

# data = '''{"categorias":
# {
# "c1":[{
# "id":"6","nombre":"Barco 4","precio":"500","src":"/home/moises/Escritorio/EDD/EDD_2S-BatallaNaval_202010833/Fase 2/img/ship.png"},
# {
# "id":"5","nombre":"Barco 4","precio":"500","src":"/home/moises/Escritorio/EDD/EDD_2S-BatallaNaval_202010833/Fase 2/img/ship.png"}],
# "Legendaria":[{
# "id":"4","nombre":"Barco 4","precio":"500","src":"/home/moises/Escritorio/EDD/EDD_2S-BatallaNaval_202010833/Fase 2/img/ship.png"},
# {
# "id":"3","nombre":"Barco 3","precio":"5","src":"/home/moises/Escritorio/EDD/EDD_2S-BatallaNaval_202010833/Fase 2/img/ship.png"}],
# "comun":[{
# "id":"22","nombre":"Barco 2","precio":"10","src":"/home/moises/Escritorio/EDD/EDD_2S-BatallaNaval_202010833/Fase 2/img/ship.png"},
# {
# "id":"2","nombre":"Barco 2","precio":"10","src":"/home/moises/Escritorio/EDD/EDD_2S-BatallaNaval_202010833/Fase 2/img/ship.png"},
# {
# "id":"1","nombre":"Barco Naval Army","precio":"50","src":"/home/moises/Escritorio/EDD/EDD_2S-BatallaNaval_202010833/Fase 2/img/ship.png"}]
# }
# }'''

# app = QApplication(sys.argv)
# prueba = MainWindow()
# prueba.fillTable(data)
# print(prueba.getPrueba(1))
# prueba.show()
# app.exec()
