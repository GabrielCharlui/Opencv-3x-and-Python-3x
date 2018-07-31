'''ImportaSerial'''
import serial #Importa Biblioteca Serial
########################

'''DefiniçõesSerial'''
port = serial.Serial("COM4",115200) #Maxima taxa de comunicação aceita pelo Raspberry
serialFromArduino = port #Passa configuração de port para 'serialFromArduino'
serialFromArduino.flushInput()

'''DefiniçõesVariaveis'''
valor=1
valor2=1

'''LêSerialDoArduinoParaRaspberry'''

if(serialFromArduino.inWaiting()>0): #Se caracter recebido
	input = serialFromArduino.read(1) #Passa o caracter para a variavel 'input'

	print(input) #Exibe o que contem a variavel 'input' 

'''IniciaCalculoDeArea'''
if (input == b'H'): #Se input for igual a H (Case-sensitive)
	valor = 0
	valor2 = 0

	################################################################################################
	# 								                                                               #    
	#	b'*' -> b Representa o bit de inicio da comunicação (Modelo Comunicação Serial Assíncrona) #
	#   *'H" -> H Representa a letra esperada (Case-sensitive)                                                    #                                                      
	#                                                                                              #
	################################################################################################