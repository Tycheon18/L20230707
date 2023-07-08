#include <iostream>
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

int commend = 999;

int main()
{
	try
	{
		DB_Driver = get_driver_instance();
		
		DB_Connection = DB_Driver->connect(DB_IP, "root", "qwe123");
		DB_Connection->setSchema("testdatabase");
		DB_Statement = DB_Connection->createStatement();

		DB_ResultSet = DB_Statement->executeQuery("select * from testtable");

		string ID, PASSWORD;
		string query;
		while(commend != 0)
		{
			commend = 999;
			cin >> commend;

			switch (commend)
			{
				case 1:
					cout << "ID와 PASSWORD를 입력해주세요." << endl;
					
					cin >> ID >> PASSWORD;
					query = "INSERT INTO testdatabase.testtable (TestID, TestWord) VALUES ('" + ID + "', '" + PASSWORD + "')";
					DB_Statement->execute(query);
					commend = 999;
					break;
				case 2:
					cout << "DB에 저장된 ID와 PASSWORD는 \n";
					for (; DB_ResultSet->next();)
					{
						cout << DB_ResultSet->getString("TestID") << " , "
							<< DB_ResultSet->getString("TestWord") << " , " << endl;
					}
					commend = 999;
					break;
				case 0:
					cout << "시스템 종료";
					break;
			}
		}

		 
		for (; DB_ResultSet->next();)
		{
			cout << DB_ResultSet->getString("TestID") << " , "
				<< DB_ResultSet->getString("TestWord") << " , " << endl;
		}

	}
	catch (sql::SQLException e)
	{
		cout << "SQL Exception : " << e.what() << endl;
	}

	return 0;
}