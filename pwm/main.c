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
uchar kd;    //以上为PID算法的比例，积分，微分系数 
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
     PID算法系数设置
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
     温度比较  PID算法
*******************************/
void pid_ys()
{
if(rltemp<settemp)  // 如果实际温度小于设定值
{
  if(settemp-rltemp>5) // 如果相差5度
  {
   CCR1=100;  //全速加热
  }
  else       //否则运行PID算法进行平滑加热
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
if(rltemp>=settemp) // 如果实际温度大于设定值
{
  if(rltemp-settemp>0)  //只要实际温度与设定值有偏差
  {
   CCR1=0;    //停止加热
  }
  else      //其他情况运行PID算法，但参数与前面的刚好相反
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
           主函数
*******************************/
void main()
{
WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
 ta_init();
Pid_init(); // PID初始
//显示
while(1)
{
      rltemp =37;
 // rltemp = g;  //给PID算法装载实际值  显示
  pid_ys();//运行温度比较 PID算法
}
}
