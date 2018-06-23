//Include Bibliotecas
#include <HX711.h>
#include <LiquidCrystal.h>

/*
  LCD pin 4 RS --> pin 8
  LCD pin 6 E --> pin 9
  LCD pin 11 DB4 --> pin 10
  LCD pin 12 DB5 --> pin 11
  LCD pin 13 DB6 --> pin 12
  LCD pin 17 DB7 --> pin 13
*/

//Definições pinos HX711 ligados no Arduino 

HX711 scale(2, 3);    // parameter "gain" is ommited; the default value 128 is used by the library

// HX711.DOUT  - pin #2
// HX711.PD_SCK - pin #3

//LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

//Definições pinos Arduino ligados a entrada da Ponte H

int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;

//Definições Variaveis Arduino

int leitura_A3;  //Varialvel Leitura Analogica Porta A3
int esteira=1; //Inicializa Variavel Esteira Desligada
int ajuste=1; //Inicializa Variavel Barreira Desligado
int balizador=1; //Inicializa Variavel Balizador Desligado
int livraesteira=0; //Inicializa Variavel FOR
int x=0; //Inicializa Variavel FOR
int cont=0; //Inicializa Variavel FOR
int sinal=0; //Inicializa Variavel Auxiliar de Sinal Arduino IF

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*
  * 
  * Variavel EM 1 - PARADA _ DESLIGADO
  * Variavel EM 0 - RODANDO _ LIGADO
  * 
*/

/*
  * A Incica Esteira
  * B Para Esteira
  * C Função Limão
  * D Função Laranja
  * E Aciona Balizador 
  * F Retorna Balizador
  * G Aciona Esteira Ignora Sensor
*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void setup() 
{    
  Serial.begin(115200); //Inicializando o serial monitor
  // lcd.begin(16, 2);
  pinMode(13,OUTPUT);
  
  //pinMode(LED,OUTPUT);   //configura pino do led como saída
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);  
  
  scale.set_scale(207701.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0
  
  //scale.power_down();             // put the ADC in sleep mode
  //delay();
  //scale.power_up();
  
  //Serial.println("HABILITADO PARA PESAR");
}

void loop() 
{     
  leitura_A3=analogRead(A3);        //take reading from photodiode(pin A3) :noise+signal
    
  /*//lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Peso ");
    lcd.setCursor(0,1);
    lcd.print(scale.get_units(10), 3);
    
    //scale.power_down();             // put the ADC in sleep mode
    //delay();
    //scale.power_up();
  */
  
  ledDistancia(); //Chama Função de Automatização Esteira 
}

void ledDistancia() 
{  
  if (Serial.available()) //Se byte pronto para leitura
  {    
    switch(Serial.read()) //Verifica qual caracter recebido
    {
      case 'A':                  //caso 'A' Inicia a Rodar Esteira
      esteira=0;
      break;
      
      case 'B':                  //caso 'B' Parar Esteira
      esteira=3;
      break;
      
      case 'G':                  //caso 'G' Ignora Sensor e Iniciar Esteira
      ajuste=0;
      sinal=0;
      livraesteira=0;
      break;
      
      case 'E':                  //caso 'E' Aciona Balizador
      balizador=0;
      cont=0;
      break;      
    }
  }
  
  if ((leitura_A3 > 985)&&(ajuste==1)) // Para a Esteira para Inspeção  
  {
    esteira=1;
    ///////////////////////////
    //Motor A parado
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    if (sinal==0)
    {
      Serial.write('H'); // Envia para o Raspberry _ Habilitar Visão Computacional
      sinal=1;
    }
  }
  
  else if (esteira == 0) // SERIAL A Inicia a Rodar Esteira
  { 
    /*TESTE LETRA A*/
    digitalWrite(13, HIGH);
    ///////////////////////////
    //Gira o Motor A no sentido horario
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    if (balizador == 0) // SERIAL E Aciona Balizador
    {
      for (cont; cont <= 130; cont++)
      {
        Serial.println(cont);
        if((cont>0)&&(cont<=3)) //Aciona Balizador
        {
          /*TESTE LETRA E*/
          ///*/*/*/*/*/*/*/*/*/balizador=3;
          digitalWrite(13, HIGH); 
          delay(1000);             
          digitalWrite(13, LOW);  
          delay(1000);
          ///////////////////////////
          //Gira o Motor B no sentido horario
          digitalWrite(IN3, HIGH);
          digitalWrite(IN4, LOW);
          /* Verificar se o arduino continua rodando motor A sem essa chamada de linha de codigo
            ///////////////////////////
            //Gira o Motor A no sentido horario
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
          */
        }
        if((cont>100)&&(cont<=103)) //Desaciona Balizador
        {
          /*TESTE LETRA E*/
          ///*/*/*/*/*/*/*/*/*/balizador=3;
          digitalWrite(13, HIGH); 
          delay(3000);             
          digitalWrite(13, LOW);  
          delay(3000);
          ///////////////////////////
          //Gira o Motor B no sentido anti-horario
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, HIGH);
          /* Verificar se o arduino continua rodando motor A sem essa chamada de linha de codigo
            ///////////////////////////
            //Gira o Motor A no sentido horario
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
          */
        }
      }
    }   
    else if (ajuste == 0) // SERIAL G Ignora Sensor de Barreira
    {
      for (livraesteira; livraesteira <= 500; livraesteira++)
      { Serial.println(livraesteira);
        /*TESTE LETRA G*/
        digitalWrite(13, HIGH);
        delay(10);
        digitalWrite(13, LOW); 
        delay(1000);
        ///////////////////////////
        //Gira o Motor A no sentido horario
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
      }
      ajuste=1;
    } 
  } 
  
  else if (esteira == 3)  //SERIAL B Parar Esteira
  {
    /*TESTE LETRA B*/
    digitalWrite(13, LOW); 
    ///////////////////////////
    //Motor A parado
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);   
  }
}
