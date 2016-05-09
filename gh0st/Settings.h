#if !defined(AFX_SETTINGS_H__CA28388C_8306_4FD8_84E0_AE175B7C76C8__INCLUDED_)
#define AFX_SETTINGS_H__CA28388C_8306_4FD8_84E0_AE175B7C76C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Settings.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettings dialog

class CSettings : public CDialog
{
// Construction
public:
	CSettings(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSettings)
	enum { IDD = IDD_SETTINGS };
	UINT	m_max_connections;
	BOOL	m_connect_auto;
	BOOL	m_bIsDisablePopTips;
	UINT	m_listen_port;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettings)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettings)
	afx_msg void OnApply();
	afx_msg void OnDisablePoptips();
	afx_msg void OnConnectAuto();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGS_H__CA28388C_8306_4FD8_84E0_AE175B7C76C8__INCLUDED_)
