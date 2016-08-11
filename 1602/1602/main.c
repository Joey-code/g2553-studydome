#include <msp430g2553.h> 
#define RS1 P2OUT |=BIT3 
#define RS0 P2OUT &=~BIT3 
#define RW1 P2OUT |=BIT4 
#define RW0 P2OUT &=~BIT4
#define EN1 P2OUT |=BIT5
#define EN0 P2OUT &=~BIT5
//sbit RS = P2^4;   //����˿� 
//sbit RW = P2^5;   	// 51�����Ŷ���
//sbit EN = P2^6;     //��P2OUT=0X38��P2.3,4,5	
//LCD_Write_Com(0x18);//��ƽ�ƻ��� 0x1C ����ƽ��
int data; 
int i,j; 
double n; 
char a[]; 

/************************��ʱ����*****************************/ 
void delay(int i) 
{ 
 int s=500; 
 for(;i>0;i--) 
  for(;s>0;s--) ;
} 
/************************lcdдָ��*****************************/ 
void write_com(char com) 
{ 
  RS0;//RS=0,����ָ�� 
  RW0;//RW=0����lcdд��ָ������� 
  EN0;//EN=0��ʼ��ִ��ָ�� 
  delay(8); 
  P1OUT=com; 
  delay(8); 
  EN1;//EN=1����ȡ��Ϣ 
  delay(8); 
  EN0;//EN=0��ִ��ָ�� 
} 
/************************lcdд����*****************************/ 
void write_data(char data_bit) 
{ 
 RS1;//RS=1���������� 
 RW0;//RW=0����lcdд��ָ������� 
 EN0;//EN=0��ִ��ָ�� 
 delay(8); 
 P1OUT=data_bit; 
 delay(8); 
 EN1;//EN=1,��ȡ��Ϣ 
 delay(8); 
 EN0;//EN=0��ִ��ָ�� 
} 

/************************lcd��ʼ��*****************************/ 
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

/************************lcd��ʾ*****************************/
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
/************************������*****************************/ 
void main(void) 
{ 
    WDTCTL = WDTPW + WDTHOLD;              // Stop WDT 
    P1SEL=0x00;       //����P2Ϊͨ��IO 
    P1DIR |= 0xff;                         // Set P2 to output direction 
     P2DIR |= 0x38;      //0011 1000  p1.3 1.4 1.5 ��ΪLCDʹ��
     //��λ���ƶ� 
  initial_lcd();      //LCD��ʼ�� 
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
        for(j = 0;j <= 618;j++)     //ɨ����ʱ���ȶ���ʾ 
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