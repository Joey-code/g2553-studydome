#include<msp430g2553.h> 
#define uint unsigned int   
#define uchar unsigned char
uint tt;
uchar t,bai,shi,ge,flag,num;
uchar table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f};
void init();
void delay(uchar);
void display(uint);
void main()
{
  WDTCTL=WDT_MDLY_0_5;
  IE1|=WDTIE;
  IFG1|=WDTIFG;
  init();
 while(1);
}
void init()
{	
  P2DIR=0XFF;
  P1DIR=0xff;
  P1OUT=0;
  flag=0;
  num=0;
}

void delay(uchar z)
	{
		uchar x,y;
		for(x=z;x>0;x--)
		for(y=110;y>0;y--);
	}

void display(uint tt)
{
  t=1;
  bai=tt/100;
  shi=tt%100/10;
  ge=tt%10;

  P2DIR=BIT0;
  P2OUT=BIT0;
  P1DIR=0xff;
  P1OUT=table[bai];
  P2OUT=0;
  P1OUT=0xff;  
  P2DIR=BIT1;
  P2OUT=BIT1;
  P1OUT=0xfe;
  delay(t);
  
  P2DIR=BIT0;
  P2OUT=BIT0;
  P1DIR=0xff;
  P1OUT=table[shi];
  P2OUT=0;
  P1OUT=0xff;  
  P2DIR=BIT1;
  P2OUT=BIT1;
  P1OUT=0xfd;
  delay(t);
	
  P2DIR=BIT0;
  P2OUT=BIT0;
  P1DIR=0xff;
  P1OUT=table[ge];
  P2OUT=0;
  P1OUT=0xff;  
  P2DIR=BIT1;
  P2OUT=BIT1;
  P1OUT=0xfb;
  delay(t);	
}
#pragma vector=WDT_VECTOR
__interrupt void watchdog()
{
 num++;
 if(num==20)
 {
  num=0;   
  tt++;
  if(tt==1000)
    tt=0;
  display(tt);
  }
}
 