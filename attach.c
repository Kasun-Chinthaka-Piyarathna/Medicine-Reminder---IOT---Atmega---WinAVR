
#define F_CPU 1000000UL
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTD2
#define EN eS_PORTD3
#define BAUD 9600                                   // define baud
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1) 


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

short place=2; short raw=2; short stop=1, lop = 0;
int num[4];
int *new_num;
int x;
char s1[2];
int i;
char m[4];
int arra;
volatile uint32_t count;
int k;
int l;
char new;
int med;

 unsigned char rxvalue(void);
 unsigned char rxdata,a,cmd,b;
 unsigned int z;
 unsigned char message[15];

void get_value();
void keypad();
void medic_details();
void ongoing(int arra);
 void Setup(void);
 void Loop(void);
 void serialSetup(void);
 void serialSend(char* sendString);
 void led(int med);
 void sendMSG();


int main(void)
{
	DDRD = 0xFF;
	DDRA = 0xFF;
	DDRB = 0x0F;
	PORTD=0xFF;
	DDRC = 0xFF;
	PORTA=0xFF;
    

    
    
    

	Lcd4_Init();
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,2);
	Lcd4_Write_String("Metrix Medics ");
	_delay_ms(100);
	Lcd4_Set_Cursor(2,5);
	Lcd4_Write_String("BOX");
	_delay_ms(1000);
	_delay_ms(1000);
	
	
	while(1)
	
	{ 
	
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,2);
	Lcd4_Write_String("Let's Enter ");
	Lcd4_Set_Cursor(2,2);
	Lcd4_Write_String("Medic Details");
	_delay_ms(1000);
	_delay_ms(1000);
	
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,2);
	Lcd4_Write_String("YES-01NO-Other");
	Lcd4_Set_Cursor(2,2);
	_delay_ms(1000);
	_delay_ms(1000);
	keypad();
	get_value();
	itoa(*new_num,s1,10);
	Lcd4_Clear();
	
	
	
	if(*new_num==01){
	
	Lcd4_Set_Cursor(1,2);
	Lcd4_Write_String("HOW MANY MEDICS ");
	Lcd4_Set_Cursor(2,2);
	Lcd4_Write_String("DO YOU HAVE");
	_delay_ms(1000);
	Lcd4_Clear();
	
	Lcd4_Set_Cursor(1,2);
	keypad();
	get_value();
	itoa(*new_num,s1,10);
	Lcd4_Clear();
	
	int m= num[1];
	
	
	
	for( i=0;i < m ; i++){
	
	medic_details();
	
	}

	
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,1);
	Lcd4_Write_String("Alerting_System ");
	Lcd4_Set_Cursor(2,2);
	Lcd4_Write_String("Is_Activated");
	_delay_ms(1000);
	
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,2);
	Lcd4_Write_String("Thank You ");
	Lcd4_Set_Cursor(2,2);
	Lcd4_Write_String("Very Much");
	_delay_ms(1000);
	Lcd4_Clear();
	
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,2);
	itoa(arra,new,10);
	Lcd4_Write_String(new);
	_delay_ms(1000);
	Lcd4_Clear();

	ongoing(arra);
	
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,2);
	Lcd4_Write_String("Metrix Medics ");
	_delay_ms(100);
	Lcd4_Set_Cursor(2,5);
	Lcd4_Write_String("BOX");

	}    
	
	else{

	Lcd4_Set_Cursor(1,2);
	Lcd4_Write_String("Metrix Medics ");
	_delay_ms(100);
	Lcd4_Set_Cursor(2,5);
	Lcd4_Write_String("BOX");


	}
	
	
	
	while(lop < 8)
	{
	
	keypad();
	_delay_ms(100);
	lop = num[0];
	  x=0;
	  raw=2;
	  place=2;
	}
	lop = 0;
	
	
	
 }	

}

void keypad(void){
	do{
		
		if(x<=1){
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("_");
		}
		else{
			
			break;
		}
		
		PORTB|=1<<PINB0;
		_delay_ms(20);

		if(bit_is_set(PINB,4))
		{
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("1");
			_delay_ms(180);
			place++;
			num[x]=1;
			++x;
		}

		if(bit_is_set (PINB,5))
		{
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("2");
			_delay_ms(180);
			place++;
			num[x]=2;
			++x;
		}

		if(bit_is_set (PINB,6))
		{
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("3");
			_delay_ms(180);
			place++;
			num[x]=3;
			++x;
		}

		PORTB&=~(1<<PINB0);
		PORTB|=(1<<PINB1);
		_delay_ms(20);

		if(bit_is_set(PINB,4))
		{
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("4");
			_delay_ms(180);
			place++;
			num[x]=4;
			++x;
		}

		if(bit_is_set (PINB,5)){
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("5");
			_delay_ms(180);
			place++;
			num[x]=5;
			++x;
		}

		if(bit_is_set(PINB,6)){
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("6");
			_delay_ms(180);
			place++;
			num[x]=6;
			++x;
		}

		PORTB&=~(1<<PINB1);
		PORTB|=(1<<PINB2);
		_delay_ms(20);

		if(bit_is_set(PINB,4))
		{
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("7");
			_delay_ms(180);
			place++;
			num[x]=7;
			++x;
		}

		if(bit_is_set (PINB,5))
		{
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("8");
			_delay_ms(180);
			place++;
			num[x]=8;
			++x;
		}

		if(bit_is_set(PINB,6)){
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("9");
			_delay_ms(180);
			place++;
			num[x]=9;
			++x;
		}

		PORTB&=~(1<<PINB2);
		PORTB|=(1<<PINB3);
		_delay_ms(20);

		if(bit_is_set (PINB,5)){
			Lcd4_Set_Cursor(raw,place);
			Lcd4_Write_String("0");
			_delay_ms(180);
			place++;
			num[x]=0;
			++x;
		}

		PORTB&=~(1<<PINB3);
		
		
		
	}
	while(stop==1);
}

void get_value(){
	int n1,n2;
	n1=num[0];
	n2=num[1];
	if(x==1)
	*new_num=n1;
	if(x==2)
	*new_num=(n1*10)+n2;
    x=0;
	raw=2;
	place=2;
}

void medic_details(){
	Lcd4_Set_Cursor(1,2);
	Lcd4_Write_String("Please! Enter ");
	Lcd4_Set_Cursor(2,2);
	Lcd4_Write_String("Medic Details");
	_delay_ms(1000);

	Lcd4_Clear();
	Lcd4_Set_Cursor(1,2);
	Lcd4_Write_String("Medication:");
	Lcd4_Set_Cursor(2,2);
	keypad();
	get_value();
	itoa(*new_num,s1,10);
    med=num[1];
	 
	 Lcd4_Clear();
	 Lcd4_Write_String("you entered:");
	 Lcd4_Write_String(s1);
	_delay_ms(1000);
	
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,2);
	Lcd4_Write_String("Hourly For ");
	Lcd4_Set_Cursor(2,2);
    keypad();
	get_value();
	itoa(*new_num,s1,10);
    arra=num[1];
	Lcd4_Clear();
	Lcd4_Write_String("you entered:");
	Lcd4_Write_String(s1);
	_delay_ms(1000);
	
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,2);
	Lcd4_Write_String("Days ");
	Lcd4_Set_Cursor(2,2);
    keypad();
	 get_value();
	 itoa(*new_num,s1,10);
	 Lcd4_Clear();
	 Lcd4_Write_String("you entered:");
	 Lcd4_Write_String(s1);
	_delay_ms(1000);
	
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,2);
	Lcd4_Write_String("Time Interval ");
	Lcd4_Set_Cursor(2,2);
	keypad();
	 get_value();
	 itoa(*new_num,s1,10);
	 Lcd4_Clear();
	 Lcd4_Write_String("you entered:");
	 Lcd4_Write_String(s1);
	_delay_ms(1000);
	
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,2);
	Lcd4_Write_String("Dose");
	Lcd4_Set_Cursor(2,2);
	keypad();
	 get_value();
	 itoa(*new_num,s1,10);
	 Lcd4_Clear();
	 Lcd4_Write_String("you entered:");
	 Lcd4_Write_String(s1);
	_delay_ms(1000);
	
	Lcd4_Clear();
	Lcd4_Set_Cursor(1,2);
	Lcd4_Write_String("BM=01/AM=02");
	Lcd4_Set_Cursor(2,2);
	keypad();
	 get_value();
	 itoa(*new_num,s1,10);
	 Lcd4_Clear();
	 Lcd4_Write_String("you entered:");
	 Lcd4_Write_String(s1);
	_delay_ms(1000);
	 Lcd4_Clear();
}

      void ongoing(int arra){
	   l = 60 * arra;
	 		Lcd4_Set_Cursor(1,2);
			Lcd4_Write_String("MATRIX MEDICS");
	  
	  for( k=0 ; k<l ; k++){

			Lcd4_Set_Cursor(1,0);
			Lcd4_Shift_Right();
				
	
			//_delay_ms(1000);
			//DDRD=0b1100000;
			PORTC|=1<<PINC1;
			//PORTA=0b10000001;
			_delay_ms(800);
			PORTC&=~(1<<PINC1);
			//PORTC=0b00000000;
			_delay_ms(200);
	  }
	  
	  		Lcd4_Clear();
			Lcd4_Set_Cursor(1,2);
			Lcd4_Write_String("IT'S TIME TO");
			Lcd4_Set_Cursor(2,2);
			Lcd4_Write_String("GET MEDICINE");
			PORTC|=1<<PINC0;
			_delay_ms(1000);
			_delay_ms(1000);
			PORTC&=~(1<<PINC0);
			sendMSG();
			led(med);
				
	  
}  
void uart_init (void)
{
	UBRRH = (BAUDRATE>>8);                      // shift the register right by 8 bits
	UBRRL = BAUDRATE;                           // set baud rate
	UCSRB|= (1<<TXEN)|(1<<RXEN);                // enable receiver and transmitter
	UCSRC|= (1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);   // 8bit data format
}
void uart_transmit_char (unsigned char data)
{
	while (!( UCSRA & (1<<UDRE)));                // wait while register is free
	UDR = data;                                   // load data in the register
}
void uart_transmit_string (const unsigned char* st)
{
	
	
		while(*st)
		uart_transmit_char(*st++);
	                         // load data in the register
}
 
 unsigned char rxvalue(void){
	 while(!(UCSRA&(1<<RXC)));
	 {
		 rxdata=UDR;
		 return rxdata;
	}
 }

void sendMSG(){



	 Lcd4_Clear();
	 Lcd4_Set_Cursor(1,1);
	 Lcd4_Write_String("Sending MSG");
	 _delay_ms(1000);
	 Lcd4_Clear();
	 Lcd4_Write_String("Setting UART....");
	 uart_init();
	 uart_transmit_string("AT+CMGF=1");
	 uart_transmit_char((char)13);
	 _delay_ms(1000);
	 uart_transmit_string("AT+CMGS=\"+94718724671\"\r");
	 _delay_ms(1000);
	 uart_transmit_string("Aleart from MEDIC BOX");
	

	 _delay_ms(1000);
	 uart_transmit_char((char)26);
	 _delay_ms(1000);
	 _delay_ms(1000);
	 _delay_ms(1000);
	 Lcd4_Clear();
	

}
void led(int med){

switch(med){

case 1:
			PORTA=0b00000001;
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			PORTA=0b01111111;
			break;

case 2:
			PORTA=0b00000010;
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			PORTA=0b01111111;
			break;
			
case 3:
			PORTA=0b00000100;
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			PORTA=0b01111111;
			break;

case 4:
			PORTA=0b00001000;
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			PORTA=0b01111111;
			break;

case 5:
			PORTA=0b00010000;
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			PORTA=0b01111111;
			break;

case 6:
			PORTA=0b00100000;
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			PORTA=0b01111111;
			break;

default:
			PORTA=0b01000000;
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			_delay_ms(1000);
			PORTA=0b01111111;
			break;



	}

}