#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")

//Сокет - программный интерфейс для обмена данными между процессами
//сокеты делятся на клиентские и серверные 
int main(void)
{
	WORD sockVer;
	WSADATA wsaData;
	int retVal;
	sockVer = MAKEWORD(2, 2);
	WSAStartup(sockVer, &wsaData);
	//Создаем сокет
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	/*socket(
		_In_ int af,		address family (раньше был protocol family - отсюда и PF_INET) PF_INET или AF_INET - интернет протокол версии 4 (IPv4)
		_In_ int type,		тип сокета SOCK_STREAM организует двухнаправленное соединение, использует Transmission Control Protocol (TCP) для IPv4
		_In_ int protocol		используемый протокол (используется TCP (IPPROTO_TCP) для параметров SOCK_STREAM и PF_INET (IPv4)
	);*/
	if (servSock == INVALID_SOCKET)		//проверка валидности сокета
	{
		printf("Unable to create socket\n");
		getchar();
		WSACleanup();
		return SOCKET_ERROR;
	}
	SOCKADDR_IN sin;
	sin.sin_family = PF_INET;		// address family (всегда PF/AF_INET)
	sin.sin_port = htons(1111);		//номер порта протокола
	sin.sin_addr.s_addr = INADDR_ANY;	//структура, которая содержит IPv4 адрес
	retVal = bind(servSock, (LPSOCKADDR)&sin, sizeof(sin));
	/*int bind(
		SOCKET         s,		дескриптор сокета
		const sockaddr * addr,		указатель на SOCKADDR структуру
		int            namelen		длина параметра
	);*/
	if (retVal == SOCKET_ERROR)
	{
		printf("Unable to bind\n");
		WSACleanup();
		return SOCKET_ERROR;
	}
	//Пытаемся начать слушать сокет
	retVal = listen(servSock, 10);
	/*int WSAAPI listen(
		SOCKET s,		дескриптор сокета
		int    backlog		максимальная очередь на подключение
	);*/
	if (retVal == SOCKET_ERROR)
	{
		printf("Unable to listen\n");
		WSACleanup();
		return SOCKET_ERROR;
	}
	//Ждем клиента
	SOCKET clientSock;
	clientSock = accept(servSock, NULL, NULL); //позволяет подключиться к сокету
	/*SOCKET WSAAPI accept(
		SOCKET   s,		дескриптор сокета
		sockaddr * addr,	указатель на буфер, содержащий адрес сущности, которая будет подключена
		int* addrlen		длина адреса
	);*/
	if (clientSock == INVALID_SOCKET)
	{
		printf("Unable to accept\n");
		WSACleanup();
		return SOCKET_ERROR;
	}
	for (;;)
	{
		TCHAR szReq[256]=TEXT(""); //массив, в который будет записана передаваемая строка
		retVal = recv(clientSock, (char*)szReq, sizeof(szReq), 0); //получение данных от клиента
		/*recv(
			_In_ SOCKET s,		дескриптор сокета клиента
			_Out_writes_bytes_to_(len, return) __out_data_source(NETWORK) char FAR* buf,		указатель на начало массива
			_In_ int len,	размер массива
			_In_ int flags	флаги, изменяющие поведение функции (прим. MSG_PEEK записывает данные в функцию, но не удаляет их из очереди)
		);*/
		if (retVal == SOCKET_ERROR)
		{
			printf("Unable to recieve\n");
			return SOCKET_ERROR;
		}
		printf("Got the request from client: \n%ls\n", szReq);
		TCHAR szResp[256] = TEXT("Message recieved");
		printf("Sending response from server\n");
		std::cout << std::endl;
		retVal = send(clientSock, (char*)szResp, sizeof(szResp), 0);
		/*recv(
			_In_ SOCKET s,		дескриптор сокета клиента
			_Out_writes_bytes_to_(len, return) __out_data_source(NETWORK) char FAR* buf,	массив, данные из которого будут переданы
			_In_ int len,	длина массива
			_In_ int flags		флаги, изменяющие поведение функции
		);*/
		if (retVal == SOCKET_ERROR)
		{
			printf("Unable to send\n");
			return SOCKET_ERROR;
		}
	}
	//Закрываем сокет
	closesocket(clientSock); //закрытие сокета с помощью его дескриптора
	closesocket(servSock);
	WSACleanup();
	return 0;
}