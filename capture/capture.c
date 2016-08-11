#include "msp430g2553.h"
#define uchar unsigned char
void main( )
{
   WDTCTL = WDTPW + WDTHOLD;  // Stop watchdog timer to prevent time out reset
    if (CALBC1_16MHZ ==0xFF || CALDCO_16MHZ == 0xFF)                                     
  {  
    while(1);                 // If calibration constants erased
                            // do not load, trap CPU!!
  } 

  P1DIR &= ~BIT2;         // P1.2 = (InputDirection + TA0.1) = CCIxA.1 --> CCR1
  P1SEL |= BIT2;
  TACTL = TASSEL_2  + MC_2 + TAIE;   //SMCLK,  /8 UCCR0
  CCTL1 = CM_3 + SCS + CAP + CCIE+CCIS_0;
    while(1)
 {
    _EINT(); //�����ж� 
    while((!(ist==1))|(!(iend==1)));
    ist=0;
    iend=0;
    cha=overflow*65536+end - start;
    time = (float)cha/1000000;
    juli =time*170;  
 }
}


#pragma vector= TIMER0_A1_VECTOR               //��ʱ��A�жϴ���
__interrupt void timer_A3(void)
{
    
    switch(TAIV)                               //������ѯ
       { case 2:                                 //�����ж�
            if(TACCTL1 & CCI)                        //������
              {
                       //��������Ϊ�½��ش���
                start=TAR;                       //��¼��ʼʱ��
                overflow=0; //�������������λ
                ist=1;
              }
            else                   //�½���
             {     
               if(ist==1)
               {
                end=TAR;//��start,end,overflow����������
                iend=1;
                TACTL|=TACLR;
               }
               }
            CCTL1&=~CCIFG;
            break;
         case 10:                                //��ʱ������ж�
         {
           overflow++;
         } break;                               //���������1
         default:break;
       } 
  }
 
/************************��ʱ����*****************************/ 
void delay(int i) 
{ 
 int s=570; 
 for(;i>0;i--) 
 for(;s>0;s--) ;
} 

void delay_s(int i) 
{ 
 int s=1140; 
 for(;i>0;i--) 
 for(;s>0;s--) ;
} 




