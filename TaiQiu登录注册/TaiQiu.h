// TaiQiu.h : TaiQiu Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // ������


// CTaiQiuApp:
// �йش����ʵ�֣������ TaiQiu.cpp
//

class CTaiQiuApp : public CWinApp
{
public:
	CTaiQiuApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTaiQiuApp theApp;
