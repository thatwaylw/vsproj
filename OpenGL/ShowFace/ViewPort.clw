; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPlayAniDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ViewPort.h"
LastPage=0

ClassCount=10
Class1=CViewPortApp
Class2=CViewPortDoc
Class3=CViewPortView
Class4=CMainFrame

ResourceCount=7
Resource1=IDD_ABOUTBOX
Class5=CAboutDlg
Resource2=IDD_SEPDLG
Class6=CSepDlg
Resource3=IDD_FAPDLG
Class7=CFapDlg
Resource4=IDD_EXPDLG
Class8=CExpDlg
Resource5=IDR_MAINFRAME
Class9=CVisDlg
Resource6=IDD_VISDLG
Class10=CPlayAniDlg
Resource7=IDD_PLAYANI_DLG

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
LastObject=CViewPortView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_PLAY_ANI
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
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_ANI_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_PLAY_ANI
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
Command17=ID_MGRID
Command18=ID_MTEXTURE
Command19=ID_MROTT
Command20=ID_MORIG
Command21=ID_MSEP
Command22=ID_MFAP
Command23=ID_MEXP
Command24=ID_MVIS
CommandCount=24

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_FILE_NEW
Command3=ID_ANI_FILE_OPEN
Command4=ID_FILE_PRINT
Command5=ID_FILE_SAVE
Command6=ID_EDIT_PASTE
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_PLAY_ANI
Command14=ID_EDIT_UNDO
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_ANI_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_PLAY_ANI
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_MGRID
Command10=ID_MTEXTURE
Command11=ID_MROTT
Command12=ID_MORIG
Command13=ID_MSEP
Command14=ID_MFAP
Command15=ID_MEXP
Command16=ID_MVIS
CommandCount=16

[DLG:IDD_SEPDLG]
Type=1
Class=CSepDlg
ControlCount=13
Control1=IDC_CHECK1,button,1342242819
Control2=IDC_STATIC,button,1342177287
Control3=IDC_CHECK2,button,1342242819
Control4=IDC_CHECK3,button,1342242819
Control5=IDC_CHECK4,button,1342242819
Control6=IDC_CHECK5,button,1342242819
Control7=IDC_CHECK6,button,1342242819
Control8=IDC_CHECK7,button,1342242819
Control9=IDC_CHECK8,button,1342242819
Control10=IDC_CHECK9,button,1342242819
Control11=IDC_SELALL,button,1342242816
Control12=IDC_SELNONE,button,1342242816
Control13=IDC_CNSEL,button,1342242816

[CLS:CSepDlg]
Type=0
HeaderFile=SepDlg.h
ImplementationFile=SepDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CHECK1
VirtualFilter=dWC

[DLG:IDD_FAPDLG]
Type=1
Class=CFapDlg
ControlCount=38
Control1=IDC_FAPSLD1,msctls_trackbar32,1342242840
Control2=IDC_FAPSLD2,msctls_trackbar32,1342242840
Control3=IDC_FAPSLD3,msctls_trackbar32,1342242840
Control4=IDC_FAPSLD4,msctls_trackbar32,1342242840
Control5=IDC_FAPSLD5,msctls_trackbar32,1342242840
Control6=IDC_FAPSLD6,msctls_trackbar32,1342242840
Control7=IDC_FAPSLD7,msctls_trackbar32,1342242840
Control8=IDC_FAPSLD8,msctls_trackbar32,1342242840
Control9=IDC_FAPSLD9,msctls_trackbar32,1342242840
Control10=IDC_FAPSLD10,msctls_trackbar32,1342242840
Control11=IDC_FAPSLD11,msctls_trackbar32,1342242840
Control12=IDC_FAPSLD12,msctls_trackbar32,1342242840
Control13=IDC_FAPVALUE1,edit,1350631552
Control14=IDC_FAPVALUE2,edit,1350631552
Control15=IDC_FAPVALUE3,edit,1350631552
Control16=IDC_FAPVALUE4,edit,1350631552
Control17=IDC_FAPVALUE5,edit,1350631552
Control18=IDC_FAPVALUE6,edit,1350631552
Control19=IDC_FAPVALUE7,edit,1350631552
Control20=IDC_FAPVALUE8,edit,1350631552
Control21=IDC_FAPVALUE9,edit,1350631552
Control22=IDC_FAPVALUE10,edit,1350631552
Control23=IDC_FAPVALUE11,edit,1350631552
Control24=IDC_FAPVALUE12,edit,1350631552
Control25=IDC_L1,static,1342312960
Control26=IDC_L2,static,1342312960
Control27=IDC_L3,static,1342312960
Control28=IDC_L4,static,1342312960
Control29=IDC_L5,static,1342312960
Control30=IDC_L6,static,1342312960
Control31=IDC_L7,static,1342312960
Control32=IDC_L8,static,1342312960
Control33=IDC_L9,static,1342312960
Control34=IDC_L10,static,1342312960
Control35=IDC_L11,static,1342312960
Control36=IDC_L12,static,1342312960
Control37=IDC_TAB1,SysTabControl32,1342177280
Control38=IDC_CLEAR,button,1342242816

[CLS:CFapDlg]
Type=0
HeaderFile=FapDlg.h
ImplementationFile=FapDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_FAPSLD1
VirtualFilter=dWC

[DLG:IDD_EXPDLG]
Type=1
Class=CExpDlg
ControlCount=26
Control1=IDC_SLIDER1,msctls_trackbar32,1342242842
Control2=IDC_SLIDER2,msctls_trackbar32,1342242842
Control3=IDC_SLIDER3,msctls_trackbar32,1342242842
Control4=IDC_SLIDER4,msctls_trackbar32,1342242842
Control5=IDC_SLIDER5,msctls_trackbar32,1342242842
Control6=IDC_SLIDER6,msctls_trackbar32,1342242842
Control7=IDC_EDIT1,edit,1350631552
Control8=IDC_EDIT2,edit,1350631552
Control9=IDC_EDIT3,edit,1350631552
Control10=IDC_EDIT4,edit,1350631552
Control11=IDC_EDIT5,edit,1350631552
Control12=IDC_EDIT6,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_CLREXP,button,1342242816
Control20=IDC_STATIC,static,1342177296
Control21=IDC_STATIC,static,1342177297
Control22=IDC_STATIC,static,1342177297
Control23=IDC_STATIC,static,1342177297
Control24=IDC_STATIC,static,1342177297
Control25=IDC_STATIC,static,1342177297
Control26=IDC_REDUCE,button,1342242819

[CLS:CExpDlg]
Type=0
HeaderFile=ExpDlg.h
ImplementationFile=ExpDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CExpDlg
VirtualFilter=dWC

[DLG:IDD_VISDLG]
Type=1
Class=CVisDlg
ControlCount=3
Control1=IDC_VISEMS,listbox,1352728833
Control2=IDC_SAVEVIS,button,1342242816
Control3=IDC_SAVEVISTAB,button,1342242816

[CLS:CVisDlg]
Type=0
HeaderFile=VisDlg.h
ImplementationFile=VisDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_VISEMS
VirtualFilter=dWC

[DLG:IDD_PLAYANI_DLG]
Type=1
Class=CPlayAniDlg
ControlCount=13
Control1=IDC_SLIDER1,msctls_trackbar32,1342242840
Control2=IDC_BTNPLAY,button,1342242827
Control3=IDC_BTNPAUSE,button,1342242827
Control4=IDC_BTNSTOP,button,1342242827
Control5=IDC_STATIC,static,1342308864
Control6=IDC_TOTALFRM,static,1342308352
Control7=IDC_CUR_FRM,edit,1350631552
Control8=IDC_GOTO,button,1342242816
Control9=IDC_PREV_FRM,button,1342242816
Control10=IDC_NEXT_FRM,button,1342242816
Control11=IDC_PLAYINFO,static,1342312448
Control12=IDC_PLAY_SPEED,edit,1350631552
Control13=IDC_STATIC,static,1342308864

[CLS:CPlayAniDlg]
Type=0
HeaderFile=PlayAniDlg.h
ImplementationFile=PlayAniDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CPlayAniDlg
VirtualFilter=dWC

