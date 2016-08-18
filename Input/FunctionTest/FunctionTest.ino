void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly: 
  Serial.println("Enter Num");
  while(Serial.available() == 0);
  int x = int(Serial.read() - '0');
  Serial.println(x);
  Serial.println("Enter Num");
  while(Serial.available() == 0);
  int y = int(Serial.read() - '0');
  Serial.println(y);  
  Serial.println(Calculate(x,y));
   Serial.println(CalculateAdd(x,y));
  
}
