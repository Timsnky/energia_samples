byte incomingbyte;                    //Configure pin 4 and 5 as soft serial port
int a=0x0000,j=0,k=0,count=0;                    //Read Starting address       
uint8_t MH,ML;
boolean EndFlag=0;
                               
void SendResetCmd();
void SendTakePhotoCmd();
void SendReadDataCmd();
void StopTakePhotoCmd();

void setup()
{ 
  Serial.begin(19200);
  Serial2.begin(38400);
}

void loop() 
{
     SendResetCmd();
     delay(4000);                               //After reset, wait 2-3 second to send take picture command
      
      /*SendTakePhotoCmd();

     while(Serial2.available()>0)
      {
        incomingbyte=Serial2.read();

      }   
      byte a[32];
      
      while(!EndFlag)
      {  
         j=0;
         k=0;
         count=0;
         SendReadDataCmd();

         delay(25);
          while(Serial2.available()>0)
          {
               incomingbyte=Serial2.read();
               k++;
               if((k>5)&&(j<32)&&(!EndFlag))
               {
               a[j]=incomingbyte;
               if((a[j-1]==0xFF)&&(a[j]==0xD9))      //Check if the picture is over
               EndFlag=1;                           
               j++;
	       count++;
               }
          }
         
          for(j=0;j<count;j++)
          {   if(a[j]<0x10)
              Serial.print("0");
              Serial.print(a[j],HEX);
              Serial.print(" ");
          }                                       //Send jpeg picture over the serial port
          Serial.println();
      }      
     while(1);*/
}

//Send Reset command
void SendResetCmd()
{
      Serial2.write(0x56);
      Serial2.write(0x00);
      Serial2.write(0x26);
      Serial2.write(0x00);
}

//Send take picture command
/*void SendTakePhotoCmd()
{
      Serial2.write(0x56);
      Serial2.write(0x00);
      Serial2.write(0x36);
      Serial2.write(0x01);
      Serial2.write(0x00);  
}

//Read data
void SendReadDataCmd()
{
      MH=a/0x100;
      ML=a%0x100;
      Serial2.write(0x56);
      Serial2.write(0x00);
      Serial2.write(0x32);
      Serial2.write(0x0c);
      Serial2.write(0x00); 
      Serial2.write(0x0a);
      Serial2.write(0x00);
      Serial2.write(0x00);
      Serial2.write(MH);
      Serial2.write(ML);   
      Serial2.write(0x00);
      Serial2.write(0x00);
      Serial2.write(0x00);
      Serial2.write(0x20);
      Serial2.write(0x00);  
      Serial2.write(0x0a);
      a+=0x20;                            //address increases 32£¬set according to buffer size
}

void StopTakePhotoCmd()
{
      Serial2.write(0x56);
      Serial2.write(0x00);
      Serial2.write(0x36);
      Serial2.write(0x01);
      Serial2.write(0x03);        
}*/


