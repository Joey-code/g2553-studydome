#include<msp430g2553.h>  
#define uint unsigned int 
#define uchar unsigned char  	
uchar t;
void delay(uchar z)
	{
		uchar x,y;
		for(x=z;x>0;x--)
		for(y=110;y>0;y--);
	}
void main()		   
{
	t=10;	
	while(1)
	{
		P2DIR=BIT0;
                P2OUT=BIT0;
                P1DIR=0xff;
		P1OUT=0x6d;
		P2OUT=0;
		P2DIR=BIT1;
                P2OUT=BIT1;
                P1DIR=0xff;
                P1OUT=0xfe;
                P2OUT=0;
		delay(t);

		P2DIR=BIT0;
                P2OUT=BIT0;
                P1DIR=0xff;
		P1OUT=0x66;
		P2OUT=0;
		P2DIR=BIT1;
                P2OUT=BIT1;
                P1DIR=0xff;
                P1OUT=0xfd;
                P2OUT=0;
		delay(t);
                
                P2DIR=BIT0;
                P2OUT=BIT0;
                P1DIR=0xff;
		P1OUT=0x4f;
		P2OUT=0;
		P2DIR=BIT1;
                P2OUT=BIT1;
                P1DIR=0xff;
                P1OUT=0xfb;
                P2OUT=0;
		delay(t);
                
                P2DIR=BIT0;
                P2OUT=BIT0;
                P1DIR=0xff;
		P1OUT=0x5b;
		P2OUT=0;
		P2DIR=BIT1;
                P2OUT=BIT1;
                P1DIR=0xff;
                P1OUT=0xf7;
                P2OUT=0;
		delay(t);
                
                P2DIR=BIT0;
                P2OUT=BIT0;
                P1DIR=0xff;
		P1OUT=0x06;
		P2OUT=0;
		P2DIR=BIT1;
                P2OUT=BIT1;
                P1DIR=0xff;
                P1OUT=0xef;
                P2OUT=0;
		delay(t);
                
                P2DIR=BIT0;
                P2OUT=BIT0;
                P1DIR=0xff;
		P1OUT=0x3f;
		P2OUT=0;
		P2DIR=BIT1;
                P2OUT=BIT1;
                P1DIR=0xff;
                P1OUT=0xdf;
                P2OUT=0;
		delay(t);
	}	
}


		