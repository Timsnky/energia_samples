float temp;
int tempPin = 18;

void setup()
{
  Serial.begin(2400);
}
float average = 0;
float result;
float value;
void loop()
{
  temp = analogRead(tempPin);
  temp = temp * 0.0699794;
  Serial.print("TEMPRATURE = ");
  Serial.print(temp);
  Serial.print("*C");
  Serial.println();
}

