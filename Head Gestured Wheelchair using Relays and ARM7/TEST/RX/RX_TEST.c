#include "MAD/ORL.H"
#include "MAD/DELAY.H"
#include "MAD/LCD.H"
#include "MAD/UART.H"

unsigned char ch;


#define r1 0x00000001
#define r2 0x00000002
#define r3 0x00000004
#define r4 0x00000008

int main()
{
 lcd_init();
 uart1_init();
 delay(400);

 IODIR0=0x0000000F;
 
 delay(400);

 IOSET0=r1;
 IOSET0=r2;
 IOSET0=r3;
 IOSET0=r4;
 

 delay(400);
 lcd_cmd(0x85);
 lcd_string("RX TEST");
 delay(1400);

 while(1)
 {
  ch=uart1_rx();
  lcd_cmd(1);
  lcd_data(ch);

  if(ch=='S')
  {
 	IOSET0=r1;
 	IOSET0=r2;
 	IOSET0=r3;
 	IOSET0=r4;
  	

	lcd_cmd(1);
	lcd_string("STOP");
  }

  else if(ch=='F')
  {

	IOSET0=r2;
	IOCLR0=r1;
	IOSET0=r4;
	IOCLR0=r3;
	lcd_cmd(1);
	lcd_string("FRONT");

  }

  else if(ch=='B')
  {
  	
	IOSET0=r1;
	IOCLR0=r2;
	IOSET0=r3;
	IOCLR0=r4;
	lcd_cmd(1);
	lcd_string("BACK");

  }

  else if(ch=='L')
  {
   	
	IOSET0=r1;
	IOSET0=r2;
	IOSET0=r4;
	IOCLR0=r3;
	lcd_cmd(1);
	lcd_string("LEFT");

  }

  else if(ch=='R')
  {
  	
	IOSET0=r2;
	IOCLR0=r1;
	IOSET0=r3;
	IOSET0=r4;

	lcd_cmd(1);
	lcd_string("RIGHT");
  }
  }
}

 