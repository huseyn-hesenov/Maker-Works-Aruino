#include <PID_v1.h>

#include <OneWire.h> 
#include <DallasTemperature.h>
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2 
#define gate 10
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
//Variables

double Setpoint, Input, Output;
 
//PID Parameters

double Kp = 2, Ki = 2, Kd = 1;


//Start PID Instance

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
int deviceCount = 0;
float tempC;

void setup()

{
sensors.begin();
  //Start Serial
  Serial.begin(9600);
 pinMode(gate,OUTPUT);
 Serial.print("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount, DEC);
  Serial.println(" devices.");
  Serial.println("");
// start serial port 
 //Serial.begin(9600); 
 Serial.println("Dallas Temperature IC Control Library Demo"); 
 // Start up the library 
// sensors.begin();
  //Set point (brightness target)

  Setpoint =-20;

  //Turn the PID on

  myPID.SetMode(AUTOMATIC);

  //Adjust PID values

  myPID.SetTunings(Kp, Ki, Kd);

}


void loop()

{
  // call sensors.requestTemperatures() to issue a global temperature 
 // request to all devices on the bus 
/********************************************************************/
 Serial.print(" Requesting temperatures..."); 
 sensors.requestTemperatures(); // Send the command to get temperature readings 
 Serial.println("DONE");

 
for (int i = 0;  i < deviceCount;  i++)
  {
    Serial.print("Sensor ");
    Serial.print(i+1);
    Serial.print(" : ");
    tempC = sensors.getTempCByIndex(i); 
    
    Serial.print(tempC);
    Serial.print((char)176);//shows degrees character
    Serial.print("C  |  ");
    Serial.print(DallasTemperature::toFahrenheit(tempC));
    Serial.print((char)176);//shows degrees character
    Serial.println("F");
   
  
  } 
    Input =tempC;
    myPID.Compute();
    analogWrite(gate, Output);
  
  Serial.println("");
  delay(1000);

  //PID calculation

 
 
  //Write the output as calculated by the PID function

 


  //Send data for serial monitoring

  Serial.print(Input);

  Serial.print(" ");

  Serial.println(Output);

}
