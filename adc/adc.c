//******************************************************************************
//  MSP430G2x33/G2x53 Demo - ADC10, DTC Sample A1 32x, AVcc, Repeat Single, DCO
//
//  Description: Use DTC to sample A1 32 times with reference to AVcc. Software
//  writes to ADC10SC to trigger sample burst. In Mainloop MSP430 waits in LPM0
//  to save power until ADC10 conversion burst complete, ADC10_ISR(DTC) will
//  force exit from any LPMx in Mainloop on reti. ADC10 internal oscillator
//  times sample period (16x) and conversion (13x). DTC transfers conversion
//  code to RAM 200h - 240h. P1.0 set at start of conversion burst, reset on
//  completion.
//
//                MSP430G2x33/G2x53
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//        >---|P1.1/A1      P1.0|-->LED
//
//  D. Dang
//  Texas Instruments Inc.
//  December 2010
//   Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************
#include  "msp430g2553.h"
void InitSys();
unsigned char hi,mi,lo;
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
   InitSys(); //³õÊ¼»¯ 
  ADC10CTL1 = CONSEQ_2 + INCH_1;            // Repeat single channel, A1
  ADC10CTL0 = ADC10SHT_2 + MSC + ADC10ON + ADC10IE+REF2_5V ; // ADC10ON, interrupt enabl
  ADC10DTC1 = 0x20;                         // 32 conversions
  ADC10AE0 |= 0x02;                         // P1.1 ADC option select

  for (;;)
  {
    ADC10CTL0 &= ~ENC;
    while (ADC10CTL1 & BUSY);               // Wait if ADC10 core is active
    ADC10SA = 0x200;                        // Data buffer start
    P1OUT |= 0x01;                          // Set P1.0 LED on
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    __bis_SR_register(CPUOFF + GIE);        // LPM0, ADC10_ISR will force exit
    lo=ADC10MEM&0x0f;
    mi=(ADC10MEM>>4)&0x0f;
    hi=(ADC10MEM>>8)&0x03;                     
  }
}

// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}

void InitSys() 
{ 
  if (CALBC1_16MHZ ==0xFF || CALDCO_16MHZ == 0xFF)                                     
  {  
    while(1);                               // If calibration constants erased
                                            // do not load, trap CPU!!
  } 
 //1Mhz
  BCSCTL1 = CALBC1_16MHZ;                    // Set range
  DCOCTL = CALDCO_16MHZ;                     // Set DCO step + modulation */
} 