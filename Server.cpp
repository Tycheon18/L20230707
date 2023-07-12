#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <winsock2.h>
#include "MySQLcommend.h"

using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main()
{
	MySQLcommend SQL;

	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = PF_INET;
	ServerSockAddr.sin_addr.s_addr = INADDR_ANY; //for Test
	ServerSockAddr.sin_port = htons(3001);

	bind(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));

	listen(ServerSocket, 5);

	SOCKADDR_IN ClientSockAddr;
	ZeroMemory(&ClientSockAddr, sizeof(ClientSockAddr));
	int ClientSockAddrLength = sizeof(ClientSockAddr);

	SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockAddrLength);
	
	while(1)
	{
		char Buffer[512] = { 0, };
		
		int RecvByte = 0;
		int SendByte = 0;

		RecvByte = recv(ClientSocket, Buffer, 512, 0);
		
		cout << Buffer << endl;
		cout << "Buffer[0]은 " << Buffer[0] << "입니다." << endl;

		if (Buffer[0] == '1' && strlen(Buffer) == 1)
		{
			char sendnum[] = "1";
			SendByte = send(ClientSocket, sendnum, strlen(sendnum) + 1, 0);

			char sendstr[] = "회원 가입 : 아이디와 비밀번호를 입력해주세요.";
			SendByte = send(ClientSocket, sendstr, strlen(sendstr) + 1, 0);

			char IDBuf[512] = { 0, };
			char PWBuf[512] = { 0, };
			string ID;
			string PW;

			RecvByte = recv(ClientSocket, IDBuf, 512, 0);
			RecvByte = recv(ClientSocket, PWBuf, 512, 0);

			for (int i = 0; i < strlen(IDBuf); ++i)
			{
				ID += IDBuf[i];
			}
			for (int i = 0; i < strlen(IDBuf); ++i)
			{
				PW += PWBuf[i];
			}
			
			char num = SQL.Join(ID, PW);

			switch (num)
			{
			case '0':
			{
				char result[] = "회원가입 성공!";
				SendByte = send(ClientSocket, result, strlen(result) + 1, 0);
				break;
			}
			case '1':
			{
				char result[] = "이미 존재하는 ID입니다.";
				SendByte = send(ClientSocket, result, strlen(result) + 1, 0);
				break;
			}
			case '2':
			{
				char result[] = "DB 오류 발생.";
				SendByte = send(ClientSocket, result, strlen(result) + 1, 0);
				break;
			}
			}

		}
		else if (Buffer[0] == '2' && strlen(Buffer) == 1)
		{
			char sendnum[] = "2";
			SendByte = send(ClientSocket, sendnum, strlen(sendnum) + 1, 0);

			char sendstr[] = "로그인 : 아이디와 비밀번호를 입력해주세요.";
			SendByte = send(ClientSocket, sendstr, strlen(sendstr) + 1, 0);

			char IDBuf[512] = { 0, };
			char PWBuf[512] = { 0, };
			string ID;
			string PW;

			RecvByte = recv(ClientSocket, IDBuf, 512, 0);
			RecvByte = recv(ClientSocket, PWBuf, 512, 0);

			for (int i = 0; i < strlen(IDBuf); ++i)
			{
				ID += IDBuf[i];
			}
			for (int i = 0; i < strlen(IDBuf); ++i)
			{
				PW += PWBuf[i];
			}

			char num = SQL.Login(ID, PW);

			switch (num)
			{
			case '0':
			{
				char result[] = "로그인 성공!";
				SendByte = send(ClientSocket, result, strlen(result) + 1, 0);
				break;
			}
			case '1':
			{
				char result[] = "비밀번호가 틀렸습니다.";
				SendByte = send(ClientSocket, result, strlen(result) + 1, 0);
				break;
			}
			case '2':
			{
				char result[] = "존재하지 않는 ID입니다.";
				SendByte = send(ClientSocket, result, strlen(result) + 1, 0);
				break;
			}
			case '3':
			{
				char result[] = "DB 오류 발생.";
				SendByte = send(ClientSocket, result, strlen(result) + 1, 0);
				break;
			}
			}

	/*		switch ()
			{
			case '0':
				cout << "로그인 성공!" << endl;
				break;
			case '1':
				cout << "비밀번호가 틀렸습니다." << endl;
				break;
			case '2':
				cout << "존재하지 않는 ID입니다." << endl;
				break;
			case '3':
				cout << "DB 오류 발생." << endl;
				break;
			}*/
		}
		else
		{
			char sendstr[] = "";
			SendByte = send(ClientSocket, sendstr, strlen(sendstr)+1, 0);
		}

		
	}

	closesocket(ClientSocket);
	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}