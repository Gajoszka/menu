#pragma once
/* Class that deals with database queries*/
//#include <mysql.h>
#include <string>
using namespace std;

class DBconnection
{
	public:
		DBconnection();
		void key_functions();
		void add_username(string username);
	private:
		
		int qstate;
	/*	MYSQL* conn;
		MYSQL_ROW row;
		MYSQL_RES* res;*/
	
};

