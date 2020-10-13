// la libreria tier one nos miermiete realizar interrupciones temporales 

#include <TimerOne.h>



const int led = LED_BUILTIN;  // delcaracion de la varialble para el led 

int ledState = LOW; // inicializacion de la variable de estado del led 

void setup(void)
{
  pinMode(led, OUTPUT);
  Timer1.initialize(500000); // configuracion del tiempo en microsegundos .
  //funcion que llamara la interrupcion cada que se cumpla el tiempo
  Timer1.attachInterrupt(Mensaje);
  Serial.begin(57600);// inicializacion de puerto serial 
}



//funcion invocada por la interrupcion de tiempo, 
//esta se ejecutara cada que se cumpla el plazo
void Mensaje(void)
{
  //mensaje en la terminal serial 
  Serial.println("---Interrupcion de tiempo (cada 500ms)--- ");
  //control de led 
  if (ledState == LOW) {
    ledState = HIGH;
 
  } else {
    ledState = LOW;
  }
  digitalWrite(led, ledState);
  
  
}


//ciclo principal 
void loop(void)
{
 
}
