#include <msp430g2553.h>
#define uchar unsigned char
#define uint unsigned int
void ta_init();
void Pid_init();
void pid_ys();
uint rltemp,settemp=40;
int e1,e2,e3,duk,uk;
uchar kp;
uchar ki;
uchar kd;    //����ΪPID�㷨�ı��������֣�΢��ϵ�� 
void ta_init()
{
  P1DIR |= 0x04;                            // P1.2 and P1.3 output
  P1SEL |= 0x04;                            // P1.2 and P1.3 TA1/2 options
  CCR0 = 100;                             // PWM Period
  CCTL1 = OUTMOD_7;                         // CCR1 reset/set
  CCR1 = 75;                               // CCR1 PWM duty cycle
  TACTL = TASSEL_2 + MC_1;                  // ACLK, up mode
}

/****************************** 
     PID�㷨ϵ������
*******************************/
void Pid_init()
{
CCR1= 0;
e1 = 0;
e2 = 0;
e3 = 0;
kp = 10;
ki = 5;
kd = 5; 
}

/****************************** 
     �¶ȱȽ�  PID�㷨
*******************************/
void pid_ys()
{
if(rltemp<settemp)  // ���ʵ���¶�С���趨ֵ
{
  if(settemp-rltemp>5) // ������5��
  {
   CCR1=100;  //ȫ�ټ���
  }
  else       //��������PID�㷨����ƽ������
  {        
   e1 = settemp-rltemp;
   duk=(kp*(e1-e2)+ki*e1+kd*(e1-e2*2+e3))/10;
   uk = uk+duk;
   if(uk>100)
   uk = 100;
   else if(uk<-100)
   uk = -100;
   if(uk<0)
   {
   CCR1=-uk;
   }
   else
   {
   CCR1=uk;
   }
   e3 = e2;
   e2 = e1; 
  }
}
if(rltemp>=settemp) // ���ʵ���¶ȴ����趨ֵ
{
  if(rltemp-settemp>0)  //ֻҪʵ���¶����趨ֵ��ƫ��
  {
   CCR1=0;    //ֹͣ����
  }
  else      //�����������PID�㷨����������ǰ��ĸպ��෴
  {
   e1 = rltemp-settemp;
   duk=(kp*(e1-e2)+ki*e1+kd*(e1-e2*2+e3))/10;
   uk = uk+duk;
   if(uk>100)
   uk = 100;
   else if(uk<-100)
   uk = -100;
   if(uk<0)
   {
    CCR1=100-(-uk);
   }
   else
   {
    CCR1=100-uk;
   }
   e3 = e2;
   e2 = e1; 
  }
}
}

/****************************** 
           ������
*******************************/
void main()
{
WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
 ta_init();
Pid_init(); // PID��ʼ
//��ʾ
while(1)
{
      rltemp =37;
 // rltemp = g;  //��PID�㷨װ��ʵ��ֵ  ��ʾ
  pid_ys();//�����¶ȱȽ� PID�㷨
}
}
