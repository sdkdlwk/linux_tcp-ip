#define FALSE       0  
#define TRUE        1  
  
#define WORDLEN 32  
  
struct serial_config  
{  
	//unsigned char serial_dev[WORDLEN];  
	 char serial_dev[WORDLEN];  
	unsigned int serial_speed;  
	unsigned char databits;  
	unsigned char stopbits;  
	unsigned char parity;  
};  
  
void serial_init();  
void serial_init1();
void serial_init2();
int serial_write(char* cmd, int count);  
int serial_write1(char* cmd, int count);  
int serial_write2(char* cmd, int count);  
int serial_read(char* cmd, int count);
int serial_read1(char* cmd, int count);
int serial_read2(char* cmd, int count);
void serial_close();  
void serial_close1();
void serial_close2();