/*===========================Aplicaion Menú Básico para PC ================================
 * Control de Servo motor y motor a pasos manipulacion de encendido y apagado de dos leds.
 * Para conexion fisica requiere del modulo ULN2003 para el motor a pasos.
 * 
 */
//===========================BLIOTECAS====================================================
#include<Servo.h>
#include<Wire.h>

//==========================DEFINICIONES==================================================
Servo Servo1;
#define LED1 3  //Asignando LED1 a Pin3
#define LED2 5  //Asignando LED2 a Pin5
#define PinServo 6   ////Asignando PinServo a Pin6
#define DT  2       // DT a pin digital 2 (DT en modulo) Pin de la interrupcion 
#define CLK  4      // CLK a pin digital 4 (CLK en modulo)
#define retardo 5 
volatile int posicion_encoder = 0; //Declarando variables para encoder
int  posicion_encoder_anterior=0;
int numero_pasos = 0;   // Valor en grados donde se encuentra el motor   
int anguloPasos=0;
String cadenaCharEntrada = "";  
bool nuevoDato = false;             //bandera de nuevo dato
byte data[] = {0, 255, 255};
const size_t dataLength = sizeof(data) / sizeof(data[0]);
int angulo=0;

         

          
          
void setup() {
attachInterrupt(digitalPinToInterrupt(DT), encoder, LOW);   //rotacion
Serial.begin(9600);
pinMode(11, OUTPUT);    // Pin 11 conectar a IN4
pinMode(10, OUTPUT);    // Pin 10 conectar a IN3
pinMode(9, OUTPUT);     // Pin 9 conectar a IN2
pinMode(8, OUTPUT);     // Pin 8 conectar a IN1
pinMode(DT, INPUT);
pinMode(CLK, INPUT);
pinMode(LED1,INPUT);
pinMode(LED2,INPUT);

cadenaCharEntrada.reserve(20);

Servo1.attach(PinServo);
Servo1.write(0);
}
//=================================CICLO PRINCIPAL=====================================
void loop() {
    if (nuevoDato){
        angulo=cadenaCharEntrada.toInt();
        
        if(angulo<=180&&angulo>=0){
          posicion_encoder=angulo;
          }
        if(angulo>200){
         delay(retardo);
         anguloPasos=((angulo-200)*1.4222222222);
         } 

         if(angulo==190)
         digitalWrite(LED1,HIGH);

         if(angulo==191)
         digitalWrite(LED1,LOW);

         if(angulo==193)
         digitalWrite(LED2,HIGH);

         if(angulo==194)
         digitalWrite(LED2,LOW);
         
        nuevoDato=false;
        cadenaCharEntrada="";
    }
    
    
    if ( posicion_encoder!=posicion_encoder_anterior){
        data[0]=posicion_encoder;
        posicion_encoder_anterior=posicion_encoder;
        Servo1.write(posicion_encoder);
        Serial.write(data, dataLength);
      }

    
    while (anguloPasos>numero_pasos){   // Girohacia la izquierda en grados
           paso_izq();
           numero_pasos = numero_pasos + 1;
       }
    while (anguloPasos<numero_pasos){   // Giro hacia la derecha en grados
            paso_der();
            numero_pasos = numero_pasos -1;
       }
    apagado();         // Apagado del Motor para que no se caliente

}
          
          
 //===========================FUNCION ENCODER===============================================         
void encoder()  {                //Funcion que determina el sentido del giro del encoder
  static unsigned long ultimaInterrupcion = 0;  // variable static con ultimo valor de
  unsigned long tiempoInterrupcion = millis();  // variable almacena valor de func. millis

  if (tiempoInterrupcion - ultimaInterrupcion > 5) {  // No lee posibles rebotes en pulsos 
                                                      //menores a 5 mseg.
    if (digitalRead(CLK) == HIGH)     // si CLK es HIGH, rotacion a la derecha
    {
      posicion_encoder-- ;        // incrementa posicion del menu en 1
    } else {                      // si CLK es LOW, rotacion a la izquierda
      posicion_encoder++ ;        // decrementa posicion del menu en 1
    }
    posicion_encoder = min(180, max(0, posicion_encoder));  // numero de opciones del Menu, 
                                                              //inferior 0 superior en 5
    ultimaInterrupcion = tiempoInterrupcion;  //actualiza valor del tiempo tiempo
  }
}
                   
          
          
          
//===========================FUNCION PASOS A LA DERECHA=======================================
void paso_der(){         // Pasos a la derecha
digitalWrite(11, LOW); //Apaga Pin 11
digitalWrite(10, LOW);  //Apaga Pin 11
digitalWrite(9, HIGH);  //Enciende Pin 9
digitalWrite(8, HIGH);   //Enciende Pin 8
delay(retardo); 
digitalWrite(11, LOW); 
digitalWrite(10, HIGH);  
digitalWrite(9, HIGH);  
digitalWrite(8, LOW);  
delay(retardo); 
digitalWrite(11, HIGH); 
digitalWrite(10, HIGH);  
digitalWrite(9, LOW);  
digitalWrite(8, LOW);  
delay(retardo); 
digitalWrite(11, HIGH); 
digitalWrite(10, LOW);  
digitalWrite(9, LOW);  
digitalWrite(8, HIGH);  
 delay(retardo);  
}
 //===========================FUNCION PASOS A LA DIZQUIERDA=======================================
void paso_izq() {        // Pasos a la izquierda
 digitalWrite(11, HIGH); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
  delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, HIGH);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, LOW);  
  delay(retardo); 
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, HIGH);  
 digitalWrite(8, HIGH);  
  delay(retardo); 
 digitalWrite(11, HIGH); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, HIGH);  
  delay(retardo); 
}
 //===========================FUNCION APAGADO===========================================      
void apagado() {         // Apagado del Motor
 digitalWrite(11, LOW); 
 digitalWrite(10, LOW);  
 digitalWrite(9, LOW);  
 digitalWrite(8, LOW);  
 }
//===========================FUNCION RECEPCION DATOS=======================================    
void serialEvent(){
  //Recepción de datos Seriales
  while (Serial.available()) {              //Si existen datos seriales, leer a todos
     char inChar = (char)Serial.read();
     cadenaCharEntrada+= inChar;
     if (inChar=='\n'){
    nuevoDato=true;
     }
  }
}
