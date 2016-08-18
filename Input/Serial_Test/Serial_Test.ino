void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BLUE_LED, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  while (Serial.available() == 0);
  int val = Serial.read();
  if( val == '1'){
    digitalWrite(BLUE_LED, HIGH);
    Serial.println("Blue Led On");
  } 
   else if( val == '0'){
    digitalWrite(BLUE_LED, LOW);
    Serial.println("Blue Led Off");
  }
  else{
    Serial.println("Invalid Input");
  }
}
