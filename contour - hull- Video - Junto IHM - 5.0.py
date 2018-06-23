######ImportaOpenCV#######
import numpy as np
import cv2
from matplotlib import pyplot as plt
#########################

######ImportaIHM########
from tkinter import *
########################

#####ImportaSerial######
import serial
########################

######################DefiniçõesSerial#########################
port = serial.Serial("COM10",115200)
serialFromArduino = port
serialFromArduino.flushInput()
###############################################################

######################DefiniçõesVariaveis######################
#valor=100005
#valor2=100005
valor=0
valor2=0
finalcx=0
finalcy=0
area_x_y=0
ativador=0
selecao=5
##############################################################

#######################DefiniçõesIHM##########################
def Rodar():
    
    lb["text"] = " Iniciar Esteira        "
    port.write(b'A') #ImprimaNaSerial'A'
    
def parar():
    
    lb["text"] = " Parar Esteira         "
    port.write(b'B') #ImprimaNaSerial'B'
    
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
    port.write(b'E') #ImprimaNaSerial'E'
        
janela = Tk()
###############################################################

########################DefiniçãoCamêra########################
cap = cv2.VideoCapture(0)
###############################################################

while(True):

    ret, img = cap.read() #IniciarCâmera
 
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
    
    janela.after(10) #AtualizaEventosCada10Milisegundos
    janela.update_idletasks() #AtualizaEventos
    janela.update() #AtualizaEventos

    ################LêSerialDoArduinoParaRaspberry#################
    if(serialFromArduino.inWaiting()>0):
        input = serialFromArduino.read(1)
    ###############################################################
    
    ######################IniciaCalculoDeArea######################
    if (input == b'H'):
        valor = 0
        valor2 = 0
    ###############################################################
    '''    
    

    '''

    #print(selecao)
    #print(input)    
    ######################ShowImagemOriginal#######################
    cv2.namedWindow('Original image',cv2.WINDOW_NORMAL)
    cv2.resizeWindow('Original image',400,400)
    cv2.imshow('Original image',img)
    ###############################################################
    
    i = -1  #DefiniçãoTipoDeContorno_Draw_Contour(i)

    #####################FiltrosDaImagem###########################
    kernel = np.ones((5,5), np.uint8)

    img_erosion = cv2.erode(img, kernel, iterations=1)
    
    img_dilation = cv2.dilate(img_erosion, kernel, iterations=1)
        
    gray = cv2.cvtColor(img_dilation,cv2.COLOR_BGR2GRAY) #ConverteImagemEmCinza
    
    opening = cv2.morphologyEx(gray,cv2.MORPH_OPEN,kernel,iterations = 2)
    
    blur = cv2.medianBlur (opening,5)
    
    binary_inv = cv2.threshold(gray,127,255,cv2.THRESH_BINARY_INV)
    
    th3 = cv2.adaptiveThreshold(blur,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C,cv2.THRESH_BINARY,17,2)
    
    bilateral_filtered_image = cv2.bilateralFilter(gray, 5, 175, 175)
   
    edge=cv2.Canny(bilateral_filtered_image,50,500) #Canny_Edge_FiltroDeContorno
    ###############################################################
    
    ########################ShowImagemCanny########################
    cv2.namedWindow('Canny Image',cv2.WINDOW_NORMAL)
    cv2.resizeWindow('Canny Image',400,400)
    cv2.imshow('Canny Image',edge)
    ###############################################################

    ##################DefiniçãoDePontosDoContorno##################
    _, contours, hierarchy = cv2.findContours(edge,cv2.RETR_TREE,cv2.CHAIN_APPROX_SIMPLE)
    ###############################################################
    
    #####################ShowImagemMascaraDraw#####################
    cv2.namedWindow('Image Draw',cv2.WINDOW_NORMAL)
    cv2.resizeWindow('Image Draw',400,400)
    cv2.imshow('Image Draw',img)
    ###############################################################

    ###############################ProcessamentoDaImagem###############################
    if ((len(contours))>0):

        ###############********************************##########
        '''trocar aqui pela serial vinda do arduino'''
        
        valor = 0
        valor2 = 0
        ###############********************************##########
                        
        cnt=contours[i]

        epsilon = 0.1*cv2.arcLength(cnt,True)
        approx = cv2.approxPolyDP(cnt,0.01*cv2.arcLength(cnt,True),True)

        cv2.drawContours (img, [cnt], 0, (0,255,0), 3)
        M = cv2.moments(cnt)
        
        hull = cv2.convexHull(cnt)
        
        cv2.drawContours(img,[cnt],0,(255,0,0),10)
        cv2.drawContours (img, [hull], 0, (0,0,255), 2)
                
        #################################Condicional_M!=0##################################
        if (M ['m00'] == 0): 
            M ['m00'] = 1
            
        cx = int(M['m10']/M['m00'])
        cy = int(M['m01']/M['m00'])
        ###################################################################################

        #################################CalculoAreaEixo_X#################################
        while (valor < 100000):

            valor += 1
            
            if (cx>=finalcx):
                finalcx=cx
                valormaior2=finalcx
                
        if (valor == 100000):
            #print('VALOR MAIOR SAIDA X',finalcx)
            calcx=finalcx
            valor += 1
        ###################################################################################

        #################################CalculoAreaEixo_X#################################    
        while (valor2 < 100000):
            valor2 += 1
            
            if (cy>=finalcy):
                finalcy=cy
                valormaior2=finalcy
                                
        if (valor2 == 100000):
            #print('VALOR MAIOR SAIDA Y',finalcy)
            calcy=finalcy
        ###################################################################################
            
            #######################
            #Calcular Area CX e CY#
            #######################
            area_x_y=calcx*calcy

            cx = 0
            finalcx = 0       
            valormaior2 = 0
            calcx = 0

            cy = 0
            finalcy = 0                
            valormaior2 = 0
            calcy = 0                  
           
            #print('AREA X e Y',area_x_y)
            valor2 += 1
            
        
        ################
        #    Limao     #
        ################

        if (selecao == 0):
            
            print('Selecionado LIMÃO')
        
            if (area_x_y > 0 and area_x_y <= 94100 ):
                #port.write(b'E') #ImprimaNaSerial'E'
                print('Limão Classe 1')
                area_x_y=0
                pass

            elif (area_x_y > 94100 and area_x_y <= 100672 ):
                #port.write(b'E') #ImprimaNaSerial'E'
                print('Limão Classe 2')
                area_x_y=0
                pass

            elif (area_x_y > 100672 and area_x_y <= 112420 ):
                #port.write(b'E') #ImprimaNaSerial'E'
                port.write(b'G') #ImprimaNaSerial'G'
                print('Limão Classe 3')
                area_x_y=0
                pass
                           

        ################
        #   Laranja    #
        ################

        if (selecao == 1):

            print('Selecionado LARANJA')

            if (area_x_y > 0 and area_x_y <= 124542 ):
                #5port.write(b'E') #ImprimaNaSerial'E'
                print('Laranja Classe 1')
                area_x_y=0
                pass

            elif (area_x_y > 124542 and area_x_y <= 125290 ):
                #port.write(b'E') #ImprimaNaSerial'E'
                print('Laranja Classe 2')
                area_x_y=0
                pass

            elif (area_x_y > 125290 and area_x_y > 145290 ):
                port.write(b'E') #ImprimaNaSerial'E'
                print('Laranja Classe 3')
                area_x_y=0
                pass

        ################################CriaçãoMascaras####################################            
        epsilon = 0.1*cv2.arcLength(cnt,True)
        approx = cv2.approxPolyDP(cnt,0.01*cv2.arcLength(cnt,True),True)

        hull = cv2.convexHull(cnt,returnPoints = False)
        defects = cv2.convexityDefects(cnt,hull)    
        
        x,y,w,h = cv2.boundingRect(cnt)
        cv2.rectangle(img,(x,y),(x+w,y+h),(0,255,0),2)
        
        # draw the rectangle surrounding the filtered contour
        rect = cv2.minAreaRect(cnt)
        box = cv2.boxPoints(rect)
        box = np.int0(box)
        
        ## Minimum Enclosing Circle
        (x,y),radius = cv2.minEnclosingCircle(cnt)
        center = (int(x),int(y))
        radius = int(radius)
        cv2.circle(img,center,radius,(0,255,0),2)

        ## Fitting an Ellipse
        '''ellipse = cv2.fitEllipse(cnt)
        cv2.ellipse(img,ellipse,(0,255,0),2)'''
        ###################################################################################

        ############################ShowImagemMascaraDraw##################################
        cv2.namedWindow('Image Draw',cv2.WINDOW_NORMAL)
        cv2.resizeWindow('Image Draw',400,400)
        cv2.imshow('Image Draw',img)        
        ###################################################################################
        
        ## Close and exit
        #cv2.waitKey(0)
        #cv2.destroyAllWindows()
        
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    ###################################################################################
