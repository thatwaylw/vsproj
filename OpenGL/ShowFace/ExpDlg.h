#if !defined(AFX_EXPDLG_H__E5F16F1C_1F08_4B56_BCBA_5C9386686833__INCLUDED_)
#define AFX_EXPDLG_H__E5F16F1C_1F08_4B56_BCBA_5C9386686833__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExpDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExpDlg dialog

class CExpDlg : public CDialog
{
// Construction
public:
	void ReduceOthers(int n);
	void RefreshDraw();
	BOOL bDSet;
	BOOL Create();
	CExpDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CExpDlg)
	enum { IDD = IDD_EXPDLG };
	CSliderCtrl	m_s6;
	CSliderCtrl	m_s5;
	CSliderCtrl	m_s4;
	CSliderCtrl	m_s3;
	CSliderCtrl	m_s2;
	CSliderCtrl	m_s1;
	float	m_exp1;
	float	m_exp2;
	float	m_exp3;
	float	m_exp4;
	float	m_exp5;
	float	m_exp6;
	BOOL	m_bRd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	int		m_nID;					//For Modalless
	CWnd * m_pParent;				//For Modalless

	// Generated message map functions
	//{{AFX_MSG(CExpDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider5(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawSlider6(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClrexp();
	afx_msg void OnReduce();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPDLG_H__E5F16F1C_1F08_4B56_BCBA_5C9386686833__INCLUDED_)
