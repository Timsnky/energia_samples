int8_t answer;
int onModulePin= 2;

char data[512];
int data_size;

char aux_str[100];
char aux;
int x = 0;


void setup(){
    Serial1.begin(2400);
    Serial.begin(2400);
    Serial.println("Starting...");
    delay(1000);

    sendATcommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"", "OK", 2000);
    sendATcommand("AT+SAPBR=3,1,\"APN\",\"safaricom\"", "OK", 2000);

    while (sendATcommand("AT+SAPBR=1,1", "OK", 20000) == 0)
    {
        delay(5000);
    }


}
void loop()
{
    // Initializes HTTP service
    
    answer = sendATcommand("AT+HTTPINIT", "OK", 10000);
    if (answer == 1)
        {
            // Sets CID parameter
            answer = sendATcommand("AT+HTTPPARA=\"CID\",1", "OK", 5000);
            if (answer == 1)
            {
            // Sets url 
                  answer = sendATcommand("AT+HTTPPARA=\"URL\",'www.homeapplication.3eeweb.com/GSMTest/gsm.php'", "OK", 5000);
            }
        }    
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
