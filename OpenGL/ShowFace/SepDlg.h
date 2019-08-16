#if !defined(AFX_SEPDLG_H__FEFFD274_96A8_4B17_ADD5_FAD02B339ACC__INCLUDED_)
#define AFX_SEPDLG_H__FEFFD274_96A8_4B17_ADD5_FAD02B339ACC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SepDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSepDlg dialog

class CSepDlg : public CDialog
{
// Construction
public:
	void RefreshView();
	BOOL Create();
	CSepDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSepDlg)
	enum { IDD = IDD_SEPDLG };
	BOOL	m_ck1;
	BOOL	m_ck2;
	BOOL	m_ck3;
	BOOL	m_ck4;
	BOOL	m_ck5;
	BOOL	m_ck6;
	BOOL	m_ck7;
	BOOL	m_ck8;
	BOOL	m_ck9;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSepDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	int		m_nID;					//For Modalless
	CWnd * m_pParent;				//For Modalless
	
	// Generated message map functions
	//{{AFX_MSG(CSepDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelall();
	afx_msg void OnSelnone();
	afx_msg void OnCnsel();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnCheck6();
	afx_msg void OnCheck7();
	afx_msg void OnCheck8();
	afx_msg void OnCheck9();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEPDLG_H__FEFFD274_96A8_4B17_ADD5_FAD02B339ACC__INCLUDED_)
