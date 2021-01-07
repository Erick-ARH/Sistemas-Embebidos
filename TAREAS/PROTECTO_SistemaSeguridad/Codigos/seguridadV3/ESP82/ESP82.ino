#include <ESP8266WiFi.h>
#include "AdafruitIO_WiFi.h"

#define IO_USERNAME  "LazaroAD"
#define IO_KEY       "aio_RNKL63u8bKDWKEOB03cRJbwgTWx6"

#define WIFI_SSID       "INFINITUMAAEE_2.4"
#define WIFI_PASS       "krBLdkz36G"


AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);


AdafruitIO_Feed *servo_vertical = io.feed("PosicionVertical");
AdafruitIO_Feed *servo_horizontal = io.feed("PosicionHorizontal");
AdafruitIO_Feed *CLampara = io.feed("ControlLampara");

AdafruitIO_Feed *LampState = io.feed("EstadoLampara");
AdafruitIO_Feed *Noche = io.feed("DeteccionNoche");
AdafruitIO_Feed *Movimiento = io.feed("DeteccionMovimiento");



String cadenaCharEntrada = "";  
bool nuevoDato = false;
 byte data[] = {0, 255, 255};
const size_t dataLength = sizeof(data) / sizeof(data[0]);
int angulo=0;
int dato;



void setup() 
{
    pinMode(2, OUTPUT);
  // Enable the serial port so we can see updates
  Serial.begin(115200);
 Serial.println("  Arranca");
  // Connect to Adafruit IO
  io.connect();
  servo_vertical->onMessage(handleVerticalMessage);
  servo_horizontal->onMessage(handleHorizontalMessage);
  CLampara->onMessage(CLamparaMessage);
  // wait for a connection
  while(io.status() < AIO_CONNECTED) 
  {
   // Serial.print(".");
    delay(500);
  }

    //Serial.println("Conectado ");
    servo_vertical->get();
    servo_horizontal->get();
    CLampara->get();
    digitalWrite(2,LOW);
    delay(200);
    digitalWrite(2,HIGH);
    delay(200);
    digitalWrite(2,LOW);
    delay(200);
    digitalWrite(2,HIGH);
    delay(200);
    digitalWrite(2,LOW);
    delay(200);
    digitalWrite(2,HIGH);
     delay(200);
    digitalWrite(2,LOW);
    delay(200);
    digitalWrite(2,HIGH);
}


void loop() {
    io.run();
    if (Serial.available()) serialEvent();
  //  Serial.println(".");
    delay(200);

}




void handleVerticalMessage(AdafruitIO_Data *data) {

  // convert the data to integer
  int angle = data->toInt();
    angle+=2000;
     Serial.println (angle);
}
void handleHorizontalMessage(AdafruitIO_Data *data) {

  // convert the data to integer
  int angle = data->toInt();
    angle+=1000;
     Serial.println (angle);
 
}
void CLamparaMessage(AdafruitIO_Data *data) {
 static int Ctrl_Lamp_State;
  // convert the data to integer
  int dato = data->toInt();

  if(dato==1){
      if(Ctrl_Lamp_State<3) Ctrl_Lamp_State++;
    else {Ctrl_Lamp_State=0;}

    
       // Serial.print("Estado de control de lampara ");     
     Serial.println (Ctrl_Lamp_State);     

     

    if (Ctrl_Lamp_State==0){
        Noche->save(0);
        delay(2000);
        Movimiento->save(0);
        delay(2000);
    }     
    if (Ctrl_Lamp_State==1){
        Noche->save(0);
        delay(2000);
        Movimiento->save(0);
        delay(2000);
    }
    if (Ctrl_Lamp_State==2){
        Noche->save(1);
        delay(2000);
        Movimiento->save(0);
        delay(2000);
    }  
        if (Ctrl_Lamp_State==3){
        Noche->save(0);
        delay(2000);
        Movimiento->save(1);
        delay(2000);
    } 
  }
}


void serialEvent(){
    // Serial.print("############# DATO SERIAL############");
           
  //Recepción de datos Seriales
  while (Serial.available()) {              //Si existen datos seriales, leer a todos
     char inChar = (char)Serial.read();
     cadenaCharEntrada+= inChar;
     if (inChar=='\n'){
     nuevoDato=true;
     }
  }
        Serial.println(cadenaCharEntrada);
    if (nuevoDato){
        dato=cadenaCharEntrada.toInt();
        //  Serial.println(dato);   
        if(dato==10) { 
        LampState->save(0);
        // Serial.println(" apagado");
        }
        if(dato==20) { 
        LampState->save(1);
        // Serial.println("  prendido");
        }

        nuevoDato=false;
        cadenaCharEntrada="";
      
    }

} 
