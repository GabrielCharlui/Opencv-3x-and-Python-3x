//Definições pinos Arduino ligados a entrada da Ponte H

int IN1 = 5;
int IN2 = 4;
int IN3 = 3;
int IN4 = 2;


//Definições Variaveis Arduino

int leitura_A3;  //Varialvel Leitura Analogica Porta A3
int esteira = 1; //Inicializa Variavel Esteira Desligada
int ajuste = 1; //Inicializa Variavel Barreira Desligado
int balizador = 1; //Inicializa Variavel Balizador Desligado
int livraesteira = 0; //Inicializa Variavel FOR
int x = 0; //Inicializa Variavel FOR
long cont = 0; //Inicializa Variavel FOR
int sinal = 0; //Inicializa Variavel Auxiliar de Sinal Arduino IF

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
/*

    Variavel EM 1 - PARADA _ DESLIGADO
    Variavel EM 0 - RODANDO _ LIGADO

*/

/*
    A Incica Esteira
    B Para Esteira
    C Função Limão
    D Função Laranja
    E Aciona Balizador
    F Retorna Balizador
    G Aciona Esteira Ignora Sensor
*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void setup()
{
  Serial.begin(115200); //Inicializando o serial monitor
  // lcd.begin(16, 2);
  pinMode(13, OUTPUT);

  //pinMode(LED,OUTPUT);   //configura pino do led como saída
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

}

void loop()
{
  leitura_A3 = analogRead(A3);      //take reading from photodiode(pin A3) :noise+signal

  if (Serial.available()) //Se byte pronto para leitura
  {
    switch (Serial.read()) //Verifica qual caracter recebido
    {
      case 'A':                  //caso 'A' Inicia a Rodar Esteira
        esteira = 0;
        sinal = 0;
        break;

      case 'B':                  //caso 'B' Parar Esteira
        esteira = 3;
        break;

      case 'G':                  //caso 'G' Ignora Sensor e Iniciar Esteira
        ajuste = 0;
        sinal = 0;
        livraesteira = 0;
        break;

      case 'E':                  //caso 'E' Aciona Balizador
        balizador = 0;
        cont = 0;
        livraesteira = 0;
        ajuste = 0;
        break;
    }
  }
  //Serial.println(leitura_A3); // Janela para Sensor de Barreira
  if ((leitura_A3 > 960) && (ajuste == 1)) // Para a Esteira para Inspeção
  {
    esteira = 1;
    ///////////////////////////
    //Motor A parado
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    if (sinal == 0)
    {
      Serial.write('H'); // Envia para o Raspberry _ Habilitar Visão Computacional
      sinal = 1;
    }
  }

  else if (ajuste == 0) // SERIAL G Ignora Sensor de Barreira
  {
    for (livraesteira; livraesteira <= 30200; livraesteira++)
    { //Serial.println(livraesteira);
      /*TESTE LETRA G*/
      //digitalWrite(13, HIGH);
      //delay(10);
      //digitalWrite(13, LOW);
      //delay(1000);,
      ///////////////////////////
      //Gira o Motor A no sentido horario
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }
    ajuste = 1;
  }

  else if (balizador == 0) // SERIAL E Aciona Balizador
  { 
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    //Serial.println("BALIZADOR");


    /*for (livraesteira; livraesteira <= 30200; livraesteira++)
    { 
      ///////////////////////////
      //Gira o Motor A no sentido horario
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
*/
      for (cont; cont <= 290000; cont++)
    {
      //Serial.println(cont);
      if ((cont > 0) && (cont <= 30000)) //Aciona Balizador t 30000
      {
        /*TESTE LETRA E*/
        ///////////////////////////
        //Gira o Motor B no sentido horario
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        //Serial.println("ACIONADO balizador");
        /* Verificar se o arduino continua rodando motor A sem essa chamada de linha de codigo
          ///////////////////////////
          //Gira o Motor A no sentido horario
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
        */
      }

      if ((cont > 30000) && (cont <= 264990)) //Intervalo Balizador
      {
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, HIGH);
        //Serial.println("intervalo balizador");
      }

      if ((cont > 264990) && (cont <= 289990)) //Desaciona Balizador t 25000
      {
        /*TESTE LETRA E*/
        ///////////////////////////
        //Gira o Motor B no sentido anti-horario
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
        //Serial.println("DESACIONADO balizador");

        /* Verificar se o arduino continua rodando motor A sem essa chamada de linha de codigo
           ///////////////////////////
           //Gira o Motor A no sentido horario
           digitalWrite(IN1, HIGH);
           digitalWrite(IN2, LOW);
        */
      }
      if (cont > 289990)
      {
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, HIGH);
        balizador = 3;
      }

    }
   // }
        
  }

  else if (esteira == 0) // SERIAL A Inicia a Rodar Esteira
  {
    /*TESTE LETRA A*/
    ////digitalWrite(13, HIGH);
    ///////////////////////////
    //Gira o Motor A no sentido horario
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    //Serial.println("Girando Motor");
  }

  else if (esteira == 3)  //SERIAL B Parar Esteira
  {
    /*TESTE LETRA B*/
    ///digitalWrite(13, LOW);
    ///////////////////////////
    //Motor A parado
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
    //Serial.println("Parado Motor");
  }

}
