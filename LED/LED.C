#include <lpc21xx.h>
void delay(unsigned long int d)
{
while(d--);
}
int main()
{
IODIR0=1<<0;
PINSEL0=0;
while(1)
{
	IOSET0=1;
	delay(500000);
	IOCLR0=1;
	delay(500000);
}
}

