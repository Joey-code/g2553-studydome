#include "msp430g2553.h"
#define uint unsigned int    //宏定义
#define uchar unsigned char  //宏定义
#define key P2IN&0XC3      //P2口的2，3，4，5作为按键输入
void delay(uchar);
void display(uint);
uchar tt,t;
uchar table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f};
void main( void )
{
  WDTCTL = WDTPW + WDTHOLD;
  P2DIR|=BIT0+BIT1;     //P2口的0，1位作为数码管的段选和位选
  P2OUT&=~(BIT0+BIT1);
  P2DIR&=~(BIT2+BIT3+BIT4+BIT5);  //P2口的2，3，4，5作为按键输入
  P2REN|=0x3c;     //开启P2口的2345的上拉电阻寄存器
  P2OUT|=~0xC3;     //设定2345口为高电平
  P1DIR=0XFF;
  P1OUT=0XFF;
  tt=0;      
  display(tt);
  t=P2IN;        //t是为了方便单步调试看P2IN的
  while(1)
	{   
            while((P2IN|0Xc3)==0XFF);     //检测是否有按键
            if((key&BIT2)==0)	       //按键检测是否为P2^2;
		{	
			delay(10);     
			if((key&BIT2)==0)     //延时消抖
			{
				tt=1;   
                                display(tt);    //显示
			}
		while((key&BIT2)==0);	//松键检测
		delay(10);
		while((key&BIT2)==0);   
			tt=0;
                        display(tt);
		}
                
                if((key&BIT3)==0)				//按键检测
		{	
			delay(10);
			if((key&BIT3)==0)
			{
				tt=2;
                                display(tt);
			}
		while((key&BIT3)==0);			//松键检测
		delay(10);
		while((key&BIT3)==0);
			tt=0;
                        display(tt);
		}
                
                if((key&BIT4)==0)				//按键检测
		{	
			delay(10);
			if((key&BIT4)==0)
			{
				tt=3;
                                display(tt);
			}
		while((key&BIT4)==0);			//松键检测
		delay(10);
		while((key&BIT4)==0);
			tt=0;
                        display(tt);
		}
                
                if((key&BIT5)==0)				//按键检测
		{	
			delay(10);
			if((key&BIT5)==0)
			{
				tt=4;
                                display(tt);
			}
		while((key&BIT5)==0);			//松键检测
		delay(10);
		while((key&BIT5)==0);
			tt=0;
                        display(tt);
		}
	}
}
void delay(uchar z)                     //延时函数
	{
		uint x,y;
		for(x=z;x>0;x--)
		for(y=1400;y>0;y--);
	}

void display(uint tt)           //显示函数
{
  t=1;
  P2DIR=BIT0;
  P2OUT=BIT0;
  P1DIR=0xff;
  P1OUT=table[tt];
  P2OUT=0;
  P1OUT=0xff;  
  P2DIR=BIT1;
  P2OUT=BIT1;
  P1OUT=0xfe;
  delay(t);
 }