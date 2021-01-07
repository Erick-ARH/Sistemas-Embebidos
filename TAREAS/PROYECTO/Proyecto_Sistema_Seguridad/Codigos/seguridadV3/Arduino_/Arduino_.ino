
#include <Servo.h>

Servo servox; 
Servo servoy;

int pos_antx = 90;
int pos_anty = 90;
int angulo=0;

// int xPos = 90;
// int yPos = 90;


String cadenaCharEntrada = "";  
bool nuevoDato = false;
 byte data[] = {0, 255, 255};
const size_t dataLength = sizeof(data) / sizeof(data[0]);
int dato=0;

#define PIR 7
#define Lampara 13
int LDRPIN =A0;
#define SETLDR 400
int LDRVal=0;
 int PIR_State;

int Ctrl_Lamp_State=3; 
// 0-> lampara apagada indefinidamente
// 1-> lampara encendida indefinidamente
// 2-> lampara encendida toda la noche
// 3-> lampara encendida con movimiento de noche

#define T_LamparaON 3000
unsigned long t_LamAcum=0;
#define T_CtrlLamp 200
unsigned long t_CtrlLampAcum=0;


bool S_Lamp=false;


void setup() {
    pinMode(PIR, INPUT);
    pinMode(Lampara, OUTPUT);

    servox.attach(5);
    servoy.attach(6);
    servox.write(90); 
    servoy.write(90);   

    Serial.begin(115200); 


}

void loop() {

    
    if (nuevoDato){
    
    dato=cadenaCharEntrada.toInt();

    if(dato==0)  Ctrl_Lamp_State=0;
    if(dato==1)  Ctrl_Lamp_State=1;
    if(dato==2)  Ctrl_Lamp_State=2;
    if(dato==3)  Ctrl_Lamp_State=3;
    

    if(dato<=1180&&dato>=1000){
            angulo=dato-1000;
            moveServo(1,angulo,pos_antx);
            pos_antx=angulo;
           // Serial.println("accion servo1");
    }

    if(dato<=2180&&dato>=2000){
        angulo=dato-2000;
        moveServo(2,angulo,pos_anty);
        pos_anty=angulo;
     //   Serial.println("accion servo2");
    }



    nuevoDato=false;
    cadenaCharEntrada="";
  }

    Ctrl_LampAutomatica();
        
//    Ctrl_LampAutomatica()
//    analogRead(LDRPIN);
//    PIR_State=digitalRead(PIR);
//
//    Serial.print("LDR: ");
//    Serial.print(LDRVal);
//    Serial.print("    PIR ");
//    Serial.println(PIR_State);

    delay(100);

}


// void goHome(){
//   moveServo(servoy,90,pos_anty);
//   moveServo(servox,90,pos_antx);
//   pos_antx=90;
//   pos_anty=90;
// }


void serialEvent(){
  //Recepción de datos Seriales
  while (Serial.available()) {              //Si existen datos seriales, leer a todos
     char inChar = (char)Serial.read();
     cadenaCharEntrada+= inChar;
     if (inChar=='\n'){
    nuevoDato=true;
     }
  }
} 



void moveServo(int ser, int angulo, int _ant){
   int pos;//=angulo;
    if (angulo>_ant){
        // Serial.print(_ant);
        // Serial.println(" Aumento");
        for (pos = _ant; pos <= angulo; pos += 1) { // sweep from 180 degrees to 0 degrees
        if (ser==1) servox.write(pos);
       if (ser==2) servoy.write(pos);

        // Serial.println(pos);
		delay(10);
    
    	}
    } else if(angulo<_ant){
        // Serial.print(_ant);
        // Serial.println("  disminuyo");
        for (pos = _ant; pos >= angulo; pos -= 1) { // sweep from 180 degrees to 0 degrees
            if (ser==1) servox.write(pos);
            if (ser==2) servoy.write(pos);
            delay(10);
        }
    }
}



void Ctrl_LampAutomatica(){
    if(millis()-t_CtrlLampAcum>=T_CtrlLamp){
        switch (Ctrl_Lamp_State){

            case 0:
                LampOFF();
            break;

            case 1:
                LampON();
            break;

            case 2:
                LDRVal=analogRead(LDRPIN);
                if (LDRVal<SETLDR)   
                    LampON();
                else
                    LampOFF();
            break;

            case 3:
                LDRVal=analogRead(LDRPIN);
                if (LDRVal<SETLDR){
                    if (digitalRead(PIR)){
                        LampON();
                        t_LamAcum=millis();
                    }             
                }

                if((millis()-t_LamAcum)>T_LamparaON){
                LampOFF();
                } 
                


            break;
        }
        t_CtrlLampAcum=millis();
    }
}


void LampON(){
    if(S_Lamp==true){
        return;
    }if(S_Lamp==false){
        S_Lamp=true;
        Serial.println("20");
        digitalWrite(Lampara,HIGH);    
    }
}
void LampOFF(){
    if(S_Lamp==false){
        return;
    }if(S_Lamp==true){
        S_Lamp=false;
        Serial.println("10");
        digitalWrite(Lampara,LOW);    
    }
}
