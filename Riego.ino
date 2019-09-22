int pinRele = 9;
int pinLedOff = 10;
int pinLedOn = 11;
int pinSensorHumedad = A0;

void setup() {
  Serial.begin(9600);
  pinMode(pinRele, OUTPUT);
  pinMode(pinLedOff, OUTPUT);
  pinMode(pinLedOn, OUTPUT);
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
                //message = message + "bajo";
                nivel = 2;
                }
            }
    }
      
  return nivel;
}

void loop() {
   int humedad = analogRead(pinSensorHumedad); //Read the parameter sensor humidity
   Serial.print("Sensor value monitored: "); //That line can be checked in serial monitor
   Serial.println(humedad); // Sensor value humidity
   delay(2000); //1 second equal to 1000 milliseconds
   int nivel = NivelDeHumedad(humedad); // Humidity Indicator
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
