void setup()
{
  // put your setup code here, to run once:
  
}

void loop()
{
  Serial2.write ("\x56\x00\x36\x01\x00", sizeof ("\x56\x00\x36\x01\x00")-1);
 
}
