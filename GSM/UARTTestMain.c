// UARTTestMain.c
// Runs on LM4F120/TM4C123
// Used to test the UART.c driver
// Daniel Valvano
// September 12, 2013

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2013

 Copyright 2013 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// U1Rx (VCP receive) connected to PB0
// U1Tx (VCP transmit) connected to PB1

#include "PLL.h"
#include "UART.h"

//---------------------OutCRLF---------------------
// Output a CR,LF to UART to go to a new line
// Input: none
// Output: none
void OutCRLF(void){
  UART_OutChar(CR);
  UART_OutChar(LF);
}
void Delay(void){unsigned long volatile time;
  time = 714;  // 0.1sec
  while(time){
		time--;
  }
}

//debug code
int main(void){
int x = 1;

  PLL_Init();
  UART_Init();              // initialize UART
  OutCRLF();
  
	
  
	while(1){
    while (x >0)
			{
	UART_OutString("AT+CMGF=1\r");
	//OutCRLF();
	Delay();
	
  UART_OutString("AT+CMGS =+254716240955\r");
	//OutCRLF();
  Delay();
	UART_OutString("Hello");
	
	UART_OutString("1A");
		
	x--;
			}
  }
}
