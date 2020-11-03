#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT11   // DHT 11
unsigned long T_DHT =0;

#include<Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // dependiendo del fabricante del LCD el codigo 0x27 puede cambiar
DHT dht(DHTPIN, DHTTYPE);


#define DT  2       // DT a pin digital 2 (DT en modulo) Pin de la interrupcion 
#define CLK  4      // CLK a pin digital 4 (CLK en modulo)
#define btn 3       // Swiche del encoder al pin 3 Pin de interrupcion
#define LED1 8
#define LED2 9
//#define Atras_menu Estado_menu=(Estado_menu-1)/10; Bandera_menu=1;
#define Home 10
#define Limite_tiempo_menu 15000  //(milisegundos)
unsigned long TMenu=0;
boolean BanderaWD=true;

String  Nombre="...";


//prototipado de funciones  a utlizarce
void Actualizacion_menu();                      // en este se  definen los menus y submenus
void Impresion( String *arrayMenu, int size);   //despliega los menus y el cursor
void encoder();                                 //interrucion de encoder, define el contador de jiro
void encoder_boton();                           //interrupcion del boton del encoder, define la navegacion y jerarquia de menus
void Contador();                                //

//variables volatiles manejadas por interrupciones y menus
volatile int posicion_encoder = 0;  // Posicion acumulada del encoder
volatile int Bandera_menu = 1;      // Valor anterior de la posicion del encoder
volatile int Estado_menu = Home;       //localizacion de direccionamiento dentro de menus o submenus
volatile int Estado_anterior_menu=Home;  //localizacion desplegada dentro de menus o submenus
int posicion_anterior_encoder=0;

//Variables de funciones anidadas
  //contador
int Contador_Acumulado = 0;
  //leds
boolean ELED1=false;
boolean ELED2=false;
boolean FLED1=false;
boolean FLED2=false;
unsigned long TLED1=0;
unsigned long TLED2=0;
unsigned long PLED1=1000;
unsigned long PLED2=1000;


void setup() {
  dht.begin();
  // Declaracion de interrupciones
  //                                   pin,  funcion, tipo de señal;  
  attachInterrupt(digitalPinToInterrupt(DT), encoder, LOW);   //rotacion
  attachInterrupt(digitalPinToInterrupt(btn), encoder_boton, LOW); //click
 // Serial.begin(9600);
  //definicion de pines
  pinMode(DT, INPUT);
  pinMode(CLK, INPUT);
  pinMode(btn, INPUT_PULLUP);    // Entrada con resistencia Pullup para el Switch del encoder
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);

  digitalWrite(LED1,HIGH);
  digitalWrite(LED2,HIGH);
  //Se inicializa la pantalla LCD y se despliega el mensaje inicial
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" INICIANDO");
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print(" INICIANDO.");
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print(" INICIANDO..");
  delay(500);
  lcd.setCursor(0, 0);
  lcd.print(" INICIANDO...");
  delay(500);
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  Actualizacion_menu(); //primer despliegue de menu
 
}

//+++++++++++ CICLO PRINCIPAL DEL SISTEMA++++++++++++++++
void loop() {

  if (Estado_menu==10){
   if(millis()-T_DHT>=500){
      Bandera_menu=1;
      T_DHT=millis();
    }
  }

  Actualizacion_menu();
  

  if (FLED1){
    if(millis()-TLED1>=(PLED1/2)){
      ELED1=!ELED1;
      digitalWrite(LED1,ELED1);
      TLED1=millis();
    }
  }

  if (FLED2){
    if(millis()-TLED2>=(PLED2/2)){
      ELED2=!ELED2;
      digitalWrite(LED2,ELED2);
      TLED2=millis();
    }
    
  }
   WatchDog_Menu();
  posicion_anterior_encoder=posicion_encoder;
}


void WatchDog_Menu(){
  if(BanderaWD==true){
    BanderaWD=false;
    TMenu=millis();
  }
  if(millis()-TMenu>Limite_tiempo_menu)
    Ir_menu(Home);

  
}
//      FUNCION DE IMPLEMENTACION DE  MENUS:
//       La variable estado de menu define que menu o submenu se desplegara 
//       siendo el primer digito el menu principal y los digitos de izquierda
//       a derecha reflejan la jerarquia de los submenus
//      arrayMenu[] contiene todas las opcines a desplegarse en cada menu
//      del mismo mimo modo desde esta rutina podemos llamar a las respectivas de cada opcion de menu.
void Actualizacion_menu() {
 
  if (Bandera_menu == 1) {
    BanderaWD=true; 
  /*Serial.print("Actualiza menu:  ");
  Serial.print(Estado_menu);
  Serial.print("  menu:  ");
  Serial.println(posicion_encoder);*/
    Bandera_menu = 0;
    if (Estado_menu == Home) {
       Pantalla_DHT();
    }
    if (Estado_menu == 0) {
      String arrayMenu[] = {"Manejo de LEDS", "Contador", "Usuario", "Opcion4","opcion5","Salir menu"};
      int size = sizeof(arrayMenu) / sizeof(arrayMenu[0]); //determinacion del tamaño del menu
      Impresion(arrayMenu, size); //Llamada a funcion de impresion 

    } else if (Estado_menu == 1) {
      String arrayMenu[] = {"Atras", "LED1", "LED2"};
      int size = sizeof(arrayMenu) / sizeof(arrayMenu[0]);
      Impresion(arrayMenu, size);
    } else if (Estado_menu == 11) {  
      String arrayMenu[] = {"Salir de LED1", "ON/OFF","frecuencia","ON/OFF frecuencia"};
      int size = sizeof(arrayMenu) / sizeof(arrayMenu[0]);
      Impresion(arrayMenu, size);
    } else if (Estado_menu == 111) {
      ELED1= ON_OFF(LED1,ELED1);
      FLED1=false;
      Ir_menu(11);
    }else if (Estado_menu == 112) {
      PLED1=CambioFrecuencia(PLED1);
    }else if (Estado_menu == 113) {
      FLED1=!FLED1;
      digitalWrite(LED1,LOW);
      Ir_menu(11);
    }else if (Estado_menu == 12) {  
      String arrayMenu[] = {"salir de LED2", "ON/OFF ","frecuencia","ON/OFF frecuencia"};
      int size = sizeof(arrayMenu) / sizeof(arrayMenu[0]);
      Impresion(arrayMenu, size);
    }else if (Estado_menu == 121) {
      FLED2=false;
      ELED2= ON_OFF(LED2,ELED2);
      Ir_menu(12);
    }else if (Estado_menu == 122) {
      PLED2=CambioFrecuencia(PLED2);
    }else if (Estado_menu == 123) {
      FLED2=!FLED2;
      digitalWrite(LED2,LOW);
      Ir_menu(12);
    }

     else if (Estado_menu == 2) {
    contador();

    } else if (Estado_menu == 3) {
      String arrayMenu[] = {"Atras","Lazaro","Erick","Sergio","Paco"};
      int size = sizeof(arrayMenu) / sizeof(arrayMenu[0]);
      Impresion(arrayMenu, size);
    } else if (Estado_menu == 31) {
      Nombre="Lazaro";
      Ir_menu(Home);
    } else if (Estado_menu == 32) {
      Nombre="Erick";
      Ir_menu(Home);
    } else if (Estado_menu == 33) {
      Nombre="Sergio";
      Ir_menu(Home);
    } else if (Estado_menu == 34) {
      Nombre="Paco";
      Ir_menu(Home);
    } 
    
    
    else if (Estado_menu == 4) {
      String arrayMenu[] = {"Atras","posion41","opsion42",};
      int size = sizeof(arrayMenu) / sizeof(arrayMenu[0]);
      Impresion(arrayMenu, size);
    } 
  }
}


//FUNCION QUE CAPTURA EL GIRO DEL ENCODER
void encoder()  {                //Funcion que determina el sentido del giro del encoder
  static unsigned long ultimaInterrupcion = 0;  // variable static con ultimo valor de
  unsigned long tiempoInterrupcion = millis();  // variable almacena valor de func. millis

  if (tiempoInterrupcion - ultimaInterrupcion > 5) {  // No lee posibles rebotes en pulsos menores a 5 mseg.
    if (digitalRead(CLK) == HIGH)     // si CLK es HIGH, rotacion a la derecha
    {
      posicion_encoder-- ;        // incrementa posicion del menu en 1
    } else {                      // si CLK es LOW, rotacion a la izquierda
      posicion_encoder++ ;        // decrementa posicion del menu en 1
    }
    posicion_encoder = min(100, max(0, posicion_encoder));  // numero de opciones del Menu, inferior 0 superior en 5
    ultimaInterrupcion = tiempoInterrupcion;  //actualiza valor del tiempo tiempo
  Bandera_menu = 1;  //bandera de actualizacion de menu
 // Serial.print("jiro  ");
  //Serial.println(posicion_encoder);
  }
  
  
}

//FUNCION QUE CAPTURA EL PULSO DEL ENCODER Y CONTRTOLA LA SINCRONIZACION DE MENUS 
//la variable Estado_Anterior_Menu despliega el estado actual desplegado en el pantalla
// y apartir del cual se determinaran los sigueintes menus
//Estado_menu representa el nuevo estado a desplegar, es decir, a que menu entraremos.
//en el Estado_menu=0 nos direccionaremos al menu principal 
void encoder_boton() {
  static unsigned long ultimaInterrupcion_B = 0;  // variable static con ultimo valor de
  unsigned long tiempoInterrupcion_B = millis();  // variable almacena valor de func. millis
  if (tiempoInterrupcion_B - ultimaInterrupcion_B > 5) {
    switch (Estado_anterior_menu) {
      case Home:
        Estado_menu=0;
        break;
      case 0:
        switch (posicion_encoder) {
          case 0:
            Estado_menu = 1;
            break;
          case 1:
            Estado_menu = 2;
            break;
          case 2:
            Estado_menu = 3;
            break;
          case 3:
            Estado_menu = 4;
            break;
          case 5:
            Estado_menu = Home;
            break;
          }
        break;

      case 1:
        switch (posicion_encoder) {
          case 0:
            Estado_menu = 0;
            break;
          case 1:
            Estado_menu = 11;
            break;
          case 2:
            Estado_menu = 12;
            break;
          }
        break;
      case 11:
        switch (posicion_encoder) {
          case 0:
            Estado_menu = 1;
            break;
          case 1:
            Estado_menu = 111;
            break;
          case 2:
            Estado_menu=112;
            break;
          case 3:
            Estado_menu=113;
            break;
          }
        break;
      case 111:
        switch (posicion_encoder) {
          case 0:
            Estado_menu = 11;
            break;
        }
        break;
      case 112:
        Estado_menu=11;
        break;
      case 113:
        Estado_menu=11;
        break;

      case 12:
        switch (posicion_encoder) {
          case 0:
            Estado_menu = 1;
            break;
          case 1:
            Estado_menu = 121;
            break;
          case 2:
            Estado_menu=122;
            break;
          case 3:
            Estado_menu=123;
            break;
          }
        break;

      case 121:
        switch (posicion_encoder) {
          case 0:
            Estado_menu = 12;
            break;
        }
        break;
      case 122:
        Estado_menu=12;
        break;
      case 123:
        Estado_menu=12;
        break;
      

      case 2:
        Estado_menu=0;
        break;

      case 3:
        switch (posicion_encoder) {
          case 0:
            Estado_menu = 0;
            break;
          case 1:
            Estado_menu = 31;
            break;
          case 2:
            Estado_menu = 32;
            break;
          case 3:
            Estado_menu = 33;
            break;
          case 4:
            Estado_menu = 34;
            break;
          }
        break;
      case 31:
        switch (posicion_encoder) {
          case 0:
            Estado_menu = 3;
            break;
          case 1:
            Estado_menu = 31;
            break;
          case 2:
            Estado_menu = 31;
            break;
          }
        break;
      case 4:
        switch (posicion_encoder) {
          case 0:
            Estado_menu = 0;
            break;
          case 1:
            Estado_menu = 4;
            break;
          case 2:
            Estado_menu = 4;
            break;
          }
        break;
      
    }
    Estado_anterior_menu = Estado_menu;
    posicion_encoder = 0;
    Bandera_menu = 1;
    ultimaInterrupcion_B = tiempoInterrupcion_B;  //actualiza valor del tiempo tiempo
  }
}



//FUNCION QUE IMPRIME EL MENU CORRESPONDIENTE
void Impresion( String *arrayMenu, int size) {
 // Serial.print("menu:  ");
  //Serial.println(posicion_encoder);
  lcd.clear();
  lcd.setCursor(0, 0);
  posicion_encoder = min(size, max(0, posicion_encoder));
  if (posicion_encoder <= 3) {      //Despliega las primeras  opciones del menu
    for (int x = 0; x < size && x <= 3 ; x++) //
    {
      lcd.setCursor(2, x);
      lcd.print(arrayMenu[x]);
    }
    lcd.setCursor(0, posicion_encoder); //ubica el cursor en la posicion correspondiente al encoder
    lcd.print(">");     //imprime el cursor
  } else {
    int menu_Extra = posicion_encoder - 3;     // si la opcion buscada es superior a la 5 despliega las correspondientes
    for (int x = menu_Extra; x < size && x <= (3 + menu_Extra) ; x++) //
    {
      lcd.setCursor(2, x - menu_Extra);
      lcd.print(arrayMenu[x]);
    }
    lcd.setCursor(0, 3);
    lcd.print(">");
  }
}

boolean ON_OFF(int LED,boolean ELED)
{
  ELED=!ELED;
  digitalWrite(LED,ELED);
  return (ELED);
  
  /*
  if(ELED==HIGH)  {
    ELED=LOW;
    digitalWrite(LED,ELED);
  }
  else{
    ELED=HIGH;
    digitalWrite(LED,ELED);
  }
  Estado_menu=11;
  return (ELED);*/
}

void contador(){
  if(posicion_encoder==0){
    posicion_encoder=Contador_Acumulado;
  }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pulsa pasa salir...");
    lcd.setCursor(5, 1);
    lcd.print("Contador:");
    lcd.setCursor(8, 2);
    lcd.print(posicion_encoder);
    Contador_Acumulado = posicion_encoder;
  
}

unsigned long CambioFrecuencia(unsigned long Periodo){
  
  if(posicion_encoder==0){
    posicion_encoder=(1000/Periodo)+posicion_encoder;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pulsa pasa salir...");
  lcd.setCursor(1, 1);
  lcd.print("frecuencia del LED:");
  lcd.setCursor(8, 2);
  lcd.print(posicion_encoder);
  Periodo=1000/posicion_encoder;
  //Serial.print("est es el p    ");
 // Serial.println(Periodo);
  return Periodo;
}

void Ir_menu(int direccion){
  Estado_menu=direccion;
  Estado_anterior_menu=direccion;
  Bandera_menu=true;
  posicion_encoder=0;
}

void Pantalla_DHT(){

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
    t=30;
    h=70;
    }
  
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Lectura DHT: ");
    lcd.setCursor(3, 1);
    lcd.print("T (C):");
    lcd.setCursor(12, 1);
    lcd.print(t);
    lcd.setCursor(3, 2);
    lcd.print("H (%): ");
    lcd.setCursor(12, 2);
    lcd.print(h);
    lcd.setCursor(1, 3);
    lcd.print("Hola ");
    lcd.setCursor(6, 3);
    lcd.print(Nombre);
  
}
