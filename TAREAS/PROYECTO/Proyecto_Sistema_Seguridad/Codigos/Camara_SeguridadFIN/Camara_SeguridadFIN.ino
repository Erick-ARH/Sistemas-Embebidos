int a=1;
#define IO_USERNAME  "LazaroAD"
#define IO_KEY       "aio_RNKL63u8bKDWKEOB03cRJbwgTWx6"

#define WIFI_SSID       "INFINITUMAAEE_2.4"
#define WIFI_PASS       "krBLdkz36G"

#include "AdafruitIO_WiFi.h"

#if defined(USE_AIRLIFT) || defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE) ||         \
    defined(ADAFRUIT_PYPORTAL)
// Configure the pins used for the ESP32 connection
#if !defined(SPIWIFI_SS) // if the wifi definition isnt in the board variant
// Don't change the names of these #define's! they match the variant ones
#define SPIWIFI SPI
#define SPIWIFI_SS 10 // Chip select pin
#define NINA_ACK 9    // a.k.a BUSY or READY pin
#define NINA_RESETN 6 // Reset pin
#define NINA_GPIO0 -1 // Not connected
#endif
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS, SPIWIFI_SS,
                   NINA_ACK, NINA_RESETN, NINA_GPIO0, &SPIWIFI);
#else
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#endif
#if defined(ARDUINO_ARCH_ESP32)
  // ESP32Servo Library (https://github.com/madhephaestus/ESP32Servo)
  // installation: library manager -> search -> "ESP32Servo"
  #include <ESP32Servo.h>
#else
  #include <Servo.h>
#endif

AdafruitIO_Feed *servo_vertical = io.feed("PosicionVertical");
AdafruitIO_Feed *servo_horizontal = io.feed("PosicionHorizontal");
AdafruitIO_Feed *CLampara = io.feed("ControlLampara");




#include<Wire.h>
//#include <ESP32Servo.h>
Servo servo1;
Servo servo2;
int servo1Pin = 2;
int servo2Pin = 15;
//int pos = 0; 
int minUs = 000;
int maxUs = 2000;
int pos_ant1=90;
int pos_ant2=90;
//SP32PWM pwm;

String cadenaCharEntrada = "";  
bool nuevoDato = false;
 byte data[] = {0, 255, 255};
const size_t dataLength = sizeof(data) / sizeof(data[0]);
int angulo=0;
int dato;

// #define PinServo 6
// #define PulsoMax 1000
// #define PulsoMin 2000
// //#define DEBUG(a)// Serial.println(a);

#define PIR 14
#define Lampara 4
#define LDRPIN 12
#define SETLDR 1000
 int LDRVal=0;
 boolean Lampara_State=false;
 boolean PIR_State=false;

unsigned long TLamparaON = 10000;
unsigned long TLamAcum=0;
unsigned long TCtrlLamp = 200;
unsigned long TCtrlLampAcum=0;
unsigned long Tinit=0;
unsigned long Tend=0;

int Ctrl_Lamp_State=3; 
// 0-> lampara apagada indefinidamente
// 1-> lampara encendida indefinidamente
// 2-> lampara encendida toda la noche
// 3-> lampara encendida con movimiento de noche



//Viral Science www.youtube.com/c/viralscience  www.viralsciencecreativity.com
//ESP Camera Artificial Intelligence Face Detection Automatic Door Lock
#include "esp_camera.h"
#include <WiFi.h>

//
// WARNING!!! Make sure that you have either selected ESP32 Wrover Module,
//            or another board which has PSRAM enabled
//
//
// Select camera model
//#define CAMERA_MODEL_WROVER_KIT
//#define CAMERA_MODEL_ESP_EYE
//#define CAMERA_MODEL_M5STACK_PSRAM
//#define CAMERA_MODEL_M5STACK_WIDE
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

const char* ssid = "INFINITUMAAEE_2.4";
const char* password = "krBLdkz36G";

void startCameraServer();

boolean matchFace = false;
boolean activateRelay = false;
long prevMillis=0;
int interval = 5000;



TaskHandle_t Tarea1;

void setup() {
Serial.begin(115200);
  
 




  

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  //init with high specs to pre-allocate larger buffers
  if(psramFound()){
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
   // Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  sensor_t * s = esp_camera_sensor_get();
  //initial sensors are flipped vertically and colors are a bit saturated
  if (s->id.PID == OV3660_PID) {
    s->set_vflip(s, 1);//flip it back
    s->set_brightness(s, 1);//up the blightness just a bit
    s->set_saturation(s, -2);//lower the saturation
  }
  //drop down frame size for higher initial frame rate
  s->set_framesize(s, FRAMESIZE_QVGA);

#if defined(CAMERA_MODEL_M5STACK_WIDE)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }
  //Serial.println("");
 // Serial.println("WiFi connected");

  startCameraServer();

  //Serial.print("Camera Ready! Use 'http://");
  //Serial.print(WiFi.localIP());
  //Serial.println("' to connect");




 pinMode(PIR, INPUT);
  pinMode(Lampara, OUTPUT);
  
  
 // Serial.setDebugOutput(true);
  //Serial.println();
   
    Serial.println("  Arranca");
  servo1.attach(servo1Pin, minUs, maxUs);
  servo2.attach(servo2Pin, minUs, maxUs);

    servo1.write(90);
    servo2.write(90);


    io.connect();
    servo_vertical->onMessage(handleVerticalMessage);
    servo_horizontal->onMessage(handleHorizontalMessage);
    CLampara->onMessage(CLamparaMessage);
    
    while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);

    servo_vertical->get();
    servo_horizontal->get();
    CLampara->get();
  }


  xTaskCreatePinnedToCore(
      loop_tarea1, /* Funcion de la tarea1 */
      "Tarea1", /* Nombre de la tarea */
      10000,  /* Tamaño de la pila */
      NULL,  /* Parametros de entrada */
      0,  /* Prioridad de la tarea */
      &Tarea1,  /* objeto TaskHandle_t. */
      0); /* Nucleo donde se correra */
       Serial.print("set up se corre en el nucleo: ");
  Serial.println(xPortGetCoreID());
}



void loop_tarea1(void * pvParameters)
{
  Serial.print("Tarea1 se corre en el nucleo: ");
  Serial.println(xPortGetCoreID());
  while(1)
  {
     io.run();
    if (Serial.available()) serialEvent();


    digitalRead(LDRPIN);
    PIR_State=digitalRead(PIR);

    Serial.print("LDR: ");
    Serial.print(LDRVal);
    Serial.print("    PIR ");
    Serial.println(PIR_State);


    
    Ctrl_LampAutomatica();
        
  }
}

void loop() {
  
  while( a==1){
  Serial.print("loop se corre en el nucleo: ");
  Serial.println(xPortGetCoreID());
  a=3;
  }
   
}





void Ctrl_LampAutomatica(){
    if(millis()-TCtrlLampAcum>=TCtrlLamp){
    switch (Ctrl_Lamp_State){

        case 0:
            digitalWrite(Lampara,LOW);
        break;

        case 1:
            digitalWrite(Lampara,HIGH);
        break;

        case 2:
            LDRVal=digitalRead(LDRPIN);
            if (LDRVal==1)
                digitalWrite(Lampara,HIGH);
            else
                digitalWrite(Lampara,LOW);
        break;

        case 3:
             LDRVal=digitalRead(LDRPIN);
            if (LDRVal==1){
                if (digitalRead(PIR)){
                    Serial.println("-------LAMPARA ON--------");
                    digitalWrite(Lampara,HIGH);
                    TLamAcum=millis();
                }             

                if(millis()-TLamAcum>TLamparaON){
                digitalWrite(Lampara,LOW);
                Serial.println("-------LAMPARA OFF--------");
                } 
            }
        break;
    }
    TCtrlLampAcum=millis();
    }
}




void serialEvent(){
    Serial.print("############# DATO SERIAL############");
           
  //Recepción de datos Seriales
  while (Serial.available()) {              //Si existen datos seriales, leer a todos
     char inChar = (char)Serial.read();
     cadenaCharEntrada+= inChar;
     if (inChar=='\n'){
     nuevoDato=true;
     }
  }

    if (nuevoDato){
        dato=cadenaCharEntrada.toInt();
            
        if(dato==0)  Ctrl_Lamp_State=0;
        if(dato==1)  Ctrl_Lamp_State=1;
        if(dato==2)  Ctrl_Lamp_State=2;
        if(dato==3)  Ctrl_Lamp_State=3;
        

        if(dato<=1180&&dato>=1000){
                angulo=dato-1000;
                moveServo(1,angulo,pos_ant1);
                pos_ant1=angulo;
                Serial.println("accion servo1");
        }

        if(dato<=2180&&dato>=2000){
            angulo=dato-2000;
            moveServo(2,angulo,pos_ant2);
            pos_ant2=angulo;
            Serial.println("accion servo2");
        }


        nuevoDato=false;
        cadenaCharEntrada="";
    }

} 

void moveServo(int servo, int angulo, int _ant){
    Serial.println(angulo);
    Serial.println(_ant);
   int pos;//=angulo;
    if (angulo>_ant){
        Serial.println("Aumento");
        for (pos = _ant; pos <= angulo; pos += 1) { // sweep from 180 degrees to 0 degrees
        if(servo==1) servo1.write(pos);
        if(servo==2) servo2.write(pos);
        Serial.print("................");
        Serial.println(pos);
    delay(10);
    
      }


    
    } else if(angulo<_ant){
        Serial.println("disminuyo");
        for (pos = _ant; pos >= angulo; pos -= 1) { // sweep from 180 degrees to 0 degrees
            if(servo==1) servo1.write(pos);
            if(servo==2) servo2.write(pos);
            Serial.print("................");
            Serial.println(pos);
            delay(15);
        }
    }
}





void handleVerticalMessage(AdafruitIO_Data *data) {

  // convert the data to integer
  int angle = data->toInt();

  // make sure we don't exceed the limit
  // of the servo. the range is from 0
  // to 180.
  if(angle < 0)
    angle = 0;
  else if(angle > 180)
    angle = 180;

  moveServo(2,angle,pos_ant2);
  Serial.print("Vertical: ");
  Serial.println(angle);
  pos_ant2=angle;

}


void handleHorizontalMessage(AdafruitIO_Data *data) {

  // convert the data to integer
  int angle = data->toInt();

  // make sure we don't exceed the limit
  // of the servo. the range is from 0
  // to 180.
  if(angle < 0)
    angle = 0;
  else if(angle > 180)
    angle = 180;

  moveServo(1,angle,pos_ant1);
  Serial.print("Horizontal: ");
  Serial.println(angle);
    pos_ant1=angle;
}
void CLamparaMessage(AdafruitIO_Data *data) {

  // convert the data to integer
  int dato = data->toInt();

  if(dato==1){
      if(Ctrl_Lamp_State<3) Ctrl_Lamp_State++;
    else Ctrl_Lamp_State=0;
    
        Serial.print("Estado de control de lampara ");     
    Serial.println (Ctrl_Lamp_State);            
  }
}
