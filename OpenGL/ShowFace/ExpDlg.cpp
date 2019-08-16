// ExpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ViewPort.h"
#include "ExpDlg.h"

#include "ViewPortView.h"
#include "DoFap.h"
#include "DoExpVisem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExpDlg dialog


CExpDlg::CExpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExpDlg::IDD, pParent)
{
	m_pParent=pParent;				//For Modalless
	m_nID=CExpDlg::IDD;				//For Modalless
	bDSet = FALSE;
	//{{AFX_DATA_INIT(CExpDlg)
	m_exp1 = exps[0];
	m_exp2 = exps[1];
	m_exp3 = exps[2];
	m_exp4 = exps[3];
	m_exp5 = exps[4];
	m_exp6 = exps[5];
	m_bRd = FALSE;
	//}}AFX_DATA_INIT
}


void CExpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExpDlg)
	DDX_Control(pDX, IDC_SLIDER6, m_s6);
	DDX_Control(pDX, IDC_SLIDER5, m_s5);
	DDX_Control(pDX, IDC_SLIDER4, m_s4);
	DDX_Control(pDX, IDC_SLIDER3, m_s3);
	DDX_Control(pDX, IDC_SLIDER2, m_s2);
	DDX_Control(pDX, IDC_SLIDER1, m_s1);
	DDX_Text(pDX, IDC_EDIT1, m_exp1);
	DDX_Text(pDX, IDC_EDIT2, m_exp2);
	DDX_Text(pDX, IDC_EDIT3, m_exp3);
	DDX_Text(pDX, IDC_EDIT4, m_exp4);
	DDX_Text(pDX, IDC_EDIT5, m_exp5);
	DDX_Text(pDX, IDC_EDIT6, m_exp6);
	DDX_Check(pDX, IDC_REDUCE, m_bRd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExpDlg, CDialog)
	//{{AFX_MSG_MAP(CExpDlg)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnCustomdrawSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, OnCustomdrawSlider2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, OnCustomdrawSlider3)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER4, OnCustomdrawSlider4)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER5, OnCustomdrawSlider5)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER6, OnCustomdrawSlider6)
	ON_BN_CLICKED(IDC_CLREXP, OnClrexp)
	ON_BN_CLICKED(IDC_REDUCE, OnReduce)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExpDlg message handlers

void CExpDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	((CViewPortView *)m_pParent)->m_pExpDlg = NULL;
	DestroyWindow();
	
//	CDialog::OnCancel();
}

BOOL CExpDlg::Create()
{
	return(CDialog::Create(m_nID,m_pParent));
}

void CExpDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
//	CDialog::PostNcDestroy();
}

BOOL CExpDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	bDSet = TRUE;
	m_s1.SetRange(0, 100, TRUE);	m_s1.SetPos((int)(exps[0]));
	m_s2.SetRange(0, 100, TRUE);	m_s2.SetPos((int)(exps[1]));
	m_s3.SetRange(0, 100, TRUE);	m_s3.SetPos((int)(exps[2]));
	m_s4.SetRange(0, 100, TRUE);	m_s4.SetPos((int)(exps[3]));
	m_s5.SetRange(0, 100, TRUE);	m_s5.SetPos((int)(exps[4]));
	m_s6.SetRange(0, 100, TRUE);	m_s6.SetPos((int)(exps[5]));
	bDSet = FALSE;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CExpDlg::RefreshDraw()
{
	((CViewPortView *)m_pParent)->ResetFaceModel();
	ResetFaps();
	
	DoExpression();
	DoVisem();
	
	if(((CViewPortView *)m_pParent)->m_pFapDlg)
		((CViewPortView *)m_pParent)->m_pFapDlg->RefreshDlg();
	
	DoFaps();
	((CViewPortView *)m_pParent)->ReDrawScene();	
}

void CExpDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	bDSet = TRUE;
	if(m_exp1 != exps[0])
	{
		exps[0] = m_exp1;
		m_s1.SetPos((int)(m_exp1));
		ReduceOthers(0);
	}
	else if(m_exp2 != exps[1])
	{
		exps[1] = m_exp2;
		m_s2.SetPos((int)(m_exp2));
		ReduceOthers(1);
	}
	else if(m_exp3 != exps[2])
	{
		exps[2] = m_exp3;
		m_s3.SetPos((int)(m_exp3));
		ReduceOthers(2);
	}
	else if(m_exp4 != exps[3])
	{
		exps[3] = m_exp4;
		m_s4.SetPos((int)(m_exp4));
		ReduceOthers(3);
	}
	else if(m_exp5 != exps[4])
	{
		exps[4] = m_exp5;
		m_s5.SetPos((int)(m_exp5));
		ReduceOthers(4);
	}
	else if(m_exp6 != exps[5])
	{
		exps[5] = m_exp6;
		m_s6.SetPos((int)(m_exp6));
		ReduceOthers(5);
	}
	bDSet = FALSE;
	
	RefreshDraw();	
	
	CEdit * pe = (CEdit *)GetFocus();
	pe->SetSel(0, 6);
	
	//	CDialog::OnOK();
}


void CExpDlg::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!bDSet)	
	{
		exps[0] = (float)(m_s1.GetPos());
		m_exp1 = exps[0];
		UpdateData(FALSE);
		ReduceOthers(0);
		RefreshDraw();
	}
	*pResult = 0;
}

void CExpDlg::OnCustomdrawSlider2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!bDSet)	
	{
		exps[1] = (float)(m_s2.GetPos());
		m_exp2 = exps[1];
		UpdateData(FALSE);
		ReduceOthers(1);
		RefreshDraw();
	}
	*pResult = 0;
}

void CExpDlg::OnCustomdrawSlider3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!bDSet)	
	{
		exps[2] = (float)(m_s3.GetPos());
		m_exp3 = exps[2];
		UpdateData(FALSE);
		ReduceOthers(2);
		RefreshDraw();
	}
	*pResult = 0;
}

void CExpDlg::OnCustomdrawSlider4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!bDSet)	
	{
		exps[3] = (float)(m_s4.GetPos());
		m_exp4 = exps[3];
		UpdateData(FALSE);
		ReduceOthers(3);
		RefreshDraw();
	}
	*pResult = 0;
}

void CExpDlg::OnCustomdrawSlider5(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!bDSet)	
	{
		exps[4] = (float)(m_s5.GetPos());
		m_exp5 = exps[4];
		UpdateData(FALSE);
		ReduceOthers(4);
		RefreshDraw();
	}
	*pResult = 0;
}

void CExpDlg::OnCustomdrawSlider6(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(!bDSet)	
	{
		exps[5] = (float)(m_s6.GetPos());
		m_exp6 = exps[5];
		UpdateData(FALSE);
		ReduceOthers(5);
		RefreshDraw();
	}
	*pResult = 0;
}

void CExpDlg::OnClrexp() 
{
	// TODO: Add your control notification handler code here
	bDSet = TRUE;
	m_s1.SetPos(0);		m_exp1 = 0.0f;		exps[0] = 0.0f;
	m_s2.SetPos(0);		m_exp2 = 0.0f;		exps[1] = 0.0f;
	m_s3.SetPos(0);		m_exp3 = 0.0f;		exps[2] = 0.0f;
	m_s4.SetPos(0);		m_exp4 = 0.0f;		exps[3] = 0.0f;
	m_s5.SetPos(0);		m_exp5 = 0.0f;		exps[4] = 0.0f;
	m_s6.SetPos(0);		m_exp6 = 0.0f;		exps[5] = 0.0f;
	bDSet = FALSE;
	
	UpdateData(FALSE);
	RefreshDraw();
	
}

void CExpDlg::OnReduce() 
{
	// TODO: Add your control notification handler code here
	int i;
	float total;
	UpdateData(TRUE);
	
	if(m_bRd)
	{
		total = 0.0f;
		for(i=0; i<6; i++)
			total += exps[i];

		total /= 100.0f;		if(total == 0.0f)	return;
		for(i=0; i<6; i++)
			exps[i] /= total;

		bDSet = TRUE;
		m_s1.SetPos((int)(exps[0]));	m_exp1 = exps[0];
		m_s2.SetPos((int)(exps[1]));	m_exp2 = exps[1];
		m_s3.SetPos((int)(exps[2]));	m_exp3 = exps[2];
		m_s4.SetPos((int)(exps[3]));	m_exp4 = exps[3];
		m_s5.SetPos((int)(exps[4]));	m_exp5 = exps[4];
		m_s6.SetPos((int)(exps[5]));	m_exp6 = exps[5];
		bDSet = FALSE;

		UpdateData(FALSE);
		RefreshDraw();
	}
}

void CExpDlg::ReduceOthers(int n)
{
	float other, total;
	int i;

	if(!m_bRd)		return;

	other = 100.0f - exps[n];
	total = 0.0f;

	for(i=0; i<6; i++)
	{
		if(i == n)	continue;
		total += exps[i];
	}
	
	if(total == 0.0f)
	{
		for(i=0; i<6; i++)
		{
			if(i == n)	continue;
			exps[i] = other / 5;
		}
	}
	else
	{
		for(i=0; i<6; i++)
		{
			if(i == n)	continue;
			exps[i] *= other;
			exps[i] /= total;
		}
	}	

	bDSet = TRUE;
	m_s1.SetPos((int)(exps[0]));	m_exp1 = exps[0];
	m_s2.SetPos((int)(exps[1]));	m_exp2 = exps[1];
	m_s3.SetPos((int)(exps[2]));	m_exp3 = exps[2];
	m_s4.SetPos((int)(exps[3]));	m_exp4 = exps[3];
	m_s5.SetPos((int)(exps[4]));	m_exp5 = exps[4];
	m_s6.SetPos((int)(exps[5]));	m_exp6 = exps[5];
	bDSet = FALSE;
	
	UpdateData(FALSE);
}
