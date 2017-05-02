/*++
    2006/02/16 by yxf  Ϊ���Ժ󿪷����㣬��������ֲ��comfunc.lib������     
    2006/05/26         ע�⵽DeleteKeyNT( LPTSTR pKeyName );����ɾ���ǿ���
    2006/09/28         ���Ӷ�REG_MULTI_SZ�Ķ�д֧�֣�ʹ��ʾ������
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

	2008/05/21 by zhaolei �������ؼ�����ֱ�����KEY_WOW64_64KEYѡ�����32λ�������64λ�µ�ע���
						  Ŀǰ���ǵĳ�����64bitϵͳ�϶�����32λģʽ�ܡ�����Ӵ�ѡ����ʻ����

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
	DWORD DeleteKeyNT( LPTSTR pKeyName );         //����ɾ���ǿ���
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
	BOOL ReadMSZString(CString strName, TCHAR* pbtValue);   //pbtValue�ɵ����߷��䣬����Ϊ255�ֽ�
	//ֻ��д��һ���ַ���
	BOOL WriteMSZString(CString strName, CString strValue);
	//buflen���峤�ȣ�ʵ��д��ʱ���Ὣ���еĽ�����λ��ǰ���д��
	//������ĺ�����֮ͬ�����ڿ���д�����ַ���
	BOOL WriteMSZString(CString strName, TCHAR* pbtValue,int buflen);  
	BOOL WriteExpandString(CString strName, CString strValue);
	void FlushWhenWrite(BOOL flush);
};// end of CRegistry class definition


#endif