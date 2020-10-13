/*
 **********************************************************************************
   Ejemplo de interrupcion  Serial Event:
Cada vez que llegan nuevos datos en serie, éste sistem los agrega a una cadena de
caracteres. Cuando se recibe una nueva linea, el bucle imprime la cadena y la 
borra.Compara dos tipos de cadenas y actua en funcion de ON y OFF, encendiendo un 
led.

NOTA: La funcion serial event() no esta disponible en Leonardo, Micro u otras 
placas basadas en el
ATmega32U4. 
**********************************************************************************
*/
//========[BIBLIOTECAS]===========================================================
//No se requieren Bibliotecas especiales
//========[VARIABLES DE ENTRADA]==================================================

String entrada = "";        // Cadena donde se almacenarán los caracteres.
bool cadenacompleta = false;// Estado logico que indica si la cadena esta completa
String Encendido="encendido";//Cadena de caracteres que se compara
String Apagado="apagado";    //Cadena de caracteres que se compara
//========[AJUSTES GENERALES]=====================================================
void setup() {
  
  pinMode(13,OUTPUT); //Establece pin 13 como salida
  Serial.begin(57600);// Inicializa el puerto serial
  
  entrada.reserve(200);// Instancia reservada de 200 bytes.
}
//========[LAZO PRINCIPAL]========================================================
void loop() {
 
  //Compara cadena de caracteres de entrada [El led se enciende o apaga]
  if (entrada==Encendido){
  digitalWrite(13, HIGH);
  }
  if (entrada==Apagado){
  digitalWrite(13,LOW);
  }
   // Imprime la cadena si la cadena esta completa
  if (cadenacompleta) {
     Serial.println();
    Serial.println("Cadena introducida: " + entrada);
   
    entrada = "";
    cadenacompleta = false;
  }
}
/*
  SerialEvent se activa siempre que un nuevo dato viene en el Rx serie de hardware
  Ésta rutina se ejecuta en cada ciclo(). Puede haber varios bytes de datos
  disponibles.
*/
//===========[EVENTO]===============================================================

void serialEvent() {
  while (Serial.available()) {
    // Lee nuevos caracteres de entrada
    char caracter = (char)Serial.read();
    // Si el caractere es una nueva linea considera que la cadena esta completa y se 
    //puede imprimir.
    if (caracter == '.') {
      cadenacompleta = true;
    }
    else {entrada += caracter; //Agrega caracter a la cadena
    }
  }
}
