

######ImportaIHM########
from tkinter import *
########################

#####ImportaSerial######
import serial
########################

######################DefiniçõesSerial#########################
port = serial.Serial("COM4",115200)
serialFromArduino = port
serialFromArduino.flushInput()
###############################################################



#######################DefiniçõesIHM##########################
def Rodar():
    
    lb["text"] = " Iniciar Esteira        "
    port.write(b'A') #ImprimaNaSerial'A'
    print('Gira Motor')
    
def parar():
    
    lb["text"] = " Parar Esteira         "
    port.write(b'B') #ImprimaNaSerial'B'
    print('Parado Motor')
    
def btc_click3():
    
    global selecao
    lb["text"] = " Separar Limão      "
    port.write(b'C') #ImprimaNaSerial'C'
    limao=0
    selecao=limao
    return selecao
    
def btc_click4():
    
    global selecao    
    lb["text"] = " Separar Laranja    "
    port.write(b'D') #ImprimaNaSerial'D'
    laranja=1
    selecao=laranja
    return selecao
                
def balizador():
    
    lb["text"] = " Acionar Balizador "
    port.write(b'G') #ImprimaNaSerial'E'
        
janela = Tk()
###############################################################


while(True):

    
 
    #########################DesignButtons#########################
    bt = Button(janela, width=10, height= 4, text="Início", fg="green", highlightbackground="green", command=Rodar)
    bt.place(x=50, y= 100)

    bt = Button(janela, width=10, height= 4, text="Parada", fg="red", highlightbackground="red", command=parar)
    bt.place(x=150, y= 100)

    bt = Button(janela, width=10, height= 4, text="Liberar Sensor/ Balizador", fg="blue", highlightbackground="blue", command=balizador)
    bt.place(x=50, y= 300)

    bt = Button(janela, width=10, height= 4, text="Limão", fg="darkgreen", highlightbackground="darkgreen", command=btc_click3)
    bt.place(x=150, y= 300)

    bt = Button(janela, width=10, height= 4, text="Laranja", fg="orangered", highlightbackground="orangered", command=btc_click4)
    bt.place(x=250, y= 300)
               
    lb = Label(janela, text="")
    lb.place(x=100, y=230)

    janela.title("Painel de Controle")
    janela.geometry("400x400+960+300")    
    janela.mainloop()

            
    
    ###################################################################################
