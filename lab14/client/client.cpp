#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <winsock2.h>
#include <tchar.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

int main()
{
	WORD ver = MAKEWORD(2, 2);
	WSADATA wsaData;
	int retVal = 0;
	WSAStartup(ver, (LPWSADATA)&wsaData);
	LPHOSTENT hostEnt;
	hostEnt = gethostbyname("localhost"); //localhost - имя хоста, которое относится к данному компьютеру имеет адрес 127.0.0.1 в IPv4 и ::1 в IPv6
	
	if (!hostEnt)
	{
		printf("Unable to collect gethostbyname\n");
		WSACleanup();
		return 1;
	}
	//Создаем сокет
	SOCKET clientSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); //описал в сервере
	if (clientSock == SOCKET_ERROR)
	{
		printf("Unable to create socket\n");
		WSACleanup();
		return 1;
	}
	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = PF_INET;
	serverInfo.sin_addr = *((LPIN_ADDR)*hostEnt->h_addr_list);			//описал в сервере
	serverInfo.sin_port = htons(1111);
	retVal = connect(clientSock, (LPSOCKADDR)&serverInfo, sizeof(serverInfo));		//описал в сервере
	if (retVal == SOCKET_ERROR)
	{
		printf("Unable to connect\n");
		WSACleanup();
		return 1;
	}
	printf("Connection made sucessfully\n");
	for (;;)
	{
		TCHAR pBuf[256]=TEXT("");
		cout << "Enter a string to send: " << endl;
		_tscanf_s(L"%ls", pBuf, 256);
		//cout << strlen(pBuf) << endl;
		retVal = send(clientSock, (char*)pBuf, sizeof(pBuf), 0);		//описал в сервере
		if (retVal == SOCKET_ERROR)
		{
			printf("Unable to send\n");
			getchar();
			WSACleanup();
			return 1;
		}
		TCHAR szResponse[256];
		retVal = recv(clientSock, (char*)szResponse, sizeof(szResponse), 0);		//описал в сервере
		if (retVal == SOCKET_ERROR)
		{
			printf("Unable to recieve\n");
			WSACleanup();
			return 1;
		}
		cout << endl;
		printf("Got the response from server\n%ls\n", szResponse);
		getchar();
	}
	closesocket(clientSock);		//описал в сервере
	WSACleanup();
	return 0;
}