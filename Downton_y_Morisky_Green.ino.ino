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

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Establecemos el tipo de LCD

//defino los pines para el RGB del alma

#define pinLedR_A 30 
#define pinLedG_A 32  
#define pinLedB_A 34

//Declaro la variable para comunicar el resultado de cada respuesta via bluetooth

char estado="";

String mensaje;
String codigo;

//Declaro variable para configurar el pin CS del módulo SD

const int CS_PIN = 4;

// Declaro las variables del test DOWNTON

int caida_previa = 0; //variable para caidas_previas
int medi = 0; //variable para medicacion
int tranq = 0; //variable para toma de tranquilizantes-sedantes
int diur = 0; //variable para toma de diureticos
int hipot = 0; //variable para toma de hipotensores
int antipark = 0; //variable para toma de antiparkinsonianos
int antidepr = 0; //variable para toma de antidepresivos
int otros = 0; //variable para toma de otros medicamentos
int medi_post = 0; //variable para sumar los medicamentos que incrementan riesgo de caidas
int def_sens = 0; //variable para deficit sensorial
int alt_vis = 0; //variable para alteraciones visuales
int alt_aud = 0; //variable para alteraciones visuales
int alt_ext = 0; //variable para alteraciones visuales
int est_ment = 0; //variable para alteraciones visuales
int deamb_normal = 0; //variable para deambulacion normal
int deamb_segura = 0; //variable para deambulacion segura con ayuda
int deamb_insegura = 0; //variable para deambulacion insegura
int deamb_imposible = 0; //variable para deambulacion imposible
int puntuacion_downton = 0; //variable para la puntuacion final del test Downton

//Declaro las variables del test Morinsky-Green

int olvido_medicamento = 0; //variable para "¿se olvida alguna vez de tomar el medicamento?"
int toma_en_hora = 0; //variable para "¿toma la medicación a la hora indicada?"
int deja_med_bien = 0; //variable para "cuando se encuentra bien, ¿deja alguna vez de tomar la medicación?"
int deja_med_mal = 0; //variable para "si alguna vez se siente mal, ¿deja de tomar la medicación?"
int med_hora_test = 0; //variable para cambio de valores en la segunda pregunta para hacer el sumatorio del test

int puntuacion_morinsky = 0; //variable para la puntuacion final del test Morinsky-Green


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
  lcd.print("Downton-Morisky?");
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
     caidas_previas();
  
}

void caidas_previas(){

  //led blanco
  digitalWrite(pinLedR_A, HIGH);
  digitalWrite(pinLedG_A, HIGH);
  digitalWrite(pinLedB_A, HIGH);
  
  Serial.print("Valorando caidas previas...");

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Has tenido");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("caidas previas?");
  delay(5000);
  lcd.clear();             // Limpiar el display
 
 while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){
       caida_previa = 0;
       Serial.println("");
       Serial.println("No ha tenido caídas previas");
       estado = "";
       //led verde
       digitalWrite(pinLedR_A, LOW);
       digitalWrite(pinLedG_A, HIGH);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       medicacion();
 }
 if(estado == '1'){
       caida_previa = 1;
       Serial.println("");
       Serial.println("Si ha tenido caídas previas");
       estado = "";
       //led rojo
       digitalWrite(pinLedR_A, HIGH);
       digitalWrite(pinLedG_A, LOW);
       digitalWrite(pinLedB_A, LOW);
       delay(1000); 
       medicacion();
 }

 caidas_previas();
 
 }

void medicacion(){

  Serial.print("Valorando toma de medicacion...");

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Tomas algun tipo");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("de medicacion?");
  delay(5000);
  lcd.clear();             // Limpiar el display
 
 while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){
       medi = 0;
       Serial.println("");
       Serial.println("No toma medicacion");
       estado = "";
       //led verde
       digitalWrite(pinLedR_A, LOW);
       digitalWrite(pinLedG_A, HIGH);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       alteraciones_visuales();
 }
 
 if(estado == '1'){
       medi = 1;
       Serial.println("");
       Serial.println("Si toma medicacion");
       estado = "";
        //led rojo
       digitalWrite(pinLedR_A, HIGH);
       digitalWrite(pinLedG_A, LOW);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       tranquilizantes_sedantes();     
 }

 medicacion();
 
 }

void tranquilizantes_sedantes(){

  Serial.print("Valorando toma de tranquilizantes-sedantes...");

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Entre ella, tomas");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("tranquilizantes..");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("o");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("sedantes?");
  delay(5000);
  lcd.clear();             // Limpiar el display;
 
 while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){
       tranq = 0;
       Serial.println("");
       Serial.println("No toma tranquilizantes o sedantes");
       estado = "";
       //led verde
       digitalWrite(pinLedR_A, LOW);
       digitalWrite(pinLedG_A, HIGH);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       diureticos();
       
 }
 if(estado == '1'){
       tranq = 1;
       Serial.println("");
       Serial.println("Si toma tranquilizantes o sedantes");
       estado = "";
       //led rojo
       digitalWrite(pinLedR_A, HIGH);
       digitalWrite(pinLedG_A, LOW);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       diureticos(); 
       
 }

 tranquilizantes_sedantes();
 
 }

void diureticos(){

  Serial.print("Valorando toma de diureticos...");

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Tomas algun");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("diuretico?");
  delay(5000);
  lcd.clear();             // Limpiar el display

 
 while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){
       diur = 0;
       Serial.println("");
       Serial.println("No toma diureticos");
       estado = "";
       //led verde
       digitalWrite(pinLedR_A, LOW);
       digitalWrite(pinLedG_A, HIGH);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       hipotensores();
       
 }
 if(estado == '1'){
       diur = 1;
       Serial.println("");
       Serial.println("Si toma diureticos");
       estado = "";
       //led rojo
       digitalWrite(pinLedR_A, HIGH);
       digitalWrite(pinLedG_A, LOW);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       hipotensores(); 
       
 }

 diureticos();
 
 }

void hipotensores(){

  Serial.print("Valorando toma de hipotensores...");

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Tomas algun");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("hipotensor?");
  delay(5000);
  lcd.clear();             // Limpiar el display

 
 while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){
       hipot = 0;
       Serial.println("");
       Serial.println("No toma hipotensores");
       estado = "";
       //led verde
       digitalWrite(pinLedR_A, LOW);
       digitalWrite(pinLedG_A, HIGH);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       antiparkinsonianos();
       
 }
 if(estado == '1'){
       hipot = 1;
       Serial.println("");
       Serial.println("Si toma hipotensores");
       estado = "";
       //led rojo
       digitalWrite(pinLedR_A, HIGH);
       digitalWrite(pinLedG_A, LOW);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       antiparkinsonianos(); 
       
 }

 hipotensores();
 
 }

void antiparkinsonianos(){

  Serial.print("Valorando toma de antiparkinsonianos...");

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Tomas algun");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("medicamento...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Anti-");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("parkinsoniano?");
  delay(5000);
  lcd.clear();             // Limpiar el display

 
 while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){
       antipark = 0;
       Serial.println("");
       Serial.println("No toma antiparkinsonianos");
       estado = "";
       //led verde
       digitalWrite(pinLedR_A, LOW);
       digitalWrite(pinLedG_A, HIGH);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       antidepresivos();
       
 }
 if(estado == '1'){
       antipark = 1;
       Serial.println("");
       Serial.println("Si toma antiparkinsonianos");
       estado = "";
       //led rojo
       digitalWrite(pinLedR_A, HIGH);
       digitalWrite(pinLedG_A, LOW);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       antidepresivos(); 
       
 }

 antiparkinsonianos();
 
 }

void antidepresivos(){

  Serial.print("Valorando toma de antidepresivos...");

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Tomas algun");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("antidepresivo?");
  delay(5000);
  lcd.clear();             // Limpiar el display
 
 while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){
       antidepr = 0;
       Serial.println("");
       Serial.println("No toma antidepresivos");
       estado = "";
       //led verde
       digitalWrite(pinLedR_A, LOW);
       digitalWrite(pinLedG_A, HIGH);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       otros_medicamentos();
       
 }
 if(estado == '1'){
       antidepr = 1;
       Serial.println("");
       Serial.println("Si toma antidepresivos");
       estado = "";
       //led rojo
       digitalWrite(pinLedR_A, HIGH);
       digitalWrite(pinLedG_A, LOW);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       otros_medicamentos(); 
       
 }

 antidepresivos();
 
 }

void otros_medicamentos(){

  Serial.print("Valorando toma de otros medicamentos...");

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Tomas algun");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("otro tipo de...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("medicamento?");
  delay(5000);
  lcd.clear();             // Limpiar el display
 
 while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){
       otros = 0;
       Serial.println("");
       Serial.println("No toma otro tipo de medicamentos");
       estado = "";
       //led verde
       digitalWrite(pinLedR_A, LOW);
       digitalWrite(pinLedG_A, HIGH);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       medicacion_post();
       
 }
 if(estado == '1'){
       otros = 1;
       Serial.println("");
       Serial.println("Si toma otro tipo de medicamentos");
       estado = "";
       //led rojo
       digitalWrite(pinLedR_A, HIGH);
       digitalWrite(pinLedG_A, LOW);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       medicacion_post(); 
       
 }

 otros_medicamentos();
 
 }

 void medicacion_post(){

  medi_post = tranq + diur + hipot + antipark + antidepr + otros;

  Serial.println("");
  Serial.println("La puntuación acumulada para el riesgo de caídas en función de los medicamentos tomados es:");
  Serial.println(medi_post);
  Serial.println("");

  olvido_tomas();
  
 }

void olvido_tomas(){

  Serial.print("Valorando olvido en toma de medicamentos...");

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te olvidas");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("alguna vez de...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("tomar el");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("medicamento?");
  delay(5000);
  lcd.clear();             // Limpiar el display
 
 while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){
       olvido_medicamento = 0;
       Serial.println("");
       Serial.println("No se olvida de las tomas de medicamentos");
       estado = "";
       //led verde
       digitalWrite(pinLedR_A, LOW);
       digitalWrite(pinLedG_A, HIGH);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       toma_hora();
       
 }
 if(estado == '1'){
       olvido_medicamento = 1;
       Serial.println("");
       Serial.println("Si se olvida de las tomas de medicamentos");
       estado = "";
       //led rojo
       digitalWrite(pinLedR_A, HIGH);
       digitalWrite(pinLedG_A, LOW);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       toma_hora(); 
       
 }

 olvido_tomas();
  
}


void toma_hora(){

  Serial.print("Valorando toma de medicamentos en hora...");

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Toma la");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("medicacion a...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("la hora");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("indicada?");
  delay(5000);
  lcd.clear();             // Limpiar el display
 
 while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){
       toma_en_hora = 0;
       med_hora_test = 1;
       Serial.println("");
       Serial.println("No toma los medicamentos en hora");
       estado = "";
       //led rojo
       digitalWrite(pinLedR_A, HIGH);
       digitalWrite(pinLedG_A, LOW);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       deja_tomas_bien();
       
 }
 if(estado == '1'){
       toma_en_hora = 1;
       med_hora_test = 0;
       Serial.println("");
       Serial.println("Toma los medicamentos en hora");
       estado = "";
       //led verde
       digitalWrite(pinLedR_A, LOW);
       digitalWrite(pinLedG_A, HIGH);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       deja_tomas_bien(); 
  
}

toma_hora();

}


void deja_tomas_bien(){

  Serial.print("Valorando si deja de tomar medicación cuando se encuentra bien...");

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Cuando te ");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("encuentras bien,");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("dejas alguna vez");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("de tomar...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("dejas alguna vez");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("de tomar...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("la");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("medicacion?");
  delay(5000);
  lcd.clear();             // Limpiar el display
 
 while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){
       deja_med_bien = 0;
       Serial.println("");
       Serial.println("No deja de tomar la medicacion cuando se encuentra bien");
       estado = "";
       //led verde
       digitalWrite(pinLedR_A, LOW);
       digitalWrite(pinLedG_A, HIGH);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       deja_tomas_mal();
       
 }
 if(estado == '1'){
       deja_med_bien = 1;
       Serial.println("");
       Serial.println("Si deja de tomar la medicacion cuando se encuentra bien");
       estado = "";
       //led rojo
       digitalWrite(pinLedR_A, HIGH);
       digitalWrite(pinLedG_A, LOW);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       deja_tomas_mal(); 
       
 }

 deja_tomas_bien();

  
}

void deja_tomas_mal(){

  Serial.print("Valorando si deja de tomar medicación cuando se encuentra mal...");

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Si alguna vez");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("te sientes mal,");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("dejas de tomar");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("la medicacion?");
  delay(5000);
  lcd.clear();             // Limpiar el display

 
 while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){
       deja_med_mal = 0;
       Serial.println("");
       Serial.println("No deja de tomar la medicacion cuando se encuentra mal");
       estado = "";
       //led verde
       digitalWrite(pinLedR_A, LOW);
       digitalWrite(pinLedG_A, HIGH);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       alteraciones_visuales();
       
 }
 if(estado == '1'){
       deja_med_mal = 1;
       Serial.println("");
       Serial.println("Si deja de tomar la medicacion cuando se encuentra mal");
       estado = "";
       //led rojo
       digitalWrite(pinLedR_A, HIGH);
       digitalWrite(pinLedG_A, LOW);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       alteraciones_visuales(); 
       
 }

 deja_tomas_mal();
  
}

void alteraciones_visuales(){
  
  Serial.print("Valorando alteraciones visuales...");

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Tienes algun");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("tipo de...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("limitacion");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("visual?");
  delay(5000);
  lcd.clear();             // Limpiar el display;
 
 while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){
       alt_vis = 0;
       Serial.println("");
       Serial.println("No tiene alteraciones visuales");
       estado = "";
       //led verde
       digitalWrite(pinLedR_A, LOW);
       digitalWrite(pinLedG_A, HIGH);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       alteraciones_auditivas();
       
 }
 if(estado == '1'){
       alt_vis = 1;
       Serial.println("");
       Serial.println("Si tiene alteraciones visuales");
       estado = "";
       //led rojo
       digitalWrite(pinLedR_A, HIGH);
       digitalWrite(pinLedG_A, LOW);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       alteraciones_auditivas(); 
       
 }

 alteraciones_visuales();
 
 }

void alteraciones_auditivas(){

  Serial.print("Valorando alteraciones auditivas...");

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Tienes algun");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("tipo de...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("limitacion");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("auditiva?");
  delay(5000);
  lcd.clear();             // Limpiar el display;
 
 while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){
       alt_aud = 0;
       Serial.println("");
       Serial.println("No tiene alteraciones auditivas");
       estado = "";
       //led verde
       digitalWrite(pinLedR_A, LOW);
       digitalWrite(pinLedG_A, HIGH);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       alteraciones_extremidades();
       
 }
 if(estado == '1'){
       alt_aud = 1;
       Serial.println("");
       Serial.println("Si tiene alteraciones auditivas");
       estado = "";
       //led rojo
       digitalWrite(pinLedR_A, HIGH);
       digitalWrite(pinLedG_A, LOW);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       alteraciones_extremidades(); 
       
 }

 alteraciones_auditivas();
 
 }

void alteraciones_extremidades(){

  Serial.print("Valorando alteraciones en extremidades...");

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Tienes alguna");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("limitacion...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("sensorial en");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("extremidades?");
  delay(5000);
  lcd.clear();             // Limpiar el display;
 
 while(Serial.available()>0){           // Si el puerto serie esta habilitadp 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){
       alt_ext = 0;
       Serial.println("");
       Serial.println("No tiene alteraciones sensoriales en extremidades");
       estado = "";
       //led verde
       digitalWrite(pinLedR_A, LOW);
       digitalWrite(pinLedG_A, HIGH);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       deficit_sensorial();
       
 }
 if(estado == '1'){
       alt_aud = 1;
       Serial.println("");
       Serial.println("Si tiene alteraciones sensoriales en extremidades");
       estado = "";
       //led rojo
       digitalWrite(pinLedR_A, HIGH);
       digitalWrite(pinLedG_A, LOW);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       deficit_sensorial(); 
       
 }

 alteraciones_extremidades();
 
 }

 void deficit_sensorial(){

 def_sens = alt_vis + alt_aud + alt_ext;

 estado_mental();

 }

void estado_mental(){

  Serial.print("Valorando estado mental...");

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Te encuentras");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("confuso?");
  delay(5000);
  lcd.clear();             // Limpiar el display
 
 while(Serial.available()>0){           // Si el puerto serie esta habilitado 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){
       est_ment = 0;
       Serial.println("");
       Serial.println("Está orientado");
       estado = "";
       //led verde
       digitalWrite(pinLedR_A, LOW);
       digitalWrite(pinLedG_A, HIGH);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       deambulacion_normal();
       
 }
 if(estado == '1'){
       est_ment = 1;
       Serial.println("");
       Serial.println("Está confuso");
       estado = "";
        //led rojo
       digitalWrite(pinLedR_A, HIGH);
       digitalWrite(pinLedG_A, LOW);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       deambulacion_normal(); 
       
 }

 estado_mental();
 
 }

void deambulacion_normal(){

  Serial.print("Valorando deambulacion...");

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Tienes problemas");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("para caminar?");
  delay(5000);
  lcd.clear();             // Limpiar el display
 
 while(Serial.available()>0){           // Si el puerto serie esta habilitado 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){
       deamb_normal = 1;
       Serial.println("");
       Serial.println("No tiene problemas para la deambulacion");
       estado = "";
       //led verde
       digitalWrite(pinLedR_A, LOW);
       digitalWrite(pinLedG_A, HIGH);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       resultado_downton();
       
 }
 if(estado == '1'){
       deamb_normal = 0;
       Serial.println("");
       Serial.println("Tiene problemas para la deambulacion");
       estado = "";
       //led rojo
       digitalWrite(pinLedR_A, HIGH);
       digitalWrite(pinLedG_A, LOW);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       deambulacion_imposible(); 
       
 }

 deambulacion_normal();
 
 }

void deambulacion_imposible(){

  Serial.print("Valorando si la deambulacion es imposible...");

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Le es imposible");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("caminar?");
  delay(5000);
  lcd.clear();             // Limpiar el display
 
 while(Serial.available()>0){           // Si el puerto serie esta habilitado 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){
       deamb_imposible = 0;
       Serial.println("");
       Serial.println("La deambulación no le es imposible");
       estado = "";
        //led verde
       digitalWrite(pinLedR_A, LOW);
       digitalWrite(pinLedG_A, HIGH);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       deambulacion_insegura();
       
 }
 if(estado == '1'){
       deamb_imposible = 1;
       Serial.println("");
       Serial.println("La deambulación le es imposible");
       estado = "";
       //led rojo
       digitalWrite(pinLedR_A, HIGH);
       digitalWrite(pinLedG_A, LOW);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       resultado_downton(); 
       
 }

 deambulacion_imposible();
 
 }

void deambulacion_insegura(){

  Serial.print("Valorando si la deambulacion es segura o insegura...");

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Al andar,");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("ya sea...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("con ayuda o");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("sin ayuda,...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("se siente");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("inseguro?");
  delay(5000);
  lcd.clear();             // Limpiar el display
 
 while(Serial.available()>0){           // Si el puerto serie esta habilitado 
        estado = Serial.read();      // Lee lo que llega por el puerto Serie
 }
     
 if(estado == '0' ){
       deamb_segura = 1;
       Serial.println("");
       Serial.println("La deambulación es segura con ayuda");
       estado = "";
        //led verde
       digitalWrite(pinLedR_A, LOW);
       digitalWrite(pinLedG_A, HIGH);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       resultado_downton();
       
 }
 if(estado == '1'){
       deamb_insegura = 1;
       Serial.println("");
       Serial.println("La deambulación es insegura con/sin ayuda");
       estado = "";
       //led rojo
       digitalWrite(pinLedR_A, HIGH);
       digitalWrite(pinLedG_A, LOW);
       digitalWrite(pinLedB_A, LOW);
       delay(1000);
       resultado_downton(); 
       
 }

 deambulacion_insegura();
 
 }

void resultado_downton() {

  puntuacion_downton = caida_previa + medi_post + def_sens + est_ment + deamb_segura + deamb_insegura + deamb_imposible;

  Serial.println("");
  Serial.println("La puntuación del test Downton para valorar el riesgo de caídas ha sido de:");
  Serial.print(puntuacion_downton);
  Serial.println("");

  delay(1000);

  if(puntuacion_downton >= 3)
  {

    Serial.println("Por lo que el mencionado test indica que presenta un alto riesgo de sufrir caidas");
    delay(1000);

    //led rojo
    digitalWrite(pinLedR_A, HIGH);
    digitalWrite(pinLedG_A, LOW);
    digitalWrite(pinLedB_A, LOW);
    
    lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
    lcd.print("Segun las");
    lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
    lcd.print("respuestas que...");
    delay(5000);
    lcd.clear();             // Limpiar el display
  
    lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
    lcd.print("me has dado,");
    lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
    lcd.print("tienes un...");
    delay(5000);
    lcd.clear();             // Limpiar el display

    lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
    lcd.print("alto riesgo a");
    lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
    lcd.print("sufrir una caida");
    delay(5000);
    lcd.clear();             // Limpiar el display

    fin_test_downton();
    
  }

  if(puntuacion_downton < 3)
  {
    //led verde
    digitalWrite(pinLedR_A, LOW);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);
       
    Serial.println("Por lo que el mencionado test indica que presenta un bajo riesgo de sufrir caidas");
    delay(1000);

    lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
    lcd.print("Segun las");
    lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
    lcd.print("respuestas que...");
    delay(5000);
    lcd.clear();             // Limpiar el display
  
    lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
    lcd.print("me has dado,");
    lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
    lcd.print("aparentemente...");
    delay(5000);
    lcd.clear();             // Limpiar el display

    lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
    lcd.print("no tienes riesgo");
    lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
    lcd.print("de caidas");
    delay(5000);
    lcd.clear();             // Limpiar el display

    fin_test_downton();
  }

  
}

void fin_test_downton(){

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("Muchas gracias");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("por ahora...");
  delay(5000);
  lcd.clear();             // Limpiar el display
  
  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("he terminado de");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("valorar tu...");
  delay(5000);
  lcd.clear();             // Limpiar el display

  lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
  lcd.print("riesgo a sufrir");
  lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
  lcd.print("una caida.");
  delay(5000);
  lcd.clear();             // Limpiar el display

  resultado_morinsky();
  
}

void resultado_morinsky() {

  puntuacion_morinsky = olvido_medicamento + med_hora_test + deja_med_bien + deja_med_mal;

  Serial.println("");
  Serial.println("La puntuación del test Morinsky para valorar el cumplimiento terapéutico ha sido de:");
  Serial.print(puntuacion_morinsky);
  Serial.println("");

  delay(1000);

  if(puntuacion_morinsky >= 1)
  {

    Serial.println("Por lo que el mencionado test indica que tiene dificultades para cumplir con el tratamiento farmacologico");
    delay(1000);

    //led rojo
    digitalWrite(pinLedR_A, HIGH);
    digitalWrite(pinLedG_A, LOW);
    digitalWrite(pinLedB_A, LOW);
    
    lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
    lcd.print("Asimismo,");
    lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
    lcd.print("parece que...");
    delay(5000);
    lcd.clear();             // Limpiar el display
  
    lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
    lcd.print("tienes");
    lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
    lcd.print("dificultad...");
    delay(5000);
    lcd.clear();             // Limpiar el display

    lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
    lcd.print("para seguir el");
    lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
    lcd.print("tratamiento...");
    delay(5000);
    lcd.clear();             // Limpiar el display

    lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
    lcd.print("Deberias de");
    lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
    lcd.print("consultar a...");
    delay(5000);
    lcd.clear();             // Limpiar el display

    lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
    lcd.print("tu enfermera");
    lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
    lcd.print("de referencia");
    delay(5000);
    lcd.clear();             // Limpiar el display

    guardaSD();
    
  }

  if(puntuacion_morinsky < 1)
  {

    Serial.println("Por lo que el mencionado test indica que cumple con el tratamiento farmacologico");
    delay(1000);
    
    //led verde
    digitalWrite(pinLedR_A, LOW);
    digitalWrite(pinLedG_A, HIGH);
    digitalWrite(pinLedB_A, LOW);

    lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
    lcd.print("Parece que");
    lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
    lcd.print("no...");
    delay(5000);
    lcd.clear();             // Limpiar el display
  
    lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
    lcd.print("tienes");
    lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
    lcd.print("dificultad...");
    delay(5000);
    lcd.clear();             // Limpiar el display

    lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
    lcd.print("para seguir el");
    lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
    lcd.print("tratamiento...");
    delay(5000);
    lcd.clear();             // Limpiar el display

    lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
    lcd.print("Cualquier duda");
    lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
    lcd.print("consulta a...");
    delay(5000);
    lcd.clear();             // Limpiar el display

    lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
    lcd.print("tu enfermera");
    lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
    lcd.print("de referencia");
    delay(5000);
    lcd.clear();             // Limpiar el display

    guardaSD();
  
}

}

void guardaSD(){

  Serial.begin(9600);
 
  //Abre un archivo para escribir en él las variables y el resultado del cuestionario Downton
  File datafile = SD.open("dm.csv", FILE_WRITE);
  
  if (datafile) {
    Serial.println("Escribiendo resultados del cuestionario Downton");
    datafile.println("");
    datafile.print(codigo);
    datafile.print(",");
    datafile.print(caida_previa);
    datafile.print(",");
    datafile.print(tranq);
    datafile.print(",");
    datafile.print(diur);
    datafile.print(",");
    datafile.print(hipot);
    datafile.print(",");
    datafile.print(antipark);
    datafile.print(",");
    datafile.print(antidepr);
    datafile.print(",");
    datafile.print(otros);
    datafile.print(",");
    datafile.print(alt_vis);
    datafile.print(",");
    datafile.print(alt_aud);
    datafile.print(",");
    datafile.print(alt_ext);
    datafile.print(",");
    datafile.print(est_ment);
    datafile.print(",");
    datafile.print(deamb_normal);
    datafile.print(",");
    datafile.print(deamb_segura);
    datafile.print(",");
    datafile.print(deamb_insegura);
    datafile.print(",");
    datafile.print(deamb_imposible);
    datafile.print(",");
    datafile.print(puntuacion_downton);
    datafile.print(",");
    
    datafile.print(olvido_medicamento);
    datafile.print(",");
    datafile.print(toma_en_hora);
    datafile.print(",");
    datafile.print(deja_med_bien);
    datafile.print(",");
    datafile.print(deja_med_mal);
    datafile.print(",");
    datafile.print(puntuacion_morinsky);

    datafile.close(); //cerramos el archivo

    lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
    lcd.print("Datos guardados");
    lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
    lcd.print("en SD");
    delay(5000);

    Serial.println("Datos guardados en SD");
    lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
    
  } else {
         //si el archivo no se abre, muestra mensaje de error:
    Serial.println("Error al abrir el archivo");
    guardaSD();
  }
  delay(100);

  fin();
}

void fin(){

    lcd.setCursor(0,0);      // El cursor en la columna 0 y la fila 0
    lcd.print("");
    lcd.setCursor(0,1);// Imprimimos el texto en el display LCD
    lcd.print("");
    delay(5000);
    fin();
}

void setup() {
  
  Serial.begin(9600);
  Serial.print("Iniciando SD ...");
  if (!SD.begin(CS_PIN)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");

  //led blanco
      digitalWrite(pinLedR_A, HIGH);
      digitalWrite(pinLedG_A, HIGH);
      digitalWrite(pinLedB_A, HIGH);
  
  pinMode(13,OUTPUT);

  lcd.begin(16,2);         // Iniciar el Display de 16 caracter por 2 lineas
  abre_APP();

}

void loop() {

}
