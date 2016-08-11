#include<msp430g2553.h>
#define BIT(x)        (1 << (x))
#define uint unsigned int
#define uchar unsigned char
void Send(uchar type,uchar transdata);
#define cyCS      0    //P1.0，片选信号//
#define cySID     1    //P1.1，串行数据
#define cyCLK    3   //P1.2，同步时钟
#define cyPORT    P1OUT
#define cyDDR     P1DIR

//1us延时函数
void delay_1us(void) 
{
        asm("nop");
}
//N us延时函数
void delay_nus(unsigned int n)
 {
        unsigned int i;
        for (i = 0; i < n; i++)
                delay_1us();
}
 void delay_1ms()
{
        uint i;
        for(i=0;i<1140;i++);
}
 
void delay_nms(uint n)
{
    uint i = 0;
    for(i = n;i > 0;i--)
        delay_1ms();
}
 
void Ini_Lcd(void)
{
        cyDDR |= BIT(cyCLK) + BIT(cySID) + BIT(cyCS);   //相应的位端口设置为输出
         delay_nms(60);  //延时等待液晶完成复位
        Send(0,0x30);  /*功能设置:一次送8位数据,基本指令集*/
        delay_nus(140);
        Send(0,0x02);  /*DDRAM地址归位*/
        delay_nus(40);
        Send(0,0x0c);  /*显示设定:开显示,不显示光标,不做当前显示位反白闪动*/
        delay_nus(100);
        Send(0,0x01);  /*清屏，将DDRAM的位址计数器调整为“00H”*/
        delay_nms(15);
        Send(0,0x06);  /*功能设置，点设定:显示字符/光标从左到右移位,DDRAM地址加1*/
        delay_nus(110);
}
 
void Send(uchar type,uchar transdata)//0-写控制命令，1-写数据
{
        uchar firstbyte = 0xf8;
        uchar temp;
        uchar i,j = 3;
        if(type) firstbyte |= 0x02;
        cyPORT |= BIT(cyCS);
        cyPORT &= ~BIT(cyCLK);
        while(j > 0)
        {
              if(j == 3) temp = firstbyte;
              else if(j == 2) temp = transdata&0xf0;
              else  temp = (transdata << 4) & 0xf0;
              for(i = 8;i > 0;i--)
                {
                        if(temp & 0x80)      
                          cyPORT |= BIT(cySID);
                        else                     
                          cyPORT &= ~BIT(cySID);
                        cyPORT |= BIT(cyCLK);
                        temp <<= 1;
                        cyPORT &= ~BIT(cyCLK);
                }
                //三个字节之间一定要有足够的延时，否则易出现时序问题
                if(j == 3)     
                  delay_nms(1);
                else          
                  delay_nms(1);
                  j--;
        }
        cyPORT &= ~BIT(cySID);
        cyPORT &= ~BIT(cyCS);
}
 
void lcd_pos(uchar x,uchar y)//定位
{
         uchar pos;
          switch(x)
          {
            case 1:pos=0x80;break;
            case 2:pos=0x90;break;
            case 3:pos=0x88;break;
            case 4:pos=0x98;break;
            default:pos=0x80;
          }
          pos += y;
          Send(0,pos);
}
 
void Disp_DZ(const uchar * pt)//显示汉字
{
 
           for(;*pt!='\0';)
           Send(1,*(pt++));
}

void print_DZ(uchar x,uchar y,const uchar * pt)
{
	lcd_pos(x,y);
    
    for(;*pt!='\0';)
    Send(1,*(pt++));
}
void Disp_NDZ(const uchar * pt,uchar num)//显示汉字  用处不大
{
    uchar i;
           for(i = 0;i < (num*2);i++)
           Send(1,*(pt++));
}


void print_NDZ(uchar x,uchar y,const uchar * pt,uchar num)
{
	lcd_pos(x,y);
    uchar i;
    for(i = 0;i < (num*2);i++)
    Send(1,*(pt++));
}
 
void print_ZF(uchar x,uchar y,uchar zifu)//显示一个字符
{
	lcd_pos(x,y);
    Send(1,zifu);
}

void ClrScreen()
{ 
  Send(0,0x01);
   delay_nms(1);
}

/*uchar *numd(float DegC)
{
   int wendu;
    wendu= DegC*100;
    b[0]=((long)wendu/1000+0x30);
    b[1]=((long)wendu%1000/100+0x30);
    b[2]=0x2e;  
    b[3]=((long)wendu%100/10+0x30);
    b[4]=((long)wendu%10+0x30);
    b[5]='\0';
    return(b); 
}
*/
