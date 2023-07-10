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
		int delnum = 0;
		while (commend != 0)
		{
			printf("ÀÛ¾÷À» ¼±ÅÃÇØÁÖ¼¼¿ä. \n");
			commend = 999;
			cin >> commend;

			switch (commend)
			{
				case 1:
					cout << "ID¿Í PASSWORD¸¦ ÀÔ·ÂÇØÁÖ¼¼¿ä." << endl;

					cin >> ID >> PASSWORD;
					query = "INSERT INTO testdatabase.testtable (TestID, TestPW) VALUES ('" + ID + "', '" + PASSWORD + "')";
					DB_Statement->execute(query);
					commend = 999;
					break;
				case 2:
					cout << "DB¿¡ ÀúÀåµÈ ID¿Í PASSWORD´Â \n";
					for (; DB_ResultSet->next();)
					{
						cout << DB_ResultSet->getString("TestID") << " , "
							<< DB_ResultSet->getString("TestPW") << " , " << endl;
					}
					commend = 999;
					break;
				case 3: 
					cin >> delnum;
					query = "DELETE FROM testdatabase.testtable WHERE TestID = 'NO" + to_string(delnum) + "'";
					DB_Statement->execute(query);
					break;
				case 4:	{
					DB_Connection->setSchema("testdatabase"); //µ¥ÀÌÅÍ °»½Å
					string inputID = "";
					string inputPW = "";
					cin >> inputID >> inputPW;
					DB_ResultSet = DB_Statement->executeQuery("SELECT * FROM testtable WHERE TestID = '" + inputID + "'");
					if (DB_ResultSet->next() == 1)
					{
						if (DB_ResultSet->getString("TestPW") == inputPW)
						{
							printf("·Î±×ÀÎ ¼º°ø \n");
						}
						else
						{
							cout << "PASSWORD°¡€ Æ²·È½À´Ï´Ù." << endl;
						}
					}
					else
					{
						cout << "Á¸ÀçÇÏÁö ¾Ê´Â IDÀÔ´Ï´Ù." << endl;
					}
					break;
					}
				case 0:
					cout << "½Ã½ºÅÛ Á¾·á";
					break;
			}
		}


		for (; DB_ResultSet->next();)
		{
			cout << DB_ResultSet->getString("TestID") << " , "
				<< DB_ResultSet->getString("TestPW") << " , " << endl;
		}

	}
	catch (sql::SQLException e)
	{
		cout << "SQL Exception : " << e.what() << endl;
	}

	return 0;
}