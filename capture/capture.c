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
    _EINT(); //开总中断 
    while((!(ist==1))|(!(iend==1)));
    ist=0;
    iend=0;
    cha=overflow*65536+end - start;
    time = (float)cha/1000000;
    juli =time*170;  
 }
}


#pragma vector= TIMER0_A1_VECTOR               //定时器A中断处理
__interrupt void timer_A3(void)
{
    
    switch(TAIV)                               //向量查询
       { case 2:                                 //捕获中断
            if(TACCTL1 & CCI)                        //上升沿
              {
                       //更变设置为下降沿触发
                start=TAR;                       //记录初始时间
                overflow=0; //溢出计数变量复位
                ist=1;
              }
            else                   //下降沿
             {     
               if(ist==1)
               {
                end=TAR;//用start,end,overflow计算脉冲宽度
                iend=1;
                TACTL|=TACLR;
               }
               }
            CCTL1&=~CCIFG;
            break;
         case 10:                                //定时器溢出中断
         {
           overflow++;
         } break;                               //溢出计数加1
         default:break;
       } 
  }
 
/************************延时函数*****************************/ 
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




