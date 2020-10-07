//******************************************************************************
// Contador de Objetos empleando un desplegador de 7 segmentos, 4 dígitos.
// Se requiere implementar dos elementos que determinen el cruce del objeto
//==============================================================================
//---[BIBLIOTECAS]---
//Para el manejo de la pantalla de cristal liquido utilizando el protocolo I2C.

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
void Pantalla();// declaracion de funcion de impresion de pantalla


//========[DEFINICIONES]========
// Definicion de direccion de la pantalla LCD
LiquidCrystal_I2C lcd(0x27,20,4);

//Definicion de pines para los botones 

const int up = 10;
const int down = 9;
int cc = 0;


int Count = 0;



void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // Inicializar las terminales digitales

//========[INICIALIZACION DE LCD]========
  lcd.begin(20,4);   
  lcd.init();                      
  lcd.backlight();
//--primer despliegue en pantalla---
  lcd.setCursor(0,0);
  lcd.print("   ==PROYECTO 3==");
  
  lcd.setCursor(0,1);
  lcd.print("      Contador");

  lcd.setCursor(0,2);
  lcd.print("     Total: ");
  lcd.print(Count);

  lcd.setCursor(0,3);
  lcd.print("presiona los botones");
  
  
//========[INICIALIZACION DE ENTRADAS DIGITALES]========
  pinMode(up, INPUT);     // Teclas o sensores de paso o proximidad
  pinMode(down, INPUT);

  digitalWrite(up, HIGH); // "Pull-Up" para entradas
  digitalWrite(down, HIGH);
  


    
  Serial.begin(9600); 
}


//-----[ LAZO PRINCIPAL ]-----
void loop() {
  if (digitalRead(down) == LOW)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    while (digitalRead(down) == LOW); // Espera hasta que tenga un nivel "LOW"
    if (Count > 0)                      // Conteo mínimo a cero
    {
    Count--;
    Pantalla();   //Llamada a funcion de desppliegue
    }
    digitalWrite(LED_BUILTIN, LOW);
  }
  
  if (digitalRead(up) == LOW)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    while (digitalRead(up) == LOW);   // Espera hasta que tenga un nivel "LOW"
    if (Count < 10000)                // Conteo máximo de 9999
    {
      Count++;
      Pantalla();//Llamada a funcion de desppliegue
    }
    digitalWrite(LED_BUILTIN, LOW);
  }

  delay(50);
}


//-----[ RUTINAS de despliegue en pantalla ]-----
 
void Pantalla()
{

 lcd.setCursor(0,0);
  lcd.print("   ==PROYECTO 3==");
  
  lcd.setCursor(0,1);
  lcd.print("      Contador");

  
  lcd.setCursor(0,2);
  lcd.print("     Total: ");
  lcd.print(Count);

 
  lcd.setCursor(0,3);
  lcd.print("presiona los botones");
}
//******************************************************************************
