#include <LPC21xx.H>
 
#define AA 1<<2
#define SI 1<<3
#define STO 1<<4
#define STA 1<<5
#define I2EN 1<<6

unsigned char i2c_read(int islast);
void i2c_init(void);
void i2c_start(void);
void i2c_write(unsigned char buff);
void i2c_stop(void);
void delay(void);
int i2c_wait_si(void);

int main(void)
{

	PINSEL0=1<<4|1<<6;       //Selecting I2C communication pin
	i2c_init();
	i2c_start(); 
	i2c_write(0xA0);	
        i2c_write(0x00);        //low
	i2c_write(0x00);	//high
	i2c_write('R');
	i2c_write('R');
	i2c_write('R');
	i2c_write('R');
        i2c_stop();
	
while(1)
	{
	  i2c_start();
	  i2c_write(0xA0);
          i2c_write(0x00);
          i2c_write(0x00);
          i2c_stop();
          i2c_start();
          i2c_write(0xA1);
          i2c_read(0);
          i2c_read(0);
          i2c_read(0);
          i2c_read(1);
          i2c_stop();
          delay();
}
}

unsigned char i2c_read(int islast){
	unsigned char data;
	I2CONCLR=SI;
	if(islast)
	{
		I2CONCLR=AA;
	}
	else	
		I2CONSET=AA;
	i2c_wait_si();
	data=I2DAT;
	return data;
}

void i2c_init(void)                      //I2C initilaization
{
    PINSEL0=1<<4|1<<6;
    I2SCLH=300;                              //Bit frequency calculated value
    I2SCLL=300;
    I2CONCLR=STA|STO|SI|AA;
    I2CONSET=I2EN;
}

void i2c_start(void)                     //I2C communication start
{ 
    I2CONCLR=STA|STO|SI|AA;
    I2CONSET=STA;
    i2c_wait_si();
}

int i2c_wait_si(void)
{
	int time=0;
	while(!(I2CONSET&SI))
	{
		time++;
		if(time>10000)
                break;//return 0;
	}
}

void i2c_write(unsigned char buff)      //Data writing through I2C
{	 
	I2DAT=buff;
	I2CONCLR=STA|STO|SI|AA;
	i2c_wait_si();
}

void delay()
{
        int i,d;
	for(i=0;i<10000;i++)
	{
                d++;
	}
        d=0;
}

void i2c_stop(void)                   //Stop the I2C communication
{
	int time=0;
  I2CONSET=STO;
	I2CONCLR=SI;
	while(I2CONSET&STO)
	{
		time++;
		if(time>10000)
		{
			break;
		}
	}
}
