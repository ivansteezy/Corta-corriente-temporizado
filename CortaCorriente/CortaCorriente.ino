
/*IvanSt33zy 2018
happy coding! :)*/

#define Enchufe1 4
#define Enchufe2 5

#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"
#include <Keypad.h>
#include <EEPROM.h>

typedef struct date_t{
  int hora = 0;
  int minuto = 0;
  int dia = 0;

  int horaFin = 0;
  int minutoFin = 0;
  int diaFin = 0;

  int Enchufe;
};

char k = 0;
date_t Fecha;

const byte NumRows = 4; 
const byte NumCol = 4;
byte rowPins[NumRows] = {6,7,8,9}; //Filukis
byte colPins[NumCol]= {10,11,12,13}; //Columnukis

char Keymap[NumRows][NumCol] = {    { '1','2','3','A' },
                                    { '4','5','6','B' },
                                    { '7','8','9','C' },
                                    { '*','0','#','D' }};

Keypad Tecla(makeKeymap(Keymap), rowPins, colPins, NumRows, NumCol);
LiquidCrystal lcd(30, 31, 32, 33, 34, 35);
RTC_DS3231 rtc;

void setup() {
    Serial.begin(9600);
    rtc.begin();
    lcd.begin(16, 2);
    pinMode(Enchufe1, OUTPUT);
    pinMode(Enchufe2, OUTPUT);
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
 char key = Tecla.getKey();
  if(key){
    lcd.clear();
    FechaInicio();
    lcd.clear();
    key = 0;
  }
  Calendario();
}     

void FechaInicio(){
 k = 0;
  do{
    lcd.setCursor(5, 0);
    lcd.print("Fecha:");
    if(k == '6'){
      Fecha.dia++;
      if(Fecha.dia > 7) Fecha.dia = 1;
    }
    if(k == '4'){
      Fecha.dia--;
      if(Fecha.dia == 0) Fecha.dia = 7;
    }

    lcd.setCursor(0, 1);
    switch(Fecha.dia){
        case 1: lcd.print("<-    Lun.    ->"); break;
        case 2: lcd.print("<-    Mar.    ->"); break;
        case 3: lcd.print("<-    Mie.    ->"); break;
        case 4: lcd.print("<-    Jue.    ->"); break;
        case 5: lcd.print("<-    Vie.    ->"); break;
        case 6: lcd.print("<-    Sab.    ->"); break;
        case 7: lcd.print("<-    Dom.    ->"); break;
  }
    k = Tecla.getKey();
  }while(k != '5');
//--------------------------Hora------------------------------------------------------------
  k = 0;
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(7, 1);
  lcd.print(":");     
  lcd.setCursor(5, 0);
  lcd.print("Hora: ");
  do{

    if(k == '2'){
      lcd.setCursor(4, 1);
      lcd.print(Fecha.hora);
      Fecha.hora++;
      if(Fecha.hora > 24){
          Fecha.hora = 0;
          lcd.setCursor(4, 1); 
          lcd.print("  ");
        }
      }

    else if(k == '8'){
      lcd.setCursor(4, 1);
      lcd.print(Fecha.hora);
      Fecha.hora--;
      if(Fecha.hora < 0){
        Fecha.hora = 23;
        lcd.setCursor(4, 1); 
        lcd.print("  ");
        }
      }
      k = Tecla.getKey();
    }while(k != '5');
  //----------------------------Minuto---------------------------------------------------------------
      k = 0;
      lcd.setCursor(8, 1);
      lcd.print("  ");
      do{
        if(k == '2'){
          lcd.setCursor(8, 1);
          lcd.print(Fecha.minuto);
          Fecha.minuto++;
          if(Fecha.minuto > 59){
            Fecha.minuto = 0;
            lcd.setCursor(8, 1);
            lcd.print("  ");
            }
          }

        if(k == '8'){
          lcd.print(Fecha.minuto);
          Fecha.minuto--;
          if(Fecha.minuto < 0){
            Fecha.minuto = 59;
            lcd.setCursor(8, 1);
            lcd.print("  ");
            }
          }
          k = Tecla.getKey();
      }while(k != '5');
      k = 0;
  //--------------------Enchufe-------------
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("Salida:");
    do{
        if(k == '6'){
          Fecha.Enchufe = 1;
          lcd.setCursor(0, 1);
          lcd.print("<-  Enchufe1  ->");
        }
        if(k == '4'){
          Fecha.Enchufe = 2;
          lcd.setCursor(0, 1);
          lcd.print("<-  Enchufe2  ->");
        }
          k = Tecla.getKey();
        }while(k != '5');
        k = 0;
  //_----------------------------------------------
//--------------------------Mensaje--------------
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Se han ingresado");
        lcd.setCursor(0, 1);
        lcd.print("datos encendido");
        delay(2000);
//----------------------Datos de apagado----------
//----------------------Dia-----------------------
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("Fecha:");
  do{
    if(k == '6'){
      Fecha.diaFin++;
      if(Fecha.diaFin > 7) Fecha.diaFin = 1;
    }
    if(k == '4'){
      Fecha.diaFin--;
      if(Fecha.diaFin == 0) Fecha.diaFin = 7;
    }

    lcd.setCursor(0, 1);
    switch(Fecha.diaFin){
        case 1: lcd.print("<-    Lun.    ->"); break;
        case 2: lcd.print("<-    Mar.    ->"); break;
        case 3: lcd.print("<-    Mie.    ->"); break;
        case 4: lcd.print("<-    Jue.    ->"); break;
        case 5: lcd.print("<-    Vie.    ->"); break;
        case 6: lcd.print("<-    Sab.    ->"); break;
        case 7: lcd.print("<-    Dom.    ->"); break;
  }
    k = Tecla.getKey();
  }while(k != '5');
//----------------------Hora----------------------
 k = 0;
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(7, 1);
  lcd.print(":");     
  lcd.setCursor(5, 0);
  lcd.print("Hora: ");
  do{

    if(k == '2'){
      lcd.setCursor(4, 1);
      lcd.print(Fecha.horaFin);
      Fecha.horaFin++;
      if(Fecha.horaFin > 24){
          Fecha.horaFin = 0;
          lcd.setCursor(4, 1); 
          lcd.print("  ");
        }
      }

    else if(k == '8'){
      lcd.setCursor(4, 1);
      lcd.print(Fecha.horaFin);
      Fecha.horaFin--;
      if(Fecha.horaFin < 0){
        Fecha.horaFin = 23;
        lcd.setCursor(4, 1); 
        lcd.print("  ");
        }
      }
      k = Tecla.getKey();
    }while(k != '5');
//----------------------Minuto--------------------
 k = 0;
      lcd.setCursor(8, 1);
      lcd.print("  ");
      do{
        if(k == '2'){
          lcd.setCursor(8, 1);
          lcd.print(Fecha.minutoFin);
          Fecha.minutoFin++;
          if(Fecha.minutoFin > 59){
            Fecha.minutoFin = 0;
            lcd.setCursor(8, 1);
            lcd.print("  ");
            }
          }

        if(k == '8'){
          lcd.print(Fecha.minutoFin);
          Fecha.minutoFin--;
          if(Fecha.minutoFin < 0){
            Fecha.minutoFin = 59;
            lcd.setCursor(8, 1);
            lcd.print("  ");
            }
          }
          k = Tecla.getKey();
      }while(k != '5');
      k = 0;
//----------------------Mensaje-------------------
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Se han ingresado");
        lcd.setCursor(0, 1);
        lcd.print("datos apagado");
        delay(2000);
        //-----
        if(Fecha.Enchufe == 1){
          GrabarDatos(Fecha.Enchufe);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Se han guardado");
          lcd.setCursor(0, 1);
          lcd.print("Para el ench 1");
          delay(2000);
        }
        if(Fecha.Enchufe == 2){
          GrabarDatos(Fecha.Enchufe);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Se han guardado");
          lcd.setCursor(0, 1);
          lcd.print("Para el ench 2");
          delay(2000);
        }
        
}

void Calendario(){
 lcd.setCursor(4, 0);
 DateTime now = rtc.now();
 lcd.print(now.day());
 lcd.print('/');
 lcd.print(now.month());
 lcd.print('/');
 lcd.print(now.year());
 lcd.print(" ");
 lcd.setCursor(4, 1);
 lcd.print(now.hour());
 lcd.print(':');
 lcd.print(now.minute());
 lcd.print(':');
 lcd.print(now.second());

//Comprobar encendido y apagado del enchufe 1
  if(EEPROM.read(6) == 1){
    if(now.dayOfTheWeek()== EEPROM.read(0) && now.hour() == EEPROM.read(1)  && now.minute() == EEPROM.read(2))
        digitalWrite(Enchufe1, HIGH);
    else if(now.dayOfTheWeek() == EEPROM.read(3) && now.hour() == EEPROM.read(4)  && now.minute() == EEPROM.read(5))
        digitalWrite(Enchufe1, LOW);
  }

  if(EEPROM.read(16) == 2){
    if(now.dayOfTheWeek()== EEPROM.read(10) && now.hour() == EEPROM.read(11)  && now.minute() == EEPROM.read(12))
        digitalWrite(Enchufe2, HIGH);
    else if(now.dayOfTheWeek() == EEPROM.read(13) && now.hour() == EEPROM.read(14)  && now.minute() == EEPROM.read(15))
        digitalWrite(Enchufe2, LOW);
  }
}

void GrabarDatos(int x){
  int addr = 0, addr2 = 10;

  if(x == 1){
    EEPROM.write(addr, Fecha.dia); addr++;              //addr 0
    EEPROM.write(addr, Fecha.hora - 1); addr++;     
    EEPROM.write(addr, Fecha.minuto - 1); addr++;
    EEPROM.write(addr, Fecha.diaFin); addr++;
    EEPROM.write(addr, Fecha.horaFin - 1); addr++;
    EEPROM.write(addr, Fecha.minutoFin - 1); addr++;
    EEPROM.write(addr, Fecha.Enchufe); addr++;          //addr 6
  }

  if(x == 2){
    EEPROM.write(addr2, Fecha.dia); addr2++;            //addr 10
    EEPROM.write(addr2, Fecha.hora - 1); addr2++;
    EEPROM.write(addr2, Fecha.minuto - 1); addr2++;
    EEPROM.write(addr2, Fecha.diaFin); addr2++;
    EEPROM.write(addr2, Fecha.horaFin - 1); addr2++;
    EEPROM.write(addr2, Fecha.minutoFin - 1); addr2++;
    EEPROM.write(addr2, Fecha.Enchufe); addr2++;        //addr 16
  }
}
