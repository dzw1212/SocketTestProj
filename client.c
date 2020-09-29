#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#define ERROR_SUCCESS 0
#define ERROR_FAILED  -1
#define BUFFSIZE      100

/* a simple tcp client, send 'hello,server' to server */

int main()
{
    int iSendSock = 0;
    int iRet = ERROR_SUCCESS;
    char acBuff[BUFFSIZE] = "hello, server";
    struct sockaddr_in stSendAddr;
	
    (void)memset(&stSendAddr, 0, sizeof(stSendAddr));
    /* create a socket to send msg */
    iSendSock = socket(AF_INET, SOCK_STREAM, 0);
    if (iSendSock < 0)
    {
        printf("create iSendSock failed! errorCode is %d.\n", iSendSock);
        return ERROR_FAILED;
    }
    /* indicate dest IP Address and Port */
    stSendAddr.sin_family = AF_INET;
    stSendAddr.sin_port = htons(55555);
    (void)inet_pton(AF_INET, "192.168.184.128", &stSendAddr.sin_addr);
    /* try to connect with server */
    iRet = connect(iSendSock, (struct sockaddr *)&stSendAddr, sizeof(stSendAddr));
    if (ERROR_SUCCESS != iRet)
    {
    	printf("connect to server failed! errorCode is %d.\n", iRet);
    	return ERROR_FAILED;
    }
    /* send message */
    iRet = send(iSendSock, acBuff, sizeof(acBuff), 0);
    if (iRet < 0)
    {
        printf("send msg to server failed! errorCode is %d.\n", iRet);
        return ERROR_FAILED;
    }

    (void)close(iSendSock);
	return 0;
}
