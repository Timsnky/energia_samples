int ledPin = 5; // choose the pin for the LED
int inputPin = 38; // choose the input pin (for PIR sensor)
int pirState = LOW; // we start, assuming no motion detected
int val = 0; // variable for reading the pin status


void setup()
{
  pinMode(ledPin, OUTPUT); // declare LED as output
  pinMode(inputPin, INPUT); // declare sensor as input
  Serial.begin(2400);
  attachInterrupt(inputPin, detect, RISING);
  //attachInterrupt(inputPin, stopDetect, FALLING);
}

void loop()
{
  val = digitalRead(inputPin); // read input value
  if (val == HIGH) 
  { //
    digitalWrite(ledPin, HIGH); // turn LED ON
    if (pirState == LOW) 
    {
    // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } 
  else 
  {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH)
    {
    // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}

void detect()
{
  Serial.println("Motion detected Start!");
  digitalWrite(ledPin, HIGH); 
}

void stopDetect()
{
  Serial.println("Motion ended Re!");
  digitalWrite(ledPin, LOW);
}
