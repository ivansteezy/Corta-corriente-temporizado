# Corta-corriente-temporizado
Corta corriente temporizado mediante un RTC

## Librías necesarias
```c
#include <LiquidCrystal.h>
#include <Wire.h>
#include "RTClib.h"
#include <Keypad.h>
#include <EEPROM.h>
```
## Precaución
Cuidado con colocar las siguientes lineas de código en algún bucle, pues la EEPROM del Arduino tiene como limite la escritura hasta 100,000, una vez usadas no habrá posibilidad de usar más espacio.

```c
    //Cuidado con esto
    EEPROM.write(addr, Fecha.dia); addr++;              
    EEPROM.write(addr, Fecha.hora - 1); addr++;     
    EEPROM.write(addr, Fecha.minuto - 1); addr++;
    EEPROM.write(addr, Fecha.diaFin); addr++;
    EEPROM.write(addr, Fecha.horaFin - 1); addr++;
    EEPROM.write(addr, Fecha.minutoFin - 1); addr++;
    EEPROM.write(addr, Fecha.Enchufe); addr++;        
```
