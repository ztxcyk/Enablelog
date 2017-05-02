
// EnableLogDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxeditbrowsectrl.h"


// CEnableLogDlg dialog
class CEnableLogDlg : public CDialogEx
{
// Construction
public:
	CEnableLogDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ENABLELOG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBcloselog2();
	afx_msg void OnBnClickedBcloselog();
	afx_msg void OnBnClickedBopenlog();
	afx_msg void OnBnClickedlog();
	void Initstr(void);
	BOOL enabledbg();
	CListCtrl m_path;
	CButton m_open;
	CButton m_close;
	CButton m_mode;
	CMFCEditBrowseCtrl m_SearchPath;
	afx_msg void OnBnClickedBfind();
	afx_msg void OnBnClickedBexport();
	static UINT  SearchThread(LPVOID lParam); //搜索线程
private:
	BOOL Findfile(const CString path);//递归搜索
private:
	// 用来保存规则的数组
	CStringArray m_rules;
	CString m_searchpath;
public:
	afx_msg void OnBnClickedSelectall();
};
