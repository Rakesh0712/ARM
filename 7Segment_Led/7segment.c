#include <lpc21xx.h>

void delay(unsigned long int );

int i=0;

int main()
{
	int num[]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7C,0X07,0X7F,0X6F};
	IODIR0=0xff;
	PINSEL0=0;	

while(1)
{
for(i=0x00;i<15;i++)
{
    IOSET0=i;
    delay(1000000);
    IOCLR0=i;
    delay(1000000);
}
}

}

void delay(unsigned long int d)
{
while(d--);
}
