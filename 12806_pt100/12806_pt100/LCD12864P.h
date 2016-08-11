#ifndef LCD12864_H_
#define LCD12864_H_
#define uint unsigned int
#define uchar unsigned char
extern void delay_1ms();
extern void delay_nms(uint n);
extern void delay_1us();
extern void delay_nus(uint n);
extern void Ini_Lcd(void);
extern void Send(uchar type,uchar transdata);//0-写控制命令，1-写数据
extern void lcd_pos(uchar x,uchar y);//定位
extern void Disp_DZ(const uchar * pt);//显示汉字
extern void Disp_NDZ(const uchar * pt,uchar num);//显示汉字
extern void Disp_SZ(uchar shuzi);//显示一个数字print_zf(uchar x,uchar y,uchar zifu)
extern void print_DZ(uchar x,uchar y,const uchar * pt);
extern void print_NDZ(uchar x,uchar y,const uchar * pt,uchar num);
extern void print_ZF(uchar x,uchar y,uchar zifu);
extern void ClrScreen();
extern int *numd(float DegC);
#endif /* LCD12864_H_ */
