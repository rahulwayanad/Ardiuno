/* HC-SR04 Sensor
   https://www.dealextreme.com/p/hc-sr04-ultrasonic-sensor-distance-measuring-module-133696
  
   This sketch reads a HC-SR04 ultrasonic rangefinder and returns the
   distance to the closest object in range. To do this, it sends a pulse
   to the sensor to initiate a reading, then listens for a pulse 
   to return.  The length of the returning pulse is proportional to 
   the distance of the object from the sensor.
     
   The circuit:
  * VCC connection of the sensor attached to +5V
  * GND connection of the sensor attached to ground
  * TRIG connection of the sensor attached to digital pin 2
  * ECHO connection of the sensor attached to digital pin 4
   Original code for Ping))) example was created by David A. Mellis
   Adapted for HC-SR04 by Tautvidas Sipavicius
   This example code is in the public domain.
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int motor_status=0;
const int trigPin = A2;
const int echoPin = A3;
int led = 13;
int prev_cm;
void setup() {
  // initialize serial communication:
  Serial.begin(9600);
   // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
   pinMode(led, OUTPUT);   
digitalWrite(led,LOW);




  
}

void loop()
{

// motor status
if(motor_status==1)

{
   Serial.println("Motor On");
 
}

else
{
    Serial.println("Motor OFF");

}


  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, cm;

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("MotorStatus:");
  if(motor_status==0)
  lcd.print("OFF");
 else
 lcd.print("ON");
 
 lcd.setCursor(0,1);
  lcd.print("Level:");
 
  
  //water lever reading
  if(13<cm)
    lcd.print("Empty");
  else if(10<cm && cm<=13)
    lcd.print("#");
  else if(8<cm && cm<=10)
    lcd.print("##");
  else if(7<cm && cm<=8)
    lcd.print("###");
  else if(5<cm && cm<=7)
    lcd.print("####");
  else if(cm<=5)
    lcd.print("#####");
else{
  lcd.print("Error");
}
  
  if(motor_status==1)
  {
    delay(9000);
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

    prev_cm= microsecondsToCentimeters(duration);
  // if previous reading and current reading is equal,motor will off; pot does not have sufficient watter
  if(prev_cm==cm)
  {
    motor_status=0;
    
  digitalWrite(led,LOW);
   Serial.print("No water in pot");
  }
  
  }

  
  
//if waterreading above 13cm, thats means tank is empty.motor will on
  if(cm>=13)
  {
    motor_status=1;
    digitalWrite(led,HIGH);
    
  }
//if waterreading below 3cm, thats means tank is full.motor will off
else if(cm<=5)
  {
    motor_status=0;
    
  digitalWrite(led,LOW);
  
  }
  
  //serial print on computer

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(500);
}





long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
