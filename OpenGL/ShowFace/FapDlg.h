#if !defined(AFX_FAPDLG_H__F94BB4FD_24F4_4BB3_92D3_708230C89180__INCLUDED_)
#define AFX_FAPDLG_H__F94BB4FD_24F4_4BB3_92D3_708230C89180__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FapDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFapDlg dialog

class CFapDlg : public CDialog
{
// Construction
public:
	void RefreshDlg();
	BOOL bDSet;
	int nTab;
	void RefreshDraw();
	BOOL Create();
	CFapDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFapDlg)
	enum { IDD = IDD_FAPDLG };
	CSliderCtrl	m_f9;
	CSliderCtrl	m_f2;
	CSliderCtrl	m_f12;
	CSliderCtrl	m_f11;
	CSliderCtrl	m_f10;
	CSliderCtrl	m_f1;
	CSliderCtrl	m_f8;
	CSliderCtrl	m_f7;
	CSliderCtrl	m_f6;
	CSliderCtrl	m_f5;
	CSliderCtrl	m_f4;
	CSliderCtrl	m_f3;
	CTabCtrl	m_tab;
	float		m_v1;
	float		m_v2;
	float		m_v3;
	float		m_v4;
	float		m_v5;
	float		m_v6;
	float		m_v7;
	float		m_v8;
	float		m_v9;
	float		m_v10;
	float		m_v11;
	float		m_v12;
	CString	m_l1;
	CString	m_l2;
	CString	m_l3;
	CString	m_l4;
	CString	m_l5;
	CString	m_l6;
	CString	m_l7;
	CString	m_l8;
	CString	m_l9;
	CString	m_l10;
	CString	m_l11;
	CString	m_l12;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFapDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	int		m_nID;					//For Modalless
	CWnd * m_pParent;				//For Modalless
	
	// Generated message map functions
	//{{AFX_MSG(CFapDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawFapsld3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawFapsld4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawFapsld5(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawFapsld6(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawFapsld7(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawFapsld8(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawFapsld1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawFapsld2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawFapsld9(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawFapsld10(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawFapsld11(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawFapsld12(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FAPDLG_H__F94BB4FD_24F4_4BB3_92D3_708230C89180__INCLUDED_)
