###Tarea Número 09
##Aplicación: Implementacion de un Sistema RTOs
##Sergio Francisco Hernández Machuca
#Abad Dolores Lázaro
#Rodriguez Hernandez Erick Abimael
Introducción

Los sistemas en tiempo real se caracterizan por el hecho de que pueden producirse graves consecuencias si son lógicas y No se cumplen las propiedades de corrección de la sincronización del sistema. Una aplicación multitarea en tiempo real es un sistema en el que se deben procesar simultáneamente varias actividades críticas en el tiempo. Una multitarea en tiempo real kernel (también llamado sistema operativo en tiempo real, RTOS) es un software que asegura que el tiempo es crítico los eventos se procesan de la manera más eficiente posible. El uso de un RTOS generalmente simplifica el diseño proceso de un sistema al permitir que la aplicación se divida en múltiples elementos independientes llamados Tareas.

En forma de descripción general cada tarea realiza lo siguiente:

Tarea 01: Se ejecuta 10 veces mandando un mensaje que evidencia que se esta ejecutando, cuando se realiza la séptima iteración manda información a la tarea 2, realizado con una estructura de switch (){}. Cuando concluye la tarea manda un mensaje advirtiendo que la tarea 1 ha terminado.

Tarea 02: Se ejecuta 10 veces mandando un mensaje que evidencia que se está ejecutando. Cuando concluye la tarea manda un mensaje advirtiendo que la tarea 2 ha terminado.

Tarea 03: Se ejecuta 7 veces mandando un mensaje que evidencia que se está ejecutando, cuando se realiza la quinta iteración manda información a la tarea 4, realizado con una estructura de for (){}. Cuando concluye la tarea manda un mensaje advirtiendo que la tarea 3 ha terminado. Cambia el valor de la variable global “c”.

Tarea 04: Se ejecuta 6 veces mandando un mensaje que evidencia que se está ejecutando, cuando la variable global “c” es igual 1 la tarea 04 recibe información de la tarea 08, realizado con una estructura de for (){}. Cuando concluye la tarea manda un mensaje advirtiendo que la tarea 04 ha terminado. Tarea 05: Se ejecuta 5 veces mandando un mensaje que evidencia que se está ejecutando, realizado con una estructura de for (){}. Cuando concluye la tarea manda un mensaje advirtiendo que la tarea 05 ha terminado.

Tarea 06: Se ejecuta de manera infinita mandando un mensaje que evidencia que se está ejecutando, realizado con una estructura de While (){}. Cuando concluye la tarea manda un mensaje advirtiendo que la tarea 06 ha terminado.

Tarea 07: Se ejecuta de manera infinita mandando un mensaje que evidencia que se está ejecutando, realizado con una estructura de While (){}. Cuando concluye la tarea manda un mensaje advirtiendo que la tarea 07 ha terminado.

Tarea 08: Se ejecuta 2 veces mandando un mensaje que evidencia que se está ejecutando. Cuando concluye la tarea manda un mensaje advirtiendo que la tarea 2 ha terminado.

Esta tarea se entregó el día 26 de noviembre del 2020, año del Covid-19.