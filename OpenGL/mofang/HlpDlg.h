#if !defined(AFX_HLPDLG_H__98A57CC1_8C0E_11D4_B7B3_5254AB1984FC__INCLUDED_)
#define AFX_HLPDLG_H__98A57CC1_8C0E_11D4_B7B3_5254AB1984FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HlpDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHlpDlg dialog

class CHlpDlg : public CDialog
{
// Construction
public:
	CHlpDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHlpDlg)
	enum { IDD = IDD_DIALOG1 };
	CString	m_edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHlpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHlpDlg)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HLPDLG_H__98A57CC1_8C0E_11D4_B7B3_5254AB1984FC__INCLUDED_)
