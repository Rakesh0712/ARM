#include <lpc21xx.h>
#include <stdio.h>
#define rs 9
#define rw 10
#define en 8

void delay(unsigned long int );
void displays(const char[],int);
void display(char,int);
int i,k=31;
unsigned long int adc;
char adc1[5];

int main()
{
	PINSEL0=1<<22;
	ADCR=1<<0|1<<15|1<<21|1<<24;
	IODIR0=0xf7ff;
	display(0x0e,0);
	//CCR=0x11;
	display('A',1);
while(1)
{
	//delay(10000000);
	while(!(ADDR&(1<<k)));
	ADDR=1<<k;
	adc=((ADDR>>6)&0x3ff);
	sprintf(adc1,"%04lu",adc);	
	display(0x80,0);
	for(i=0;i<4;i++)
		{
		 display(adc1[i],1);
		}
		delay(10000);
}
}
void displays(const char c[], int x)
{	
	for(i=0;c[i]!='\0';i++)
	{
		IOSET0=c[i];
 		if(x==0)
		{
			IOCLR0=1<<rs;
		}
                else
		{
			IOSET0=1<<rs;
		}
	IOCLR0=1<<rw;
	IOSET0=1<<en;
	delay(100000);
	IOCLR0=1<<en;
	delay(100000);
	IOCLR0=c[i];
}
}

void delay(unsigned long int d)
{
while(d--);
}

void display(char c, int x)
{	
		IOSET0=c;
  		if(x==0)
		{
			IOCLR0=1<<rs;
		}
	else
		{
			IOSET0=1<<rs;
		}
	
	IOCLR0=1<<rw;
	IOSET0=1<<en;
	delay(100000);
	IOCLR0=1<<en;
	delay(100000);
	IOCLR0=c;
}
