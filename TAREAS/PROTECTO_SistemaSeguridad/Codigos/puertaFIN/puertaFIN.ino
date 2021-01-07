//
//#include <WiFi.h>
//#include "Adafruit_MQTT.h"
//#include "Adafruit_MQTT_Client.h"

#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

//#define IRsensor 23
#define Door 8
//#define Boton 15

//#define TWD_Access 20000
//unsigned long t_Access=0;
//#define TWD_OpenDoor 10000
//unsigned long t_OpenDoor=0;
//#define T_MQTT 50
//unsigned long t_MQTT=0;
//#define T_Face 2000
//unsigned long t_Face=0;

void printDate();
void DoorOpen();


struct Button{
    const int Pin;
    bool Pressed;
};
Button BotonInterno={22,false};


struct Ultrasonico{
  const int Echo;
  const int Trigger;
  long distance;
  unsigned long Tmuestreo;
  unsigned long t_transcurrido;
  bool  NewData;    
  };
Ultrasonico ultrasonico={12,13,0 ,100,0,false}; // Echo, Trigger, Distancia (setear en 0 ), periodo de muestreo, momento de muestreo(setear en 0 ), bandera de actualizacion

LiquidCrystal_I2C lcd(0x27,20,4);

const byte ROWS = 4;  // Cuatro hileras del teclado
const byte COLS = 4;  // Cuatro Columnas del teclado
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},// --> Adaptar al teclado propio <--
  {'4', '5', '6', 'B'},// Definición de los símbolos del teclado (serigrafía)
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {1, 0, 14, 15};    // Hileras   // Conexiones a las terminales del teclado:
byte colPins[COLS] = {16, 17, 18, 19};  // Columnas
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);// Inicialización de la una instancia del Teclado
char keycount = 0;        // Conteo de intentos
char code[4] ={'F','F','F','F'};             // Retención de teclas oprimidas



#define Ncontraseñas 5;
bool Flag_seguridad=true;
bool Flag_acceso=true;



String cadenaCharEntrada = "";  
bool nuevoDato = false;
 byte data[] = {0, 255, 255};
const size_t dataLength = sizeof(data) / sizeof(data[0]);
int dato;


/************************* WiFi Access Point *********************************/
//#define WLAN_SSID       "INFINITUMAAEE_2.4"
//#define WLAN_PASS       "krBLdkz36G"
///************************* Adafruit.io Setup *********************************/
//#define AIO_SERVER      "io.adafruit.com"
//#define AIO_SERVERPORT  1883                   // use 8883 for SSL
//#define AIO_USERNAME  "LazaroAD"
//#define AIO_KEY       "aio_RNKL63u8bKDWKEOB03cRJbwgTWx6"
//WiFiClient client;
/*********************** declaracion de clientes y publicaciones************************/
//Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
//Adafruit_MQTT_Publish PuertaE = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/PuertaE");
//Adafruit_MQTT_Subscribe BloqueoTotal = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/BloqueoTotal");
//Adafruit_MQTT_Subscribe seguridad = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/seguridad");
//Adafruit_MQTT_Subscribe Cerradura = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Cerradura");
//
//void MQTT_connect();




//void IRAM_ATTR isr() {
//  BotonInterno.Pressed=true;
////   Serial.print("+++++++++++++++++ Interrupcion boton interior +++++++++++++++");
//}

void setup() {
    Serial.begin(9600);
    pinMode(ultrasonico.Trigger, OUTPUT);
    pinMode(ultrasonico.Echo, INPUT);
//    pinMode(IRsensor, INPUT);
    pinMode(BotonInterno.Pin, INPUT);
    pinMode(Door,OUTPUT);
    digitalWrite(Door, HIGH);  


    // Serial.println("INICIANDO SISTEMA");

    lcd.begin(20,4);
    lcd.init();                  
    lcd.backlight();// turn on LCD backlight  
   // printDate();


     lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("INICIANDO... ");
    delay(3000);

    //pinMode(BotonInterno.Pin, INPUT);
//    attachInterrupt(BotonInterno.Pin, isr, RISING);

//    /****** conexion**************/
//  WiFi.begin(WLAN_SSID, WLAN_PASS);
//  while (WiFi.status() != WL_CONNECTED) {
//      lcd.clear();
//    lcd.setCursor(0, 1);
//    lcd.print("    Conectando...   ");
//        delay(200);
//    lcd.clear();
//        delay(200);
//     }
//
//     lcd.clear();
//    lcd.setCursor(0, 1);
//    lcd.print("   CONECTADO A RED!!   ");
//
//  
//  /******subscripciones****/
//  mqtt.subscribe(&BloqueoTotal);
//  mqtt.subscribe(&seguridad);
//  mqtt.subscribe(&Cerradura);

printDate();
}



 


//
//void serialEvent(){
//        // Serial.print("############# DATO SERIAL ############");
//               
//      //Recepción de datos Seriales
//      while (Serial.available()) {              //Si existen datos seriales, leer a todos
//         char inChar = (char)Serial.read();
//         cadenaCharEntrada+= inChar;
//         if (inChar=='\n'){
//         nuevoDato=true;
//         }
//      }
//    
//     if (nuevoDato){
//        dato=cadenaCharEntrada.toInt();
//       //Serial.println(dato);
//          
//          // 1 -> abre la puerta
//          // 2 -> puerta Bloqueada
//          // 3 -> seguridad 
//          // 4 -> Acceso libre
//          if (dato==1) {
//              if((millis()-t_Face)>=T_Face){
//                  lcd.clear();
//                    lcd.setCursor(0, 1);
//                    lcd.print("  Rostro detectado! ");
//                    delay(500);
//                if(Flag_acceso) DoorOpen();
//                t_Face=millis();
//
//              }
//          }
//          if (dato==2) Flag_acceso=false;
//          if (dato==3) {
//              Flag_acceso= true;
//              Flag_seguridad =true;
//              }
//          if (dato==4){
//              Flag_acceso=true;
//              Flag_seguridad=false;
//          }
//          if (dato==50){
//              lcd.clear();
//             lcd.setCursor(0, 0); 
//                lcd.print("  Camara iniciada     ");
//                delay(2000);
//                printDate();
//          }
//      
//        
//        nuevoDato=false;
//        cadenaCharEntrada="";
//     }
//
//} 

void AccessCtrl(){
//    bool OUT=false;
    if (Flag_acceso){
//        t_Access=millis();

//    if(Flag_seguridad==false){
//        lcd.clear();
//        lcd.setCursor(0, 0); 
//        lcd.print("       HOLA!!!      ");  // Impresión de un mensaje en la LCD
//        lcd.setCursor(0, 1);    // Mover cursor a la segunda línea
//        lcd.print("   Presiona # ... ");
//        
//        while(((millis()-t_Access)<TWD_Access)&&OUT==false){ 
//            if (Serial.available()) serialEvent();
//            Get_MQTT_Data();
//            char customKey = customKeypad.getKey();
//            if (customKey){
//                if(customKey=='#'){
//                    DoorOpen();    
//                }
//            
//            else  if (customKey == '*') {   // Tecla "Cancel/Lock" presionada para limpiar LCD...
//                    lcd.clear();
//                    lcd.setCursor(0, 1);
//                    lcd.print("  ACCESO CANCELADO  ");
//                    delay(3000);
//                    printDate();
//                
//                    delay(2000);
//                    OUT=true;
//                }
//                delay(40);
//        }}
//    }else{
//    lcd.clear();
//    lcd.setCursor(0, 0); 
//    lcd.print("       HOLA!!!      ");  // Impresión de un mensaje en la LCD
//    lcd.setCursor(0, 1);    // Mover cursor a la segunda línea
//    lcd.print("Mira a la camara ");
//    lcd.setCursor(0, 2);    // Mover cursor a la segunda línea
//    lcd.print("  ingresa el PIN... ");
//    lcd.setCursor(0, 3);
//    //lcd.cursor(); 
    
    while(((millis()-t_Access)<TWD_Access)&&OUT==false){ 
        if (Serial.available()) serialEvent();
        Get_MQTT_Data();
        char customKey = customKeypad.getKey();
        if (customKey){
            
            if (customKey && (keycount < 4) && (customKey != '#') && (customKey != '*')) {
                lcd.print('*');             // Enmascaramiento de info, para protección
                code[keycount] = customKey;
                keycount++;
                t_Access=millis();
            }
            else  if (customKey == '*') {   // Tecla "Cancel/Lock" presionada para limpiar LCD...
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("  ACCESO CANCELADO  ");
                delay(3000);
                printDate();
                code[0]='F';
                code[1]='F';
                code[2]='F';
                code[3]='F';
                keycount=0;
                delay(3000);
                OUT=true;
            }
            else if(customKey=='#'){
                bool validation=PasswordValidation(code);
                code[0]='F';
                code[1]='F';
                code[2]='F';
                code[3]='F';
                keycount=0;
                if (validation)                   
                    DoorOpen();
                else {
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("   ACCESO DENEGADO  ");
                delay(3000);
                printDate();
                delay(2500);   
                }
                OUT=true;
            }
        }
        delay(40);
    }}

    }else{
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("  ACCESO BLOQUEADO  ");  // Impresión de un mensaje en la LCD  
    delay(2000);
    
    }
    printDate();
}

bool PasswordValidation(char code[4]){
    if ((code[0] == '1') && (code[1] == '5') && (code[2] == '9') && (code[3] == 'D'))
         return true;
    else return false;
}




//-------------------------funciones de ultrasonico---------------------
void GetDistance(Ultrasonico ultra) {
   if((millis()-ultra.t_transcurrido)>=ultra.Tmuestreo){
      long duration, distanceCm;
      
      digitalWrite(ultra.Trigger, LOW);  //para generar un pulso limpio ponemos a LOW 4us
      delayMicroseconds(4);
      digitalWrite(ultra.Trigger, HIGH);  //generamos Trigger (disparo) de 10us
      delayMicroseconds(10);
      digitalWrite(ultra.Trigger, LOW);
      
      duration = pulseIn(ultra.Echo, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
      
      ultra.distance= duration * 10 / 292/ 2;   //convertimos a distancia, en cm

      
     // Serial.print("       Distancia:  ");
    //   Serial.print(ultra.distance);

    //   Serial.print("     IR:  ");
    //   Serial.println(digitalRead(IRsensor));
      ultra.t_transcurrido=millis();

      DowithDistance( ultra);
   }
}

void DowithDistance(Ultrasonico Ultra){
   if (Ultra.distance<=30){
     // Serial.println(" hay una persona");
      AccessCtrl();
   }

}

//-------------------------funciones de puerta-------------------------
void DoorOpen(){
    t_OpenDoor=millis();
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("   Abriendo puerta  ");
    lcd.setCursor(0, 2);
    lcd.print("      Empuje ");
  // Serial.println("########## Abriendo puerta #########");
   digitalWrite(Door, LOW);  
   PuertaE.publish("1");
   while (digitalRead(IRsensor)==LOW)
   {
     delay(100);
    // Serial.println("Cerradura abierta, empuja la puerta ");
     if ((millis()-t_OpenDoor)>TWD_OpenDoor) break;
   }
   //Serial.println("######### Cerrando puerta ######### ");
   digitalWrite(Door, HIGH);  
   PuertaE.publish("0");
    printDate();
    delay(1000);
    
}


//-----------------funciones de pantalla-------------------------
void printDate(){
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("    Magnolias 311   ");
    lcd.setCursor(0, 2);
    lcd.print("  Colonia Floresta  ");
}


//-------------------funicones de teclado--------------------------






//--------------------- Conecion MQTT ----------------------------------
/*************reconexion con la red**************/
//void MQTT_connect() {
//  int8_t ret;
//
//    if (mqtt.connected()) {
//      return;
//    }
//    // Serial.print("Connecting to MQTT... ");
//    lcd.clear();
//    lcd.setCursor(0, 1);
//    lcd.print("Connecting to MQTT");
//
//  uint8_t retries = 3;
//
//    lcd.clear();
//    lcd.setCursor(0, 1);
//    lcd.print("     . ");
//        delay(200);
//    lcd.print(". ");
//        delay(200);
//    lcd.print(". ");
//        delay(200);
//  
//  while ((ret = mqtt.connect()) != 0) {        
//            mqtt.disconnect();
//            delay(5000);  
//            retries--;
//            
//            if (retries == 0) {
//              lcd.print(". ");
//              delay(5);
//            }
//     }
//     
////   Serial.println("MQTT Connected!");
//    lcd.clear();
//    lcd.setCursor(0, 1);
//    lcd.print("Connected to MQTT!!");
//    delay(3000);
//    printDate();
//}
//
//
//void Get_MQTT_Data(){
//  //  if((millis()-t_MQTT)>=T_MQTT){ 
//        //Serial.println("'''''''''''''''''''''qqqqqqqqqqqqqqq'''''''''''''''''''''");     
//        MQTT_connect();
//        Adafruit_MQTT_Subscribe *subscription;
//        /*******lectura de subscripciones********/
//        while ((subscription = mqtt.readSubscription(300))) {
//
//            //lectura de puerta
//            if (subscription == &Cerradura) {
//             //   Serial.println("Cerradura 3333333333333333");    
//                    char Cerradura_state = *Cerradura.lastread;              
//                    if(Cerradura_state=='A'){  
//                        lcd.clear();
//                        lcd.setCursor(0, 1);
//                        lcd.print("  MQTT Abriendo   ");
//                        delay(500);
//                        DoorOpen();  
//                        // Serial.println("Cerradura abierta por adafruit");                                   
//                    }
//            }      
//
//            //Lesctura de Control manual
//            if (subscription == &seguridad) {
//               // Serial.println("Seguridad 3333333333333333333333"); 
//                    char seguridad_state = *seguridad.lastread;
//                    if(seguridad_state=='A'){
//                        Flag_seguridad=true;
//                        // Serial.println("Seguridad Activada por adafruit");    
//                        lcd.clear();
//                        lcd.setCursor(0, 1);
//                        lcd.print(" Seguridad Activada ");
//                        delay(500);
//                    }
//                    if(seguridad_state=='D'){
//                        Flag_seguridad=false;
//                        lcd.clear();
//                        lcd.setCursor(0, 1);
//                        lcd.print("SeguridadDesactivada");
//                        delay(500);
//                        // Serial.println("Seguridad Desactivada por adafruit");   
//                    }  
//            }     
//
//            if (subscription == &BloqueoTotal) {
//              //  Serial.println("Bloqueo 333333333333333333333333");  
//                    char BloqueoTotal_state = *BloqueoTotal.lastread;
//                    if(BloqueoTotal_state=='E'){
//                        lcd.clear();
//                        lcd.setCursor(0, 1);
//                        lcd.print(" Bloqueado MQTT ");
//                        delay(500);
//                        Flag_acceso=false;
//                        // Serial.println("Bloqueo Activado por adafruit");   
//                    }
//                    if(BloqueoTotal_state=='A'){
//
//                        lcd.clear();
//                        lcd.setCursor(0, 1);
//                        lcd.print(" Desbloqueado MQTT ");
//                        delay(500);
//                        Flag_acceso=true;
//                        // Serial.println("Bloqueo desactivado por adafruit");  
//                    }  
//            }     
//
//
//        }
//    // t_MQTT=millis();
//    // }
//}
//






//
//void loop() {
// GetDistance(ultrasonico);
//
// if (Serial.available()) serialEvent();
//
////  if (BotonInterno.Pressed) {
////     BotonInterno.Pressed=false; 
////      if(Flag_acceso){
////         lcd.clear();
////         lcd.setCursor(0, 1);
////         lcd.print("   Abriendo Desde ");
////         lcd.setCursor(0, 2);
////         lcd.print("      adentro");
////         delay(1000); 
////       DoorOpen();  
////      }    
////  }
//
//
//  Get_MQTT_Data();
//
// delay(80);
//   
//}
