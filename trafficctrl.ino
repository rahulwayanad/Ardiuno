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


long duration, cm,prev_cm;
int lightstatus;
const int trigPin = A2;
const int echoPin = A3;

int redcounter=30;
int greencounter=30;
int whitecounter=10;

int red=3;
int white=4;
int green=5;
int prv_cm=0;
int traffic_status; 
  

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
   
   pinMode(red, OUTPUT);   
   pinMode(white, OUTPUT);   
   pinMode(green, OUTPUT);   

distanceReader();
}

void loop()
{
 

distanceReader();
redDisplay(redcounter);

}

void distanceReader()
{
  
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
  delay(10);
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
  prev_cm=microsecondsToCentimeters(duration);
  if(cm<100)
  {
if(prev_cm==cm)
{
  traffic_status=1; //on traffic 
  Serial.println("Traffic");
  
}
else
{
  traffic_status=0; //driving 
  Serial.println("running");
}

  }
  //Serial.println(cmarray);

/*  
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Distance:");
  lcd.print(cm);
  lcd.print("cm");
 lcd.setCursor(0,1);
  lcd.print("Level:");
  
  */

  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

}

void redDisplay(int cntr)
{
  lightstatus=1;
  Serial.println(lightstatus);
  Serial.println("RED");
  digitalWrite(red,HIGH);
  for(int i=cntr;i>=0;i--)
              {
                countdownLcd(i);
            delay(500);
            distanceReader();
            if(cm>=30 && lightstatus==1 && traffic_status==1 )
            {
                    digitalWrite(red,LOW);
                  greencounter=60;
                  whiteDisplay(10);
                  break;
             
            }
            else



            {
               greencounter=30;
              
              }
            
  
  }
  digitalWrite(red,LOW);
  whiteDisplay(whitecounter);
  
 }




void greenDisplay(int cntr)
{
  lightstatus=2;
  Serial.println(lightstatus);
    Serial.println("GREEN");
    digitalWrite(green,HIGH);
 for(int i=cntr;i>=0;i--)
  {
      countdownLcd(i);
  delay(500);
  distanceReader();
  }
  digitalWrite(green,LOW);

}




void whiteDisplay(int cntr)
{
  lightstatus=3;
  Serial.println(lightstatus);
    Serial.println("WHITE");
  digitalWrite(white,HIGH);
  for(int i=cntr;i>=0;i--)
  {
      countdownLcd(i);
  delay(500);
  distanceReader();
  }
  digitalWrite(white,LOW);
greenDisplay(greencounter);

}


void countdownLcd(int cnt)
{
  Serial.print("Count Down :");
  Serial.print(cnt);
  Serial.println();
}







long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
