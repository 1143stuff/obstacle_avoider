// @author: Aditya Sundararajan
// www.github.com/1143stuff


#include<avr/io.h>
#define ADC_VREF_TYPE 0x40
#include<util/delay.h>
#include<stdlib.h>
#include "UART_mega128.h"
#define SET_BIT(a,b) a|=(1<<b)
#define CLR_BIT(a,b) a&=~(1<<b)
void init_adc(void);
unsigned int read_adc(unsigned char adc_input);
int main(void)
{
USART_Init(MYUBRR); //INIT the UART
int x,i;
DDRB=0x70;
DDRE=0xFF;
PORTB=0x10;
init_adc();
char buffer[32];

USART_Init(MYUBRR); //INIT the UART
USART_SendString("Hey UART is UP and RUNNING!!!\n"); //Welcome Message


while(1)
{
x=read_adc(7); //READ FROM ADC7 AS THE OBSTACLE SENSOR IS CONNECTED AT ADC7


sprintf(buffer,"%d\n",x); //DISPLAY THE VALUE OF x
USART_SendString(buffer);

//HERE, IT HAS BEEN PROGRAMMED IN SUCH A WAY THAT, IF OBSTABLE IS DETECTED, THE BOT WILL TURN RIGHT.

if(x<50) //IF OBSTACLE IS DETECTED
{
for(i=0;i<5;i++) //HERE, THE FOR LOOP IS EXECUTED 5 TIMES, SO THAT, ONCE OBSTACLE IS DETECTED, THE BOT WILL MAKE A PERFECT 90 DEGREE TURN TO THE RIGHT
{
CLR_BIT(PORTE,3); //THIS STOPS THE RIGHT MOTOR
SET_BIT(PORTB,6); //THIS STARTS THE LEFT MOTOR
_delay_ms(100);
}
}

else //IF NO OBSTACLE IS DETECTED, THE BOT WILL MOVE STRAIGHT
{
SET_BIT(PORTE,3); //THIS STARTS THE RIGHT MOTOR
SET_BIT(PORTB,6); //THIS STARTS THE LEFT MOTOR
}

}
return 0;
}

void init_adc(void)
{
// ADC initialization
// ADC Clock frequency: 2000.000 kHz
// ADC Voltage Reference: AVCC pin
ADMUX=0x40;
ADCSRA=0x83;
DDRF=0;
}
unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input|0x40;
//Delay needed for the stabilization of the ADC input voltage
_delay_us(10);
//Start the AD Conversion
ADCSRA|=0x40;
//Wait for the AD conversion to complete
while((ADCSRA & 0x10)==0);
ADCSRA|=0x10;
return ADCW;
}
