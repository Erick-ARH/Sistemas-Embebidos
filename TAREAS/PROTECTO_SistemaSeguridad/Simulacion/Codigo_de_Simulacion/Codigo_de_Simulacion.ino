#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#define pir_Pin 6
//---[Habilitación de la LCD]---
//--> CAMBIA para LCD de 20x4, manejada por módulo I2C <--
// Inicializa la LCD
LiquidCrystal_I2C lcd(0x27,20,4);


//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//---[Habilitación del TECLADO]---
const byte ROWS = 4;  // Cuatro hileras del teclado
const byte COLS = 4;  // Cuatro Columnas del teclado
// --> Adaptar al teclado propio <--
// Definición de los símbolos del teclado (serigrafía)
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
// Conexiones a las terminales del teclado:
byte rowPins[ROWS] = {22,23, 24, 25};    // Hileras
byte colPins[COLS] = {26, 27, 28, 29};  // Columnas
// Inicialización de la una instancia del Teclado
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//---[Habilitación de Otros Elementos]---
const int LED_RED = 9;   // LED Rojo (Red)
const int LED_GREEN = 10; // LED Verde (Green)
const int RELAY = 8;     // Relevador de apertura (o motor)
int pir_Value;
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//---[ VARIABLES ]---
char keycount = 0;        // Conteo de intentos
char code[4];             // Retención de teclas oprimidas

//---[AJUSTES]-------------------------------------------------------------------
void setup() {
    // initialize LCD
     Serial.begin(9600);
    pinMode(7,OUTPUT);
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(RELAY, OUTPUT);
  // Ajuste de las características de la LCD (¡Modificar para LCD de 20x4!)
  lcd.begin(20,4);
  lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("INICIANDO SISTEMA DE");
    lcd.setCursor(0, 2);
    lcd.print("      SEGURIDAD");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 2);
    lcd.print("  SISTEMA ACTIVADO");
    delay(2000);
    
//  lcd.print(" Introduce Pasword:");  // Impresión de un mensaje en la LCD
  lcd.setCursor(0, 3);    // Mover cursor a la segunda línea
  lcd.cursor();           // Encender el cursor
    digitalWrite(LED_GREEN, HIGH);  // Prendido
   digitalWrite(LED_RED,LOW);     // Apagado
  digitalWrite(RELAY, LOW );       // Apagado del relevador
 
  printDate();
}
//---[CICLO]--------------------------------------------------------------------
void loop() {
   
  char customKey = customKeypad.getKey();

  if (customKey && (keycount < 4) && (customKey != '#') && (customKey != '*')) {
    // lcd.print(customKey);    // Para imprimir tecla introducida
    lcd.print('*');             // Enmascaramiento de info, para protección
    code[keycount] = customKey;
    keycount++;
  }
  if (customKey == '*') {   // Tecla "Cancel/Lock" presionada para limpiar LCD...
    Lock();                 // ...y cerrar la puerta
  }
  if (customKey == '#') {   // Revisar Password y abrir
    lcd.setCursor(0,1);
    lcd.print("                    ");
    if ((code[0] == '1') && (code[1] == '5') && (code[2] == '9') && (code[3] == 'D'))
      // Verificar el password, por omisión: “169D”
    {
     digitalWrite(LED_GREEN, LOW); // Apaga LED Verde
     digitalWrite(LED_RED, HIGH);  // Enciende LED Rojo
      digitalWrite(RELAY, HIGH);    // Apertura de la puerta
     lcd.clear();
      lcd.setCursor(0, 2);            //
      lcd.print("    = PUERTA = ");  // Muestra mensaje de error
    
      
      lcd.setCursor(0,3);
      lcd.print("    = ABIERTA =");

      delay(3000);  // Se mantiene abierta por 4 segundos
      
      Lock();
    }
    else
    {
      lcd.clear();
      lcd.setCursor(0, 2);            //
      lcd.print("Password Incorrecto");  // Muestra mensaje de error
      delay(1500);    // Espera un momento
    
      Lock();
    }
  }
    pir_Value=digitalRead(pir_Pin);
  Serial.print(pir_Value);
  if(pir_Value==HIGH){
    digitalWrite(7,HIGH);
    Serial.print("Movimiento detectado");
    }
    else{
      digitalWrite(7,LOW);
      Serial.print("No detectado");
      }
      
}
//******************************************************************************
//-----[ SUBRUTINAS y FUNCIONES ]-----
//---[Cerradura de Puerta y ACtualización de mensaje en la LCD ]---
void Lock() {
  lcd.clear();
  lcd.setCursor(0, 2);            //
  lcd.print("    = PUERTA =");  //
  lcd.setCursor(0, 3);            //
  lcd.print("    = CERRADA =");  //
  delay(1500); // Espera un tiempo
 
//  lcd.setCursor(0, 1);            //
//  lcd.print("                ");  // Limpieza del password
//  lcd.setCursor(0, 1);
  lcd.clear();
  lcd.setCursor(0, 0);    // Mover cursor a la segunda línea
  lcd.print("    Magnolias 311");  // Impresión de un mensaje en la LCD
 lcd.setCursor(0, 1);    // Mover cursor a la segunda línea
  lcd.print("  Colonia Floresta  ");  // Impresión de un mensaje en la LCD
   lcd.setCursor(0, 2);    // Mover cursor a la segunda línea
  lcd.print(" Introduce Pasword:");  // Impresión de un mensaje en la LCD
 
   lcd.setCursor(0, 3);
  lcd.cursor();           // Encender el cursor
 
  keycount = 0;                   // Reinicia número de intentos
  digitalWrite(LED_GREEN, HIGH);  // LED Verde
 digitalWrite(LED_RED, LOW);     // LED Rojo
  digitalWrite(RELAY, LOW);       // Cierra la puerta
}

void printDate(){
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("    Magnolias 311   ");
    lcd.setCursor(0, 2);
    lcd.print("  Colonia Floresta  ");
}
