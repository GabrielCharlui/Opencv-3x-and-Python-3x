'''ImportaSerial'''
import serial #Importa Biblioteca Serial
########################

'''DefiniçõesSerial'''
port = serial.Serial("COM4",115200) #Maxima taxa de comunicação aceita pelo Raspberry
serialFromArduino = port #Passa configuração de port para 'serialFromArduino'
serialFromArduino.flushInput()


'''EnviaSerialDoRaspberryParaArduino'''

port.write(b'D') #ImprimaNaSerial'D'



	################################################################################################
	# 								                                                               #    
	#	b'*' -> b Representa o bit de inicio da comunicação (Modelo Comunicação Serial Assíncrona) #
	#   *'H" -> D Representa a letra Enviada (Case-sensitive)                                      #                                                      
	#                                                                                              #
	################################################################################################