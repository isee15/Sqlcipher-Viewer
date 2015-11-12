#pragma once
#include <atlconv.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;
class StringHelper
{
public:
	static void Char2Wchar(const char *str,LPWSTR outStr);
	static wstring ExportCsv(vector<vector<string>>& data);
	static wstring ExportHtml(vector<vector<string>>& data);
	static wstring EncodeHtml(wstring str);
};