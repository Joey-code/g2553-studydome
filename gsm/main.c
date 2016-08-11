#include  "msp430g2553.h"
unsigned char string1[] = { "at\r" };
unsigned char string2[] = { "at+cmgf=1\r" };
unsigned char string3[] = { "at+cmgs=" };
unsigned char string4[] = { "18773221946" };
unsigned char string5[] = { "heihei" };
unsigned char string6[] = { "\x1a\r" };
void _delay_cycles(unsigned long x){
    while(x--);
}
void main(void)
{
unsigned int a=0;
unsigned int b=0;
unsigned int c=0;
unsigned int d=0;
unsigned int e=0;
unsigned int f=0;

  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |=BIT0;

//uart≥ı ºªØ
  P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
  P1SEL2= BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD

  UCA0CTL1 |= UCSSEL_1;                     // CLK = ACLK
  UCA0BR0 = 0x03;                           // 32kHz/9600 = 3.41
  UCA0BR1 = 0x00;                           //
  UCA0MCTL = UCBRS1 + UCBRS0;               // Modulation UCBRSx = 3
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

while(1)
{
	_delay_cycles(2000000);
while(string1[a])                 // USCI_A0 TX buffer ready?
  { while (!(IFG2&UCA0TXIFG));
	UCA0TXBUF =string1[a++];}

_delay_cycles(2000000);
while(string2[b])                 // USCI_A0 TX buffer ready?
  { while (!(IFG2&UCA0TXIFG));
	UCA0TXBUF =string2[b++];}

_delay_cycles(2000000);
while(string3[c])                 // USCI_A0 TX buffer ready?
  {while (!(IFG2&UCA0TXIFG));
	UCA0TXBUF =string3[c++];}
while (!(IFG2&UCA0TXIFG));
UCA0TXBUF='"';
while(string4[d])                 // USCI_A0 TX buffer ready?
  {while (!(IFG2&UCA0TXIFG));
	UCA0TXBUF =string4[d++];}
while (!(IFG2&UCA0TXIFG));
UCA0TXBUF='"';
	 while (!(IFG2&UCA0TXIFG));
	 UCA0TXBUF='\r';

	 _delay_cycles(2000000);
	 while(string5[e])                 // USCI_A0 TX buffer ready?
	   {while (!(IFG2&UCA0TXIFG));
		 UCA0TXBUF =string5[e++];}

	 _delay_cycles(2000000);
	 while(string6[f])                 // USCI_A0 TX buffer ready?
	   {while (!(IFG2&UCA0TXIFG));
		 UCA0TXBUF =string6[f++];}

	 _delay_cycles(10000000);
	 a=0;
	 b=0;
	 c=0;
	 d=0;
	 e=0;
	 f=0;
}}



