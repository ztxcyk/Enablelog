/*++
    2006/02/16 by yxf  为了以后开发方便，将此类移植到comfunc.lib中来。     
    2006/05/26         注意到DeleteKeyNT( LPTSTR pKeyName );可以删除非空项
    2006/09/28         增加对REG_MULTI_SZ的读写支持，使用示例如下
    CRegistry reg;
    char  value[255];
    char  newvalue[255];
    reg.SetRootKey(HKEY_LOCAL_MACHINE);
    reg.SetKey("SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E967-E325-11CE-BFC1-08002BE10318}",TRUE);
    reg.ReadMSZString("UpperFilters",value);
    strcpy(newvalue,"Ntdisk");
    int len=strlen("Ntdisk")+1;
    memcpy((char*)(newvalue+len),value,255-len);
    reg.WriteMSZString("UpperFilters",newvalue,255);

	2008/05/21 by zhaolei 对三个关键函数直接添加KEY_WOW64_64KEY选项，允许32位程序访问64位下的注册表。
						  目前我们的程序在64bit系统上都还是32位模式跑。不添加此选项，访问会出错。

--*/
#ifndef __REGISTRY_H__
#define __REGISTRY_H__

class CRegistry
{
public:
	CRegistry();
	~CRegistry();

int m_nLastError;

// CRegistry properties	
protected:
	HKEY m_hRootKey;
	BOOL m_bLazyWrite;
	CString m_strCurrentPath;

public:
	inline BOOL PathIsValid() 
	{
		return (m_strCurrentPath.GetLength() > 0); 
	}
	
	inline CString GetCurrentPath() 
	{
		return m_strCurrentPath; 
	}
	
	inline HKEY GetRootKey() 
	{
		return m_hRootKey; 
	}


//CRegistry	methods
public:	
	void FlushAll();
	
	BOOL ReadBinary(CString strName, BYTE* pBinArray, ULONG nLen);
	DWORD DeleteKeyNT( LPTSTR pKeyName );         //可以删除非空项
	DWORD EnumSubKey(CStringArray *SubArray,LPCTSTR pKeyName);	
	BOOL ClearKey();
	BOOL SetRootKey(HKEY hRootKey);
	BOOL CreateKey(CString strKey);
	BOOL DeleteKey(CString strKey);      
	BOOL DeleteValue(CString strName);
	int GetDataSize(CString strValueName);
	DWORD GetDataType(CString strValueName);
	int GetSubKeyCount();
	int GetValueCount();
	BOOL KeyExists(CString strKey, HKEY hRootKey = NULL);
	BOOL SetKey(CString strKey, BOOL bCanCreate);
	BOOL ValueExists(CString strName);
	void RenameValue(CString strOldName, CString strNewName);

	// data reading functions
	COleDateTime ReadDateTime(CString strName, COleDateTime dtDefault);
	double ReadFloat(CString strName, double fDefault);
	CString ReadString(CString strName, CString strDefault);
	int ReadInt(CString strName, int nDefault);
	BOOL ReadBool(CString strName, BOOL bDefault);
	COLORREF ReadColor(CString strName, COLORREF rgbDefault);
	BOOL ReadFont(CString strName, CFont* pFont);
	BOOL ReadPoint(CString strName, CPoint* pPoint);
	BOOL ReadSize(CString strName, CSize* pSize);
	BOOL ReadRect(CString strName, CRect* pRect);
	DWORD ReadDword(CString strName, DWORD dwDefault);

	// data writing functions
	BOOL WriteBool(CString strName, BOOL bValue);
	BOOL WriteDateTime(CString strName, COleDateTime dtValue);
	BOOL WriteString(CString strName, CString strValue);
	BOOL WriteFloat(CString strName, double fValue);
	BOOL WriteInt(CString strName, int nValue);
	BOOL WriteColor(CString strName, COLORREF rgbValue);
	BOOL WriteFont(CString strName, CFont* pFont);
	BOOL WritePoint(CString strName, CPoint* pPoint);
	BOOL WriteSize(CString strName, CSize* pSize);
	BOOL WriteRect(CString strName, CRect* pRect);
	BOOL WriteDword(CString strName, DWORD dwValue);
	BOOL WriteBinary(CString strName,  BYTE* pbtValue, int nLen);
	BOOL ReadMSZString(CString strName, TCHAR* pbtValue);   //pbtValue由调用者分配，必须为255字节
	//只能写入一个字符串
	BOOL WriteMSZString(CString strName, CString strValue);
	//buflen缓冲长度，实际写入时，会将其中的结束符位置前面的写入
	//和上面的函数不同之处在于可以写入多个字符串
	BOOL WriteMSZString(CString strName, TCHAR* pbtValue,int buflen);  
	BOOL WriteExpandString(CString strName, CString strValue);
	void FlushWhenWrite(BOOL flush);
};// end of CRegistry class definition


#endif