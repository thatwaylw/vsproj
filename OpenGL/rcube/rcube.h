// rcube.h : main header file for the RCUBE application
//

#if !defined(AFX_RCUBE_H__57539885_8347_11D4_B7B3_5254AB1984FC__INCLUDED_)
#define AFX_RCUBE_H__57539885_8347_11D4_B7B3_5254AB1984FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRcubeApp:
// See rcube.cpp for the implementation of this class
//

class CRcubeApp : public CWinApp
{
public:
	CRcubeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRcubeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CRcubeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RCUBE_H__57539885_8347_11D4_B7B3_5254AB1984FC__INCLUDED_)
