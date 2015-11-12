#include "DbHelper.h"

void log(const char* msg)
{
	//OutputDebugStringA(msg);
}

bool checkError(sqlite3 *db,int ret)
{
	if (ret != SQLITE_OK) {
		log(sqlite3_errmsg(db));
		return false;
	}
	return true;
}


DbHelper::~DbHelper()
{
	if (this->db != NULL) 
	{
		sqlite3_close(this->db);
	}
}
void DbHelper::SetDatabase(string path,string keyStr)
{
	if (this->db != NULL) 
	{
		sqlite3_close(this->db);
	}
	int ret = sqlite3_open(path.c_str(),&db);
	if (checkError(db,ret) && keyStr.length() > 0) 
	{
		const char *key = keyStr.c_str();
		ret = sqlite3_key(db,key,strlen(key));
	}
}

vector<string> DbHelper::GetTables()
{
	vector<string> result;
	if (this->db == NULL) 
	{
		return result;
	}
	sqlite3_stmt *stmt;
	const char *sql = "select name from sqlite_master where type = 'table'";
	int ret = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,NULL);
	if (checkError(db,ret))
	{
		//int colCount = sqlite3_column_count(stmt);
		while ( (ret = sqlite3_step(stmt)) == SQLITE_ROW) {   
			result.push_back((char *)sqlite3_column_text(stmt, 0));
		}
	}
	sqlite3_finalize(stmt);
	return result;
}

vector<vector<string>> DbHelper::QueryTable(string sqlStr)
{
	vector<vector<string>> result;
	if (this->db == NULL) 
	{
		return result;
	}
	sqlite3_stmt *stmt;
	const char *sql = sqlStr.c_str();
	int ret = sqlite3_prepare_v2(db,sql,strlen(sql),&stmt,NULL);
	if (checkError(db,ret))
	{
		int colCount = sqlite3_column_count(stmt);
		vector<string> cols;
		for (int i = 0; i < colCount; i++)
		{
			const char *colName = sqlite3_column_name(stmt,i);
			cols.push_back(colName);

		}
		result.push_back(cols);
		while ( (ret = sqlite3_step(stmt)) == SQLITE_ROW) {   
			vector<string> data;
			for (int i = 0; i < colCount; i++) {
				char *text = (char *)sqlite3_column_text(stmt, i);
				data.push_back(text == NULL ? "":text);
			}
			result.push_back(data);
		}

	}
	sqlite3_finalize(stmt);
	return result;
}