// TaiQiu.h : TaiQiu 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // 主符号


// CTaiQiuApp:
// 有关此类的实现，请参阅 TaiQiu.cpp
//

class CTaiQiuApp : public CWinApp
{
public:
	CTaiQiuApp();


// 重写
public:
	virtual BOOL InitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTaiQiuApp theApp;
