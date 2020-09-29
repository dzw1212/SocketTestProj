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
#define TRUE          1
#define IPADDRSIZE    20

/* a simple tcp server, print what client send */

int main()
{
	char acBuff[BUFFSIZE];
	char acIPAddr[IPADDRSIZE];
	int iSelfSock = 0;
	int iRecvSock = 0;
	int iMaxConnNum = 2;
	int iRet = ERROR_SUCCESS;
	int iOpt = SO_REUSEADDR;
	struct sockaddr_in stSelfAddr;
	struct sockaddr_in stRecvAddr;
	int iRecvAddrLen = sizeof(stRecvAddr);

	(void)memset(acBuff, 0, sizeof(acBuff));
	(void)memset(acIPAddr, 0, sizeof(acIPAddr));
	(void)memset(&stSelfAddr, 0, sizeof(stSelfAddr));
	(void)memset(&stRecvAddr, 0, sizeof(stRecvAddr));

	/* creater a socket used to listen from client */
	iSelfSock = socket(AF_INET, SOCK_STREAM, 0);
	if (iSelfSock < 0)
	{
		printf("Create iSelfSock failed! errorCode is %d.\n", iSelfSock);
		return ERROR_FAILED;
	}
	/* Set Option for socket */
	iRet = setsockopt(iSelfSock, SOL_SOCKET, SO_REUSEADDR, &iOpt, sizeof(iOpt));
	if (ERROR_SUCCESS != iRet)
	{
		printf("Set Socket option failed! errorCode is %d.\n", iRet);
		return ERROR_FAILED;
	}
	/* bind IP addr for socket */
	stSelfAddr.sin_family = AF_INET;
	stSelfAddr.sin_port = htons(55555);
	stSelfAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	iRet = bind(iSelfSock, (struct sockaddr *)&stSelfAddr, sizeof(stSelfAddr));
	if (ERROR_SUCCESS != iRet)
	{
		printf("bind addr failed! errorCode is %d.\n", iRet);
		return ERROR_FAILED;
	}

	/* start listen from client */
	iRet = listen(iSelfSock, iMaxConnNum);
	if (ERROR_SUCCESS != iRet)
	{
		printf("server listen failed! errorCode is %d.\n", iRet);
		return ERROR_FAILED;
	}

	/* accept connection from client and deal */
	printf("wait for socket from any client...\n");
	while(TRUE)
	{
		(void)memset(acBuff, 0, sizeof(acBuff));
		iRecvSock = accept(iSelfSock, (struct sockaddr *)&stRecvAddr, &iRecvAddrLen);
		iRet = recv(iRecvSock, acBuff, sizeof(acBuff), 0);
		if (iRet < 0)
		{
			printf("recv from client failed! errorCode is %d.\n", iRet);
			return ERROR_FAILED;
		}
		(void)inet_ntop(AF_INET, &stRecvAddr.sin_addr, acIPAddr, sizeof(acIPAddr));
		printf("Get one message from client:\n");
		printf("port    : %d\n", stRecvAddr.sin_port);
		printf("IP Addr : %s\n", acIPAddr);
		printf("message : %s\n", acBuff);
		(void)close(iRecvSock);
	}
	return ERROR_SUCCESS;
}
