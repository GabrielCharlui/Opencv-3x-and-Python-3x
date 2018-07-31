void setup() 
{	//Inicializando o serial monitor
	Serial.begin(115200);  // Maxima taxa de comunicação aceita pelo Raspberry
}

void loop() 
{
	//Serial.print('N')  //Printa na Serial do Arduino
	Serial.write('W'); //Escreve na Serial do Arduino enviando o caracter pela serial para Raspberry
}
