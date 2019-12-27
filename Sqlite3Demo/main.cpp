#include <iostream>
#include <string.h>
#include <map>
//#include <windows.h>
#include "shlobj.h" // getDesktopPath()��ͷ�ļ�
#include "sqlite3.h"

using namespace std;

std::multimap <string, string> m_mapTest;

// ���̲������Ϣ��map�У��ɰ�IsSmokingBarCode��
bool IsSmokingBarCode(string strBarCode)
{
	// �򿪱����̲����ݿ�
	sqlite3 * pDB = NULL;
	char* cErrMsg;
	int nRes = sqlite3_open(".\\global.db"/*"C:\\ProgramData\\magicbox\\global.db"*/, &pDB);									// ���ﲻ֪��Ϊ�Σ�sqlite3_open()����ֵ��Զ��0������������������������������������������
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
	int rc = sqlite3_get_table(pDB, sql.c_str(), &pazResult, &pnRow, &pnColumn, NULL);								// pnRowΪ0��˵��û�в鵽���ݣ��鵽�˴浽map�� �̲����룺�̲�����
	if (rc != SQLITE_OK)
	{
		cout << "Get Table database error: " <<  sqlite3_errmsg(pDB) << endl;
		return false;
	}
	//cout << pnColumn << sql.c_str() << endl;

	for (int i = 0; i < pnColumn; i++)
	{
		if (strcmp(pazResult[i], "name") == 0)																		// ƥ���ֶ���
		{
			m_mapTest.insert(std::make_pair(pazResult[pnColumn + i], pazResult[pnColumn + i + 1]));
			cout << pazResult[i] << pazResult[pnColumn + i] << endl;
			//module::GetSysConfigModule()->m_mapSmoking[pazResult[pnColumn + i]] = pazResult[pnColumn + i + 1];	// ����multimap�Ĳ���ֻ����insert()���������飡����
		}
	}
	return true;
}

// ��ȡ����·��
string getDesktopPath()
{
	LPITEMIDLIST pidl;
	LPMALLOC pShellMalloc;
	char szDir[200];
	if (SUCCEEDED(SHGetMalloc(&pShellMalloc)))
	{
		if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl))) {
			// ����ɹ�����true  
			SHGetPathFromIDListA(pidl, szDir);
			pShellMalloc->Free(pidl);
		}
		pShellMalloc->Release();
	}

	return string(szDir);
}

// д���ݵ��ļ�
bool WriteData2Text()
{
	// ������ļ�.txt
	string strDeskPath = getDesktopPath() + "\\����.txt";
	FILE* pFile = fopen(strDeskPath.c_str(), "wb");
	if (NULL == pFile)
	{
		cout << "open example.txt error.\n" << endl;
		return false;
	}

	// д������
	std::multimap<string, string>::iterator it;
	for (it = m_mapTest.begin(); it != m_mapTest.end(); it++)
	{
		fwrite(it->first.c_str(), 1, strlen(it->first.c_str()), pFile);
		fwrite(" ", 1, 1, pFile);		// �ո�
		fwrite(it->second.c_str(), 1, strlen(it->second.c_str()), pFile);
		fwrite("\r\n", 1, 2, pFile);	// ����
	}


	// ��ջ��� �� �ر���.txt  
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
