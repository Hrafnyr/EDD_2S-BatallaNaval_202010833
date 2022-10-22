
import os
import json
import sys
from PyQt5.uic import loadUi
from PyQt5 import QtWidgets, QtGui
from PyQt5.QtWidgets import QMainWindow,QApplication

class MainWindowC(QMainWindow):
    def __init__(self): #,jsonResponse,*args,**kwargs
        super(MainWindowC,self).__init__() #*args,**kwargs
        loadUi(os.path.dirname(os.path.abspath(__file__))+"/carrito.ui",self)
        
        #colocar tamaño por defecto de columnas
        self.tableStore.setColumnWidth(0,200)
        self.tableStore.setColumnWidth(1,150)
        self.tableStore.setColumnWidth(2,185)
        self.rows = 0
        

    def fillTable(self,info):
        data = json.loads(info)
        size_ = len(data["data"])  
        for i in range(size_):
            self.insert(data["data"][i]["indice"],data["data"][i]["id"],data["data"][i]["nombre"])
            self.rows+=1

    def insert(self,indice,id,name):
        #creao fila vacia e insertar en tabla
        rowPosition = self.tableStore.rowCount()
        self.tableStore.insertRow(rowPosition)

        #Llenar fila con datos
        self.tableStore.setItem(rowPosition,0,QtWidgets.QTableWidgetItem(indice))
        self.tableStore.setItem(rowPosition,1,QtWidgets.QTableWidgetItem(id))
        self.tableStore.setItem(rowPosition,2,QtWidgets.QTableWidgetItem(name))

        #redimensionar
        self.tableStore.verticalHeader().setDefaultSectionSize(80)
    
    def eliminar(self,fila):
        self.tableStore.removeRow(fila-1)

    def clearTable(self):
        if self.rows > 0:
            self.tableStore.clearContents()
            self.tableStore.setRowCount(0)
            self.rows = 0
    
    def getIndice(self,fila):
        
        data = self.tableStore.item(fila-1,0)
        return data.text()


# app = QApplication(sys.argv)
# prueba = MainWindowC()

# prueba.show()
# app.exec()
