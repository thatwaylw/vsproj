#if !defined(AFX_PLAYANIDLG_H__0894916C_87C1_46EA_BEB2_B579D4149CCF__INCLUDED_)
#define AFX_PLAYANIDLG_H__0894916C_87C1_46EA_BEB2_B579D4149CCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlayAniDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPlayAniDlg dialog
#include "DoFap.h"
#include "DoExpVisem.h"

#define MAX_FRMS 2000

typedef struct{
	int aniv1;
	int aniv2;
	int anivb;
	int anie1;
	int aniev1;
	int anie2;
	int aniev2;
	int anifaps[NO_FAPS];
	int anitime;
}AniParam, * pAniParam;

class CPlayAniDlg : public CDialog
{
// Construction
public:
	char WavFile[50];
	int  SwapTmp(int top);
	void TestSection();
	void InsertFrm();
	void ParseFrm(pAniParam p);
	void PlayFrame();
	void PlayAniFile();
	void ReadAniFile();
	void ReadFrame(pAniParam pa, FILE * fp);
	BOOL	bDSet;
	BOOL	bPlay;
	CString FileName;
	char trash[BUFFER_SIZE];
	BOOL	bIntpl;
	int		frm_len, min_len;
	float	intpl_fac;
	
	FILE * fp_swp;
	int	   sec_top, sec_btm;
	
	BOOL Create();
	CPlayAniDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPlayAniDlg)
	enum { IDD = IDD_PLAYANI_DLG };
	CSliderCtrl	m_sfrm;
	CString	m_totalfrm;
	int		m_curfrm;
	CString	m_playinfo;
	float	m_fdet;
	//}}AFX_DATA
private:
	AniParam anip[MAX_FRMS];
	AniParam top_anip, btm_anip;
	int total_frm;
	int cur_Frm;
	long play_t;
	int skip_frm;
	int play_frm;
	int idx;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayAniDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	int		m_nID;					//For Modalless
	CWnd * m_pParent;				//For Modalless
	
	CBitmapButton m_BtnPlay;
	CBitmapButton m_BtnPause;
	CBitmapButton m_BtnStop;
	// Generated message map functions
	//{{AFX_MSG(CPlayAniDlg)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnplay();
	afx_msg void OnBtnpause();
	afx_msg void OnBtnstop();
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGoto();
	afx_msg void OnPrevFrm();
	afx_msg void OnNextFrm();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLAYANIDLG_H__0894916C_87C1_46EA_BEB2_B579D4149CCF__INCLUDED_)
