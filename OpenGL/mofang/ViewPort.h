// ViewPort.h : main header file for the VIEWPORT application
//

#if !defined(AFX_VIEWPORT_H__E4FB22ED_82A7_11D4_B7B3_5254AB1984FC__INCLUDED_)
#define AFX_VIEWPORT_H__E4FB22ED_82A7_11D4_B7B3_5254AB1984FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CViewPortApp:
// See ViewPort.cpp for the implementation of this class
//

class CViewPortApp : public CWinApp
{
public:
	CViewPortApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewPortApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CViewPortApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWPORT_H__E4FB22ED_82A7_11D4_B7B3_5254AB1984FC__INCLUDED_)
