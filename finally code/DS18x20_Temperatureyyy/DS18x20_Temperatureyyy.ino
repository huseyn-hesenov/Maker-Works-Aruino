#include <OneWire.h>
#include <PID_v1.h>
#define gate 10
// OneWire DS18S20, DS18B20, DS1822 Temperature Example
//
// http://www.pjrc.com/teensy/td_libs_OneWire.html
//
// The DallasTemperature library can do all this work for you!
// https://github.com/milesburton/Arduino-Temperature-Control-Library
double Setpoint, Input, Output;
 
//PID Parameters
//#define KP .255
//#define KI .0003
//#define KD .127
double KP = 2, KI = 5, KD = 1;
PID myPID(&Input, &Output, &Setpoint, KP, KI, KD, DIRECT);
//pid settings and gains
#define OUTPUT_MIN 0
#define OUTPUT_MAX 255


float sensors[8];
byte x = 0;

OneWire  ds(6);  // on pin 10 (a 4.7K resistor is necessary)

void setup(void) {
  Serial.begin(9600);
    
//  while (!updateTemp()) {} //wait until temp sensor updated
pinMode(gate,OUTPUT);
Setpoint=60;
myPID.SetMode(AUTOMATIC);

  //Adjust PID values

  myPID.SetTunings(KP, KI, KD);


}

//bool updateTemp() {
  
//}

void loop(){
byte i;
  byte present = 0;
  byte type_s;
  byte data[12];
  byte addr[8];
  float celsius;

  while (ds.search(addr)) {
    ds.reset();
    ds.select(addr);
    ds.write(0x44, 1);        // start conversion, with parasite power on at the end

    delay(500);     
    
    present = ds.reset();
    ds.select(addr);
    ds.write(0xBE);         // Read Scratchpad

    for ( i = 0; i < 9; i++) {           // we need 9 bytes
      data[i] = ds.read();
    }
    int16_t raw = (~data[1] << 8) | data[0];

      raw = raw << 4; // 9 bit resolution default
      if (data[7] == 0x10) {
        // "count remain" gives full 12 bit resolution
        raw = (raw & 0xFFF0) + 12 - data[6];
      }

    celsius = (float)raw / 16.0 - 169.45;
    sensors[x]=celsius;
   // temperature1= sensors[0]; 
    Serial.print(sensors[x]);
    Serial.println(" "); 
    Input=sensors[0];
    myPID.Compute();
    analogWrite(gate, Output);
    x++;
  }  Serial.println(" "); 
    x=0;
    //Serial.println("No more addresses.");
    delay(250);
 
  delay(1000);
  }
