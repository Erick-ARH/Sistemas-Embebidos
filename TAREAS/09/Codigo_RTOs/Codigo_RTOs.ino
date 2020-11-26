//==============================================================================
// Ejemplo del uso de FreeRTOS - Para ESP32
// 
//
//-----------------------------------------------------------------------------
// EJERCICIO PARA TAREA, A EXPLICAR EN EQUIPO:
//-----------------------------------------------------------------------------
// Aumentar el número de tareas a 8, considerando:
// 1.) Para verificar la secuencia de ejecución de las tareas, utilice la
// siguiente notación para la ocurrencia de las tareas:
// 
// Tarea 1: --- 01
// Tarea 2: ----- 02
// Tarea 3: ------- 03
// Tarea 4: --------- 04
// Tarea 5: ----------- 05
// Tarea 6: ------------- 06
// Tarea 7: --------------- 07
// Tarea 8: ----------------- 08
// 
// En la ocurrencia de la tarea agregar si recibió o envió datos a otras 
// Tareas, por ejemplo, la siguiente línea indicaría que en esta instancia
// la Tarea 6 envió algo a la Tarea 4:
// Tarea 6: ------------- 06 [-> 4]
// En el siguiente caso, la Tarea 5 recibió algo de la Tarea 2.
// Tarea 5: ----------- 05 [<-2]

// 2.) Cambiar los siguientes parámetros para ejercitar las diversas opciones:
// a.) Prioridades de las tareas
// b.) Frecuencia de ejecución de las tareas. Algunas de ellas se ejecutarán 
// más veces que otras.//que la 8 se haga tres veces
// c.) Conclusión de las tareas. Algunas tareas terminarán antes que otras.
// que la 7 se haga menos veces
// d.) Comunicación entre tareas. Verificar cuáles son las funciones o 
// directivas que se pueden emplear para que una tarea comunique algo a otra.
// Ejercitar que las comunicaciones se den después de que pasaron varias 
// ejecuciones, por ejemplo, que la tarea 3 comunique a la tarea 5 después de
// que la tarea 3 ha ocurrido por quinta vez. Hacer algo similar para otros
// casos.
// e.) Ejercitar dos características más que crea importantes de FrreRTOS en el
// mismo ejemplo.
// f.) Comentar adecuadamente las líneas del código.
// g.) Para la presentación, puede emplear el monitor serial, simulado o real,
// verificando que efectivamente ocurre la secuencia que planeó.
//==============================================================================
#include <Arduino.h>
//------------------------------------------------------------------------------
//-----[ AJUSTES ]--------------------------------------------------------------
//------------------------------------------------------------------------------
int c;  //variable global
void setup() {
  Serial.begin(112500);
  Serial.println("-- INICIO --"); // 
  delay(1000);
// Creación de las tareas:
  xTaskCreate(
    Tarea1,     // Función que ejecuta la tarea
    "Tarea1",   // Cadena con el nombre de la tarea
    10000,      // Tamaño del "Stack" o pila
    NULL,       // Parámetro pasado como entrada
    1,          // Prioridad de la tarea
    NULL);      // Manejador (Handle) de la tarea
  
xTaskCreate(Tarea2,"Tarea2",10000,NULL,2,NULL);
xTaskCreate(Tarea3,"Tarea3",10000,NULL,3,NULL);
xTaskCreate(Tarea4,"Tarea4",10000,NULL,4,NULL);
xTaskCreate(Tarea5,"Tarea5",10000,NULL,5,NULL);
xTaskCreate(Tarea6,"Tarea6",10000,NULL,6,NULL);
xTaskCreate(Tarea7,"Tarea7",10000,NULL,7,NULL);
xTaskCreate(Tarea8,"Tarea8",10000,NULL,8,NULL);
}
//-----------------------
//-----[ PRINCIPAL ]-----
//-----------------------
void loop() {
  delay(1000);              // Retardo para imprimir 
                            // 
}
//==============================================================================
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-----[ TAREA 1 ]--------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Tarea1( void * parameter ){//Funcion que ejecuta la tarea 1
    for( int i = 0;i<10;i++ ){  // Número de veces que ocurre esta tarea
        switch (i){
          case 0:     // Primera ejecución T1
            Serial.println("--- 01");   // Evidencia de ocurrencia
          break;
          case 1:     // Segunda ejecución T1
            Serial.println("--- 01");   // Evidencia de ocurrencia
          break;
          case 2:     // Tercera ejecución T1
            Serial.println("--- 01");   // Evidencia de ocurrencia
          break;
          case 3:     // Cuarta ejecución T1
            Serial.println("--- 01");   // Evidencia de ocurrencia
          break;
          case 4:     // Quinta ejecución T1
            Serial.println("--- 01");   // Evidencia de ocurrencia
          break;
          case 5:     // Sexta ejecución T1
            Serial.println("--- 01");   // Evidencia de ocurrencia
          break;
          case 6:     // Séptima ejecución T1
            Serial.println("--- 01 [->2]");   // Evidencia de ocurrencia
          break;
          case 7:     // Octava ejecución T1
            Serial.println("--- 01");   // Evidencia de ocurrencia
          break;
          case 8:     // Novena ejecución T1
            Serial.println("--- 01");   // Evidencia de ocurrencia
            // Función para enviar dato a Tarea 6
            //Serial.println("[->6]");
          break;
          case 9:     // Décima ejecución T1
            Serial.println("--- 01");   // Evidencia de ocurrencia
          break;
          default:
            Serial.println("--- 01");   // Evidencia de ocurrencia
          break;
        }
        delay(1000);              // Tiempo de espera para volver al case
    }
    Serial.println("Tarea 01 Terminada");     // Conclusión de la tarea
    vTaskDelete( NULL );          // Se "Borra"
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-----[ TAREA 2 ]--------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Tarea2( void * parameter){//Nombre de la funcion que ejecuta la tarea 02
    for( int i = 0;i<9;i++ ){//Numero de veces que se ejecutara la tarea
        Serial.println("----- 02");//Evidencia de ejecucion de tarea
        delay(1000);//Retardo para regresar al for
    }
    Serial.println("Tarea 02 Terminada");   // Conclusión de la tarea
    vTaskDelete( NULL );//Eliminacion de tarea
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-----[ TAREA 3 ]--------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Tarea3( void * parameter){//Nombre de funcion que ejecuta la tarea 03
    for( int i = 0;i<8;i++ ){//Numero de iteraciones de la tarea
        //Cuando i=5, se enviara informacion a la tarea4
        //La variable global "c" se carga con 1
        if(i==5){Serial.println("------- 03 [-> 4]");
        c=1;}
        else{
        Serial.println("------- 03");}//Evidencia de ejecucion de tarea
        delay(1000);//retardo para regresar al for
    }
    Serial.println("Tarea 03 Terminada");   // Conclusión de la tarea
    vTaskDelete( NULL );//Eliminacion de tarea
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-----[ TAREA 4 ]--------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Tarea4( void * parameter){//Nombre de la funcion que ejecuta la tarea 4
    for( int i = 0;i<7;i++ ){//Numero de iteraciones de la tarea
      //Cuando la varible global cambie a 1 recibirá informaciond de la tarea 8
      //La variable global "c" se carga con 0
      if(c==1){
        Serial.println("--------- 04 [<-8]");
        c=0;
        }else{
        Serial.println("--------- 04");}//Evidencia de ejecucion de tarea
        delay(1000);//Retardo para volver al for
    }
    Serial.println("Tarea 04 Terminada");   // Conclusión de la tarea
    vTaskDelete( NULL );//Eliminacion de tarea
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-----[ TAREA 5 ]--------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Tarea5( void * parameter){//Nombre de la funcion que ejecuta la tarea 5
    for( int i = 0;i<6;i++ ){//Numero de iteracion de de la tarea 5

        Serial.println("----------- 05");//evidencia de ejecucion de la tarea 5
        delay(1000);//Retardo para volver al for
    }
    Serial.println("Tarea 05 Terminada");   // Conclusión de la tarea
    vTaskDelete( NULL );//Eliminacion de tarea
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-----[ TAREA 6 ]--------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void Tarea6( void * parameter){//Nombre de la funcion que ejecuta la tarea 6
     while(1){// Ciclo que determina la ejecucion infinita de la tarea
        
        Serial.println("------------- 06");//Evidencia de ejecucion
        delay(1000);//Retardo para volver al ciclo
    }
    Serial.println("Tarea 06 Terminada");   // Conclusión de la tarea
    vTaskDelete( NULL );//Eliminacion de tarea
}

/*
void Tarea6( void * parameter){
    for( int i = 0;i<5;i++ ){
    
        Serial.println("------------- 06");
        delay(1000);
    }
    Serial.println("--> 06");   // Conclusión de la tarea
    vTaskDelete( NULL );
}
*/
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-----[ TAREA 7 ]--------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Tarea7( void * parameter){//Nombre de la funcion que ejecuta la tarea 7
  while(1){//Ciclo que determina la ejecucion infinita de la tarea
   // for( int i = 0;i<4;i++ ){
 
      Serial.println("--------------- 07");//Evidencia de ejecucion de la tarea
      delay(1000);
    }
    Serial.println("Tarea 07 Terminada");   // Conclusión de la tarea
    vTaskDelete( NULL );//Eliminacion de tarea
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-----[ TAREA 8 ]--------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Tarea8( void * parameter){//Nombre de la funcion que ejecuta la tarea 08
    for( int i = 0;i<3;i++ ){//Numero de iteraciones de la tarea

        Serial.println("----------------- 08");//Evidencia de ejecucion
        delay(1000);//Retardo para volver al for
    }
    Serial.println("Tarea 08 Terminada");   // Conclusión de la tarea
    vTaskDelete( NULL );//Eliminacion de tarea
}
//*******************************************************************************
