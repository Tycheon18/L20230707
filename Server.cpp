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
		cout << "Buffer[0]�� " << Buffer[0] << "�Դϴ�." << endl;

		if (Buffer[0] == '1' && strlen(Buffer) == 1)
		{
			char sendnum[] = "1";
			SendByte = send(ClientSocket, sendnum, strlen(sendnum) + 1, 0);

			char sendstr[] = "ȸ�� ���� : ���̵�� ��й�ȣ�� �Է����ּ���.";
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
				char result[] = "ȸ������ ����!";
				SendByte = send(ClientSocket, result, strlen(result) + 1, 0);
				break;
			}
			case '1':
			{
				char result[] = "�̹� �����ϴ� ID�Դϴ�.";
				SendByte = send(ClientSocket, result, strlen(result) + 1, 0);
				break;
			}
			case '2':
			{
				char result[] = "DB ���� �߻�.";
				SendByte = send(ClientSocket, result, strlen(result) + 1, 0);
				break;
			}
			}

		}
		else if (Buffer[0] == '2' && strlen(Buffer) == 1)
		{
			char sendnum[] = "2";
			SendByte = send(ClientSocket, sendnum, strlen(sendnum) + 1, 0);

			char sendstr[] = "�α��� : ���̵�� ��й�ȣ�� �Է����ּ���.";
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
				char result[] = "�α��� ����!";
				SendByte = send(ClientSocket, result, strlen(result) + 1, 0);
				break;
			}
			case '1':
			{
				char result[] = "��й�ȣ�� Ʋ�Ƚ��ϴ�.";
				SendByte = send(ClientSocket, result, strlen(result) + 1, 0);
				break;
			}
			case '2':
			{
				char result[] = "�������� �ʴ� ID�Դϴ�.";
				SendByte = send(ClientSocket, result, strlen(result) + 1, 0);
				break;
			}
			case '3':
			{
				char result[] = "DB ���� �߻�.";
				SendByte = send(ClientSocket, result, strlen(result) + 1, 0);
				break;
			}
			}

	/*		switch ()
			{
			case '0':
				cout << "�α��� ����!" << endl;
				break;
			case '1':
				cout << "��й�ȣ�� Ʋ�Ƚ��ϴ�." << endl;
				break;
			case '2':
				cout << "�������� �ʴ� ID�Դϴ�." << endl;
				break;
			case '3':
				cout << "DB ���� �߻�." << endl;
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