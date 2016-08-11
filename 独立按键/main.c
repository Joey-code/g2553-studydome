#include "msp430g2553.h"
#define uint unsigned int    //�궨��
#define uchar unsigned char  //�궨��
#define key P2IN&0XC3      //P2�ڵ�2��3��4��5��Ϊ��������
void delay(uchar);
void display(uint);
uchar tt,t;
uchar table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f};
void main( void )
{
  WDTCTL = WDTPW + WDTHOLD;
  P2DIR|=BIT0+BIT1;     //P2�ڵ�0��1λ��Ϊ����ܵĶ�ѡ��λѡ
  P2OUT&=~(BIT0+BIT1);
  P2DIR&=~(BIT2+BIT3+BIT4+BIT5);  //P2�ڵ�2��3��4��5��Ϊ��������
  P2REN|=0x3c;     //����P2�ڵ�2345����������Ĵ���
  P2OUT|=~0xC3;     //�趨2345��Ϊ�ߵ�ƽ
  P1DIR=0XFF;
  P1OUT=0XFF;
  tt=0;      
  display(tt);
  t=P2IN;        //t��Ϊ�˷��㵥�����Կ�P2IN��
  while(1)
	{   
            while((P2IN|0Xc3)==0XFF);     //����Ƿ��а���
            if((key&BIT2)==0)	       //��������Ƿ�ΪP2^2;
		{	
			delay(10);     
			if((key&BIT2)==0)     //��ʱ����
			{
				tt=1;   
                                display(tt);    //��ʾ
			}
		while((key&BIT2)==0);	//�ɼ����
		delay(10);
		while((key&BIT2)==0);   
			tt=0;
                        display(tt);
		}
                
                if((key&BIT3)==0)				//�������
		{	
			delay(10);
			if((key&BIT3)==0)
			{
				tt=2;
                                display(tt);
			}
		while((key&BIT3)==0);			//�ɼ����
		delay(10);
		while((key&BIT3)==0);
			tt=0;
                        display(tt);
		}
                
                if((key&BIT4)==0)				//�������
		{	
			delay(10);
			if((key&BIT4)==0)
			{
				tt=3;
                                display(tt);
			}
		while((key&BIT4)==0);			//�ɼ����
		delay(10);
		while((key&BIT4)==0);
			tt=0;
                        display(tt);
		}
                
                if((key&BIT5)==0)				//�������
		{	
			delay(10);
			if((key&BIT5)==0)
			{
				tt=4;
                                display(tt);
			}
		while((key&BIT5)==0);			//�ɼ����
		delay(10);
		while((key&BIT5)==0);
			tt=0;
                        display(tt);
		}
	}
}
void delay(uchar z)                     //��ʱ����
	{
		uint x,y;
		for(x=z;x>0;x--)
		for(y=1400;y>0;y--);
	}

void display(uint tt)           //��ʾ����
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