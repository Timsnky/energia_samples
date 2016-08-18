String email = "homeapplicationgsm@gmail.com";
String password = "1234";

void setup()
{
  Serial.begin(2400);
  Serial1.begin(2400);     // the GPRS baud rate 
  Serial.println("initializing");
  
  // attach(return 1) or detach(return 0) from GPRS service 
  Serial1.println("AT+CGATT?");
  delay(100);
  toSerial();

  //AT+SAPBR	OK	Configures GPRS profile
  Serial1.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(2000);
  toSerial();

  // bearer settings bew.orange.co.ke
  Serial1.println("AT+SAPBR=3,1,\"APN\",\"safaricom\"");
  delay(2000);
  toSerial();

  // bearer settings
  Serial1.println("AT+SAPBR=1,1");
  delay(2000);
  toSerial();
  
  imapspixub();
   delay(20000);
}

void loop()
{
     
    Serial.println("LOOPING");
    
}

void imapspixub()
{
  Serial.println("function");
  Serial.println("end");
   // initialize http service
   Serial1.println("AT+HTTPINIT");
   delay(10000); 
   toSerial();
   
   //Configures HTTP parameters 
   Serial.println("Uploading data to server");
   Serial1.println("AT+HTTPPARA=\"URL\",\"http://homeapplication.3eeweb.com/?data=51,1:52,1:53,1:02,1&email=" + email + "&password=" + password + "\"");
   delay(2000);
   toSerial();

   // set http action type 0 = GET, 1 = POST, 2 = HEAD
   Serial1.println("AT+HTTPACTION=0");
   delay(10000);
   toSerial();
   
   //Closes the opened HTTP session
   Serial1.println("");
   Serial1.println("AT+HTTPTERM");
   toSerial();
   delay(5000);
}

//check if sim is available to send data
void toSerial()
{
  while(Serial1.available()!=0)
  {
    Serial.write(Serial1.read());
  }
}
  
/*ftp://u820178500@93.188.160.106/public_html/Camera/homeapplicationgsm*/
