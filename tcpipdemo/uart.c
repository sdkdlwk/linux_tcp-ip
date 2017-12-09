#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <termios.h>  
#include <errno.h>  
#include <ctype.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <time.h>  
#include <unistd.h>  
#include"pthread.h"  
#include "uart.h"  
  
  
struct serial_config serialread;  
struct serial_config serialread1;
struct serial_config serialread2;
  
static int serial_fd;  
static int serial_fd1; 
static int serial_fd2; 

int speed_arr[] = {B230400, B115200, B57600, B38400, B19200, B9600, B4800, B2400, B1200, B300,  
		   B38400, B19200, B9600, B4800, B2400, B1200, B300};  
  
int name_arr[] = {230400, 115200, 57600, 38400, 19200, 9600, 4800, 2400, 1200, 300,  
		  38400, 19200, 9600, 4800, 2400, 1200, 300};  
  
 
//-----------------------------------------------  
//读取serial.cfg文件并进行配置  
//-----------------------------------------------  
void readserialcfg()  
{  
	FILE *serial_fp;  
	char j[10];  
	  
	printf("readserailcfg\n");  
  
	serial_fp = fopen("./serial.cfg","r");  
	if(NULL == serial_fp)  
	{  
		printf("can't open serial.cfg");  
	}  
	else  
	{  
		fscanf(serial_fp, "DEV=%s\n", serialread.serial_dev);  
  
		fscanf(serial_fp, "SPEED=%s\n", j);  
		serialread.serial_speed = atoi(j);  
  
		fscanf(serial_fp, "DATABITS=%s\n", j);  
		serialread.databits = atoi(j);  
  
		fscanf(serial_fp, "STOPBITS=%s\n", j);  
		serialread.stopbits = atoi(j);  
  
		fscanf(serial_fp, "PARITY=%s\n", j);  
		serialread.parity = j[0];  
	}  
  
	fclose(serial_fp);  
}  
void readserialcfg1()  
{  
	FILE *serial_fp1;  
	char j[10];  
	  
	printf("readserailcfg\n");  
  
	serial_fp1 = fopen("./serial1.cfg","r");  
	if(NULL == serial_fp1)  
	{  
		printf("can't open serial.cfg");  
	}  
	else  
	{  
		fscanf(serial_fp1, "DEV=%s\n", serialread1.serial_dev);  
  
		fscanf(serial_fp1, "SPEED=%s\n", j);  
		serialread1.serial_speed = atoi(j);  
  
		fscanf(serial_fp1, "DATABITS=%s\n", j);  
		serialread1.databits = atoi(j);  
  
		fscanf(serial_fp1, "STOPBITS=%s\n", j);  
		serialread1.stopbits = atoi(j);  
  
		fscanf(serial_fp1, "PARITY=%s\n", j);  
		serialread1.parity = j[0];  
	}  
  
	fclose(serial_fp1);  
} 
void readserialcfg2()  
{  
	FILE *serial_fp2;  
	char j[10];  
	  
	printf("readserailcfg\n");  
  
	serial_fp2 = fopen("./serial2.cfg","r");  
	if(NULL == serial_fp2)  
	{  
		printf("can't open serial.cfg");  
	}  
	else  
	{  
		fscanf(serial_fp2, "DEV=%s\n", serialread2.serial_dev);  
  
		fscanf(serial_fp2, "SPEED=%s\n", j);  
		serialread2.serial_speed = atoi(j);  
  
		fscanf(serial_fp2, "DATABITS=%s\n", j);  
		serialread2.databits = atoi(j);  
  
		fscanf(serial_fp2, "STOPBITS=%s\n", j);  
		serialread2.stopbits = atoi(j);  
  
		fscanf(serial_fp2, "PARITY=%s\n", j);  
		serialread2.parity = j[0];  
	}  
  
	fclose(serial_fp2);  
}   
//-----------------------------------------------  
//设置波特率  
//-----------------------------------------------  
void set_speed(int fd)  
{  
	int i;  
	int status;  
	struct termios Opt;  
	struct termios oldOpt;  
	tcgetattr(fd, &oldOpt);  
//  printf("serialread.speed is %d\n",serialread.serial_speed);  
	for( i = 0; i < sizeof(speed_arr)/sizeof(int); i++)  
	{  
		if(serialread.serial_speed == name_arr[i])  
		{  
			tcflush(fd, TCIOFLUSH);  
			cfsetispeed(&Opt, speed_arr[i]);  
			cfsetospeed(&Opt, speed_arr[i]);  
			status = tcsetattr(fd, TCSANOW, &Opt);  
			if(status != 0)  
			{  
				perror("tcsetattr fd");  
				return;  
			}  
			tcflush(fd, TCIOFLUSH);  
		}  
	}  
}  
void set_speed1(int fd)  
{  
	int i;  
	int status;  
	struct termios Opt;  
	struct termios oldOpt;  
	tcgetattr(fd, &oldOpt);  
//  printf("serialread1.speed is %d\n",serialread1.serial_speed);  
	for( i = 0; i < sizeof(speed_arr)/sizeof(int); i++)  
	{  
		if(serialread1.serial_speed == name_arr[i])  
		{  
			tcflush(fd, TCIOFLUSH);  
			cfsetispeed(&Opt, speed_arr[i]);  
			cfsetospeed(&Opt, speed_arr[i]);  
			status = tcsetattr(fd, TCSANOW, &Opt);  
			if(status != 0)  
			{  
				perror("tcsetattr fd1");  
				return;  
			}  
			tcflush(fd, TCIOFLUSH);  
		}  
	}  
} 
void set_speed2(int fd)  
{  
	int i;  
	int status;  
	struct termios Opt;  
	struct termios oldOpt;  
	tcgetattr(fd, &oldOpt);  
  printf("serialread2.speed is %d\n",serialread2.serial_speed);  
	for( i = 0; i < sizeof(speed_arr)/sizeof(int); i++)  
	{  
		if(serialread2.serial_speed == name_arr[i])  
		{  
			tcflush(fd, TCIOFLUSH);  
			cfsetispeed(&Opt, speed_arr[i]);  
			cfsetospeed(&Opt, speed_arr[i]);  
			status = tcsetattr(fd, TCSANOW, &Opt);  
			if(status != 0)  
			{  
				perror("tcsetattr fd2");  
				return;  
			}  
			tcflush(fd, TCIOFLUSH);  
		}  
	}  
}   
  
//-----------------------------------------------  
//设置其他参数  
//-----------------------------------------------  
int set_Parity(int fd)  
{  
	struct termios options;  
	struct termios oldoptions;  
	if(tcgetattr(fd, &oldoptions) != 0)  
	{  
		perror("SetupSerial");  
		return(FALSE);  
	}  
  
	options.c_cflag |= (CLOCAL|CREAD);  
	options.c_cflag &=~CSIZE;  
//  printf("serialread.databits is %d\n",serialread.databits);  
	switch(serialread.databits)  
	{  
		case 7:  
			options.c_cflag |= CS7;  
			break;  
		case 8:  
			options.c_cflag |= CS8;  
			break;  
		default:  
			options.c_cflag |= CS8;  
			fprintf(stderr, "Unsupported data size\n");  
			return(FALSE);  
	}  
//  printf("serialread.parity is %c\n",serialread.parity);  
	switch(serialread.parity)  
	{  
		case 'n':  
		case 'N':  
			options.c_cflag &= ~PARENB;  
			options.c_iflag &= ~INPCK;  
			break;  
		case 'o':  
		case 'O':  
			options.c_cflag |= (PARODD | PARENB);  
			options.c_iflag |= INPCK;  
			break;  
		case 'e':  
		case 'E':  
			options.c_cflag |= PARENB;  
			options.c_cflag &= ~PARODD;  
			options.c_iflag |= INPCK;  
			break;  
		default:  
			options.c_cflag &= ~PARENB;  
			options.c_iflag &= ~INPCK;  
			fprintf(stderr, "Unsupported parity\n");  
			return(FALSE);  
	}  
//  printf("serialread.stopbits is %d\n",serialread.stopbits);  
	switch(serialread.stopbits)  
	{  
		case 1:  
			options.c_cflag &= ~CSTOPB;  
			break;  
		case 2:  
			options.c_cflag |= CSTOPB;  
			break;  
		default:  
			options.c_cflag &= ~CSTOPB;  
			fprintf(stderr, "Unsupported stop bits\n");  
			return(FALSE);  
	}  
	if(serialread.parity != 'n')  
		options.c_iflag |= INPCK;  
	options.c_cc[VTIME] = 0;    //150;          //15 seconds  
	options.c_cc[VMIN] = 0;  
#if 1  
	options.c_iflag |= IGNPAR|ICRNL;  
	options.c_oflag |= OPOST;   
	options.c_iflag &= ~(IXON|IXOFF|IXANY);                       
#endif  
	tcflush(fd, TCIFLUSH);  
	if(tcsetattr(fd, TCSANOW, &options) != 0)  
	{  
		perror("SetupSerial+");  
		return(FALSE);  
	}  
	return(TRUE);  
}  
int set_Parity1(int fd)  
{  
	struct termios options;  
	struct termios oldoptions;  
	if(tcgetattr(fd, &oldoptions) != 0)  
	{  
		perror("SetupSerial 1");  
		return(FALSE);  
	}  
  
	options.c_cflag |= (CLOCAL|CREAD);  
	options.c_cflag &=~CSIZE;  
//  printf("serialread1.databits is %d\n",serialread1.databits);  
	switch(serialread1.databits)  
	{  
		case 7:  
			options.c_cflag |= CS7;  
			break;  
		case 8:  
			options.c_cflag |= CS8;  
			break;  
		default:  
			options.c_cflag |= CS8;  
			fprintf(stderr, "Unsupported data size\n");  
			return(FALSE);  
	}  
//  printf("serialread1.parity is %c\n",serialread1.parity);  
	switch(serialread1.parity)  
	{  
		case 'n':  
		case 'N':  
			options.c_cflag &= ~PARENB;  
			options.c_iflag &= ~INPCK;  
			break;  
		case 'o':  
		case 'O':  
			options.c_cflag |= (PARODD | PARENB);  
			options.c_iflag |= INPCK;  
			break;  
		case 'e':  
		case 'E':  
			options.c_cflag |= PARENB;  
			options.c_cflag &= ~PARODD;  
			options.c_iflag |= INPCK;  
			break;  
		default:  
			options.c_cflag &= ~PARENB;  
			options.c_iflag &= ~INPCK;  
			fprintf(stderr, "Unsupported parity\n");  
			return(FALSE);  
	}  
//  printf("serialread1.stopbits is %d\n",serialread1.stopbits);  
	switch(serialread1.stopbits)  
	{  
		case 1:  
			options.c_cflag &= ~CSTOPB;  
			break;  
		case 2:  
			options.c_cflag |= CSTOPB;  
			break;  
		default:  
			options.c_cflag &= ~CSTOPB;  
			fprintf(stderr, "Unsupported stop bits\n");  
			return(FALSE);  
	}  
	if(serialread1.parity != 'n')  
		options.c_iflag |= INPCK;  
	options.c_cc[VTIME] = 0;    //150;          //15 seconds  
	options.c_cc[VMIN] = 0;  
#if 1  
	options.c_iflag |= IGNPAR|ICRNL;  
	options.c_oflag |= OPOST;   
	options.c_iflag &= ~(IXON|IXOFF|IXANY);                       
#endif  
	tcflush(fd, TCIFLUSH);  
	if(tcsetattr(fd, TCSANOW, &options) != 0)  
	{  
		perror("SetupSerial 1+");  
		return(FALSE);  
	}  
	return(TRUE);  
}  
int set_Parity2(int fd)  
{  
	struct termios options;  
	struct termios oldoptions;  
	if(tcgetattr(fd, &oldoptions) != 0)  
	{  
		perror("SetupSerial 2");  
		return(FALSE);  
	}  
  
	options.c_cflag |= (CLOCAL|CREAD);  
	options.c_cflag &=~CSIZE;  
//  printf("serialread2.databits is %d\n",serialread2.databits);  
	switch(serialread2.databits)  
	{  
		case 7:  
			options.c_cflag |= CS7;  
			break;  
		case 8:  
			options.c_cflag |= CS8;  
			break;  
		default:  
			options.c_cflag |= CS8;  
			fprintf(stderr, "Unsupported data size\n");  
			return(FALSE);  
	}  
//  printf("serialread2.parity is %c\n",serialread2.parity);  
	switch(serialread2.parity)  
	{  
		case 'n':  
		case 'N':  
			options.c_cflag &= ~PARENB;  
			options.c_iflag &= ~INPCK;  
			break;  
		case 'o':  
		case 'O':  
			options.c_cflag |= (PARODD | PARENB);  
			options.c_iflag |= INPCK;  
			break;  
		case 'e':  
		case 'E':  
			options.c_cflag |= PARENB;  
			options.c_cflag &= ~PARODD;  
			options.c_iflag |= INPCK;  
			break;  
		default:  
			options.c_cflag &= ~PARENB;  
			options.c_iflag &= ~INPCK;  
			fprintf(stderr, "Unsupported parity\n");  
			return(FALSE);  
	}  
//  printf("serialread2.stopbits is %d\n",serialread2.stopbits);  
	switch(serialread2.stopbits)  
	{  
		case 1:  
			options.c_cflag &= ~CSTOPB;  
			break;  
		case 2:  
			options.c_cflag |= CSTOPB;  
			break;  
		default:  
			options.c_cflag &= ~CSTOPB;  
			fprintf(stderr, "Unsupported stop bits\n");  
			return(FALSE);  
	}  
	if(serialread2.parity != 'n')  
		options.c_iflag |= INPCK;  
	options.c_cc[VTIME] = 0;    //150;          //15 seconds  
	options.c_cc[VMIN] = 0;  
#if 1  
	options.c_iflag |= IGNPAR|ICRNL;  
	options.c_oflag |= OPOST;   
	options.c_iflag &= ~(IXON|IXOFF|IXANY);                       
#endif  
	tcflush(fd, TCIFLUSH);  
	if(tcsetattr(fd, TCSANOW, &options) != 0)  
	{  
		perror("SetupSerial 2+");  
		return(FALSE);  
	}  
	return(TRUE);  
}  

//-----------------------------------------------  
//打开串口设备  
//-----------------------------------------------  
int OpenDev(char *Dev)  
{  
	int fd = open(Dev, O_RDWR, 0);  
	if(-1 == fd)  
	{  
		perror("Can't Open Serial Port");  
		return -1;  
	}  
	else  
		return fd;  
}  
  
//--------------------------------------------------  
//串口初始化  
//--------------------------------------------------  
void serial_init()  
{  
	char *Dev;  
  
	readserialcfg();  

	printf("init serial\n");  
  
	Dev = serialread.serial_dev;  
	//打开串口设备  
	serial_fd = OpenDev(Dev);  
  
	if(serial_fd > 0)  
		set_speed(serial_fd);       //设置波特率  
	else  
	{  
		printf("Can't Open Serial Port!\n");  
		exit(0);  
	}  
	//恢复串口未阻塞状态  
	if (fcntl(serial_fd, F_SETFL, O_NONBLOCK) < 0)  
	{  
		printf("fcntl failed!\n");  
		exit(0);  
	}  

	//设置串口参数  
	if(set_Parity(serial_fd) == FALSE)  
	{  
		printf("Set parity Error\n");  
		exit(1);  
	}  
  
}  
void serial_init1()  
{  
	char *Dev1;  
  
	readserialcfg1();  

	printf("init serial1\n");  
  
	Dev1 = serialread1.serial_dev;  
	//打开串口设备  
	serial_fd1 = OpenDev(Dev1);  
  
	if(serial_fd1 > 0)  
		set_speed1(serial_fd1);       //设置波特率  
	else  
	{  
		printf("Can't Open Serial1 Port!\n");  
		exit(0);  
	}  
	//恢复串口未阻塞状态  
	if (fcntl(serial_fd1, F_SETFL, O_NONBLOCK) < 0)  
	{  
		printf("fcntl failed!\n");  
		exit(0);  
	}  

	//设置串口参数  
	if(set_Parity1(serial_fd1) == FALSE)  
	{  
		printf("Set parity Error\n");  
		exit(1);  
	}  
  
}  
void serial_init2()  
{  
	char *Dev2;  
  
	readserialcfg2();  

	printf("init serial2\n");  
  
	Dev2 = serialread2.serial_dev;  
	//打开串口设备  
	serial_fd2 = OpenDev(Dev2);  
  
	if(serial_fd2 > 0)  
		set_speed2(serial_fd2);       //设置波特率  
	else  
	{  
		printf("Can't Open Serial2 Port!\n");  
		exit(0);  
	}  
	//恢复串口未阻塞状态  
	if (fcntl(serial_fd2, F_SETFL, O_NONBLOCK) < 0)  
	{  
		printf("fcntl failed!\n");  
		exit(0);  
	}  

	//设置串口参数  
	if(set_Parity2(serial_fd2) == FALSE)  
	{  
		printf("Set parity Error\n");  
		exit(1);  
	}  
  
}    
int serial_write(char* cmd, int count)  
{  
	printf("serial write for %d bytes\n",count);  
	return write(serial_fd,cmd,count);  
}  
int serial_write1(char* cmd, int count)  
{  
	printf("serial write for %d bytes\n",count);  
	return write(serial_fd1,cmd,count);  
}
int serial_write2(char* cmd, int count)  
{  
	printf("serial write for %d bytes\n",count);  
	return write(serial_fd2,cmd,count);  
}
int serial_read(char* cmd, int count)  
{  
	//printf("serial read for %d bytes\n",count); 
	return read(serial_fd,cmd,count);  
}
int serial_read1(char* cmd, int count)  
{  
	//printf("serial read for %d bytes\n",count); 
	return read(serial_fd1,cmd,count);  
}
int serial_read2(char* cmd, int count)  
{  
	//printf("serial read for %d bytes\n",count); 
	return read(serial_fd2,cmd,count);  
}
void serial_close()  
{  
	printf("close serial\n");  
	close(serial_fd);  
}  
void serial_close1()  
{  
	printf("close serial\n");  
	close(serial_fd1);  
} 
void serial_close2()  
{  
	printf("close serial\n");  
	close(serial_fd2);  
} 