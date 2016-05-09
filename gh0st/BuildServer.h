#if !defined(AFX_BUILDSERVER_H__C125C3E7_59DD_4873_8E2E_CD783EDF2831__INCLUDED_)
#define AFX_BUILDSERVER_H__C125C3E7_59DD_4873_8E2E_CD783EDF2831__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BuildServer.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CBuildServer dialog

class CBuildServer : public CDialog
{
// Construction
public:
	CBuildServer(CWnd* pParent = NULL);   // standard constructor
    void OnChangeConfig();
	static	DWORD WINAPI TestMaster(LPVOID lparam);
// Dialog Data
	//{{AFX_DATA(CBuildServer)
	enum { IDD = IDD_BUILD_SERVER };
	CString	m_remote_port;
	CString	m_remote_host;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBuildServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBuildServer)
	afx_msg void OnTestMaster();
	afx_msg void OnEnableHttp();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeRemoteHost();
	afx_msg void OnChangeRemotePort();
	afx_msg void OnBuild();
	afx_msg void OnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUILDSERVER_H__C125C3E7_59DD_4873_8E2E_CD783EDF2831__INCLUDED_)
