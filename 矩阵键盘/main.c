
#include "msp430g2553.h"
#include<key.h>
uchar tt;
void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  while(1)
  {
    Init_Keypad();
    Key_Event();
    tt=key_val;
  }
}
