void setup() 
{	//Inicializando o serial monitor
	Serial.begin(115200); // Maxima taxa de comunicação aceita pelo Raspberry 
	pinMode(13, OUTPUT); // Configura o pino d13 como saída 
}

void loop() 
{
	
	if (Serial.available()) //Se byte pronto para leitura
	{    
		switch(Serial.read()) //Verifica qual caracter recebido
		{
			case 'A': //caso 'A' 
			
			digitalWrite(13, HIGH); // Configura o pino 13 como HIGH
			
			delay(1000);  // Espera 1000 ms (1 segundo)            
			
			digitalWrite(13, LOW); // Configura o pino 13 como LOW  
			
			delay(1000); // Espera 1000 ms (1 segundo
			
			break;
			
		}
	}
	
	
}

