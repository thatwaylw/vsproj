// TestRot.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������


// CTestRotApp:
// �йش����ʵ�֣������ TestRot.cpp
//

class CTestRotApp : public CWinApp
{
public:
	CTestRotApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestRotApp theApp;
