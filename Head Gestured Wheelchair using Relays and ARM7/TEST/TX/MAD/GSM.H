void gsm_init(void); // Initializes GSM Modem
void gsm_sendmsg_mob(unsigned char mob[],unsigned char msg[]);

unsigned char xx,newmsg=0;
unsigned char temp[70],temp1=0;

unsigned char mobi[15];
unsigned char msge[20];
unsigned char mobilenum[11];
unsigned char msg[20];

void serial(void)  __irq
{
   
		xx=uart1_rx();
		if(xx=='+')
			newmsg=1;
		temp[temp1]=xx;
		temp1++;
 
		VICVectAddr= 0x00000000;
}

void uart1_interrupt(void)
{
 
 VICVectCntl0 =  0x20|7;
 VICVectAddr0 = (unsigned) serial;
 VICIntEnable =  0x00000080;
 U1IER        =  0x01;
}

void gsm_init(void)
{
	lcd_init();
	uart1_init();
	delay(1000);
	
	lcd_string("GSM Initalizing");
	delay(1000);

	uart1_string("ate0");
	uart1_enter();
	delay(1000);


	checkgsm:

		uart1_string("at");
		uart1_enter();
		delay(1000);
		if(((U1LSR)&(0x01))==0)
		goto checkgsm;

	lcd_cmd(1);
	lcd_string("GSM Connected");
	delay(1000);

	uart1_string("at+cmgf=1");
	uart1_enter();
	delay(3000);

	lcd_cmd(1);
	lcd_string("Text Format");
	delay(1000);

	uart1_string("at+cmgd=1");
	uart1_enter();
	delay(3000);
	uart1_string("at+cmgd=2");
	uart1_enter();
	delay(3000);
	uart1_string("at+cmgd=3");
	uart1_enter();
	delay(1000);
	
	lcd_cmd(1);
	lcd_string("SMS Deleted");
	delay(1000);
}

void gsm_sendmsg_mob(unsigned char mob[],unsigned char msg[])
{
	newmsg=0;
	lcd_cmd(1);
	lcd_string("Sending SMS..");
	delay(1000);

	uart1_string("at+cmgs=");
	uart1_data('"');
	uart1_string(mob);
	uart1_data('"');
	uart1_enter();
	uart1_string(msg);
	uart1_data(0x1a);
	while(newmsg==0);
	lcd_cmd(1);
	lcd_string("SMS Sent..");
	delay(5000);
	temp1=0;
	newmsg=0;
}

void gsm_readmsg()
{
	unsigned char m=0,l=0,k=0,n=0,o=0,p,q=0,r,s=0;
	

	for(m=0;temp[m]!='\0';m++)
	{
		if(temp[m]=='"')
		{
			l++;
		}

		if(l==1)
		{
			mobi[k]=temp[m];
			k++;
		}

		if(temp[m]==13)
		{
			n++;
		}

		if(n==1)
		{
			msge[o]=temp[m];
			o++;
		}
	}

	mobi[k]='\0';
	msge[o]='\0';

	for(p=4;mobi[p]!='\0';p++)
	{
		   mobilenum[q]=mobi[p];
		   q++;
	}

	mobilenum[q]='\0';

	for(r=2;msge[r]!='\0';r++)
	{
		msg[s]=msge[r];
		s++;
	}

	msg[s]='\0';
	delay(3000);
	lcd_cmd(1);
	lcd_string(mobilenum);
	lcd_cmd(0xc0);
	lcd_string(msg);
	temp1=0;
	delay(4000);
}
