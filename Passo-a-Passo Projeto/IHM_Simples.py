from tkinter import *


def bt_click():
    
    print("A")
    lb["text"] = "Start"

def bt_click2():
    
    print("B")
    lb["text"] = "Stop"

def bt_click3():
    
    print("C")
    lb["text"] = "Separar Limão"

def bt_click4():
    
    print("D")
    lb["text"] = "Separar Laranja"
    

janela = Tk()

while(1):

    bt = Button(janela, width=10, height= 4, text="Início", fg="green", highlightbackground="green", command=bt_click)
    bt.place(x=100, y= 100)

    bt = Button(janela, width=10, height= 4, text="Parada", fg="red", highlightbackground="red", command=bt_click2)
    bt.place(x=300, y= 100)

    bt = Button(janela, width=10, height= 4, text="Limão", fg="blue", highlightbackground="blue", command=bt_click3)
    bt.place(x=100, y= 300)

    bt = Button(janela, width=10, height= 4, text="Laranja", fg="black", highlightbackground="black", command=bt_click4)
    bt.place(x=300, y= 300)
               
    lb = Label(janela, text="Selecione Opção")
    lb.place(x=100, y=230)

    janela.title("Painel de Controle")
    janela.geometry("300x300+200+200")
    janela.mainloop()
    
    


