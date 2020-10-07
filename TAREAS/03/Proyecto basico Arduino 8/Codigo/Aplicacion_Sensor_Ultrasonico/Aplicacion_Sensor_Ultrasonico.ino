//******************************************************************************
// Aplicación para la medición de distancia con un sensor Ultrasónico.
//Elementos importantes:
//Se requiere un extensor modelo PCF8574
//Pantalla LCD de 20x4.
//Implementacion del codigo para calcular la distancia presente entre un objeto 
//"X" y el sensor ultrasónico.
// 
//******************************************************************************
//========[BIBLIOTECAS]========
//Para el manejo de la pantalla de cristal liquido utilizando el protocolo I2C.
#include <LiquidCrystal_I2C.h>

//========[DEFINICIONES]========
// Definicion de direccion de la pantalla LCD y pines definidos para las termi-
//nales del sensor ultrasonico(Trigger y eco)y declarativa de variables usadas.
LiquidCrystal_I2C lcd(0x27,20,4);

int trigPin = 3;            // Trigger
int echoPin = 2;            // Eco
long duration, cm, inches;

//=============================================================================

//========[AJUSTES]========
void setup(){
  Serial.begin(9600);       // Inicialización de puerto serial
  pinMode(trigPin, OUTPUT); // definición de Salidas / Entradas
  pinMode(echoPin, INPUT);

  lcd.begin(20,4);          // Ajuste de la pantalla LCD
}
//========[LAZO PRINCIPAL]========
void loop(){
  // El sensor es disparado por un pulso ("HIGH"-"LOW") de 10 o mas uSegs.
  //Emplear un pulso corto (en "LOW") antes de asefurar un pulso limpio en
  // "HIGH".
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lectura de la señal del sensor. Un pulso en nivel "HIGH", cuya duración es
  //el tiempo (en microsegundos) desde el envío de la señal "ping" hasta la re-
  //cepción del eco al rebotar en el objeto detectado.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  
  cm = long((duration/2) / 29.1);  // Conversión del tiempo leído, a distancia.
  inches = long((duration/2) / 73.914);

  // Despliegue de la información calculada y letreros.
 lcd.setCursor(0,0);
  lcd.print("=Distancia Medida=");
  
  lcd.setCursor(0,1);
  lcd.print("Pulgadas:");
  lcd.print(inches);
  lcd.print("in");
  
  lcd.setCursor(0,2);
  lcd.print("Centimetros:");
  lcd.print(cm);
  lcd.print("cm");

 
lcd.setCursor(0,3);
  lcd.print("-Sana Distancia-");
  
 
  delay(250);                   //Tiempo de espera para reiniciar proceso
}












//*****************************************************************************
