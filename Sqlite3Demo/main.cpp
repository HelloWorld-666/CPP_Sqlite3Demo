#include <iostream>
#include <string.h>
#include <map>
//#include <windows.h>
#include "shlobj.h" // getDesktopPath()的头文件
#include "sqlite3.h"

using namespace std;

std::multimap <string, string> m_mapTest;

// 存烟草相关信息到map中（旧版IsSmokingBarCode）
bool IsSmokingBarCode(string strBarCode)
{
	// 打开本地烟草数据库
	sqlite3 * pDB = NULL;
	char* cErrMsg;
	int nRes = sqlite3_open(".\\global.db"/*"C:\\ProgramData\\magicbox\\global.db"*/, &pDB);									// 这里不知道为何，sqlite3_open()返回值永远是0？？？？？？？？？？？？？？？？？？？？？
	if (nRes != SQLITE_OK)
	{
		cout << "open global.db error: %s\n" << sqlite3_errmsg(pDB) << endl;
		sqlite3_close(pDB);
		return false;
	}

	//std::string sql = "select * from smoking where bar_code = '6901028207042'";
	std::string sql = "select name,bar_code from smoking where bar_code = ";
	sql += strBarCode;
	char **pazResult;
	int pnRow;
	int pnColumn;
	int rc = sqlite3_get_table(pDB, sql.c_str(), &pazResult, &pnRow, &pnColumn, NULL);								// pnRow为0，说明没有查到数据；查到了存到map中 烟草条码：烟草名称
	if (rc != SQLITE_OK)
	{
		cout << "Get Table database error: " <<  sqlite3_errmsg(pDB) << endl;
		return false;
	}
	//cout << pnColumn << sql.c_str() << endl;

	for (int i = 0; i < pnColumn; i++)
	{
		if (strcmp(pazResult[i], "name") == 0)																		// 匹配字段名
		{
			m_mapTest.insert(std::make_pair(pazResult[pnColumn + i], pazResult[pnColumn + i + 1]));
			cout << pazResult[i] << pazResult[pnColumn + i] << endl;
			//module::GetSysConfigModule()->m_mapSmoking[pazResult[pnColumn + i]] = pazResult[pnColumn + i + 1];	// 错误：multimap的插入只能用insert()不能用数组！！！
		}
	}
	return true;
}

// 获取桌面路径
string getDesktopPath()
{
	LPITEMIDLIST pidl;
	LPMALLOC pShellMalloc;
	char szDir[200];
	if (SUCCEEDED(SHGetMalloc(&pShellMalloc)))
	{
		if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl))) {
			// 如果成功返回true  
			SHGetPathFromIDListA(pidl, szDir);
			pShellMalloc->Free(pidl);
		}
		pShellMalloc->Release();
	}

	return string(szDir);
}

// 写数据到文件
bool WriteData2Text()
{
	// 打开输出文件.txt
	string strDeskPath = getDesktopPath() + "\\测试.txt";
	FILE* pFile = fopen(strDeskPath.c_str(), "wb");
	if (NULL == pFile)
	{
		cout << "open example.txt error.\n" << endl;
		return false;
	}

	// 写入数据
	std::multimap<string, string>::iterator it;
	for (it = m_mapTest.begin(); it != m_mapTest.end(); it++)
	{
		fwrite(it->first.c_str(), 1, strlen(it->first.c_str()), pFile);
		fwrite(" ", 1, 1, pFile);		// 空格
		fwrite(it->second.c_str(), 1, strlen(it->second.c_str()), pFile);
		fwrite("\r\n", 1, 2, pFile);	// 换行
	}


	// 清空缓存 并 关闭流.txt  
	m_mapTest.clear();
	fclose(pFile);
	return true;
}

int main()
{
	string strBarCode = "6901028207043";
	bool bIsSuccess = IsSmokingBarCode(strBarCode);
	if (!bIsSuccess)
	{
		cout << "IsSmokingBarCode() error !" << endl;
	}
	bIsSuccess = WriteData2Text();
	if (!bIsSuccess)
	{
		cout << "WriteData2Text() error !" << endl;
	}

	getchar();
	return 0;
}
