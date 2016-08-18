int8_t answer;

char aux_str[30];

char test_str[ ]= "0000000011111111222222223333333344444444555555556666666677777777000000001111111122222222333333334444";

int data_size, aux;


void setup(){
    Serial1.begin(2400); 
   Serial.begin(2400);
  delay(1000); 


    Serial.println("Starting...");
   
    Serial.println("Connecting to the network...");

    /*while( (sendATcommand("AT+CREG?", "+CREG: 0,1", 500) 
           || sendATcommand("AT+CREG?", "+CREG: 0,5", 500)) == 0 );*/
    Serial1.println("AT+CGATT?");
    delay(100);

    configure_FTP();

    uploadFTP();
}


void loop(){
  Serial.println("Loop");
  delay(2000);
  configure_FTP();

    uploadFTP();
  
}


void configure_FTP(){
    Serial.println("Command1");
    sendATcommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"", "OK", 2000);
    toSerial();
    Serial.println("Command2");
    sendATcommand("AT+SAPBR=3,1,\"APN\",\"safaricom\"", "OK", 2000);
    toSerial();
    Serial.println("Command3");
    Serial1.println("AT+SAPBR=1,1");
    delay(2000);
    toSerial();
    Serial.println("Command4");
    sendATcommand("AT+FTPCID=1", "OK", 2000);
    Serial.println("Command5");
    sendATcommand("AT+FTPSERV=\"ftp.93.188.160.106\"", "OK", 2000);
    Serial.println("Command6");
    sendATcommand("AT+FTPPORT=21", "OK", 2000);
    Serial.println("Command7");
    sendATcommand("AT+FTPUN=\"u820178500\"", "OK", 2000);
    Serial.println("Command8");
    sendATcommand("AT+FTPPW=\"echelon5341\"", "OK", 2000);

}


void uploadFTP(){
    Serial.println("Command9");
    sendATcommand("AT+FTPPUTNAME=\"img.txt\"", "OK", 2000);
    Serial.println("Command10");
    sendATcommand("AT+FTPPUTPATH=\"/public_html\"", "OK", 2000);
    Serial.println("Command11");
    if (sendATcommand("AT+FTPPUT=1", "+FTPPUT:1,1,", 30000) == 1)
    {
        data_size = 0;
        while(Serial1.available()==0);
        aux = Serial1.read();
        do{
            data_size *= 10;
            data_size += (aux-0x30);
            while(Serial1.available()==0);
            aux = Serial1.read();        
        }
        while(aux != 0x0D);

        if (data_size >= 100)
        {
            if (sendATcommand("AT+FTPPUT=2,100", "+FTPPUT:2,100", 30000) == 1)
            {
                Serial1.println(sendATcommand(test_str, "+FTPPUT:1,1", 30000), DEC);          
                Serial1.println(sendATcommand("AT+FTPPUT=2,0", "+FTPPUT:1,0", 30000), DEC);
                Serial.println("Upload done!!");
            }
            else 
            {
                sendATcommand("AT+FTPPUT=2,0", "OK", 30000);                    
            }
        }
        else
        {
            sendATcommand("AT+FTPPUT=2,0", "OK", 30000); 
        }
    }
    else
    {
        Serial.println("Error openning the FTP session");
    }
}

void toSerial()
{
  while(Serial1.available()!=0)
  {
    Serial.write(Serial1.read());
  }
}

int8_t sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout){

    uint8_t x=0,  answer=0;
    char response[100];
    unsigned long previous;

    memset(response, '\0', 100);    // Initialize the string

    delay(100);

    while( Serial1.available() > 0) Serial1.read();    // Clean the input buffer

    Serial1.println(ATcommand);    // Send the AT command 
    toSerial();

        x = 0;
    previous = millis();

    // this loop waits for the answer
    do{
        if(Serial1.available() != 0){    
            // if there are data in the UART input buffer, reads it and checks for the asnwer
            response[x] = Serial1.read();
            //Serial.print(response[x]);
            x++;
            // check if the desired answer  is in the response of the module
            if (strstr(response, expected_answer) != NULL)    
            {
                answer = 1;
            }
        }
    }
    // Waits for the asnwer with time out
    while((answer == 0) && ((millis() - previous) < timeout));    
        toSerial();
        return answer;
}

int8_t sendATcommand2(char* ATcommand, char* expected_answer1, 
            char* expected_answer2, unsigned int timeout){

    uint8_t x=0,  answer=0;
    char response[100];
    unsigned long previous;

    memset(response, '\0', 100);    // Initialize the string

    delay(100);

    while( Serial1.available() > 0) Serial1.read();    // Clean the input buffer

    Serial1.println(ATcommand);    // Send the AT command 
    toSerial();


        x = 0;
    previous = millis();

    // this loop waits for the answer
    do{ 
        // if there are data in the UART input buffer, reads it and checks for the asnwer
        if(Serial1.available() != 0){               
            response[x] = Serial1.read();
            x++;
            // check if the desired answer 1 is in the response of the module
            if (strstr(response, expected_answer1) != NULL)    
            {
                answer = 1;
            }
            // check if the desired answer 2 is in the response of the module
            if (strstr(response, expected_answer2) != NULL)    
            {
                answer = 2;
            }
        }
        // Waits for the asnwer with time out
    }while((answer == 0) && ((millis() - previous) < timeout));    
        toSerial();
        return answer;
}
