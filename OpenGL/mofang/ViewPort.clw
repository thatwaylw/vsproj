; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CViewPortView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ViewPort.h"
LastPage=0

ClassCount=6
Class1=CViewPortApp
Class2=CViewPortDoc
Class3=CViewPortView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Resource2=IDR_MAINFRAME
Class6=CHlpDlg
Resource3=IDD_DIALOG1

[CLS:CViewPortApp]
Type=0
HeaderFile=ViewPort.h
ImplementationFile=ViewPort.cpp
Filter=N

[CLS:CViewPortDoc]
Type=0
HeaderFile=ViewPortDoc.h
ImplementationFile=ViewPortDoc.cpp
Filter=N

[CLS:CViewPortView]
Type=0
HeaderFile=ViewPortView.h
ImplementationFile=ViewPortView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=IDC_EDIT1


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=IDM_HLP
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=ViewPort.cpp
ImplementationFile=ViewPort.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308865

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=IDM_UNDO
Command17=IDM_RESET
Command18=IDM_SLOW
Command19=ID_SSZ_Q
Command20=ID_SSZ_Z
Command21=ID_SSZ_H
Command22=ID_SSZ_ALL
Command23=ID_NSZ_Q
Command24=ID_NSZ_Z
Command25=ID_NSZ_H
Command26=ID_NSZ_ALL
Command27=ID_SZ_LEFT
Command28=ID_SZ_MID
Command29=ID_SZ_RIGHT
Command30=ID_SZ_ALL
Command31=ID_XZ_LEFT
Command32=ID_XZ_MID
Command33=ID_XZ_RIGHT
Command34=ID_XZ_ALL
Command35=ID_ZZ_S
Command36=ID_ZZ_Z
Command37=ID_ZZ_X
Command38=ID_ZZ_ALL
Command39=ID_YZ_S
Command40=ID_YZ_Z
Command41=ID_YZ_X
Command42=ID_YZ_ALL
Command43=ID_APP_ABOUT
Command44=IDM_HLP
CommandCount=44

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=IDM_SLOW
Command3=ID_FILE_NEW
Command4=ID_FILE_OPEN
Command5=ID_FILE_PRINT
Command6=IDM_RESET
Command7=ID_FILE_SAVE
Command8=IDM_UNDO
Command9=ID_EDIT_PASTE
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_EDIT_CUT
Command17=ID_EDIT_UNDO
CommandCount=17

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=IDM_SLOW
Command10=IDM_HLP
CommandCount=10

[DLG:IDD_DIALOG1]
Type=1
Class=CHlpDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDC_STATIC,static,1342308865
Control3=IDC_EDIT1,edit,1350633604

[CLS:CHlpDlg]
Type=0
HeaderFile=HlpDlg.h
ImplementationFile=HlpDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CHlpDlg

