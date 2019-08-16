#if !defined(AFX_VISDLG_H__C310BC80_2EFE_47F2_BB71_C389FE3A8E04__INCLUDED_)
#define AFX_VISDLG_H__C310BC80_2EFE_47F2_BB71_C389FE3A8E04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VisDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVisDlg dialog

class CVisDlg : public CDialog
{
// Construction
public:
	void RefreshDraw();
	BOOL Create();
	CVisDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVisDlg)
	enum { IDD = IDD_VISDLG };
	CListBox	m_viss;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	int		m_nID;					//For Modalless
	CWnd * m_pParent;				//For Modalless
	
	// Generated message map functions
	//{{AFX_MSG(CVisDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSavevis();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeVisems();
	afx_msg void OnSavevistab();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISDLG_H__C310BC80_2EFE_47F2_BB71_C389FE3A8E04__INCLUDED_)
