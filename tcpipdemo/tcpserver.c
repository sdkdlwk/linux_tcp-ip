#include <sys/types.h>  
#include <sys/socket.h>  
#include <stdio.h>  
#include <unistd.h>  
#include <string.h>  
#include <arpa/inet.h>  
#include <signal.h>  
#include <sys/wait.h>  
#include "uart.h"

 
#define PORT 52666  
#define SIZE 1024  
const char* ip = "192.168.1.119";




int Creat_socket()         //创建套接字和初始化以及监听函数  
{  
    int listen_socket = socket(AF_INET, SOCK_STREAM, 0);      //创建一个负责监听的套接字    
    if(listen_socket == -1)  
    {  
        perror("socket");  
        return -1;  
    }  
    struct sockaddr_in addr;  
    memset(&addr, 0, sizeof(addr));  
      
    addr.sin_family = AF_INET;  /* Internet地址族 */  
    addr.sin_port = htons(PORT);  /* 端口号 */  
    //addr.sin_addr.s_addr = htonl(INADDR_ANY);   /* IP地址 */  
	
	//addr.sin_port = htons(port); 
	//inet_addr函数将用点分十进制字符串表示的IPv4地址转化为用网络   
	//字节序整数表示的IPv4地址   
	addr.sin_addr.s_addr = inet_addr(ip);   
	
	int bReuseaddr = 1;
	setsockopt(listen_socket,SOL_SOCKET,SO_REUSEADDR,(const char*)&bReuseaddr,sizeof(int));  

    int ret = bind(listen_socket, (struct sockaddr *)&addr, sizeof(addr));    //连接  
    if(ret == -1)  
    {  
        perror("bind");  
        return -1;  
    }  
      
    ret = listen(listen_socket, 5);   //监听  
    if(ret == -1)  
    {  
        perror("listen");  
        return -1;  
    }  
    return listen_socket;  
}  
  
int wait_client(int listen_socket)  
{  
    struct sockaddr_in cliaddr;  
    socklen_t addrlen = sizeof(cliaddr);  
    printf("等待客户端连接。。。。\n");  
    int client_socket = accept(listen_socket, (struct sockaddr *)&cliaddr, &addrlen);     //创建一个和客户端交流的套接字  
    if(client_socket == -1)  
    {  
        perror("accept");  
        return -1;  
    }  
      
    printf("成功接收到一个客户端：%s\n", inet_ntoa(cliaddr.sin_addr));  
      
    return client_socket;  
}  
  
void hanld_client(int listen_socket, int client_socket)    //信息处理函数,功能是将客户端传过来的小写字母转化为大写字母  
{  
    char buf[SIZE];  
    while(1)  
    {  
        int ret = read(client_socket, buf, SIZE-1);  
		
		
		if(buf [2] == 0x01)
		{
		  printf("data is: 0x%02x ,0x%02x ,0x%02x ,0x%02x  ######\n", buf[0],buf[1],buf[2],buf[3]);  
		  serial_write2(buf,4);
		}
		
		
		
        if(ret == -1)  
        {  
            perror("read");  
            break;  
        }  
        if(ret == 0)  
        {  
            break;  
        }  
/*         buf[ret] = '\0';  
        int i;  
        for(i = 0; i < ret; i++)  
        {  
            buf[i] = buf[i] + 'A' - 'a';  
        }  
          
        printf("%s\n", buf);  
        write(client_socket, buf, ret);  
          
        if(strncmp(buf, "end", 3) == 0)  
        {  
            break;  
        } */
    }
    close(client_socket);  
}  
  
void handler(int sig)  
{  
     
    while (waitpid(-1,  NULL,   WNOHANG) > 0)  
    {  

/*     int status;  
    status=kill(pid,SIGKILL);  
    if (status == -1)  
        printf("kill faild\n");  */
	
					
		printf ("成功处理一个子进程的退出\n");  
		
    }  
}  

int main()  
{  
	serial_init1();
	serial_init2();

    int listen_socket = Creat_socket();  

    signal(SIGCHLD,  handler);    //处理子进程，防止僵尸进程的产生  
    while(1)  
    {  
        int client_socket = wait_client(listen_socket);   //多进程服务器，可以创建子进程来处理，父进程负责监听。  
        int pid = fork();  
		//pid = fork();
		printf ("fork pid = %d \n", pid);  
        if(pid == -1)  
        {  
            perror("fork");  
            break;  
        }  
        if(pid > 0)  
        {  
            close(client_socket);  
            continue;  
        }  
        if(pid == 0)  
        {  
            close(listen_socket);  
            hanld_client(listen_socket, client_socket);  
            break;  
        }  
    }  
      
    close(listen_socket);  
      
    return 0;  
}  