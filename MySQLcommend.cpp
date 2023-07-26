#include "MySQLcommend.h"
#include <iostream>
#include <stdio.h>
#include <winsock2.h>
#include <exception>

#include <jdbc/mysql_connection.h>
#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>

#pragma comment(lib, "vs14/debug/mysqlcppconn.lib")

using namespace std;

#ifdef _RUN_AS_LOCALHOST
//const std::string DB_HOST = "tcp://127.0.0.1:3306";
const std::string DB_IP = "127.0.0.1:3306";
const std::string DB_ID = "root";
const std::string DB_PASSWORD = "qwe123";
#else
const std::string DB_IP = "tcp://127.0.0.1:3306";
const std::string DB_ID = "root";
const std::string DB_PASSWORD = "qwe123";
#endif


sql::Connection* DB_Connection = nullptr;
sql::Driver* DB_Driver = nullptr;
sql::Statement* DB_Statement = nullptr;
sql::PreparedStatement* DB_PST = nullptr;
sql::ResultSet* DB_ResultSet = nullptr;

MySQLcommend::MySQLcommend()
{
	printf("DB ���� ����\n");
	try
	{
		DB_Driver = get_driver_instance();

		DB_Connection = DB_Driver->connect(DB_IP, "root", "qwe123");
		DB_Connection->setSchema("testdatabase");
		DB_Statement = DB_Connection->createStatement();

		DB_ResultSet = DB_Statement->executeQuery("select * from testtable");

		printf("DB ���� ����\n");
	}
	catch (sql::SQLException e)
	{
		cout << "SQL Exception : " << e.what() << endl;
	}
}

MySQLcommend::~MySQLcommend()
{
}

bool MySQLcommend::CheckID(string ID)
{
	try
	{
		DB_Driver = get_driver_instance();

		DB_Connection = DB_Driver->connect(DB_IP, "root", "qwe123");
		DB_Connection->setSchema("testdatabase");
		DB_Statement = DB_Connection->createStatement();

		DB_ResultSet = DB_Statement->executeQuery("select * from testtable");

		string query;

		DB_ResultSet = DB_Statement->executeQuery("SELECT * FROM testtable WHERE TestID = '" + ID + "'");
		if (DB_ResultSet->next() == 1)
		{
			return false;
		}
		else
		{
			return true;
		}

	}
	catch (sql::SQLException e)
	{
		return false;
	}
}

char MySQLcommend::Login(string id, string pw)
{
	try
	{
		DB_Driver = get_driver_instance();

		DB_Connection = DB_Driver->connect(DB_IP, "root", "qwe123");
		DB_Connection->setSchema("testdatabase");
		DB_Statement = DB_Connection->createStatement();

		DB_ResultSet = DB_Statement->executeQuery("select * from testtable");

		bool check = this->CheckID(id);

		DB_ResultSet = DB_Statement->executeQuery("SELECT * FROM testtable WHERE TestID = '" + id + "'");
		if (DB_ResultSet->next() == 1)
		{
			DB_ResultSet = DB_Statement->executeQuery("SELECT * FROM testtable WHERE TestID = '" + id + "' AND TestPW = '" + pw + "'");
			if (DB_ResultSet->next() == 1)
			{
				return '0';
			}
			else
			{
				return '1';
			}
		}
		else
		{
			return '2';
		}

	}
	catch (sql::SQLException e)
	{
		return '3';
	}

}

char MySQLcommend::Join(string id, string pw)
{
	try
	{
		DB_Driver = get_driver_instance();

		DB_Connection = DB_Driver->connect(DB_IP, "root", "qwe123");
		DB_Connection->setSchema("testdatabase");
		DB_Statement = DB_Connection->createStatement();

		DB_ResultSet = DB_Statement->executeQuery("select * from testtable");

		bool check = this->CheckID(id);
		if (check)
		{
			string query = "INSERT INTO testdatabase.testtable (TestID, TestPW) VALUES ('" + id + "', '" + pw + "')";
			DB_Statement->execute(query);

			return '0';
		}
		else
		{
			return '1';
		}
	}
	catch (sql::SQLException e)
	{
		return '2';
	}

}

//commend = 999;
//cin >> commend;

//string ID, PASSWORD;
//string query;
//int delnum = 0;

//switch (commend)
//	{
//	case 1:
//		cout << "ID�� PASSWORD�� �Է����ּ���." << endl;

//		cin >> ID >> PASSWORD;
//		query = "INSERT INTO testdatabase.testtable (TestID, TestPW) VALUES ('" + ID + "', '" + PASSWORD + "')";
//		DB_Statement->execute(query);
//		commend = 999;
//		break;
//	case 2:
//		cout << "DB�� ����� ID�� PASSWORD�� \n";
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
//		DB_Connection->setSchema("testdatabase"); //������ ����
//		string inputID = "";
//		string inputPW = "";
//		cin >> inputID >> inputPW;
//		DB_ResultSet = DB_Statement->executeQuery("SELECT * FROM testtable WHERE TestID = '" + inputID + "'");
//		if (DB_ResultSet->next() == 1)
//		{
//			if (DB_ResultSet->getString("TestPW") == inputPW)
//			{
//				printf("�α��� ���� \n");
//			}
//			else
//			{
//				printf("PASSWORD�� Ʋ�Ƚ��ϴ�. \n");
//			}
//		}
//		else
//		{
//			cout << "�������� �ʴ� ID�Դϴ�." << endl;
//		}
//		break;
//	}
//	case 0:
//		cout << "�ý��� ����";
//		break;
//}