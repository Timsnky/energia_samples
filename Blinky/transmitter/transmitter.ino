
const int pinY = A0;
const int pinX = A1;

int sensorValuey = 0;
int sensorValuex = 0;
int yAxis = 0;
int xAxis = 0;
void setup() 
{
  Serial.begin(9600); 
}
void loop() 
{
   
 sensorValuey = analogRead(pinY); 
 //Serial.println(sensorValuey);
 sensorValuex = analogRead(pinX); 
 //Serial.println(sensorValuex);
 if (sensorValuey > 300 && sensorValuey < 360)
 {
  Serial.println("1");
 }
 if  (sensorValuey > 361)
 {
   Serial.println("2");
 }
 if  (sensorValuey < 300)
 {
   Serial.println("3");
 }
 if  (sensorValuex > 361)
 {
   Serial.println("4");
 }
 if  (sensorValuex < 300)
 {
    Serial.println("5");
 }
 delay(250);
}
