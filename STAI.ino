#include <Ultrasonic.h>

#include <SD.h>

//Configurados por defecto para la biblioteca SD en arduino MEGA
//MOSO (amarillo) = pin 50
//MOSI (azul) = pin 51
//SCLK (marron) = pin 52
//CS (verde) = pin 4

#include <SoftwareSerial.h>
#include <Wire.h>

#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>

// Declaro un nuevo puerto para la comunicación serie

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Establecemos el tipo de LCD

Ultrasonic ultrasonic (2,3);

//defino los pines para el RGB del alma

#define pinLedR_A 30 
#define pinLedG_A 32  
#define pinLedB_A 34

//Declaro variable para configurar el pin CS del módulo SD

const int CS_PIN = 4;

String mensaje;

//Variables del cuestionario: código de identificacion) -----------------------------------------------

String codigo;

// Declaro las variables del test STAIC (ESTADO)

int variableI1 = 0; //variable para "me siento calmado"
int variableI2 = 0; //variable para "me encuentro inquieto"
int variableI3 = 0; //variable para "me siento nervioso"
int variableI4 = 0; //variable para "me encuentro descansado"
int variableI5 = 0; //variable para "tengo miedo"
int variableI6 = 0; //variable para "estoy relajado"
int variableI7 = 0; //variable para "estoy preocupado"
int variableI8 = 0; //variable para "me encuentro satisfecho"
int variableI9 = 0; //variable para "me siento feliz"
int variableI10 = 0; //variable para "me siento seguro"
int variableI11 = 0; //variable para "me encuentro bien"
int variableI12 = 0; //variable para "me siento molesto"
int variableI13 = 0; //variable para "me siento agradablemente"
int variableI14 = 0; //variable para "me encuentro atemorizado"
int variableI15 = 0; //variable para "me encuentro confuso"
int variableI16 = 0; //variable para "me siento animoso"
int variableI17 = 0; //variable para "me siento angustiado"
int variableI18 = 0; //variable para "me encuentro alegre"
int variableI19 = 0; //variable para "me encuentro contrariado"
int variableI20 = 0; //variable para "me siento triste"

// Declaro las variables del test STAIC (RASGO)

int variableII1 = 0; //variable para "me preocupa cometer errores"
int variableII2 = 0; //variable para "siento ganas de llorar"
int variableII3 = 0; //variable para "me siento desgraciado"
int variableII4 = 0; //variable para "me cuesta tomar una decisión"
int variableII5 = 0; //variable para "me cuesta enfrentarme a mis problemas"
int variableII6 = 0; //variable para "me preocupo demasiado"
int variableII7 = 0; //variable para "me encuentro molesto"
int variableII8 = 0; //variable para "pensamientos sin importancia me vienen a la cabeza y me molestan"
int variableII9 = 0; //variable para "me preocupan las cosas de la escuela"
int variableII10 = 0; //variable para "me cuesta decidir en lo que tengo que hacer"
int variableII11 = 0; //variable para "noto que mi corazón late más rápido"
int variableII12 = 0; //variable para "aunque no lo digo, tengo miedo"
int variableII13 = 0; //variable para "me preocupo por las cosas que puedan ocurrir"
int variableII14 = 0; //variable para "me cuesta quedarme dormido por las noches"
int variableII15 = 0; //variable para "tengo sensaciones extrañas en el estómago"
int variableII16 = 0; //variable para "me preocupa lo que otros piensen de mi"
int variableII17 = 0; //variable para "me influyen tanto los problemas que no puedo olvidarlos durante un tiempo"
int variableII18 = 0; //variable para "tomo las cosas demasiado en serio"
int variableII19 = 0; //variable para "encuentro muchas dificultades en mi vida"
int variableII20 = 0; //variable para "me siento menos feliz que los demás chicos"

// Declaro las variables del test STAIC (SUMATORIO)

int X = 0;
int Y = 0;
int Z = 0;
int estadomomento = 0;
int estadogeneral = 0;

void PRESENTANDO1() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);

  lcd.blink();
  delay(1000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Hola, mi nombre");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("es MISKCBOT");
  delay (1000);
  lcd.noBlink();
  delay (3000);

  lcd.clear();             // Limpiar el display
  PRESENTANDO2();
}

void PRESENTANDO2() {

  lcd.blink();
  delay(1000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Me gustaria");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("saber...");
  delay (1000);
  lcd.noBlink();
  delay (3000);

  lcd.clear();             // Limpiar el display
  PRESENTANDO3();
}

void PRESENTANDO3() {

  lcd.blink();
  delay(1000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("como te");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("encuentras, y...");
  delay (1000);
  lcd.noBlink();
  delay (3000);

  lcd.clear();             // Limpiar el display
  PRESENTANDO4();
}

void PRESENTANDO4() {

  lcd.blink();
  delay(1000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("conocerte mejor");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("para...");
  delay (1000);
  lcd.noBlink();
  delay (3000);

  lcd.clear();             // Limpiar el display
  PRESENTANDO5();
}

void PRESENTANDO5() {

  lcd.blink();
  delay(1000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("cuidarte lo");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("mejor posible.");
  delay (1000);
  lcd.noBlink();
  delay (3000);

  lcd.clear();             // Limpiar el display
  CONSENTIMIENTO();
}

void CONSENTIMIENTO() {

  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Si quieres, me");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("das una caricia?");

  if (ultrasonic.Ranging(CM) < 5) {
      
      CARICIA_OK();
  }

  CONSENTIMIENTO();
}

void CARICIA_OK() {

  lcd.blink();
  delay(1000);
  lcd.clear();             // Limpiar el display

  //led verde
  digitalWrite(pinLedR_A, LOW);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, LOW);
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Gracias, cuanto");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("me alegro.");
  delay (1000);
  lcd.noBlink();
  delay (3000);

  lcd.clear();             // Limpiar el display
  abre_APP();
  
}

void abre_APP(){

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Podrias abrir la");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("APP en tu movil");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("con el nombre");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("STAIC?");
  delay(5000);
  lcd.clear();             // Limpiar el display
  codigo_usuario();
 
 }

void codigo_usuario() {

  Serial.print("Preguntando código...");
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Puedes insertar");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("un codigo...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("que me permita");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("identificarte?");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  while(Serial.available() > 0) 
  
  {
    
    char c = Serial.read();
    mensaje += c; //suma el contenido de la variable c en la variable mensaje
    codigo = mensaje;
    
    if(codigo.length() > 8) {
     
      Serial.println(codigo);
      mensaje = "";
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
 
      delay(1000);
      
      imprime_codigo();
    }

  }

  codigo_usuario();

}

void imprime_codigo(){

     //led blanco
     digitalWrite(pinLedR_A, HIGH);
     digitalWrite(pinLedG_A, HIGH);
     digitalWrite(pinLedB_A, HIGH);

     lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
     lcd.print("Usuario:");
     lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
     lcd.print(codigo);
     delay(5000);
     lcd.clear();             // Limpiar el display
     EXPLICACION_1();
  
}

void EXPLICACION_1() {

  lcd.blink();
  delay(1000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Ahora, te hare");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("preguntas por");
  delay (1000);
  lcd.noBlink();
  delay (3000);

  lcd.clear();             // Limpiar el display
  EXPLICACION_2();
  
}

void EXPLICACION_2() {

  lcd.blink();
  delay(1000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("como te sientes");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("AHORA MISMO");
  delay (1000);
  lcd.noBlink();
  delay (3000);

  lcd.clear();             // Limpiar el display
  EXPLICACION_3();
  
}

void EXPLICACION_3() {

  lcd.blink();
  delay(1000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("cuando te haga");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("la pregunta");
  delay (1000);
  lcd.noBlink();
  delay (3000);

  lcd.clear();             // Limpiar el display
  EXPLICACION_4();
  
}

void EXPLICACION_4() {

  lcd.blink();
  delay(1000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("pulsa en la");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("tablet el boton");
  delay (1000);
  lcd.noBlink();
  delay (3000);

  lcd.clear();             // Limpiar el display
  EXPLICACION_5();
  
}

void EXPLICACION_5() {

  lcd.blink();
  delay(1000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("del microfono");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("");
  delay (1000);
  lcd.noBlink();
  delay (3000);

  lcd.clear();             // Limpiar el display
  EXPLICACION_6();
  
}

void EXPLICACION_6() {

  lcd.blink();
  delay(1000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("y dime alto");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("tu respuesta:");
  delay (1000);
  lcd.noBlink();
  delay (3000);

  lcd.clear();             // Limpiar el display
  EXPLICACION_7();
  
}

void EXPLICACION_7() {

  lcd.blink();
  delay(1000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("<NADA>, <ALGO>");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("o <MUCHO>");
  delay (1000);
  lcd.noBlink();
  delay (3000);

  lcd.clear();             // Limpiar el display
  EXPLICACION_8();
  
}

void EXPLICACION_8() {

  lcd.blink();
  delay(1000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Si te encuentras");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("preparado,");
  delay (1000);
  lcd.noBlink();
  delay (3000);

  lcd.clear();             // Limpiar el display
  EXPLICACION_9();
  
}

void EXPLICACION_9() {

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("me das otra");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("caricia?");

  if (ultrasonic.Ranging(CM) < 5) {

      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      
      I1();
  }

  EXPLICACION_9();
  
}

void I1() {

  variableI1 = 0;

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te encuentras");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("calmado?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*nada")
    {
      variableI1 = 1;
      Serial.println("La puntuación <me siento calmado> es");
      Serial.println(variableI1);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000); 
      I2();
    }
    
    if(mensaje=="*algo")
    {
      variableI1 = 2;
      Serial.println("La puntuación <me siento calmado> es");
      Serial.println(variableI1);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      I2();
    }

    if(mensaje=="*mucho")
    {
      variableI1 = 3;
      Serial.println("La puntuación <me siento calmado> es:");
      Serial.println(variableI1);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I2();
    }
  
  }

  I1();
  
}

// Declaro la función para la pregunta "ME ENCUENTRO INQUIETO"

void I2() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableI2 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te encuentras");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("inquieto?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
     
  }
  if(mensaje.length()>0){
    
    if(mensaje=="*nada")
    {
      variableI2 = 1;
      Serial.println("La puntuación <me siento inquieto> es");
      Serial.println(variableI2);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I3();
    }
    
    if(mensaje=="*algo")
    {
      variableI2 = 2;
      Serial.println("La puntuación <me siento inquieto> es");
      Serial.println(variableI2);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I3();
    }

    if(mensaje=="*mucho")
    {
      variableI2 = 3;
      Serial.println("La puntuación <me siento inquieto> es");
      Serial.println(variableI2);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I3();
    }
  
  }

  I2();
  
}

// Declaro la función para la pregunta "ME SIENTO NERVIOSO"

void I3() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableI3 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te sientes");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("nervioso?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*nada")
    {
      variableI3 = 1;
      Serial.println("La puntuación <me siento nervioso> es");
      Serial.println(variableI3);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I4();
    }
    
    if(mensaje=="*algo")
    {
      variableI3 = 2;
      Serial.println("La puntuación <me siento nervioso> es");
      Serial.println(variableI3);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I4();
    }

    if(mensaje=="*mucho")
    {
      variableI3 = 3;
      Serial.println("La puntuación <me siento nervioso> es:");
      Serial.println(variableI3);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I4();
    }
  
  }

  I3();
  
}

// Declaro la función para la pregunta "ME ENCUENTRO DESCANSADO"

void I4() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableI4 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te encuentras");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("descansado?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*nada")
    {
      variableI4 = 1;
      Serial.println("La puntuación <me encuentro descansado> es");
      Serial.println(variableI4);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      I5();
    }
    
    if(mensaje=="*algo")
    {
      variableI4 = 2;
      Serial.println("La puntuación <me encuentro descansado> es");
      Serial.println(variableI4);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I5();
    }

    if(mensaje=="*mucho")
    {
      variableI4 = 3;
      Serial.println("La puntuación <me encuentro descansado> es:");
      Serial.println(variableI4);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I5();
    }
  
  }

  I4();
  
}

// Declaro la función para la pregunta "TENGO MIEDO"

void I5() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableI5 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Tienes");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("miedo?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*nada")
    {
      variableI5 = 1;
      Serial.println("La puntuación <tengo miedo> es:");
      Serial.println(variableI5);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I6();
    }
    
    if(mensaje=="*algo")
    {
      variableI5 = 2;
      Serial.println("La puntuación <tengo miedo> es:");
      Serial.println(variableI5);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I6();
    }

    if(mensaje=="*mucho")
    {
      variableI5 = 3;
      Serial.println("La puntuación <tengo miedo> es:");
      Serial.println(variableI5);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      I6();
    }
  
  }

  I5();
  
}

// Declaro la función para la pregunta "ESTOY RELAJADO"

void I6() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableI6 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Estas");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("relajado?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*nada")
    {
      variableI6 = 1;
      Serial.println("La puntuación <estoy relajado> es:");
      Serial.println(variableI6);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      I7();
    }
    
    if(mensaje=="*algo")
    {
      variableI6 = 2;
      Serial.println("La puntuación <estoy relajado> es:");
      Serial.println(variableI6);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I7();
    }

    if(mensaje=="*mucho")
    {
      variableI6 = 3;
      Serial.println("La puntuación <estoy relajado> es:");
      Serial.println(variableI6);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I7();
    }
  
  }

  I6();
  
}

// Declaro la función para la pregunta "ESTOY PREOCUPADO"

void I7() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableI7 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Estas");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("preocupado?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*nada")
    {
      variableI7 = 1;
      Serial.println("La puntuación <estoy preocupado> es:");
      Serial.println(variableI7);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I8();
    }
    
    if(mensaje=="*algo")
    {
      variableI7 = 2;
      Serial.println("La puntuación <estoy preocupado> es:");
      Serial.println(variableI7);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I8();
    }

    if(mensaje=="*mucho")
    {
      variableI7 = 3;
      Serial.println("La puntuación <estoy preocupado> es:");
      Serial.println(variableI7);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      I8();
    }
  
  }

  I7();
  
}

// Declaro la función para la pregunta "ME ENCUENTRO SATISFECHO"

void I8() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableI8 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te encuentras");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("satisfecho?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*nada")
    {
      variableI8 = 1;
      Serial.println("La puntuación <me encuentro satisfecho> es:");
      Serial.println(variableI8);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      I9();
    }
    
    if(mensaje=="*algo")
    {
      variableI8 = 2;
      Serial.println("La puntuación <me encuentro satisfecho> es:");
      Serial.println(variableI8);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I9();
    }

    if(mensaje=="*mucho")
    {
      variableI8 = 3;
      Serial.println("La puntuación <me encuentro satisfecho> es:");
      Serial.println(variableI8);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I9();
    }
 
  }

  I8();
  
}

// Declaro la función para la pregunta "ME SIENTO FELIZ"

void I9() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableI9 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te sientes");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("feliz?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*nada")
    {
      variableI9 = 1;
      Serial.println("La puntuación <me siento feliz> es:");
      Serial.println(variableI9);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      I10();
    }
    
    if(mensaje=="*algo")
    {
      variableI9 = 2;
      Serial.println("La puntuación <me siento feliz> es:");
      Serial.println(variableI9);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I10();
    }

    if(mensaje=="*mucho")
    {
      variableI9 = 3;
      Serial.println("La puntuación <me siento feliz> es:");
      Serial.println(variableI9);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I10();
    }
  
  }

  I9();
  
}

// Declaro la función para la pregunta "ME SIENTO SEGURO"

void I10() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableI10 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te sientes");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("seguro?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*nada")
    {
      variableI10 = 1;
      Serial.println("La puntuación <me siento seguro> es:");
      Serial.println(variableI10);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      I11();
    }
    
    if(mensaje=="*algo")
    {
      variableI10 = 2;
      Serial.println("La puntuación <me siento seguro> es:");
      Serial.println(variableI10);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I11();
    }

    if(mensaje=="*mucho")
    {
      variableI10 = 3;
      Serial.println("La puntuación <me siento seguro> es:");
      Serial.println(variableI10);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I11();
    }
  
  }

  I10();
  
}

// Declaro la función para la pregunta "ME ENCUENTRO BIEN"

void I11() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableI11 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te encuentras");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("bien?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*nada")
    {
      variableI11 = 1;
      Serial.println("La puntuación <me encuentro bien> es:");
      Serial.println(variableI11);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      I12();
    }
    
    if(mensaje=="*algo")
    {
      variableI11 = 2;
      Serial.println("La puntuación <me encuentro bien> es:");
      Serial.println(variableI11);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I12();
    }

    if(mensaje=="*mucho")
    {
      variableI11 = 3;
      Serial.println("La puntuación <me encuentro bien> es:");
      Serial.println(variableI11);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I12();
    }
  
  }

  I11();
  
}

// Declaro la función para la pregunta "ME SIENTO MOLESTO"

void I12() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableI12 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te sientes");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("molesto?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*nada")
    {
      variableI12 = 1;
      Serial.println("La puntuación <me siento molesto> es:");
      Serial.println(variableI12);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I13();
    }
    
    if(mensaje=="*algo")
    {
      variableI12 = 2;
      Serial.println("La puntuación <me siento molesto> es:");
      Serial.println(variableI12);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I13();
    }

    if(mensaje=="*mucho")
    {
      variableI12 = 3;
      Serial.println("La puntuación <me siento molesto> es:");
      Serial.println(variableI12);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      I13();
    }
 
  }

  I12();
  
}

// Declaro la función para la pregunta "ME SIENTO AGRADABLEMENTE"

void I13() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableI13 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te sientes");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("agradablemente?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*nada")
    {
      variableI13 = 1;
      Serial.println("La puntuación <me siento agradablemente> es:");
      Serial.println(variableI13);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      I14();
    }
    
    if(mensaje=="*algo")
    {
      variableI13 = 2;
      Serial.println("La puntuación <me siento agradablemente> es:");
      Serial.println(variableI13);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I14();
    }

    if(mensaje=="*mucho")
    {
      variableI13 = 3;
      Serial.println("La puntuación <me siento agradablemente> es:");
      Serial.println(variableI13);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I14();
    }
 
  }

  I13();
  
}

// Declaro la función para la pregunta "ME ENCUENTRO ATEMORIZADO"

void I14() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableI14 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te encuentras");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("atemorizado?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*nada")
    {
      variableI14 = 1;
      Serial.println("La puntuación <me encuentro atemorizado> es:");
      Serial.println(variableI14);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I15();
    }
    
    if(mensaje=="*algo")
    {
      variableI14 = 2;
      Serial.println("La puntuación <me encuentro atemorizado> es:");
      Serial.println(variableI14);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I15();
    }

    if(mensaje=="*mucho")
    {
      variableI14 = 3;
      Serial.println("La puntuación <me encuentro atemorizado> es:");
      Serial.println(variableI14);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      I15();
    }

  }

  I14();
  
}

// Declaro la función para la pregunta "ME ENCUENTRO CONFUSO"

void I15() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableI15 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te encuentras");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("confuso?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*nada")
    {
      variableI15 = 1;
      Serial.println("La puntuación <me encuentro confuso> es:");
      Serial.println(variableI15);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I16();
    }
    
    if(mensaje=="*algo")
    {
      variableI15 = 2;
      Serial.println("La puntuación <me encuentro confuso> es:");
      Serial.println(variableI15);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I16();
    }

    if(mensaje=="*mucho")
    {
      variableI15 = 3;
      Serial.println("La puntuación <me encuentro confuso> es:");
      Serial.println(variableI15);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      I16();
    }
  
  }

  I15();
  
}

// Declaro la función para la pregunta "ME SIENTO ANIMOSO"

void I16() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableI16 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te sientes");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("con animo?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*nada")
    {
      variableI16 = 1;
      Serial.println("La puntuación <me siento con animo> es:");
      Serial.println(variableI16);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      I17();
    }
    
    if(mensaje=="*algo")
    {
      variableI16 = 2;
      Serial.println("La puntuación <me siento con animo> es:");
      Serial.println(variableI16);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I17();
    }

    if(mensaje=="*mucho")
    {
      variableI16 = 3;
      Serial.println("La puntuación <me siento con animo> es:");
      Serial.println(variableI16);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I17();
    }
  
  }

  I16();
  
}

// Declaro la función para la pregunta "ME SIENTO ANGUSTIADO"

void I17() {
  
  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableI17 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te sientes");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("angustiado?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*nada")
    {
      variableI17 = 1;
      Serial.println("La puntuación <me siento angustiado> es:");
      Serial.println(variableI17);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I18();
    }
    
    if(mensaje=="*algo")
    {
      variableI17 = 2;
      Serial.println("La puntuación <me siento angustiado> es:");
      Serial.println(variableI17);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I18();
    }

    if(mensaje=="*mucho")
    {
      variableI17 = 3;
      Serial.println("La puntuación <me siento angustiado> es:");
      Serial.println(variableI17);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      I18();
    }
  
  }

  I17();
  
}

// Declaro la función para la pregunta "ME ENCUENTRO ALEGRE"

void I18() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableI18 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te encuentras");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("alegre?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*nada")
    {
      variableI18 = 1;
      Serial.println("La puntuación <me encuentro alegre> es:");
      Serial.println(variableI18);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      I19();
    }
    
    if(mensaje=="*algo")
    {
      variableI18 = 2;
      Serial.println("La puntuación <me encuentro alegre> es:");
      Serial.println(variableI18);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I19();
    }

    if(mensaje=="*mucho")
    {
      variableI18 = 3;
      Serial.println("La puntuación <me encuentro alegre> es:");
      Serial.println(variableI18);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I19();
    }
  
  }

  I18();
  
}

// Declaro la función para la pregunta "ME ENCUENTRO CONTRARIADO"

void I19() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableI19 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te encuentras");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("contrariado?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*nada")
    {
      variableI19 = 1;
      Serial.println("La puntuación <me encuentro contrariado> es:");
      Serial.println(variableI19);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I20();
    }
    
    if(mensaje=="*algo")
    {
      variableI19 = 2;
      Serial.println("La puntuación <me encuentro contrariado> es:");
      Serial.println(variableI19);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      I20();
    }

    if(mensaje=="*mucho")
    {
      variableI19 = 3;
      Serial.println("La puntuación <me encuentro contrariado> es:");
      Serial.println(variableI19);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      I20();
    }
  
  }

  I19();
  
}

// Declaro la función para la pregunta "ME SIENTO TRISTE"

void I20() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableI20 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te sientes");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("triste?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*nada")
    {
      variableI20 = 1;
      Serial.println("La puntuación <me siento triste> es:");
      Serial.println(variableI20);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      SUMATORIO_AHORA_MISMO();
    }
    
    if(mensaje=="*algo")
    {
      variableI20 = 2;
      Serial.println("La puntuación <me siento triste> es:");
      Serial.println(variableI20);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      SUMATORIO_AHORA_MISMO();
    }

    if(mensaje=="*mucho")
    {
      variableI20 = 3;
      Serial.println("La puntuación <me siento triste> es:");
      Serial.println(variableI20);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      SUMATORIO_AHORA_MISMO();
    }
  
  }

  I20();
  
}

void SUMATORIO_AHORA_MISMO() {

  X = variableI2 + variableI3 + variableI5 + variableI7 + variableI12 + variableI14 + variableI15 + variableI17 + variableI19 + variableI20;
  Y = variableI1 + variableI4 + variableI6 + variableI8 + variableI9 + variableI10 + variableI11 + variableI13 + variableI16 + variableI18;
  estadomomento = (X - Y) + 40;
  
  Serial.println("La puntuación de la ansiedad-estado en este momento es:");
  Serial.print(estadomomento);
  Serial.println("");
  
  delay(1000);

  if(estadomomento < 24)
    {
      Serial.println("Por lo que el nivel de Ansiedad-Estado es: BAJO");
      delay(1000);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);

      lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
      lcd.print("Que bien, tu");
      lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
      lcd.print("nivel de...");
      delay(5000);
      lcd.clear();             // Limpiar el display

      lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
      lcd.print("ansiedad actual");
      lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
      lcd.print("es bajo");
      delay(5000);
      lcd.clear();             // Limpiar el display
      
      EXPLICACION_10();
    }
  
  if(estadomomento >= 24 && estadomomento <= 38)
    {
      Serial.println("Por lo que el nivel de Ansiedad-Estado es: MEDIO");
      delay(1000);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);

      lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
      lcd.print("Parece que tu");
      lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
      lcd.print("nivel de...");
      delay(5000);
      lcd.clear();             // Limpiar el display

      lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
      lcd.print("ansiedad actual");
      lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
      lcd.print("es medio");
      delay(5000);
      lcd.clear();             // Limpiar el display
      
      EXPLICACION_10();
    }

   if(estadomomento > 38)
    {
      Serial.println("Por lo que el nivel de Ansiedad-Estado es: ALTO");
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);

      lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
      lcd.print("Vaya, por lo");
      lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
      lcd.print("que veo...");
      delay(5000);
      lcd.clear();             // Limpiar el display

      lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
      lcd.print("deberias tomarte");
      lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
      lcd.print("un respiro...");
      delay(5000);
      lcd.clear();             // Limpiar el display

      lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
      lcd.print("porque tienes");
      lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
      lcd.print("un nivel de...");
      delay(5000);
      lcd.clear();             // Limpiar el display

      lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
      lcd.print("ansiedad alto");
      lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
      lcd.print("");
      delay(5000);
      lcd.clear();             // Limpiar el display
      
      EXPLICACION_10();
    }
  
}

void EXPLICACION_10() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);
  
  lcd.blink();
  delay(1000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Ahora, me podrias");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("responder a unas");
  delay (1000);
  lcd.noBlink();
  delay (3000);

  lcd.clear();             // Limpiar el display
  EXPLICACION_11();
  
}

void EXPLICACION_11() {
  
  lcd.blink();
  delay(1000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("preguntas por");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("como te sientes");
  delay (1000);
  lcd.noBlink();
  delay (3000);

  lcd.clear();             // Limpiar el display
  EXPLICACION_12();
  
}

void EXPLICACION_12() {
  
  lcd.blink();
  delay(1000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("EN GENERAL");
  delay (1000);
  lcd.noBlink();
  delay (3000);

  lcd.clear();             // Limpiar el display
  EXPLICACION_13();
  
}

void EXPLICACION_13() {
  
  lcd.blink();
  delay(1000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Necesito que");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("respondas:");
  delay(1000);
  lcd.noBlink();
  delay (3000);

  lcd.clear();             // Limpiar el display
  EXPLICACION_14();
  
}

void EXPLICACION_14() {
  
  lcd.blink();
  delay(1000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("<CASI NUNCA>");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("<ALGO> o");
  delay(1000);
  lcd.noBlink();
  delay (3000);

  lcd.clear();             // Limpiar el display
  EXPLICACION_15();
  
}

void EXPLICACION_15() {
  
  lcd.blink();
  delay(1000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("<A MENUDO>");
  delay(1000);
  lcd.noBlink();
  delay (3000);

  lcd.clear();             // Limpiar el display
  CONSENTIMIENTO_2();
  
}

void CONSENTIMIENTO_2() {

  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Estas preparado?");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("Me acaricias?");

  if (ultrasonic.Ranging(CM) < 5) {
      
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II1();
      
  }

  CONSENTIMIENTO_2();
}

// Declaro la función para la pregunta "ME PREOCUPA COMETER ERRORES"

void II1() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableII1 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te preocupa");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("cometer errores?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*casi nunca")
    {
      variableII1 = 1;
      Serial.println("La puntuación <me preocupa cometer errores> es");
      Serial.println(variableII1);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II2();
    }
    
    if(mensaje=="*algo")
    {
      variableII1 = 2;
      Serial.println("La puntuación <me preocupa cometer errores> es");
      Serial.println(variableII1);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II2();
    }

    if(mensaje=="*a menudo")
    {
      variableII1 = 3;
      Serial.println("La puntuación <me preocupa cometer errores> es:");
      Serial.println(variableII1);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      II2();
    }
  
  }

  II1();
  
}

// Declaro la función para la pregunta "SIENTO GANAS DE LLORAR"

void II2() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableII2 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Sientes ganas");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("de llorar?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
     
  }
  if(mensaje.length()>0){
    
    if(mensaje=="*casi nunca")
    {
      variableII2 = 1;
      Serial.println("La puntuación <siento ganas de llorar> es");
      Serial.println(variableII2);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II3();
    }
    
    if(mensaje=="*algo")
    {
      variableII2 = 2;
      Serial.println("La puntuación <siento ganas de llorar> es");
      Serial.println(variableII2);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II3();
    }

    if(mensaje=="*a menudo")
    {
      variableII2 = 3;
      Serial.println("La puntuación <siento ganas de llorar> es");
      Serial.println(variableII2);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      II3();
    }
  
  }

  II2();
  
}

// Declaro la función para la pregunta "ME SIENTO DESGRACIADO"

void II3() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableII3 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te sientes");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("desgraciado?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*casi nunca")
    {
      variableII3 = 1;
      Serial.println("La puntuación <me siento desgraciado> es");
      Serial.println(variableII3);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II4();
    }
    
    if(mensaje=="*algo")
    {
      variableII3 = 2;
      Serial.println("La puntuación <me siento desgraciado> es");
      Serial.println(variableII3);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II4();
    }

    if(mensaje=="*a menudo")
    {
      variableII3 = 3;
      Serial.println("La puntuación <me siento desgraciado> es:");
      Serial.println(variableII3);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      II4();
    }
  
  }

  II3();
  
}

// Declaro la función para la pregunta "ME CUESTA TOMAR UNA DECISIÓN"

void II4() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableII4 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te cuesta tomar");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("una decision?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    
    if(mensaje=="*casi nunca")
    {
      variableII4 = 1;
      Serial.println("La puntuación <me cuesta tomar una decisión> es");
      Serial.println(variableII4);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II5();
    }
    
    if(mensaje=="*algo")
    {
      variableII4 = 2;
      Serial.println("La puntuación <me cuesta tomar una decisión> es");
      Serial.println(variableII4);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II5();
    }

    if(mensaje=="*a menudo")
    {
      variableII4 = 3;
      Serial.println("La puntuación <me cuesta tomar una decisión> es:");
      Serial.println(variableII4);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      II5();
    }
  
  }

  II4();
  
}

// Declaro la función para la pregunta "ME CUESTA ENFRENTARME A MIS PROBLEMAS"

void II5() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableII5 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te cuesta");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("enfrentarte a");
  delay(5000);
  lcd.clear();             // Limpiar el display
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("tus problemas?");
  delay(3500);
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*casi nunca")
    {
      variableII5 = 1;
      Serial.println("La puntuación <me cuesta enfrentarme a mis problemas> es:");
      Serial.println(variableII5);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II6();
    }
    
    if(mensaje=="*algo")
    {
      variableII5 = 2;
      Serial.println("La puntuación <me cuesta enfrentarme a mis problemas> es:");
      Serial.println(variableII5);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II6();
    }

    if(mensaje=="*a menudo")
    {
      variableII5 = 3;
      Serial.println("La puntuación <me cuesta enfrentarme a mis problemas> es:");
      Serial.println(variableII5);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      II6();
    }
  
  }

  II5();
  
}

// Declaro la función para la pregunta "ME PREOCUPO DEMASIADO"

void II6() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableII6 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te preocupas");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("demasiado?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*casi nunca")
    {
      variableII6 = 1;
      Serial.println("La puntuación <me preocupo demasiado> es:");
      Serial.println(variableII6);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II7();
    }
    
    if(mensaje=="*algo")
    {
      variableII6 = 2;
      Serial.println("La puntuación <me preocupo demasiado> es:");
      Serial.println(variableII6);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II7();
    }

    if(mensaje=="*a menudo")
    {
      variableII6 = 3;
      Serial.println("La puntuación <me preocupo demasiado> es:");
      Serial.println(variableII6);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      II7();
    }
  
  }

  II6();
  
}

// Declaro la función para la pregunta "ME ENCUENTRO MOLESTO"

void II7() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableII7 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te encuentras");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("molesto?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*casi nunca")
    {
      variableII7 = 1;
      Serial.println("La puntuación <me encuentro molesto> es:");
      Serial.println(variableII7);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II8();
    }
    
    if(mensaje=="*algo")
    {
      variableII7 = 2;
      Serial.println("La puntuación <me encuentro molesto> es:");
      Serial.println(variableII7);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II8();
    }

    if(mensaje=="*mucho")
    {
      variableII7 = 3;
      Serial.println("La puntuación <me encuentro molesto> es:");
      Serial.println(variableII7);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      II8();
    }
  
  }

  II7();
  
}

// Declaro la función para la pregunta "PENSAMIENTOS SIN IMPORTANCIA ME VIENEN A LA CABEZA Y ME MOLESTAN"

void II8() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableII8 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te vienen a la");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("cabeza...");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("pensamientos sin");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("importancia y...");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("te molestan?");
  delay(5000);
  lcd.clear();             // Limpiar el display

  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*casi nunca")
    {
      variableII8 = 1;
      Serial.println("La puntuación <pensamientos sin importancia me vienen a la cabeza y me molestan> es:");
      Serial.println(variableII8);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II9();
    }
    
    if(mensaje=="*algo")
    {
      variableII8 = 2;
      Serial.println("La puntuación <pensamientos sin importancia me vienen a la cabeza y me molestan> es:");
      Serial.println(variableII8);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II9();
    }

    if(mensaje=="*a menudo")
    {
      variableII8 = 3;
      Serial.println("La puntuación <pensamientos sin importancia me vienen a la cabeza y me molestan> es:");
      Serial.println(variableII8);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      II9();
    }
 
  }

  II8();
  
}

// Declaro la función para la pregunta "ME PREOCUPAN LAS COSAS DE LA ESCUELA"

void II9() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableII9 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te preocupan las");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("cosas del cole?");
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*casi nunca")
    {
      variableII9 = 1;
      Serial.println("La puntuación <me preocupan las cosas de la escuela> es:");
      Serial.println(variableII9);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II10();
    }
    
    if(mensaje=="*algo")
    {
      variableII9 = 2;
      Serial.println("La puntuación <me preocupan las cosas de la escuela> es:");
      Serial.println(variableII9);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II10();
    }

    if(mensaje=="*a menudo")
    {
      variableII9 = 3;
      Serial.println("La puntuación <me preocupan las cosas de la escuela> es:");
      Serial.println(variableII9);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      II10();
    }
  
  }

  II9();
  
}

// Declaro la función para la pregunta "ME CUESTA DECIDIR EN LO QUE TENGO QUE HACER"

void II10() {
  
  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableII10 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te cuesta");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("decidir en...");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("lo que tienes");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("que hacer?");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*casi nunca")
    {
      variableII10 = 1;
      Serial.println("La puntuación <me cuesta decidir en lo que tengo que hacer> es:");
      Serial.println(variableII10);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II11();
    }
    
    if(mensaje=="*algo")
    {
      variableII10 = 2;
      Serial.println("La puntuación <me cuesta decidir en lo que tengo que hacer> es:");
      Serial.println(variableII10);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II11();
    }

    if(mensaje=="*a menudo")
    {
      variableII10 = 3;
      Serial.println("La puntuación <me cuesta decidir en lo que tengo que hacer> es:");
      Serial.println(variableII10);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      II11();
    }
  
  }

  II10();
  
}

// Declaro la función para la pregunta "NOTO QUE MI CORAZÓN LATE MÁS RÁPIDO"

void II11() {
  
  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableII11 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Notas que el");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("corazon te...");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("late mas");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("rapido");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*casi nunca")
    {
      variableII11 = 1;
      Serial.println("La puntuación <noto que mi corazon late mas rapido> es:");
      Serial.println(variableII11);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II12();
    }
    
    if(mensaje=="*algo")
    {
      variableII11 = 2;
      Serial.println("La puntuación <noto que mi corazon late mas rapido> es:");
      Serial.println(variableII11);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II12();
    }

    if(mensaje=="*a menudo")
    {
      variableI11 = 3;
      Serial.println("La puntuación <noto que mi corazon late mas rapido> es:");
      Serial.println(variableII11);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      II12();
    }
  
  }

  II11();
  
}

// Declaro la función para la pregunta "AUNQUE NO LO DIGO, TENGO MIEDO"

void II12() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableII12 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Aunque no lo");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("digas...");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("tienes");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("miedo?");
  delay(5000);
  lcd.clear();             // Limpiar el display;
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*casi nunca")
    {
      variableII12 = 1;
      Serial.println("La puntuación <aunque no lo digo, tengo miedo> es:");
      Serial.println(variableII12);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II13();
    }
    
    if(mensaje=="*algo")
    {
      variableII12 = 2;
      Serial.println("La puntuación <aunque no lo digo, tengo miedo> es:");
      Serial.println(variableII12);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II13();
    }

    if(mensaje=="*a menudo")
    {
      variableII12 = 3;
      Serial.println("La puntuación <aunque no lo digo, tengo miedo> es:");
      Serial.println(variableII12);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      II13();
    }
 
  }

  II12();
  
}

// Declaro la función para la pregunta "ME PREOCUPO POR LAS COSAS QUE PUEDAN OCURRIR"

void II13() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableII13 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te preocupas por");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("las cosas que...");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("puedan");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("ocurrir?");
  delay(5000);
  lcd.clear();             // Limpiar el display;
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*casi nunca")
    {
      variableII13 = 1;
      Serial.println("La puntuación <me preocupo por las cosas que puedan ocurrir> es:");
      Serial.println(variableII13);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II14();
    }
    
    if(mensaje=="*algo")
    {
      variableII13 = 2;
      Serial.println("La puntuación <me preocupo por las cosas que puedan ocurrir> es:");
      Serial.println(variableII13);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II14();
    }

    if(mensaje=="*a menudo")
    {
      variableII13 = 3;
      Serial.println("La puntuación <me preocupo por las cosas que puedan ocurrir> es:");
      Serial.println(variableII13);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      II14();
    }
 
  }

  II13();
  
}

// Declaro la función para la pregunta "ME CUESTA QUEDARME DORMIDO POR LAS NOCHES"

void II14() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableII14 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te cuesta");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("quedarte...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("dormido por");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("las noches?");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*casi nunca")
    {
      variableII14 = 1;
      Serial.println("La puntuación <me cuesta quedarme dormido por las noches> es:");
      Serial.println(variableII14);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II15();
    }
    
    if(mensaje=="*algo")
    {
      variableII14 = 2;
      Serial.println("La puntuación <me cuesta quedarme dormido por las noches> es:");
      Serial.println(variableII14);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II15();
    }

    if(mensaje=="*mucho")
    {
      variableII14 = 3;
      Serial.println("La puntuación <me cuesta quedarme dormido por las noches> es:");
      Serial.println(variableII14);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      II15();
    }

  }

  II14();
  
}

// Declaro la función para la pregunta "ME ENCUENTRO CONFUSO"

void II15() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableII15 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Tienes");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("sensaciones...");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("raras en");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("el estomago?");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*casi nunca")
    {
      variableII15 = 1;
      Serial.println("La puntuación <tengo sensaciones extrañas en el estomago> es:");
      Serial.println(variableII15);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II16();
    }
    
    if(mensaje=="*algo")
    {
      variableII15 = 2;
      Serial.println("La puntuación <tengo sensaciones extrañas en el estomago> es:");
      Serial.println(variableII15);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II16();
    }

    if(mensaje=="*mucho")
    {
      variableII15 = 3;
      Serial.println("La puntuación <tengo sensaciones extrañas en el estomago> es:");
      Serial.println(variableII15);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      II16();
    }
  
  }

  II15();
  
}

// Declaro la función para la pregunta "ME PREOCUPA LO QUE OTROS PIENSEN DE MI"

void II16() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableII16 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te preocupa lo");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("que otros...");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("piensen de");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("ti?");
  delay(5000);
  lcd.clear();             // Limpiar el display

  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*casi nunca")
    {
      variableII16 = 1;
      Serial.println("La puntuación <me preocupa lo que otros piensen de mi> es:");
      Serial.println(variableII16);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II17();
    }
    
    if(mensaje=="*algo")
    {
      variableII16 = 2;
      Serial.println("La puntuación <me preocupa lo que otros piensen de mi> es:");
      Serial.println(variableII16);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II17();
    }

    if(mensaje=="*a menudo")
    {
      variableII16 = 3;
      Serial.println("La puntuación <me preocupa lo que otros piensen de mi> es:");
      Serial.println(variableII16);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      II17();
    }
  
  }

  II16();
  
}

// Declaro la función para la pregunta "ME INFLUYEN TANTO LOS PROBLEMAS QUE NO PUEDO OLVIDARLOS DURANTE UN TIEMPO"

void II17() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableII17 = 0;

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te influyen");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("tanto los...");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("problemas que no");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("puedes...");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("olvidarlos");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("durante un...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("tiempo?");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*casi nunca")
    {
      variableII17 = 1;
      Serial.println("La puntuación <me influyen tanto los problemas que no puedo olvidarlos durante un tiempo> es:");
      Serial.println(variableII17);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II18();
    }
    
    if(mensaje=="*algo")
    {
      variableII17 = 2;
      Serial.println("La puntuación <me influyen tanto los problemas que no puedo olvidarlos durante un tiempo> es:");
      Serial.println(variableII17);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II18();
    }

    if(mensaje=="*a menudo")
    {
      variableII17 = 3;
      Serial.println("La puntuación <me influyen tanto los problemas que no puedo olvidarlos durante un tiempo> es:");
      Serial.println(variableII17);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      II18();
    }
  
  }

  II17();
  
}

// Declaro la función para la pregunta "TOMO LAS COSAS DEMASIADO EN SERIO"

void II18() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableII18 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te tomas");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("las cosas...");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("demasiado en");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("serio?");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*casi nunca")
    {
      variableII18 = 1;
      Serial.println("La puntuación <me encuentro alegre> es:");
      Serial.println(variableII18);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II19();
    }
    
    if(mensaje=="*algo")
    {
      variableII18 = 2;
      Serial.println("La puntuación <me encuentro alegre> es:");
      Serial.println(variableII18);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II19();
    }

    if(mensaje=="*a menudo")
    {
      variableII18 = 3;
      Serial.println("La puntuación <me encuentro alegre> es:");
      Serial.println(variableII18);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      II19();
    }
  
  }

  II18();
  
}

// Declaro la función para la pregunta "ENCUENTRO MUCHAS DIFICULTADES EN MI VIDA"

void II19() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableII19 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Encuentras");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("muchas...");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("dificultades en");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("tu vida?");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*casi nunca")
    {
      variableII19 = 1;
      Serial.println("La puntuación <encuentro muchas dificultades en mi vida> es:");
      Serial.println(variableII19);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II20();
    }
    
    if(mensaje=="*algo")
    {
      variableII19 = 2;
      Serial.println("La puntuación <me encuentro contrariado> es:");
      Serial.println(variableII19);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      II20();
    }

    if(mensaje=="*a menudo")
    {
      variableII19 = 3;
      Serial.println("La puntuación <me encuentro contrariado> es:");
      Serial.println(variableII19);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      II20();
    }
  
  }

  II19();
  
}

// Declaro la función para la pregunta "ME SIENTO TRISTE"

void II20() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);

  variableII20 = 0;
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te siente menos");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("feliz que los...");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("demas");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("chicos?");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  while(Serial.available()>0) {
    delay(10); //da estabilidad
    char c = Serial.read();
    mensaje += c; // suma el contenido de la variable c en la variable mensaje
   
  }
  if(mensaje.length()>0){
    if(mensaje=="*casi nunca")
    {
      variableII20 = 1;
      Serial.println("La puntuación <me siento triste> es:");
      Serial.println(variableII20);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      SUMATORIO_EN_GENERAL();
    }
    
    if(mensaje=="*algo")
    {
      variableII20 = 2;
      Serial.println("La puntuación <me siento triste> es:");
      Serial.println(variableII20);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      SUMATORIO_EN_GENERAL();
    }

    if(mensaje=="*a menudo")
    {
      variableII20 = 3;
      Serial.println("La puntuación <me siento triste> es:");
      Serial.println(variableII20);
      mensaje=""; //resetea variable
      lcd.clear();             // Limpiar el display
      delay(100);
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);      
      SUMATORIO_EN_GENERAL();
    }
  
  }

  II20();
  
}

void SUMATORIO_EN_GENERAL() {

  Z = variableII1 + variableII2 + variableII3 + variableII4 + variableII5 + variableII6 + variableII7 + variableII8 + variableII9 + variableII10 + variableII11 + variableII12 + variableII13 + variableII14 + variableII15 + variableII16 + variableII17 + variableII18 + variableII19 + variableII20;
  
  estadogeneral = Z;
  
  Serial.println("La puntuación de la ansiedad-rasgo es:");
  Serial.print(estadogeneral);
  Serial.println("");
  
  delay(1000);

  if(estadogeneral < 29)
    {
      Serial.println("Por lo que el nivel de Ansiedad-Rasgo es: BAJO");
      delay(1000);
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
      
      lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
      lcd.print("Que bien, ");
      lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
      lcd.print("parece que...");
      delay(5000);
      lcd.clear();             // Limpiar el display

      lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
      lcd.print("tu rasgo");
      lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
      lcd.print("personal de...");
      delay(5000);
      lcd.clear();             // Limpiar el display

      lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
      lcd.print("ansiedad es por");
      lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
      lcd.print("lo general...");
      delay(5000);
      lcd.clear();             // Limpiar el display

      lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
      lcd.print("de un nivel");
      lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
      lcd.print("bajo");
      delay(5000);
      lcd.clear();             // Limpiar el display
      
      guardaSD();
    }
  
  if(estadogeneral >= 29 && estadogeneral <= 41)
    {
      Serial.println("Por lo que el nivel de Ansiedad-Rasgo es: MEDIO");
      delay(1000);
      
      //led amarillo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);

      lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
      lcd.print("Segun tus");
      lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
      lcd.print("respuestas...");
      delay(5000);
      lcd.clear();             // Limpiar el display

      lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
      lcd.print("tu rasgo");
      lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
      lcd.print("personal de...");
      delay(5000);
      lcd.clear();             // Limpiar el display

      lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
      lcd.print("ansiedad es por");
      lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
      lcd.print("lo general...");
      delay(5000);
      lcd.clear();             // Limpiar el display

      lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
      lcd.print("de un nivel");
      lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
      lcd.print("medio");
      delay(5000);
      lcd.clear();             // Limpiar el display
      
      guardaSD();
    }

   if(estadogeneral > 41)
    {
      Serial.println("Por lo que el nivel de Ansiedad-Rasgo es: ALTO");
      delay(1000);
      
      //led rojo
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, LOW);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);

      lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
      lcd.print("Vaya, parece");
      lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
      lcd.print("que...");
      delay(5000);
      lcd.clear();             // Limpiar el display

      lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
      lcd.print("tu rasgo");
      lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
      lcd.print("personal de...");
      delay(5000);
      lcd.clear();             // Limpiar el display

      lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
      lcd.print("ansiedad es por");
      lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
      lcd.print("lo general...");
      delay(5000);
      lcd.clear();             // Limpiar el display

      lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
      lcd.print("de un nivel");
      lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
      lcd.print("alto");
      delay(5000);
      lcd.clear();             // Limpiar el display
            
      guardaSD();
    }
  
}

void guardaSD(){

Serial.begin(9600);
 
  //Abre un archivo para escribir en él las variables y el resultado del cuestionario Downton
  File datafile = SD.open("STAIC.csv", FILE_WRITE);
  
  if (datafile) {
    Serial.println("Abriendo archivo STAIC, escribiendo resultados del cuestionario");

    datafile.println("");
    datafile.print(codigo);
    datafile.print(",");
    datafile.print(variableI1);
    datafile.print(",");
    datafile.print(variableI2);
    datafile.print(",");
    datafile.print(variableI3);
    datafile.print(",");
    datafile.print(variableI4);
    datafile.print(",");
    datafile.print(variableI5);
    datafile.print(",");
    datafile.print(variableI6);
    datafile.print(",");
    datafile.print(variableI7);
    datafile.print(",");
    datafile.print(variableI8);
    datafile.print(",");
    datafile.print(variableI9);
    datafile.print(",");
    datafile.print(variableI10);
    datafile.print(",");
    datafile.print(variableI11);
    datafile.print(",");
    datafile.print(variableI12);
    datafile.print(",");
    datafile.print(variableI13);
    datafile.print(",");
    datafile.print(variableI14);
    datafile.print(",");
    datafile.print(variableI15);
    datafile.print(",");
    datafile.print(variableI16);
    datafile.print(",");
    datafile.print(variableI17);
    datafile.print(",");
    datafile.print(variableI18);
    datafile.print(",");
    datafile.print(variableI19);
    datafile.print(",");
    datafile.print(variableI20);
    datafile.print(",");
    datafile.print(variableII1);
    datafile.print(",");
    datafile.print(variableII2);
    datafile.print(",");
    datafile.print(variableII3);
    datafile.print(",");
    datafile.print(variableII4);
    datafile.print(",");
    datafile.print(variableII5);
    datafile.print(",");
    datafile.print(variableII6);
    datafile.print(",");
    datafile.print(variableII7);
    datafile.print(",");
    datafile.print(variableII8);
    datafile.print(",");
    datafile.print(variableII9);
    datafile.print(",");
    datafile.print(variableII10);
    datafile.print(",");
    datafile.print(variableII11);
    datafile.print(",");
    datafile.print(variableII12);
    datafile.print(",");
    datafile.print(variableII13);
    datafile.print(",");
    datafile.print(variableII14);
    datafile.print(",");
    datafile.print(variableII15);
    datafile.print(",");
    datafile.print(variableII16);
    datafile.print(",");
    datafile.print(variableII17);
    datafile.print(",");
    datafile.print(variableII18);
    datafile.print(",");
    datafile.print(variableII19);
    datafile.print(",");
    datafile.print(variableII20);
    datafile.print(",");
    datafile.print(estadomomento);
    datafile.print(",");
    datafile.print(estadogeneral);
    
    datafile.close(); //cerramos el archivo

    Serial.println("Datos guardados en SD");

    lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
    lcd.print("Datos guerdados");
    lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
    lcd.print("en SD");
    delay(5000);
    lcd.clear();             // Limpiar el display
    
  } else {
         //si el archivo no se abre, muestra mensaje de error:
    Serial.println("Error al abrir el archivo");
    guardaSD();
  }
  delay(100);

  FIN_TEST();
 
}

void FIN_TEST() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  delay(1000);
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Muchas gracias");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("por contarme...");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("oo                                   ccccczmo te sientes.");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("Puedes volver...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("a contar conmigo");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("cuando quieras.");
  delay(5000);
  lcd.clear();             // Limpiar el display

  FIN_TEST();
}


void setup() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  
  Serial.begin(9600);
  Serial.print("Iniciando SD ...");
  if (!SD.begin(CS_PIN)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");
  
  pinMode(13,OUTPUT);

  lcd.begin(16,2);         // Iniciar el Display de 16 caracter por 2 lineas
  
  PRESENTANDO1();
  
}

void loop() {
  
  
}
