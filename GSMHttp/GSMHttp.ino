int8_t answer;
int onModulePin= 2;

char data[512];
int data_size;

char aux_str[100];
char aux;
int x = 0;


void setup(){
    Serial1.begin(2400);
    delay(1000);
    Serial.begin(2400);
    delay(1000);
    Serial.println("Starting...");
    delay(1000);

    sendATcommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"", "OK", 2000);
    Serial.println("Testing1");
    delay(1000);
    sendATcommand("AT+SAPBR=3,1,\"APN\",\"safaricom\"", "OK", 2000);
    Serial.println("Testing2");
    delay(1000);
    sendATcommand("AT+SAPBR=3,1,\"USER\",\"saf\"", "OK", 2000);
    sendATcommand("AT+SAPBR=3,1,\"PWD\",\"data\"", "OK", 2000);

    /*while (sendATcommand("AT+SAPBR=1,1", "OK", 2000) == 0)
    {
      Serial.println("Testing3");
        delay(2000);
    }*/

}
void loop(){
    // Initializes HTTP service
    Serial.println("Testing");
    delay(1000);
    answer = sendATcommand("AT+HTTPINIT", "OK", 10000);
    if (answer == 1)
    {
        // Sets CID parameter
        Serial.println("Init Ok");
        delay(1000);
        answer = sendATcommand("AT+HTTPPARA=\"CID\",1", "OK", 5000);
        if (answer == 1)
        {
          Serial.println("cid Ok");
          delay(1000);
            // Sets url 
            answer = sendATcommand("AT+HTTPPARA=\"URL\",'http://homeapplication.3eeweb.com/?gsm=51,1'", "OK", 5000);
            if (answer == 1)
            {
              Serial.println("url Ok");
              delay(1000);
                // Starts GET action
                answer = sendATcommand("AT+HTTPACTION=0", "+HTTPACTION:0,200", 10000);
                
                if (answer == 1)
                {
                  Serial.println("get Ok");
                  delay(1000);
                    x=0;
                    do{
                        sprintf(aux_str, "AT+HTTPREAD=%d,100", x);
                        if (sendATcommand2(aux_str, "+HTTPREAD:", "ERROR", 30000) == 1)
                        {
                            data_size = 0;
                            while(Serial1.available()==0);
                            aux = Serial1.read();
                            do{
                                data_size *= 10;
                                data_size += (aux-0x30);
                                while(Serial1.available()==0);
                                aux = Serial1.read();        
                            }while(aux != 0x0D);

                            Serial.print("Data received: ");
                            Serial.println(data_size);

                            if (data_size > 0)
                            {
                                while(Serial1.available() < data_size);
                                Serial1.read();

                                for (int y = 0; y < data_size; y++)
                                {
                                    data[x] = Serial1.read();
                                    x++;
                                }
                                data[x] = '\0';
                            }
                            else
                            {
                                Serial.println("Download finished");    
                            }
                        }
                        else if (answer == 2)
                        {
                            Serial.println("Error from HTTP");
                        }
                        else
                        {
                            Serial.println("Error getting the url1");
                            data_size = 0;
                        }
                        
                        sendATcommand("", "+HTTPACTION:0,200", 20000);
                    }while (data_size > 0);
                    
                    Serial.print("Data received: ");
                    Serial.println(data);
                }
                else
                {
                    Serial.println("Error getting the url");
                }
            }
            else
            {
                Serial.println("Error setting the url");
            }
        }
        else
        {
            Serial.println("Error setting the CID");
        }    
    }
    else
    {
        Serial.println("Error initializating");
    }
    
    sendATcommand("AT+HTTPTERM", "OK", 5000);

    delay(5000);

}

int8_t sendATcommand(char* ATcommand, char* expected_answer1, unsigned int timeout){

    uint8_t x=0,  answer=0;
    char response[100];
    unsigned long previous;

    memset(response, '\0', 100);    // Initialize the string

    delay(100);

    while( Serial1.available() > 0) Serial1.read();    // Clean the input buffer

    Serial1.println(ATcommand);    // Send the AT command 


        x = 0;
    previous = millis();

    // this loop waits for the answer
    do{
        if(Serial1.available() != 0){    
            response[x] = Serial1.read();
            x++;
            // check if the desired answer is in the response of the module
            if (strstr(response, expected_answer1) != NULL)    
            {
                answer = 1;
            }
        }
        // Waits for the asnwer with time out
    }
    while((answer == 0) && ((millis() - previous) < timeout));    

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


        x = 0;
    previous = millis();

    // this loop waits for the answer
    do{        
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

    return answer;
}
