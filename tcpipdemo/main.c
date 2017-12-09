/************************************************************************* 
	> File Name: server.c 
	> Author: fucang_zxx 
	> Mail: fucang_zxx@163.com  
	> Created Time: Sun 24 Jul 2016 03:45:21 PM CST 
 ************************************************************************/  
  
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h> 
#include <unistd.h> 
#include "uart.h"
#include <wiringPi.h>
int pin = 7;
void gpio_init()
{
	wiringPiSetup() ;
	//pinMode(12, OUTPUT) ; //test for gpio
	pinMode (pin, PWM_OUTPUT); ////test for gpio_pwm
}

int main()  
{  
	//for init other
	char buff[255];
	int nread=0;
	int i = 0;
	//int bright=0;	
	
	//gpio_init();
	serial_init1();
	serial_init2();

	while(1)  
	{  
		//memset(buf, '\0', sizeof(buf));  
		//ssize_t size = read(accept_fd, buf, sizeof(buf) - 1); 
		

		//test for gpio
 		digitalWrite(pin, HIGH);
		delay (500) ;
		digitalWrite(pin,  LOW);
		delay (500) ;
		
		
/*     for (bright = 0 ; bright < 1024 ; ++bright)
    {
      pwmWrite (pin, bright) ;
      delay (1) ;
    }

    for (bright = 1023 ; bright >= 0 ; --bright)
    {
      pwmWrite (pin, bright) ;
      delay (1) ;
    } */
	
		//char buff2[] = "hello!\n"; 

		//if(buf [2] == 0x01)
		//{
		  //printf("data is: 0x%02x ,0x%02x ,0x%02x ,0x%02x  ######\n", buf[0],buf[1],buf[2],buf[3]);  
		  //serial_write(buf,4);
		//}
		  
		if((nread = serial_read1(buff,255))>0) 
		{  
			serial_write2(buff,nread); 
			printf("i1 = %d \n",i++);
		} 
		
		if((nread = serial_read2(buff,255))>0) 
		{  
			serial_write1(buff,nread);
			printf("i2 = %d \n",i++);
		}
		usleep(10);
	}
	
	
	serial_close1();
	serial_close2();
	return 0;  
}  