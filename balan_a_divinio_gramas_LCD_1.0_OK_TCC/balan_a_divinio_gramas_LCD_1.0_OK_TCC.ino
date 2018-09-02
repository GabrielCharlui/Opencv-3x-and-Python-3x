#include <HX711.h>

// HX711.DOUT  - pin #A1
// HX711.PD_SCK - pin #A0

HX711 scale(A1, A0);    // parameter "gain" is ommited; the default value 128 is used by the library

#include <LiquidCrystal.h>
/*
Pinos LCD  --> Pinos Arduino
_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
LCD pin 4 RS --> pin 8
LCD pin 6 E --> pin 7
LCD pin 11 DB4 --> pin 6
LCD pin 12 DB5 --> pin 5
LCD pin 13 DB6 --> pin 4
LCD pin 17 DB7 --> pin 3
*/
LiquidCrystal lcd(8, 7, 6, 5, 4, 3);
//LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  Serial.println("ARGUARDE INICIANDO BANLANCA");
  Serial.println("CONFIGURANDO ESCALA");
 
  /*      * * * * * * * * * * * * * 
  calibra * kg -> scale.set_scale * Multiplica
          * x ->  Resultado       * Divide
          * * * * * * * * * * * * *

  */
  //scale.set_scale(213154.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.set_scale(207701.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  Serial.println("HABILITADO PARA PESAR");
}

void loop() {
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| PESO:\t");
  Serial.println(scale.get_units(10), 3);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Peso ");
  lcd.setCursor(0,1);
  lcd.print(scale.get_units(10), 3);
  
  scale.power_down();             // put the ADC in sleep mode
  //delay();
  scale.power_up();
}
