#include "MAD/ORL.H"
#include "MAD/DELAY.H"
#include "MAD/LCD.H"
#include "MAD/UART.H"
#include "MAD/MEMS.H"

unsigned char ch;

int main()
{
	lcd_init();
	uart1_init();
	mems_init();
	
	lcd_cmd(1);
	delay(1000);
	lcd_cmd(0x85);
	lcd_string("WELCOME");

	
	while(1)
	{
		delay(500);
		ch=mems_start();
		lcd_cmd(1);
		lcd_string("MEMS DATA");
		delay(500);


		if(ch==1)
		{
			delay(1000);
			uart1_data('S');
			lcd_cmd(1);
			lcd_cmd(0x80);
			lcd_data('S');
			lcd_cmd(0xc0);
			lcd_num(ch);
		}
		else if(ch==5)
		{
			delay(1000);
			uart1_data('F');
			lcd_cmd(1);
			lcd_cmd(0x80);
			lcd_data('F');
			lcd_cmd(0xc0);
			lcd_num(ch);
		}
		else if((ch==8)||(ch==9))
		{
			delay(1000);
			uart1_data('B');
			lcd_cmd(1);
			lcd_cmd(0x80);
			lcd_data('B');
			lcd_cmd(0xc0);
			lcd_num(ch);
		}

		else if((ch==21)||(ch==22))
		{
			delay(1000);
			uart1_data('L');
			lcd_cmd(1);
			lcd_cmd(0x80);
			lcd_data('L');
			lcd_cmd(0xc0);
			lcd_num(ch);
		}
		else if((ch==24)||(ch==25))
		{
			delay(1000);
			uart1_data('R');
			lcd_cmd(1);
			lcd_cmd(0x80);
			lcd_data('R');
			lcd_cmd(0xc0);
			lcd_num(ch);
		}
		mems_stop();
	}
}	
		


