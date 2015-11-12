#include "StringHelper.h"
#include <fstream>
#include <sstream>
#include <locale>
#include <algorithm>
void StringHelper::Char2Wchar(const char *str,LPWSTR outStr)
{
	int   nLen   =   strlen(str)   +   1;      
	int   nwLen   =   MultiByteToWideChar(CP_UTF8,   0,   str,   nLen,   NULL,   0);      
	MultiByteToWideChar(CP_UTF8,   0,   str,   nLen,   outStr,   nwLen); 
}

wstring StringHelper::ExportCsv(vector<vector<string>>& data)
{
	return L"";
}

wstring StringHelper::ExportHtml(vector<vector<string>>& src)
{
	if (src.size() == 0) return L"";
	wchar_t name[65535] = {0};
	std::wstringstream data;
	vector<string> cols = src[0];
	//[data appendString:@"\357\273\277"];
	data<<L"<!DOCTYPE HTML>\
		   <html>\
		   <head>\
		   <meta http-equiv='Content-Type' content='text/html; charset=gbk'/>\
		   <script src='http://libs.baidu.com/jquery/2.0.0/jquery.min.js'></script>\
		   <script src='http://cdn.datatables.net/1.10.7/js/jquery.dataTables.min.js'></script>\
		   <script>\
		   $(document).ready(function () {\
		   $('#resultTb').dataTable({\
		   'paging': false,\
		   'info': false\
		   });\
		   });\
		   </script>\
		   <link href='http://cdn.datatables.net/1.10.7/css/jquery.dataTables.css' rel='stylesheet'>\
		   <style type='text/css'>\
		   td {\
		   max-width: 400px;\
		   word-wrap:break-word;\
		   }\
		   </style>\
		   </head>\
		   <body><h1>"<<L"data export"<<
		   L"</h1>\
			<div>\
			<table id='resultTb' class='display cell-border' cellspacing='0' width=100%%> \
			<thead>\
			<tr>\
			";

	for (size_t i = 0; i < cols.size(); i++) {
		StringHelper::Char2Wchar(cols[i].c_str(),name);
		data<<L"<th>"<<EncodeHtml(name)<<L"</th>";
	}
	data<<L"</tr></thead><tbody>";

	for (size_t i = 1; i < src.size(); i++) {
		data<<L"<tr>";
		vector<string> rows = src[i];
		for (size_t j = 0; j < rows.size(); j++) 
		{
			StringHelper::Char2Wchar(rows[j].c_str(),name);
			data<<L"<td>"<<EncodeHtml(name)<<L"</td>";
		}
		data<<L"</tr>";
	}
	data<<L"</tbody></table></div></body></html>";
	return data.str();
}

void replaceAll(std::wstring& str, const std::wstring& from, const std::wstring& to) {
	if(from.empty())
		return;
	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != std::wstring::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

wstring StringHelper::EncodeHtml(wstring str)
{
	replaceAll(str,L"&",L"&amp;");
	replaceAll(str,L"<",L"&lt;");
	replaceAll(str,L">",L"&gt;");
	replaceAll(str,L"\"",L"&quot;");
	replaceAll(str,L"'",L"&apos;");
	return str;
}