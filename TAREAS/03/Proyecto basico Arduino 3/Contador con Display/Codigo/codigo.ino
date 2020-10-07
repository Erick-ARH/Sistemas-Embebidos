//******************************************************************************
// Contador de Objetos empleando un desplegador de 7 segmentos, 4 dígitos.
// Se requiere implementar dos elementos que determinen el cruce del objeto
//==============================================================================
//---[BIBLIOTECAS]---
#include <TimerOne.h>

// en dos posiciones que delimitan la zona de transferencia (Adelante<-> Atrás)
// Definición de conexiones del CI 74HC595 con Arduino
const int Data = 7;
const int Clock = 8;
const int Latch = 6;

const int SEG0 = 5;
const int SEG1 = 4;

const int SEG2 = 3;
const int SEG3 = 2;

// Conexión de las teclas (serán sistemas de detección - ultrasonido,
// infrarrojos, Etc.)
const int up = 10;
const int down = 9;
int cc = 0;
char Value[4];
const char SegData[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

int Count = 0;
//-----[ AJUSTES GENERALES ]-----
void setup() {
  // Inicializar las terminales digitales
  Serial.begin(9600);
  pinMode(Data, OUTPUT);
  pinMode(Clock, OUTPUT);
  pinMode(Latch, OUTPUT);
  pinMode(SEG0, OUTPUT);
  pinMode(SEG1, OUTPUT);
  pinMode(SEG2, OUTPUT);
  pinMode(SEG3, OUTPUT);

  pinMode(up, INPUT);     // Teclas o sensores de paso o proximidad
  pinMode(down, INPUT);

  digitalWrite(up, HIGH); // "Pull-Up" para entradas
  digitalWrite(down, HIGH);

  // Incialización del rastreador del Desplegador
  cc = 0;
  // Ajuste de un Timer con un valor de 100000 microsegundos
  // (ó 0.1 sec - ó 10Hz => El LED parpadea 5 veces, 5 ciclos "on-off", por segundo)
  Timer1.initialize(10000);
  // Aquí se enlaza la rutina de ATENCIÓN a la INTERRUPCIÓN
  Timer1.attachInterrupt(timerIsr);
}
//-----[ LAZO PRINCIPAL ]-----
void loop() {
  char cnt[4];
  if (digitalRead(down) == LOW)
  {
    while (digitalRead(down) == LOW); // Espera hasta que tenga un nivel "LOW"
    if (Count > 0)                      // Conteo mínimo a cero
    {
    Count--;
    }
  }
  if (digitalRead(up) == LOW)
  {
    while (digitalRead(up) == LOW);   // Espera hasta que tenga un nivel "LOW"
    if (Count < 10000)                // Conteo máximo de 9999
    {
      Count++;
    }
  }

  // Despliegue del valor contado en la tira de 7 segmentos
  sprintf(cnt, "%04d", Count);        // Arreglo en "ASCII" del valor a mostrar
  Serial.println(Count);              // Imprimir para depuración
  Value[0] = cnt[0] & 0x0F;           // AND con "0x0F" para remover "upper nibble"
  Value[1] = cnt[1] & 0x0F;           // Ejemplo: el número 2 en ASCII es 0x32, solo
  Value[2] = cnt[2] & 0x0F;           //... se requiere el 2
  Value[3] = cnt[3] & 0x0F;
  delay(50);
}
//==============================================================================
//-----[ RUTINAS de SOPORTE ]-----
// Generación de Dígitos
//----------------------
void DisplayDigit(char d)
{
  int i;
  for (i = 0; i < 8; i++) // Corrimiento de datos en un registro
  {
    if ((d & 0x80) == 0x80)
    {
      digitalWrite(Data, HIGH);
    }
    else
    {
      digitalWrite(Data, LOW);
    }
    d = d << 1;

    // Generación del pulso de reloj
    digitalWrite(Clock, LOW);
    digitalWrite(Clock, HIGH);
  }

  // Captura del dato
  digitalWrite(Latch, LOW);
  digitalWrite(Latch, HIGH);
}
//--------------------------
// ATENCIÓN a la INTERRUPCIÓN
//--------------------------
void timerIsr()
{
  cc++;
  if (cc == 5)  // De momento sólo se tienen 4 dígitos
  {
    cc = 1;
  }
  Scanner();
  TCNT0 = 0xCC;
}
//--------------------------------------------------
// Función de Rastreo del Desplegador de 7 Segmentos
//--------------------------------------------------
void Scanner() {
  // Impresión de valor de salida para cada dígito
  switch (cc)
  {
    case 1:
      digitalWrite(SEG3, HIGH);
      DisplayDigit(SegData[Value[0]]);
      digitalWrite(SEG0, LOW);
      break;
    case 2:
      digitalWrite(SEG0, HIGH);
      DisplayDigit(SegData[Value[1]]);
      digitalWrite(SEG1, LOW);
      break;
    case 3:
      digitalWrite(SEG1, HIGH);
      DisplayDigit(SegData[Value[2]]);
      digitalWrite(SEG2, LOW);
      break;
    case 4:
      digitalWrite(SEG2, HIGH);
      DisplayDigit(SegData[Value[3]]);
      digitalWrite(SEG3, LOW);
      break;
  }
}

//******************************************************************************
