#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27,16,2);
//Variables
int pinRele = 9;
int pinLedOff = 10;
int pinLedOn = 11;
int pinSensorHumedad = A0;
char bufferValue[16];
char bufferStatus[16];
void setup() {
  Wire.begin(); //Begin de port I2C
  Serial.begin(9600);
  pinMode(pinRele, OUTPUT);
  pinMode(pinLedOff, OUTPUT);
  pinMode(pinLedOn, OUTPUT);

  lcd.clear();
  lcd.init();
  lcd.backlight();
}

// Rango de valores proporcionados por el sensor
// Sumergido en agua: 0
// En el aire o en un suelo muy seco: 1023
// Suelo ligeramente humedo: entre [600, 700]
// Suelo seco: [800, 1023]

int NivelDeHumedad(int humedad){ 
  int nivel;
  if(humedad > -1 && humedad < 600){
    nivel = 0;
  }else{
        if(humedad > 599 && humedad < 701){
            nivel = 1;
          }
          else{
              if(humedad > 700 && humedad < 1024){
                nivel = 2;
                }
            }
    }
      
  return nivel;
}

void loop() {
   //lcd.clear();
   int humedad = analogRead(pinSensorHumedad); //Read the parameter sensor humidity
   Serial.print("Sensor value monitored: "); //That line can be checked in serial monitor
   Serial.println(humedad); // Sensor value humidity
   //lcd.print("Valor: "+humedad);
   sprintf(bufferValue, "Ssr value:  %.4d",humedad);
   lcd.setCursor(0,0);
   lcd.print(bufferValue);
   delay(2000); //1 second equal to 1000 milliseconds
   int nivel = NivelDeHumedad(humedad); // Humidity Indicator
   
   sprintf(bufferStatus, "Ssr Status: %d",nivel);
   lcd.setCursor(0,1);
   lcd.print(bufferStatus);
   delay(2000); //1 second equal to 1000 milliseconds
    switch(nivel){
      case 0:analogWrite(pinLedOff, 255); // Always On when the level humidity is alto
             analogWrite(pinLedOn, 0); // Always Off when the level humidity is alto
             delay(2000);
             analogWrite(pinRele, 255); // Always Off when the level humidity is alto
      break;
      case 1:analogWrite(pinLedOff, 255);
             analogWrite(pinLedOn, 0);
             delay(2000);
             analogWrite(pinRele, 255);
      break;
      case 2:analogWrite(pinLedOff, 0);
             analogWrite(pinLedOn, 255);
             delay(2000);
             analogWrite(pinRele, 0);
      break;  
     }     
   }   
