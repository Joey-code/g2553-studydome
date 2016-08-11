#include <msp430g2553.h> 
#define RS1 P2OUT |=BIT3 
#define RS0 P2OUT &=~BIT3 
#define RW1 P2OUT |=BIT4 
#define RW0 P2OUT &=~BIT4
#define EN1 P2OUT |=BIT5
#define EN0 P2OUT &=~BIT5
//sbit RS = P2^4;   //定义端口 
//sbit RW = P2^5;   	// 51中引脚定义
//sbit EN = P2^6;     //用P2OUT=0X38即P2.3,4,5	
//LCD_Write_Com(0x18);//左平移画面 0x1C 是右平移
int data; 
int i,j; 
double n; 
char a[]; 

/************************延时函数*****************************/ 
void delay(int i) 
{ 
 int s=500; 
 for(;i>0;i--) 
  for(;s>0;s--) ;
} 
/************************lcd写指令*****************************/ 
void write_com(char com) 
{ 
  RS0;//RS=0,输入指令 
  RW0;//RW=0向lcd写入指令或数据 
  EN0;//EN=0始终执行指令 
  delay(8); 
  P1OUT=com; 
  delay(8); 
  EN1;//EN=1读取信息 
  delay(8); 
  EN0;//EN=0执行指令 
} 
/************************lcd写数据*****************************/ 
void write_data(char data_bit) 
{ 
 RS1;//RS=1输入数据 
 RW0;//RW=0向lcd写入指令或数据 
 EN0;//EN=0执行指令 
 delay(8); 
 P1OUT=data_bit; 
 delay(8); 
 EN1;//EN=1,读取信息 
 delay(8); 
 EN0;//EN=0执行指令 
} 

/************************lcd初始化*****************************/ 
void initial_lcd(void) 
{ 
  delay(20); 
 write_com(0x38); 
 delay(15); 
 write_com(0x0c); 
 delay(15); 
 write_com(0x06); 
 delay(15);
 write_com(0x01);
} 

/************************lcd显示*****************************/
void LCD_Display(char x,char y,char *str) 

{ 

 char xtemp; 

switch(x) 

    { 

case 0:xtemp=0x80+y; 

 break; 

case 1:xtemp=0xc0+y; 

 break; 

default:break; 

    } 

write_com(xtemp); 

while(*str!=0) 

    { 

 write_data(*str); 

str++; 

    } 

} 
/************************主函数*****************************/ 
void main(void) 
{ 
    WDTCTL = WDTPW + WDTHOLD;              // Stop WDT 
    P1SEL=0x00;       //设置P2为通用IO 
    P1DIR |= 0xff;                         // Set P2 to output direction 
     P2DIR |= 0x38;      //0011 1000  p1.3 1.4 1.5 作为LCD使能
     //复位控制端 
  initial_lcd();      //LCD初始化 
  __enable_interrupt();                     // Enable interrupts. 
   TACCR0 = 30;                              // Delay to allow Ref to settle 
    TACCTL0 |= CCIE;                          // Comvolre-mode interrupt. 
    TACTL = TASSEL_2 | MC_1;                  // TACLK = SMCLK, Up mode. 
    LPM0;                                     // Wait for delay. 
    TACCTL0 &= ~CCIE;                         // Disable timer Interrupt 
    __disable_interrupt(); 
  for (;;) 
     { 
     n =12345678; 
     a[0]=((long)n/100000000%10+0x30); 
     a[1]=0x2e; 
     a[2]=((long)n/10000000%10+0x30); 
     a[3]=((long)n/1000000%10+0x30); 
     a[4]=((long)n/100000%10+0x30); 
     a[5]=((long)n/10000%10+0x30); 
     a[6]=((long)n/1000%10+0x30);     
     a[7]=((long)n/100%10+0x30); 
     a[8]=((long)n/10%10+0x30); 
     a[9]=((long)n/1%10+0x30); 
     a[10]='\0'; 
        for(j = 0;j <= 618;j++)     //扫描延时稳定显示 
             { 
//   LCD_Display(0,0,"Voltage="); 
//   LCD_Display(0,15,"V"); 
   LCD_Display(0,15,a); 
   LCD_Display(1,15,"No:22 copyright"); 
              } 
      } 
} 
//  ADC10 interrupt service routine 
 #pragma vector=TIMER0_A0_VECTOR 
 __interrupt void ta0_isr(void) 
 { 
   TACTL = 0; 
   LPM0_EXIT;                                // Exit LPM0 on return 
 } 