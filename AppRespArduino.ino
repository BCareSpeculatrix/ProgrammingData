#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>

#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#include <LCD.h>


//Variables asociadas a los dos LEDs que se van a controlar
int led_1 = 30;
int led_2 = 32;
int led_3 = 34;

char valor;  //Variable para indicar que llega una orden
String estado;

#include <SoftwareSerial.h>


LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Establecemos el tipo de LCD


void setup() {

  pinMode(led_1, OUTPUT);
  pinMode(led_2, OUTPUT);
  pinMode(led_3, OUTPUT);
  lcd.begin(16,2);
  Serial.begin(9600);
}

void loop() {

  if (Serial.available())  //Si el puerto serie (Bluetooth) está disponible
  {
    valor = Serial.read(); //Lee el dato entrante via Bluetooth

    if (valor == 'E')  //Si el dato entrante es una E
    {
      
      pantalla_LCD();  //Llama la función que muestra el mensaje en la pantalla LCD
    }
        if (valor == 'F')  //Si el dato entrante es una F
    {
      
      pantalla_LCD();  //Llama la función que muestra el mensaje en la pantalla LCD
    }
            if (valor == 'A')  //Si el dato entrante es una F
    {
      digitalWrite(led_1, HIGH);
      digitalWrite(led_2, HIGH);
      digitalWrite(led_3, HIGH);
      pantalla_LCD();  //Llama la función que muestra el mensaje en la pantalla LCD
    }
            if (valor == 'B')  //Si el dato entrante es una F
    {
      digitalWrite(led_1, LOW);
      digitalWrite(led_2, HIGH);
      digitalWrite(led_3, LOW);
      pantalla_LCD();  //Llama la función que muestra el mensaje en la pantalla LCD
    }
            if (valor == 'C')  //Si el dato entrante es una F
    {
      digitalWrite(led_1, HIGH);
      digitalWrite(led_2, HIGH);
      digitalWrite(led_3, LOW);
      pantalla_LCD();  //Llama la función que muestra el mensaje en la pantalla LCD
    }
            if (valor == 'D')  //Si el dato entrante es una F
    {
      digitalWrite(led_1, HIGH);
      digitalWrite(led_2, LOW);
      digitalWrite(led_3, LOW);
      pantalla_LCD();  //Llama la función que muestra el mensaje en la pantalla LCD
    }
  }
}

void pantalla_LCD()
{
  delay(30);
  while (Serial.available())
  {
    char c = Serial.read();  //Lee el dato entrante y lo almacena en una variable tipo char
    estado += c;             //Crea una cadena tipo String con los datos entrates
  }
  if (estado.length() > 0)   //Se verifica que la cadena tipo String tenga un largo mayor a cero
  {
    lcd.clear();             //Borra cualquier mensaje que esté mostrando la pantalla LCD
    lcd.setCursor(0, 0);     //Posiciona el cursor en la Fila 0 y Columna 0 en la pantalla LCD
    lcd.print(estado);      //Muestra el mensaje en la pantalla LCD
    estado = "";            //Limpia la variable para posteriormente leer nuevos datos
  }
}
