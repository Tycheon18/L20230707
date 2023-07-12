//#define _WINSOCK_DEPRECATED_NO_WARNINGS 
//
//#include <iostream>
//#include <stdio.h>
//#include <winsock2.h>
//#include <exception>
//
//#include <jdbc/mysql_connection.h>
//#include <jdbc/cppconn/driver.h>
//#include <jdbc/cppconn/exception.h>
//#include <jdbc/cppconn/resultset.h>
//#include <jdbc/cppconn/statement.h>
//#include <jdbc/cppconn/prepared_statement.h>
//
//#pragma comment(lib, "ws2_32.lib")
//#pragma comment(lib, "vs14/debug/mysqlcppconn.lib")
//
//using namespace std;
//
//#ifdef _RUN_AS_LOCALHOST
////const std::string DB_HOST = "tcp://127.0.0.1:3306";
//const std::string DB_IP = "127.0.0.1:3306";
//const std::string DB_ID = "root";
//const std::string DB_PASSWORD = "qwe123";
//#else
//const std::string DB_IP = "tcp://127.0.0.1:3306";
//const std::string DB_ID = "root";
//const std::string DB_PASSWORD = "qwe123";
//#endif
//
//
//sql::Connection* DB_Connection = nullptr;
//sql::Driver* DB_Driver = nullptr;
//sql::Statement* DB_Statement = nullptr;
//sql::PreparedStatement* DB_PST = nullptr;
//sql::ResultSet* DB_ResultSet = nullptr;
//
//int commend = 999;
//
//void login(int commend)
//{
//		try
//	{
//		DB_Driver = get_driver_instance();
//
//		DB_Connection = DB_Driver->connect(DB_IP, "root", "qwe123");
//		DB_Connection->setSchema("testdatabase");
//		DB_Statement = DB_Connection->createStatement();
//
//		DB_ResultSet = DB_Statement->executeQuery("select * from testtable");
//
//		while (commend != 0)
//		{
//			printf("작업을 선택해주세요. \n");
//			commend = 999;
//			cin >> commend;
//
//			login(commend);
//			
//		}
//
//
//		for (; DB_ResultSet->next();)
//		{
//			cout << DB_ResultSet->getString("TestID") << " , "
//				<< DB_ResultSet->getString("TestPW") << " , " << endl;
//		}
//
//	}
//	catch (sql::SQLException e)
//	{
//		cout << "SQL Exception : " << e.what() << endl;
//	}
//
//
//
//	string ID, PASSWORD;
//	string query;
//	int delnum = 0;
//
//	switch (commend)
//	{
//	case 1:
//		cout << "ID와 PASSWORD를 입력해주세요." << endl;
//
//		cin >> ID >> PASSWORD;
//		query = "INSERT INTO testdatabase.testtable (TestID, TestPW) VALUES ('" + ID + "', '" + PASSWORD + "')";
//		DB_Statement->execute(query);
//		commend = 999;
//		break;
//	case 2:
//		cout << "DB에 저장된 ID와 PASSWORD는 \n";
//		for (; DB_ResultSet->next();)
//		{
//			cout << DB_ResultSet->getString("TestID") << " , "
//				<< DB_ResultSet->getString("TestPW") << " , " << endl;
//		}
//		commend = 999;
//		break;
//	case 3:
//		cin >> delnum;
//		query = "DELETE FROM testdatabase.testtable WHERE TestID = 'NO" + to_string(delnum) + "'";
//		DB_Statement->execute(query);
//		break;
//	case 4: {
//		DB_Connection->setSchema("testdatabase"); //데이터 갱신
//		string inputID = "";
//		string inputPW = "";
//		cin >> inputID >> inputPW;
//		DB_ResultSet = DB_Statement->executeQuery("SELECT * FROM testtable WHERE TestID = '" + inputID + "'");
//		if (DB_ResultSet->next() == 1)
//		{
//			if (DB_ResultSet->getString("TestPW") == inputPW)
//			{
//				printf("로그인 성공 \n");
//			}
//			else
//			{
//				printf("PASSWORD가 틀렸습니다. \n");
//			}
//		}
//		else
//		{
//			cout << "존재하지 않는 ID입니다." << endl;
//		}
//		break;
//	}
//	case 0:
//		cout << "시스템 종료";
//		break;
//	}
//}
//
//int main()
//{
//	//try
//	//{
//	//	DB_Driver = get_driver_instance();
//
//	//	DB_Connection = DB_Driver->connect(DB_IP, "root", "qwe123");
//	//	DB_Connection->setSchema("testdatabase");
//	//	DB_Statement = DB_Connection->createStatement();
//
//	//	DB_ResultSet = DB_Statement->executeQuery("select * from testtable");
//
//	//	while (commend != 0)
//	//	{
//	//		printf("작업을 선택해주세요. \n");
//	//		commend = 999;
//	//		cin >> commend;
//
//	//		login(commend);
//	//		
//	//	}
//
//
//	//	for (; DB_ResultSet->next();)
//	//	{
//	//		cout << DB_ResultSet->getString("TestID") << " , "
//	//			<< DB_ResultSet->getString("TestPW") << " , " << endl;
//	//	}
//
//	//}
//	//catch (sql::SQLException e)
//	//{
//	//	cout << "SQL Exception : " << e.what() << endl;
//	//}
//
//	WSAData wsaData;
//	WSAStartup(MAKEWORD(2, 2), &wsaData);
//
//	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
//
//	SOCKADDR_IN ServerSockAddr;
//	ZeroMemory(&ServerSockAddr, sizeof(ServerSockAddr));
//	ServerSockAddr.sin_family = PF_INET;
//	ServerSockAddr.sin_addr.s_addr = INADDR_ANY; //for Test
//	ServerSockAddr.sin_port = htons(3001);
//
//	bind(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));
//
//	listen(ServerSocket, 5);
//
//	SOCKADDR_IN ClientSockAddr;
//	ZeroMemory(&ClientSockAddr, sizeof(ClientSockAddr));
//	int ClientSockAddrLength = sizeof(ClientSockAddr);
//
//	SOCKET ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockAddrLength);
//
//
//	//while (1)
//	//{
//	//	
//	//	int recvByte = recv(ClientSocket, Buffer, 1024, 0);
//	//	if (recvByte == SOCKET_ERROR)
//	//	{
//	//		printf("recv Error!");
//	//		break;
//	//	}
//	//	else if (recvByte == 0)
//	//	{
//	//		break;
//	//	}
//
//	//	Buffer[recvByte] = '\0';
//	//	printf("[TCP/%s:%d] %s\n", inet_ntoa(ClientSockAddr.sin_addr), ntohs(ClientSockAddr.sin_port), Buffer);
//
//	//	int sendByte = send(ClientSocket, Buffer, 1024, 0);
//	//	if (sendByte == SOCKET_ERROR)
//	//	{
//	//		printf("send Error!");
//	//		break;
//	//	}
//
//	//	closesocket(ClientSocket);
//	//	printf("[TCP 서버] 클라이언트 종료: IP 주소=%s, 포트 번호=%d\n", inet_ntoa(ClientSockAddr.sin_addr), ntohs(ClientSockAddr.sin_port));
//	//}
//
//	//delete[] Buffer;
//
//	closesocket(ClientSocket);
//	closesocket(ServerSocket);
//
//	WSACleanup();
//
//	return 0;
//}