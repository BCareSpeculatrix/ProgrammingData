#include <SD.h>

//Configurados por defecto para la biblioteca SD en arduino MEGA
//MOSO (amarillo) = pin 50
//MOSI (azul) = pin 51
//SCLK (marron) = pin 52
//CS (verde) = pin 4

#include <SoftwareSerial.h>
#include <Wire.h>


//Declaro las variables para el control de la matriz lcd----------------

#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>


LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Establecemos el tipo de LCD

//defino los pines para el RGB del alma

#define pinLedR_A 30 
#define pinLedG_A 32  
#define pinLedB_A 34


//Declaro variable para configurar el pin CS del módulo SD

const int CS_PIN = 4;

//variables en el ejemplo de codigo------------------------

SoftwareSerial mySerial(18, 19); //RX, TX

//Declaro variables para comunicar algunos de los resultados e caa respuesta via bluetooth

String mensaje;
String fecha;
long fecha_long;
char estado = "";

//Variables del cuestionario FBC (incluyendo código de identificacion) -----------------------------------------------

String codigo;

//-----------------

long edad;
String etapa;
float AgAc_edad;
float v_edad;

//-----------------

String genero;
float AgAc_genero;
float v_genero;

//-----------------

String estado_desarrollo;
float AgAc_estado_desarrollo;
float v_estado_desarrollo;

//-----------------

String cultura;
float AgAc_cultura;
float v_cultura;

//-----------------

String familia;
float AgAc_familia;
float v_familia;

//-----------------

String limitacion_movilidad;
float AgAc_limitacion_movilidad;
float v_limitacion_movilidad;

//-----------------

String limitacion_cognitiva;
float AgAc_limitacion_cognitiva;
float v_limitacion_cognitiva;

//-----------------

String limitacion_sensorial;
float AgAc_limitacion_sensorial;
float v_limitacion_sensorial;

//-----------------

String sistema_cuidados;
float AgAc_sistema_cuidados;
float v_sistema_cuidados;

//------------------

String ambiente;
float AgAc_ambiente;
float v_ambiente;

//-----------------

String recursos;
float AgAc_recursos;
float v_recursos;

//-----------------

String tiempo;
float AgAc_tiempo;
float v_tiempo;

//-----------------


void codigo_usuario() {

  Serial.print("Preguntando código...");

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  
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
     tutorial();
  
}

void tutorial() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Mira el tutorial");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("en la pantalla");
  delay(5000);
  lcd.clear();             // Limpiar el display

  while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '1' ){

       //led verde
       digitalWrite(pinLedR_A, LOW);
       digitalWrite(pinLedG_A, HIGH);
       digitalWrite(pinLedB_A, LOW);
  
       Serial.println("");
       Serial.println("Tutorial leído");
       Serial.println("");
       estado = "";
       delay(1000);
       pregunta_fecha_nacimiento();
 }

tutorial();
  
}

void pregunta_fecha_nacimiento() {

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("En que ano");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("naciste?");
  delay(5000);
  lcd.clear();             // Limpiar el display


while(Serial.available() > 0) 
  
  {
    char c = Serial.read();
    mensaje += c; //suma el contenido de la variable c en la variable mensaje
    fecha = mensaje;
    
    if(fecha.length() > 3) {

      mensaje = "";
      
      //led verde
      digitalWrite(pinLedR_A, LOW);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, LOW);
      delay(1000);
     
      imprime_fecha();
    }
    

  }

  pregunta_fecha_nacimiento();
  
}


void imprime_fecha(){

     #define DEBUG(a)  Serial.println(a);
     
     Serial.println("La fecha de nacimieto es:");
     Serial.println(fecha);

     fecha_long = fecha.toInt();
     DEBUG(fecha_long);

     pregunta_cumple();
  
}

void pregunta_cumple(){

  estado = "";

  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Has celebrado");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("tu cumple?");
  delay(5000);
  lcd.clear();             // Limpiar el display


  while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){

   edad = 2018 - fecha_long - 1;
  
   //led verde
   digitalWrite(pinLedR_A, LOW);
   digitalWrite(pinLedG_A, HIGH);
   digitalWrite(pinLedB_A, LOW);
   delay(1000);
   
   calculos_edad();
       
 }
 
 if(estado == '1'){
        
   edad = 2018 - fecha_long;
   
   //led verde
   digitalWrite(pinLedR_A, LOW);
   digitalWrite(pinLedG_A, HIGH);
   digitalWrite(pinLedB_A, LOW);
   delay(1000);
   
   calculos_edad();
       
 }

  pregunta_cumple();
  
}

void calculos_edad(){

  if(edad <= 7)
 
  {
    AgAc_edad = 0;
    v_edad = 1 - AgAc_edad;
    etapa = "infancia";

    //led rojo
    digitalWrite(pinLedR_A, HIGH);
    digitalWrite(pinLedG_A, LOW);
    digitalWrite(pinLedB_A, LOW);
    
  }

  if(edad > 7 && edad <= 14)
  
  {
    AgAc_edad = 0.5;
    v_edad = 1 - AgAc_edad;
    etapa = "adolescencia temprana";

    //led amarillo
    digitalWrite(pinLedR_A, HIGH);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);
    
  }

  if(edad > 14 && edad <= 75)
  
  {
    AgAc_edad = 1;
    v_edad = 1 - AgAc_edad;
    etapa = "adolescencia y madurez";
    
    //led verde
    digitalWrite(pinLedR_A, LOW);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);
    
  }

  if(edad > 75 && edad <= 85)
  
  {
    AgAc_edad = 0.5;
    v_edad = 1 - AgAc_edad;
    etapa = "anciano";

    //led amarillo
    digitalWrite(pinLedR_A, HIGH);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);
    
  }

  if(edad > 85)
  
  {
    AgAc_edad = 0;
    v_edad = 1 - AgAc_edad;
    etapa = "alto longevo";

    //led rojo
    digitalWrite(pinLedR_A, HIGH);
    digitalWrite(pinLedG_A, LOW);
    digitalWrite(pinLedB_A, LOW);
    
  }

    Serial.println("");
    Serial.println("La edad del usuario ");
    Serial.print(codigo);
    Serial.print(" es de ");
    Serial.print(edad);
    Serial.print(" años");
    Serial.println("");
    Serial.println("La AgAc para el FBC Edad =");
    Serial.print(AgAc_edad);
    Serial.println("");
    Serial.println("La vulnerabilidad para el FBC Edad =");
    Serial.println(v_edad);

    delay(1000);

    pregunta_genero();
  
}

void pregunta_genero(){

  estado = "";

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Como consideras");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("que es tu...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("genero?:");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("A: limitador, o");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("B: favorable");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print(" ");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){

   genero = "limitador";
   AgAc_genero = 0.5;
   v_genero = 1 - AgAc_genero;
  
   //led amarillo
    digitalWrite(pinLedR_A, HIGH);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("El genero del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(genero);
    Serial.println("");
    Serial.println("La AgAc para el FBC Genero =");
    Serial.print(AgAc_genero);
    Serial.println("");
    Serial.println("La vulnerabilidad para el FBC Genero =");
    Serial.println(v_genero);

    delay(1000);

    pregunta_estado_desarrollo();
    
 }
 
 if(estado == '1'){
        
   genero = "indiferente o favorable";
   AgAc_genero = 1;
   v_genero = 1 - AgAc_genero;

    //led verde
    digitalWrite(pinLedR_A, LOW);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("El genero del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(genero);
    Serial.println("");
    Serial.println("La AgAc para el FBC Genero =");
    Serial.print(AgAc_genero);
    Serial.println("");
    Serial.println("La vulnerabilidad para el FBC Genero =");
    Serial.println(v_genero);

    delay(1000);

    pregunta_estado_desarrollo();  
       
 }

    pregunta_genero();
  
}

void pregunta_estado_desarrollo(){

    estado = "";

 //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Como consideras");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("que es tu...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("estado de");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("desarrollo?...");
  delay(5000);
  lcd.clear();             // Limpiar el display;


  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("A: Regresivo,");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("B: Estancado, o");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("C: Adecuado");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){

   estado_desarrollo = "regresivo";
   AgAc_estado_desarrollo = 0;
   v_estado_desarrollo = 1 - AgAc_estado_desarrollo;

   //led rojo
   digitalWrite(pinLedR_A, HIGH);
   digitalWrite(pinLedG_A, HIGH);
   digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("El estado de desarrollo del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(estado_desarrollo);
    Serial.println("");
    Serial.println("La AgAc para el FBC Estado de desarrollo =");
    Serial.print(AgAc_estado_desarrollo);
    Serial.println("");
    Serial.println("La vulnerabilidad para el FBC Estado de desarrollo =");
    Serial.println(v_estado_desarrollo);

   delay(1000);
   pregunta_cultura();
  
       
 }
 
 if(estado == '1'){
        
   estado_desarrollo = "estancado";
   AgAc_estado_desarrollo = 0.5;
   v_estado_desarrollo = 1 - AgAc_estado_desarrollo;

    //led amarillo
    digitalWrite(pinLedR_A, HIGH);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);   

    Serial.println("");
    Serial.println("El estado de desarrollo del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(estado_desarrollo);
    Serial.println("");
    Serial.println("La AgAc para el FBC Estado de desarrollo =");
    Serial.print(AgAc_estado_desarrollo);
    Serial.println("");
    Serial.println("La vulnerabilidad para el FBC Estado de desarrollo =");
    Serial.println(v_estado_desarrollo);

    delay(1000);
    pregunta_cultura();
  
    
 }

 if(estado == '2'){
        
   estado_desarrollo = "adecuado";
   AgAc_estado_desarrollo = 1;
   v_estado_desarrollo = 1 - AgAc_estado_desarrollo;

    //led verde
    digitalWrite(pinLedR_A, LOW);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("El estado de desarrollo del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(estado_desarrollo);
    Serial.println("");
    Serial.println("La AgAc para el FBC Estado de desarrollo =");
    Serial.print(AgAc_estado_desarrollo);
    Serial.println("");
    Serial.println("La vulnerabilidad para el FBC Estado de desarrollo =");
    Serial.println(v_estado_desarrollo);

    delay(1000);
    pregunta_cultura();
    

 }

    pregunta_estado_desarrollo();
  
}

void pregunta_cultura(){

    estado = "";


 //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te sientes");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("integrado...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("culturalmente?");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("A: Aculturado,");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("B: En proceso, o");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("C: Enculturado");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){

   cultura = "aculturado";
   AgAc_cultura = 0;
   v_cultura = 1 - AgAc_cultura;

   //led rojo
   digitalWrite(pinLedR_A, HIGH);
   digitalWrite(pinLedG_A, HIGH);
   digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("La orientación sociocultural hacia el cuidado del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(cultura);
    Serial.println("");
    Serial.println("La AgAc para el FBC Orientación sociocultural hacia el cuidado =");
    Serial.print(AgAc_cultura);
    Serial.println("");
    Serial.println("La vulnerabilidad para el FBC Orientación sociocultural hacia el cuidado =");
    Serial.println(v_cultura);

   delay(1000);
   pregunta_sistema_familiar();
       
 }
 
 if(estado == '1'){
        
   cultura = "en proceso";
   AgAc_cultura = 0.5;
   v_cultura = 1 - AgAc_cultura;

    //led amarillo
    digitalWrite(pinLedR_A, HIGH);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("La orientación sociocultural hacia el cuidado del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(cultura);
    Serial.println("");
    Serial.println("La AgAc para el FBC Orientación sociocultural hacia el cuidado =");
    Serial.print(AgAc_cultura);
    Serial.println("");
    Serial.println("La vulnerabilidad para el FBC Orientación sociocultural hacia el cuidado =");
    Serial.println(v_cultura);

    delay(1000);
    pregunta_sistema_familiar();
       
 }

 if(estado == '2'){
        
   cultura = "enculturado";
   AgAc_cultura = 1;
   v_cultura = 1 - AgAc_cultura;

    //led verde
    digitalWrite(pinLedR_A, LOW);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("La orientación sociocultural hacia el cuidado del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(cultura);
    Serial.println("");
    Serial.println("La AgAc para el FBC Orientación sociocultural hacia el cuidado =");
    Serial.print(AgAc_cultura);
    Serial.println("");
    Serial.println("La vulnerabilidad para el FBC Orientación sociocultural hacia el cuidado =");
    Serial.println(v_cultura);

    delay(1000);
    pregunta_sistema_familiar();
       
 }

    pregunta_cultura();
  
}

void pregunta_sistema_familiar(){

    estado = "";

 //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Como consideras");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("que te cuida...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("tu familia?");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("A: Nunca,");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("B: A veces, o");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("C: Siempre");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){

   //led rojo
   digitalWrite(pinLedR_A, HIGH);
   digitalWrite(pinLedG_A, HIGH);
   digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("El sistema familiar de apoyo del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(familia);
    Serial.println("");
    Serial.println("La AgAc para el FBC Sistema familiar de apoyo =");
    Serial.print(AgAc_familia);
    Serial.println("");
    Serial.println("La vulnerabilidad para el FBC Sistema familiar de apoyo =");
    Serial.println(v_familia);

   delay(1000);
 
   familia = "sin apoyo familiar";
   AgAc_familia = 0;
   v_familia = 1 - AgAc_familia;

   pregunta_limitacion_movilidad();
 }
 
 if(estado == '1'){
        
   familia = "apoyo familiar parcial (ante determinadas situaciones";
   AgAc_familia = 0.5;
   v_familia = 1 - AgAc_familia;

    //led amarillo
    digitalWrite(pinLedR_A, HIGH);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("El sistema familiar de apoyo del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(familia);
    Serial.println("");
    Serial.println("La AgAc para el FBC Sistema familiar de apoyo =");
    Serial.print(AgAc_familia);
    Serial.println("");
    Serial.println("La vulnerabilidad para el FBC Sistema familiar de apoyo =");
    Serial.println(v_familia);

    delay(1000);
    pregunta_limitacion_movilidad();   
 }

 if(estado == '2'){
        
   familia = "apoyo familiar integrado";
   AgAc_familia = 1;
   v_familia = 1 - AgAc_familia;

   //led verde
   digitalWrite(pinLedR_A, LOW);
   digitalWrite(pinLedG_A, HIGH);
   digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("El sistema familiar de apoyo del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(familia);
    Serial.println("");
    Serial.println("La AgAc para el FBC Sistema familiar de apoyo =");
    Serial.print(AgAc_familia);
    Serial.println("");
    Serial.println("La vulnerabilidad para el FBC Sistema familiar de apoyo =");
    Serial.println(v_familia);

   delay(1000);   
   pregunta_limitacion_movilidad();    
 }

    pregunta_sistema_familiar();
  
}

void pregunta_limitacion_movilidad(){

    estado = "";

 //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Tiene algun");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("problema motor?");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("A: Si, total,");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("B:Si, compensada");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("C: No, ninguna");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){

   //led rojo
   digitalWrite(pinLedR_A, HIGH);
   digitalWrite(pinLedG_A, HIGH);
   digitalWrite(pinLedB_A, LOW);

   delay(1000);
 
   limitacion_movilidad = "totalmente inmovilizado";
   AgAc_limitacion_movilidad = 0;
   v_limitacion_movilidad = 1 - AgAc_limitacion_movilidad;

    Serial.println("");
    Serial.println("La funcion de movilidad del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(limitacion_movilidad);
    Serial.println("");
    Serial.println("La AgAc para el FBC Función de movilidad =");
    Serial.print(AgAc_limitacion_movilidad);
    Serial.println("");
    Serial.println("La vulnerabilidad para el FBC Función de movilidad =");
    Serial.println(v_limitacion_movilidad);

    pregunta_limitacion_cognitiva();
       
 }
 
 if(estado == '1'){
        
   limitacion_movilidad = "parcialmente inmoviliado";
   AgAc_limitacion_movilidad = 0.5;
   v_limitacion_movilidad = 1 - AgAc_limitacion_movilidad;

    //led amarillo
    digitalWrite(pinLedR_A, HIGH);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("La funcion de movilidad del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(limitacion_movilidad);
    Serial.println("");
    Serial.println("La AgAc para el FBC Función de movilidad =");
    Serial.print(AgAc_limitacion_movilidad);
    Serial.println("");
    Serial.println("La vulnerabilidad para el FBC Función de movilidad =");
    Serial.println(v_limitacion_movilidad);

    delay(1000);
     pregunta_limitacion_cognitiva();
       
 }

 if(estado == '2'){
        
   limitacion_movilidad = "sin limitacion en la movilidad";
   AgAc_limitacion_movilidad = 1;
   v_limitacion_movilidad = 1 - AgAc_limitacion_movilidad;

    //led verde
    digitalWrite(pinLedR_A, LOW);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("La funcion de movilidad del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(limitacion_movilidad);
    Serial.println("");
    Serial.println("La AgAc para el FBC Función de movilidad =");
    Serial.print(AgAc_limitacion_movilidad);
    Serial.println("");
    Serial.println("La vulnerabilidad para el FBC Función de movilidad =");
    Serial.println(v_limitacion_movilidad);

    delay(1000);
     pregunta_limitacion_cognitiva();
       
 }

    pregunta_limitacion_movilidad();
  
}

void pregunta_limitacion_cognitiva(){

    estado = "";

 //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Tiene limitacion");
  lcd.setCursor(0,1);// "Imprimimos el texto en el display LCD
  lcd.print("cognitiva?");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("A: Si, total");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("B: Si, parcial o");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("C: No ninguna");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){

   //led rojo
   digitalWrite(pinLedR_A, HIGH);
   digitalWrite(pinLedG_A, HIGH);
   digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("La funcion cognitiva del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(limitacion_cognitiva);
    Serial.println("");
    Serial.println("La AgAc para el FBC Función cognitiva =");
    Serial.print(AgAc_limitacion_cognitiva);
    Serial.println("");
    Serial.println("La vulnerabilidad en funcion del FBC Función cognitiva =");
    Serial.println(v_limitacion_cognitiva);

   delay(1000);


   limitacion_cognitiva = "inconsciente o incapaz de emitir juicios de situacion";
   AgAc_limitacion_cognitiva = 0;
   v_limitacion_cognitiva = 1 - AgAc_limitacion_cognitiva;

   pregunta_limitacion_sensorial();
   
 }
 
 if(estado == '1'){
        
   limitacion_cognitiva = "limitacion cognitiva parcial: inadecuacion o inconstancia de juicios de situacion";
   AgAc_limitacion_cognitiva = 0.5;
   v_limitacion_cognitiva = 1 - AgAc_limitacion_cognitiva;

    //led amarillo
    digitalWrite(pinLedR_A, HIGH);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("La funcion cognitiva del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(limitacion_cognitiva);
    Serial.println("");
    Serial.println("La AgAc para el FBC Función cognitiva =");
    Serial.print(AgAc_limitacion_cognitiva);
    Serial.println("");
    Serial.println("La vulnerabilidad en funcion del FBC Función cognitiva =");
    Serial.println(v_limitacion_cognitiva);

    delay(1000);
    pregunta_limitacion_sensorial();
       
 }

 if(estado == '2'){
        
   limitacion_cognitiva = "sin limitacion cognitiva";
   AgAc_limitacion_cognitiva = 1;
   v_limitacion_cognitiva = 1 - AgAc_limitacion_cognitiva;

    //led verde
    digitalWrite(pinLedR_A, LOW);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("La funcion cognitiva del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(limitacion_cognitiva);
    Serial.println("");
    Serial.println("La AgAc para el FBC Función cognitiva =");
    Serial.print(AgAc_limitacion_cognitiva);
    Serial.println("");
    Serial.println("La vulnerabilidad en funcion del FBC Función cognitiva =");
    Serial.println(v_limitacion_cognitiva);

    delay(1000);
    pregunta_limitacion_sensorial();   
       
 }

    pregunta_limitacion_cognitiva();
  
}

void pregunta_limitacion_sensorial(){

    estado = "";

 //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Tiene limitacion");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("sensorial?");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("A: Si, total");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("B: Si, parcial o");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("C: No, ninguna");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){

   limitacion_sensorial = "aislamiento sensorial del entorno";
   AgAc_limitacion_sensorial = 0;
   v_limitacion_sensorial = 1 - AgAc_limitacion_sensorial;

   //led rojo
   digitalWrite(pinLedR_A, HIGH);
   digitalWrite(pinLedG_A, HIGH);
   digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("La funcion sensorial del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(limitacion_sensorial);
    Serial.println("");
    Serial.println("La AgAc para el FBC Función sensorial =");
    Serial.print(AgAc_limitacion_sensorial);
    Serial.println("");
    Serial.println("La vulnerabilidad en funcion del FBC Función sensorial =");
    Serial.println(v_limitacion_sensorial);

   delay(1000);
   pregunta_sistema_cuidados();
     
 }
 
 if(estado == '1'){
        
   limitacion_sensorial = "aislamiento parcial del entorno, no compensado";
   AgAc_limitacion_sensorial = 0.5;
   v_limitacion_sensorial = 1 - AgAc_limitacion_sensorial;

    //led amarillo
    digitalWrite(pinLedR_A, HIGH);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("La funcion sensorial del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(limitacion_sensorial);
    Serial.println("");
    Serial.println("La AgAc para el FBC Función sensorial =");
    Serial.print(AgAc_limitacion_sensorial);
    Serial.println("");
    Serial.println("La vulnerabilidad en funcion del FBC Función sensorial =");
    Serial.println(v_limitacion_sensorial);

    delay(1000);
    pregunta_sistema_cuidados();
       
 }

 if(estado == '2'){
        
   limitacion_sensorial = "sin limitacion sensorial o con aislamiento parcial del entorno compensado";
   AgAc_limitacion_sensorial = 1;
   v_limitacion_sensorial = 1 - AgAc_limitacion_sensorial;

    //led verde
    digitalWrite(pinLedR_A, LOW);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("La funcion sensorial del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(limitacion_sensorial);
    Serial.println("");
    Serial.println("La AgAc para el FBC Función sensorial =");
    Serial.print(AgAc_limitacion_sensorial);
    Serial.println("");
    Serial.println("La vulnerabilidad en funcion del FBC Función sensorial =");
    Serial.println(v_limitacion_sensorial);

    delay(1000);
    pregunta_sistema_cuidados();   
       
 }


    pregunta_limitacion_sensorial();
  
}

void pregunta_sistema_cuidados(){

    estado = "";

 //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Como te");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("cuidas?");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("A: Nunca,");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("B: A veces, o");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("C: Siempre");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){

   sistema_cuidados = "indiferente a cuidados de salud";
   AgAc_sistema_cuidados = 0;
   v_sistema_cuidados = 1 - AgAc_sistema_cuidados;

   //led rojo
   digitalWrite(pinLedR_A, HIGH);
   digitalWrite(pinLedG_A, HIGH);
   digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("Los factores del sistema de cuidado de la salud del usuario ");
    Serial.print(codigo);
    Serial.print(" son ");
    Serial.print(sistema_cuidados);
    Serial.println("");
    Serial.println("La AgAc para el FBC Sistema de cuidado de la salud =");
    Serial.print(AgAc_sistema_cuidados);
    Serial.println("");
    Serial.println("La vulnerabilidad en funcion del FBC Sistema de cuidado de la salud =");
    Serial.println(v_sistema_cuidados);

   delay(1000);
   pregunta_ambiente();
      
 }
 
 if(estado == '1'){
        
   sistema_cuidados = "realizacion de cuidados solo ante las alteraciones de salud";
   AgAc_sistema_cuidados = 0.5;
   v_sistema_cuidados = 1 - AgAc_sistema_cuidados;

    //led amarillo
    digitalWrite(pinLedR_A, HIGH);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("Los factores del sistema de cuidado de la salud del usuario ");
    Serial.print(codigo);
    Serial.print(" son ");
    Serial.print(sistema_cuidados);
    Serial.println("");
    Serial.println("La AgAc para el FBC Sistema de cuidado de la salud =");
    Serial.print(AgAc_sistema_cuidados);
    Serial.println("");
    Serial.println("La vulnerabilidad en funcion del FBC Sistema de cuidado de la salud =");
    Serial.println(v_sistema_cuidados);

    delay(1000);
    pregunta_ambiente();
       
 }

 if(estado == '2'){
        
   sistema_cuidados = "cuidados de salud integrales";
   AgAc_sistema_cuidados = 1;
   v_sistema_cuidados = 1 - AgAc_sistema_cuidados;

    //led verde
    digitalWrite(pinLedR_A, LOW);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("Los factores del sistema de cuidado de la salud del usuario ");
    Serial.print(codigo);
    Serial.print(" son ");
    Serial.print(sistema_cuidados);
    Serial.println("");
    Serial.println("La AgAc para el FBC Sistema de cuidado de la salud =");
    Serial.print(AgAc_sistema_cuidados);
    Serial.println("");
    Serial.println("La vulnerabilidad en funcion del FBC Sistema de cuidado de la salud =");
    Serial.println(v_sistema_cuidados);

    delay(1000);
    pregunta_ambiente();
       
 }

    pregunta_sistema_cuidados();
  
}

void pregunta_ambiente(){

    estado = "";

 //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("El entorno");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("apoya tu cuidado");
  delay(5000);
  lcd.clear();             // Limpiar el display


  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("A: No");
  lcd.setCursor(0,1);      // El cursor en la columna 0 y la fila 0
  lcd.print("B: te entorpece");
  delay(5000);
  lcd.clear();
  
  lcd.setCursor(0,0);// Imprimimos el texto en el display LCD
  lcd.print("C: Si");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){

   ambiente = "incompatibles con el cuidado";
   AgAc_ambiente = 0;
   v_ambiente = 1 - AgAc_ambiente;

   //led rojo
   digitalWrite(pinLedR_A, HIGH);
   digitalWrite(pinLedG_A, HIGH);
   digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("Los factores ambientales del usuario ");
    Serial.print(codigo);
    Serial.print(" son ");
    Serial.print(ambiente);
    Serial.println("");
    Serial.println("La AgAc para el FBC Factores ambientales =");
    Serial.print(AgAc_ambiente);
    Serial.println("");
    Serial.println("La vulnerabilidad en funcion del FBC Factores ambientales =");
    Serial.println(v_ambiente);

   delay(1000);
   pregunta_recursos();
   
 }
 
 if(estado == '1'){
        
   ambiente = "entorpecedores del cuidado";
   AgAc_ambiente = 0.5;
   v_ambiente = 1 - AgAc_ambiente;

    //led amarillo
    digitalWrite(pinLedR_A, HIGH);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("Los factores ambientales del usuario ");
    Serial.print(codigo);
    Serial.print(" son ");
    Serial.print(ambiente);
    Serial.println("");
    Serial.println("La AgAc para el FBC Factores ambientales =");
    Serial.print(AgAc_ambiente);
    Serial.println("");
    Serial.println("La vulnerabilidad en funcion del FBC Factores ambientales =");
    Serial.println(v_ambiente);

    delay(1000);
    pregunta_recursos();
       
 }

 if(estado == '2'){
        
   ambiente = "favorecedores del cuidado";
   AgAc_ambiente = 1;
   v_ambiente = 1 - AgAc_ambiente;

    //led verde
    digitalWrite(pinLedR_A, LOW);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("Los factores ambientales del usuario ");
    Serial.print(codigo);
    Serial.print(" son ");
    Serial.print(ambiente);
    Serial.println("");
    Serial.println("La AgAc para el FBC Factores ambientales =");
    Serial.print(AgAc_ambiente);
    Serial.println("");
    Serial.println("La vulnerabilidad en funcion del FBC Factores ambientales =");
    Serial.println(v_ambiente);

    delay(1000);
    pregunta_recursos();   
       
 }

    pregunta_ambiente();
  
}

void pregunta_recursos(){

    estado = "";

 //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Tienes recursos");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("para cuidarte?");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("A: No");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("B: Necesito mas");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("C: Si");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){

   recursos = "disponibilidad imposible";
   AgAc_recursos = 0;
   v_recursos = 1 - AgAc_recursos;

   //led rojo
   digitalWrite(pinLedR_A, HIGH);
   digitalWrite(pinLedG_A, HIGH);
   digitalWrite(pinLedB_A, LOW);

   delay(1000);

    Serial.println("");
    Serial.println("La disponibilidad y adecuación de recursos del usuario ");
    Serial.print(codigo);
    Serial.print(" son ");
    Serial.print(recursos);
    Serial.println("");
    Serial.println("La AgAc para el FBC Disponibilidad y adecuación de recursos =");
    Serial.print(AgAc_recursos);
    Serial.println("");
    Serial.println("La vulnerabilidad en funcion del FBC Disponibilidad y adecuación de recursos =");
    Serial.println(v_recursos);
   
   pregunta_tiempo();

 }
 
 if(estado == '1'){
        
   recursos = "se requiere de busqueda";
   AgAc_recursos = 0.5;
   v_recursos = 1 - AgAc_recursos;

    //led amarillo
    digitalWrite(pinLedR_A, HIGH);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);

    delay(1000);

    Serial.println("");
    Serial.println("La disponibilidad y adecuación de recursos del usuario ");
    Serial.print(codigo);
    Serial.print(" son ");
    Serial.print(recursos);
    Serial.println("");
    Serial.println("La AgAc para el FBC Disponibilidad y adecuación de recursos =");
    Serial.print(AgAc_recursos);
    Serial.println("");
    Serial.println("La vulnerabilidad en funcion del FBC Disponibilidad y adecuación de recursos =");
    Serial.println(v_recursos);

    pregunta_tiempo();
       
 }

 if(estado == '2'){
        
   recursos = "adecuados";
   AgAc_recursos = 1;
   v_recursos = 1 - AgAc_recursos;

   //led verde
   digitalWrite(pinLedR_A, LOW);
   digitalWrite(pinLedG_A, HIGH);
   digitalWrite(pinLedB_A, LOW);

   delay(1000);

    Serial.println("");
    Serial.println("La disponibilidad y adecuación de recursos del usuario ");
    Serial.print(codigo);
    Serial.print(" son ");
    Serial.print(recursos);
    Serial.println("");
    Serial.println("La AgAc para el FBC Disponibilidad y adecuación de recursos =");
    Serial.print(AgAc_recursos);
    Serial.println("");
    Serial.println("La vulnerabilidad en funcion del FBC Disponibilidad y adecuación de recursos =");
    Serial.println(v_recursos);
    
   pregunta_tiempo();
       
 }

   pregunta_recursos();
  
}

void pregunta_tiempo(){

   estado = "";

 //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Tienes tiempo");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("para cuidarte?");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("A: No");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("B: Necesito mas");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("C: Si");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("");
  delay(5000);
  lcd.clear();             // Limpiar el display;

  while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){

   tiempo = "disponibilidad imposible";
   AgAc_tiempo = 0;
   v_tiempo = 1 - AgAc_tiempo;

   //led rojo
   digitalWrite(pinLedR_A, HIGH);
   digitalWrite(pinLedG_A, HIGH);
   digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("La disponibilidad y adecuación de tiempo del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(tiempo);
    Serial.println("");
    Serial.println("La AgAc para el FBC Disponibilidad y adecuación de tiempo =");
    Serial.print(AgAc_tiempo);
    Serial.println("");
    Serial.println("La vulnerabilidad en funcion del FBC Disponibilidad y adecuación de tiempo =");
    Serial.println(v_tiempo);

   delay(1000);
   fin_test();   
       
 }
 
 if(estado == '1'){
        
   tiempo = "se requiere de busqueda";
   AgAc_tiempo = 0.5;
   v_tiempo = 1 - AgAc_tiempo;

   //led amarillo
   digitalWrite(pinLedR_A, HIGH);
   digitalWrite(pinLedG_A, HIGH);
   digitalWrite(pinLedB_A, LOW); 

    Serial.println("");
    Serial.println("La disponibilidad y adecuación de tiempo del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(tiempo);
    Serial.println("");
    Serial.println("La AgAc para el FBC Disponibilidad y adecuación de tiempo =");
    Serial.print(AgAc_tiempo);
    Serial.println("");
    Serial.println("La vulnerabilidad en funcion del FBC Disponibilidad y adecuación de tiempo =");
    Serial.println(v_tiempo);

   delay(1000);
   fin_test();
       
 }

 if(estado == '2'){
        
   tiempo = "adecuados";
   AgAc_tiempo = 1;
   v_tiempo = 1 - AgAc_tiempo;

    //led verde
    digitalWrite(pinLedR_A, LOW);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);

    Serial.println("");
    Serial.println("La disponibilidad y adecuación de tiempo del usuario ");
    Serial.print(codigo);
    Serial.print(" es ");
    Serial.print(tiempo);
    Serial.println("");
    Serial.println("La AgAc para el FBC Disponibilidad y adecuación de tiempo =");
    Serial.print(AgAc_tiempo);
    Serial.println("");
    Serial.println("La vulnerabilidad en funcion del FBC Disponibilidad y adecuación de tiempo =");
    Serial.println(v_tiempo);

    delay(1000);
    fin_test();
       
 }

    pregunta_tiempo();
  
}

void fin_test(){

 //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Muchas gracias,");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("ya te conozco");
  delay(5000);
  lcd.clear();  

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("mas. Asi he");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("evaluado tu");
  delay(5000);
  lcd.clear();

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("nivel de");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("cuidados y");
  delay(5000);
  lcd.clear();

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("vulnerabilidad.");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("Sus datos seran");
  delay(5000);
  lcd.clear();

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("guardados en mi");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("memoria");
  delay(5000);
  lcd.clear();


  guardaSD();
  
}

void guardaSD(){

Serial.begin(9600);
 
  //Abre un archivo para escribir en él las variables y el resultado del cuestionario Downton
  File datafile = SD.open("FBC.csv", FILE_WRITE);
  
  if (datafile) {
    Serial.println("Abriendo archivo FBC, escribiendo resultados del cuestionario");

    datafile.println("");
    datafile.print(codigo);
    datafile.print(",");
    datafile.print(edad);
    datafile.print(",");
    datafile.print(etapa);
    datafile.print(",");
    datafile.print(AgAc_edad);
    datafile.print(",");
    datafile.print(v_edad);
    datafile.print(",");
    datafile.print(genero);
    datafile.print(",");
    datafile.print(AgAc_genero);
    datafile.print(",");
    datafile.print(v_genero);
    datafile.print(",");
    datafile.print(estado_desarrollo);
    datafile.print(",");
    datafile.print(AgAc_estado_desarrollo);
    datafile.print(",");
    datafile.print(v_estado_desarrollo);
    datafile.print(",");
    datafile.print(cultura);
    datafile.print(",");
    datafile.print(AgAc_cultura);
    datafile.print(",");
    datafile.print(v_cultura);
    datafile.print(",");
    datafile.print(familia);
    datafile.print(",");
    datafile.print(AgAc_familia);
    datafile.print(",");
    datafile.print(v_familia);
    datafile.print(",");
    datafile.print(limitacion_movilidad);
    datafile.print(",");
    datafile.print(AgAc_limitacion_movilidad);
    datafile.print(",");
    datafile.print(v_limitacion_movilidad);
    datafile.print(",");
    datafile.print(limitacion_cognitiva);
    datafile.print(",");
    datafile.print(AgAc_limitacion_cognitiva);
    datafile.print(",");
    datafile.print(v_limitacion_cognitiva);
    datafile.print(",");
    datafile.print(limitacion_sensorial);
    datafile.print(",");
    datafile.print(AgAc_limitacion_sensorial);
    datafile.print(",");
    datafile.print(v_limitacion_sensorial);
    datafile.print(",");
    datafile.print(sistema_cuidados);
    datafile.print(",");
    datafile.print(AgAc_sistema_cuidados);
    datafile.print(",");
    datafile.print(v_sistema_cuidados);
    datafile.print(",");
    datafile.print(ambiente);
    datafile.print(",");
    datafile.print(AgAc_ambiente);
    datafile.print(",");
    datafile.print(v_ambiente);
    datafile.print(",");
    datafile.print(recursos);
    datafile.print(",");
    datafile.print(AgAc_recursos);
    datafile.print(",");
    datafile.print(v_recursos);
    datafile.print(",");
    datafile.print(tiempo);
    datafile.print(",");
    datafile.print(AgAc_tiempo);
    datafile.print(",");
    datafile.print(v_tiempo);
    
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

  fin();
 
}

void fin(){

lcd.clear();             // Limpiar el display
fin();
  
}

void setup() {

  Serial.begin(9600);

//iniciando SD------------------------------------

  Serial.print("Iniciando SD ...");
  if (!SD.begin(CS_PIN)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");

//------------------------------------------------

  lcd.begin(16,2);         // Iniciar el Display de 16 caracter por 2 lineas

//Defino los pines del alma-----------------------

  pinMode(pinLedR_A, OUTPUT);
  pinMode(pinLedG_A, OUTPUT);
  pinMode(pinLedB_A, OUTPUT);

//------------------------------------------------
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Hola...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Podrias abrir la");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("APP en tu movil");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("con el nombre");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("FBC?");
  delay(5000);
  lcd.clear();             // Limpiar el display
     
  codigo_usuario();

}

void loop() {
  // put your main code here, to run repeatedly:

}
