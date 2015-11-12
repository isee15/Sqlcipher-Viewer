#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "sqlite3.h"

using namespace std;
class DbHelper
{
public:
	~DbHelper();
	void SetDatabase(string path,string key);
	vector<string> GetTables();
	vector<vector<string>> QueryTable(string sql);

private:
	sqlite3 *db;
};