#include <DallasTemperature.h>
#include <OneWire.h>
#include <PID_v1.h>

int fanPinREG = 10;

double Setpoint, Input, Output;

//Tuning Parameters
float Kp=2;    //Proportional Gain
float Ki=5;    //Integral Gain
float Kd=1;    //Differential Gain

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,Kp,Ki,Kd, DIRECT);

// Data wire is plugged into port D6 on the Arduino
#define ONE_WIRE_BUS 6

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void setup()
{
Serial.begin(9600);
// Start up the library (DS18B20 DallasTemperature)
sensors.begin();

////////////////////////////////////// PWM BY REGISTRY CHANGE ////////////////////////
pinMode(fanPinREG, OUTPUT);
  
 // TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20); // COM2B1: clear OC2B on Compare Match; WGM21/20/22 (latter in TCCR2B below): count from 0 to OCR2A
  //TCCR2B = _BV(WGM22) | _BV(CS21); // CS20: prescaler 8
 // OCR2A = 80;
  //OCR2B = 40; // for 50% duty cycle
////////////////////////////////////////////////////////////////////////////////////

  sensors.requestTemperatures();
  Input = sensors.getTempCByIndex(0);//analogRead(0);     /**************  TEMPERATURE  **********************/
  Setpoint = 15;            /***********  TEMPERATURE SETPOINT (CELCIUS)  ******/

  //turn the PID on
  myPID.SetMode(AUTOMATIC);  
}

void loop(void)
{

  sensors.requestTemperatures();
  Input = sensors.getTempCByIndex(0);    //Temperature from DS18B20
  myPID.Compute();
  analogWrite(fanPinREG,Output);
  Serial.print("Temperature C = ");
  Serial.println(Input);

}
