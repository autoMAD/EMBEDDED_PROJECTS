#include <LPC214X.H>

#define sw 0x00000001
#define r1 0x00000002



int main()
{
	IODIR0=r1;

	while(1)
	{
		if(((IOPIN0)&(sw))==0)
		{
			IOCLR0=r1;
		}

		else
		{
			IOSET0=r1;
		}
	}
}
