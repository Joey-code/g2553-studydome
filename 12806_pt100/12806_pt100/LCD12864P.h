#ifndef LCD12864_H_
#define LCD12864_H_
#define uint unsigned int
#define uchar unsigned char
extern void delay_1ms();
extern void delay_nms(uint n);
extern void delay_1us();
extern void delay_nus(uint n);
extern void Ini_Lcd(void);
extern void Send(uchar type,uchar transdata);//0-д�������1-д����
extern void lcd_pos(uchar x,uchar y);//��λ
extern void Disp_DZ(const uchar * pt);//��ʾ����
extern void Disp_NDZ(const uchar * pt,uchar num);//��ʾ����
extern void Disp_SZ(uchar shuzi);//��ʾһ������print_zf(uchar x,uchar y,uchar zifu)
extern void print_DZ(uchar x,uchar y,const uchar * pt);
extern void print_NDZ(uchar x,uchar y,const uchar * pt,uchar num);
extern void print_ZF(uchar x,uchar y,uchar zifu);
extern void ClrScreen();
extern int *numd(float DegC);
#endif /* LCD12864_H_ */
