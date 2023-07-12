#pragma once

#include <iostream>

using namespace std;

class MySQLcommend
{
	int commend = 999;
public:
	MySQLcommend();
	~MySQLcommend();

	bool CheckID(string ID);
	char Login(string id, string pw);
	char Join(string id, string pw);
};

