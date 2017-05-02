
// EnableLogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EnableLog.h"
#include "EnableLogDlg.h"
#include "afxdialogex.h"
#include "Registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

BOOL IsWow64()
{
	LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
		GetModuleHandle("kernel32"),
		"IsWow64Process"
		);
	BOOL           bIsWow64 = FALSE;

	if (NULL != fnIsWow64Process)
	{
		if (!fnIsWow64Process(GetCurrentProcess(),&bIsWow64))
		{
			// Error handle
			return FALSE;
		}
	}
	return bIsWow64;
}


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEnableLogDlg dialog




CEnableLogDlg::CEnableLogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEnableLogDlg::IDD, pParent)
	, m_searchpath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEnableLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_path);
	DDX_Control(pDX, IDC_BOPENLOG, m_open);
	DDX_Control(pDX, IDC_BCLOSELOG, m_close);
	DDX_Control(pDX, IDC_log, m_mode);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_SearchPath);
}

BEGIN_MESSAGE_MAP(CEnableLogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BCLOSELOG, &CEnableLogDlg::OnBnClickedBcloselog)
	ON_BN_CLICKED(IDC_BOPENLOG, &CEnableLogDlg::OnBnClickedBopenlog)
	ON_BN_CLICKED(IDC_log, &CEnableLogDlg::OnBnClickedlog)
	ON_BN_CLICKED(IDC_BFIND, &CEnableLogDlg::OnBnClickedBfind)
	ON_BN_CLICKED(IDC_BEXPORT, &CEnableLogDlg::OnBnClickedBexport)
	ON_BN_CLICKED(IDC_SELECTALL, &CEnableLogDlg::OnBnClickedSelectall)
END_MESSAGE_MAP()


// CEnableLogDlg message handlers

BOOL CEnableLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	Initstr();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEnableLogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEnableLogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEnableLogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CEnableLogDlg::OnBnClickedBcloselog()
{
	// TODO: Add your control notification handler code here
	CRegistry Reg;
	Reg.SetRootKey(HKEY_LOCAL_MACHINE);
	Reg.SetKey("Software\\Saming",TRUE);
	Reg.WriteDword("enabledbg",0);
	m_open.EnableWindow(TRUE);
	m_close.EnableWindow(FALSE);
	m_mode.EnableWindow(FALSE);
}


void CEnableLogDlg::OnBnClickedBopenlog()
{
	// TODO: Add your control notification handler code here
	CRegistry Reg;
	Reg.SetRootKey(HKEY_LOCAL_MACHINE);
	Reg.SetKey("Software\\Saming",TRUE);
	Reg.WriteDword("enabledbg",1);
	m_close.EnableWindow(TRUE);
	m_open.EnableWindow(FALSE);
	m_mode.EnableWindow(TRUE);
}


void CEnableLogDlg::OnBnClickedlog()
{
	// TODO: Add your control notification handler code here

	static CRect rectLarge;
	static CRect rectSmall;
	if(rectLarge.IsRectNull())
	{
		CRect rectSeperator;
		GetWindowRect(&rectLarge);
		GetDlgItem(IDC_SEPERATOR)->GetWindowRect(&rectSeperator);

		rectSmall.left=rectLarge.left;
		rectSmall.top=rectLarge.top;
		rectSmall.right=rectLarge.right;
		rectSmall.bottom=rectSeperator.bottom;
	}
	CString strtemp;
	((CButton*)GetDlgItem(IDC_log))->GetWindowText(strtemp);
	if(!strtemp.Compare("日志详情>>"))
	{
		((CButton*)GetDlgItem(IDC_log))->SetWindowText("简约模式<<");
		SetWindowPos(NULL,0,0,rectLarge.Width(),rectLarge.Height(),SWP_NOMOVE|SWP_NOZORDER);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_log))->SetWindowText("日志详情>>");
		SetWindowPos(NULL,0,0,rectSmall.Width(),rectSmall.Height(),SWP_NOMOVE|SWP_NOZORDER);
	}

}


BOOL CEnableLogDlg::enabledbg()
{
	CRegistry Reg;
	Reg.SetRootKey(HKEY_LOCAL_MACHINE);
	Reg.SetKey("Software\\Saming",TRUE);
	if(Reg.ReadDword("enabledbg",0)==1)
	{
		return TRUE;
	}
	return FALSE;
}

void CEnableLogDlg::Initstr(void)
{
	//初始化界面按钮状态
	if(enabledbg())
	{
		m_open.EnableWindow(FALSE);
		m_mode.EnableWindow(TRUE);
	}
	else
	{
		m_mode.EnableWindow(FALSE);
		m_close.EnableWindow(FALSE);
	}

	//设置默认路径
	if(IsWow64())
		m_SearchPath.SetWindowTextA("C:\\Program Files (x86)\\Netmanager\\Programe");
	else
		m_SearchPath.SetWindowTextA("C:\\Program Files\\Netmanager\\Programe");

	//设置显示
	m_path.SetExtendedStyle(m_path.GetExtendedStyle()    |  LVS_EX_CHECKBOXES | LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_path.DeleteAllItems();//清空  
	m_path.InsertColumn(0,_T(".."));//添加列  
	m_path.InsertColumn(1,_T("路径"));  
	m_path.SetColumnWidth(0, 20);//设置列宽  
	m_path.SetColumnWidth(1, 310);  
	m_path.SetRedraw(FALSE);//防止重绘  

	//设置搜索 规则
	m_rules.Add(".log");
	m_rules.Add(".txt");

	OnBnClickedlog();
}


void CEnableLogDlg::OnBnClickedBfind()
{
	// TODO: Add your control notification handler code here
	((CButton*)GetDlgItem(IDC_BFIND))->EnableWindow(FALSE);
	m_path.DeleteAllItems();
	m_SearchPath.GetWindowText(m_searchpath);
	if(m_searchpath.IsEmpty())
	{
		return;
	}
	CWinThread* pThread = AfxBeginThread(CEnableLogDlg::SearchThread, this);
	CloseHandle(pThread->m_hThread);
	return ;
}


void CEnableLogDlg::OnBnClickedBexport()
{
	// TODO: Add your control notification handler code here
	int nCount = m_path.GetItemCount();
	if(nCount==0)
		return;
	TCHAR FullPath[MAX_PATH] = {0};
	GetCurrentDirectory(MAX_PATH,FullPath);
	CString dirname(FullPath);
	dirname+="\\xcyklog";
	if(!PathFileExists(dirname))
	{
		if(!CreateDirectory(dirname, NULL))
		{
			return;
		}
	}
	CString copyfilename;
	CString filename;
	for (int i = 0; i < nCount; i++)
	{
		if(m_path.GetCheck(i))
		{
			filename=copyfilename=m_path.GetItemText(i,1);
			copyfilename.Replace("\\","-");
			CopyFile(m_searchpath+"\\"+filename,dirname+"\\"+copyfilename,FALSE);
		}
	}
}

UINT CEnableLogDlg::SearchThread(LPVOID lParam)
{
	CEnableLogDlg* pfind = (CEnableLogDlg*)lParam;

	pfind->Findfile(pfind->m_searchpath);
	((CButton*)pfind->GetDlgItem(IDC_BFIND))->EnableWindow(TRUE);
	return 1;
}

BOOL CEnableLogDlg::Findfile(const CString path)
{
	CString findfile(path);
	findfile += "\\*.*";

	WIN32_FIND_DATA filedir;
	HANDLE hfind = FindFirstFile(findfile, &filedir);
	if (INVALID_HANDLE_VALUE == hfind)
		return FALSE;
	int nIndex;
	do
	{
		CString sub;
		if (filedir.cFileName[0] == '.')//忽略"." 和".."
			continue;
		//过滤目录
		sub.Format(_T("%s\\%s"), path, filedir.cFileName);
		if (filedir.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			CString dirsub;
			dirsub.Format(_T("%s\\%s"), path, filedir.cFileName);
			Findfile(dirsub);
			continue;
		}
		else
		{
			int pos = sub.ReverseFind('.');
			if (pos == -1)
				continue;
			CString ext = sub.Mid(pos);
			if (ext.IsEmpty())
				continue;
			ext.MakeLower();
			for (int i = 0; i < m_rules.GetCount(); i++)
			{
				if (ext == m_rules.GetAt(i))
				{
					nIndex=m_path.InsertItem( 0,_T("") );

					m_path.SetItemText( nIndex, 1, sub.Right(sub.GetLength()-m_searchpath.GetLength()-1));  
					continue;
				}
			}
		}
	} while (FindNextFile(hfind, &filedir));
	FindClose(hfind);
	m_path.SetRedraw(TRUE);//显示 
	return TRUE;
}

void CEnableLogDlg::OnBnClickedSelectall()
{
	// TODO: Add your control notification handler code here
	static BOOL g_isselectall=TRUE;
	int nCount = m_path.GetItemCount();
	if(g_isselectall)
	{
		for (int i = 0; i < nCount; i++)
		{
			m_path.SetCheck(i);
		}
		g_isselectall=FALSE;
	}
	else
	{
		for (int i = 0; i < nCount; i++)
		{
			m_path.SetCheck(i,FALSE);
		}
		g_isselectall=TRUE;
	}
	m_path.SetFocus();
}
