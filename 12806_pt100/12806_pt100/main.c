#include "msp430g2553.h"
#include"LCD12864P.h"
float V0,g,R,ave; 
int max,min;
uchar m,i;
long int sum;
uchar DispBuff[],yushe[]={'0','0','C','\0','\0'};
int a[];
void display();
void init_AD();
float Lineariztion(float j);
uchar *write_Num(float DegC);
void main(void)
{  
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  Ini_Lcd();
  init_AD();
while(1)
  {
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exi
       }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{  
  sum+=ADC10MEM;
  max=max>ADC10MEM?max:ADC10MEM; 
  min=ADC10MEM>min?min:ADC10MEM;
  m++; 
  if(m>17)
{
m=0;
ave=(sum-max-min)>>4;
sum=0;
Lineariztion(ave);
write_Num(g);

}
__bic_SR_register_on_exit(CPUOFF); 
}


void  init_AD()
{
 ADC10CTL0 = SREF_1 + ADC10SHT_3 + REFON + ADC10ON + ADC10IE+REF2_5V;
 delay_nus(60);
  ADC10CTL1 = INCH_0;                       // input A1
  ADC10AE0 |= 0x01; // PA.1 ADC option select
  max=a[0];
  min=1023;
}

float Lineariztion(float j)
{ 

float rt,rt1,t,n,k; 
V0=j/1023*2.5;
j=(j/1023*2.5)*3870/(53.07603259-(j/1023*2.5));   //53.03056815
rt=j; 
t=(rt-100)/0.36;
do{
    rt=j; 
    rt1=100+t*(0.390802-0.0000580195*t);
    k=rt1; 
    rt=j; 
    n=(rt-rt1)/0.36; 
    t=t+n; 
    rt1=k; 
    rt=j; 
  }
  while(((rt-rt1)>0.005)||(rt1-rt)>0.005); 
  g=t; 
  return(g); 
} 

uchar *write_Num(float DegC)
{
 int Num;
Num= DegC*100;
 char DispBuff[7];
uchar i;
DispBuff[5]='C';
DispBuff[6]='\0';
for(i=0;i<5;i++)                       //拆分数字
 {
if(i==2)                     //小数点
  DispBuff[i]='.';
 else
{
DispBuff[4-i]=(Num%10)+0x30;
Num/=10;
}
}
print_DZ(1,3,"温度");
print_DZ(1,5,":");
print_NDZ(4,0,"设定温度",4);
print_DZ(4,5,yushe);
for(i=0;i<10;i++)
print_DZ(3,2,DispBuff);
}