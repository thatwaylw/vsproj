// SepDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ViewPort.h"
#include "SepDlg.h"

#include "ViewPortView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSepDlg dialog

#ifndef GLOBAL_DEF
#define GLOBAL_DEF
#include "GlobalDef.h"
#endif
extern BOOL	ShowSeps[NO_FACE_REGIONS];

CSepDlg::CSepDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSepDlg::IDD, pParent)
{
	m_pParent=pParent;				//For Modalless
	m_nID=CSepDlg::IDD;				//For Modalless
	
	//{{AFX_DATA_INIT(CSepDlg)
	m_ck1 = ShowSeps[0];
	m_ck2 = ShowSeps[1];
	m_ck3 = ShowSeps[2];
	m_ck4 = ShowSeps[3];
	m_ck5 = ShowSeps[4];
	m_ck6 = ShowSeps[5];
	m_ck7 = ShowSeps[7];
	m_ck8 = ShowSeps[8];
	m_ck9 = ShowSeps[9];
	//}}AFX_DATA_INIT
}


void CSepDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSepDlg)
	DDX_Check(pDX, IDC_CHECK1, m_ck1);
	DDX_Check(pDX, IDC_CHECK2, m_ck2);
	DDX_Check(pDX, IDC_CHECK3, m_ck3);
	DDX_Check(pDX, IDC_CHECK4, m_ck4);
	DDX_Check(pDX, IDC_CHECK5, m_ck5);
	DDX_Check(pDX, IDC_CHECK6, m_ck6);
	DDX_Check(pDX, IDC_CHECK7, m_ck7);
	DDX_Check(pDX, IDC_CHECK8, m_ck8);
	DDX_Check(pDX, IDC_CHECK9, m_ck9);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSepDlg, CDialog)
	//{{AFX_MSG_MAP(CSepDlg)
	ON_BN_CLICKED(IDC_SELALL, OnSelall)
	ON_BN_CLICKED(IDC_SELNONE, OnSelnone)
	ON_BN_CLICKED(IDC_CNSEL, OnCnsel)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_BN_CLICKED(IDC_CHECK8, OnCheck8)
	ON_BN_CLICKED(IDC_CHECK9, OnCheck9)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSepDlg message handlers

void CSepDlg::OnOK() 
{
	// TODO: Add extra validation here
//	CDialog::OnOK();
}

void CSepDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	((CViewPortView *)m_pParent)->m_pSepDlg = NULL;
	DestroyWindow();
	
//	CDialog::OnCancel();
}

BOOL CSepDlg::Create()
{
	return(CDialog::Create(m_nID,m_pParent));
}

void CSepDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;	
//	CDialog::PostNcDestroy();
}

void CSepDlg::OnSelall() 
{
	// TODO: Add your control notification handler code here
	m_ck1 = TRUE;
	m_ck2 = TRUE;
	m_ck3 = TRUE;
	m_ck4 = TRUE;
	m_ck5 = TRUE;
	m_ck6 = TRUE;
	m_ck7 = TRUE;
	m_ck8 = TRUE;
	m_ck9 = TRUE;
	UpdateData(FALSE);
	RefreshView();
}

void CSepDlg::OnSelnone() 
{
	// TODO: Add your control notification handler code here
	m_ck1 = FALSE;
	m_ck2 = FALSE;
	m_ck3 = FALSE;
	m_ck4 = FALSE;
	m_ck5 = FALSE;
	m_ck6 = FALSE;
	m_ck7 = FALSE;
	m_ck8 = FALSE;
	m_ck9 = FALSE;
	UpdateData(FALSE);
	RefreshView();
}

void CSepDlg::OnCnsel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_ck1 = !m_ck1;
	m_ck2 = !m_ck2;
	m_ck3 = !m_ck3;
	m_ck4 = !m_ck4;
	m_ck5 = !m_ck5;
	m_ck6 = !m_ck6;
	m_ck7 = !m_ck7;
	m_ck8 = !m_ck8;
	m_ck9 = !m_ck9;
	UpdateData(FALSE);
	RefreshView();
}

void CSepDlg::OnCheck1() 
{
	UpdateData(TRUE);
	ShowSeps[0] = m_ck1;
	((CViewPortView *)m_pParent)->DrawScene();	
}

void CSepDlg::OnCheck2() 
{
	UpdateData(TRUE);
	ShowSeps[1] = m_ck2;
	((CViewPortView *)m_pParent)->DrawScene();	
}

void CSepDlg::OnCheck3() 
{
	UpdateData(TRUE);
	ShowSeps[2] = m_ck3;
	((CViewPortView *)m_pParent)->DrawScene();	
}

void CSepDlg::OnCheck4() 
{
	UpdateData(TRUE);
	ShowSeps[3] = m_ck4;
	((CViewPortView *)m_pParent)->DrawScene();	
}

void CSepDlg::OnCheck5() 
{
	UpdateData(TRUE);
	ShowSeps[4] = m_ck5;
	((CViewPortView *)m_pParent)->DrawScene();	
}

void CSepDlg::OnCheck6() 
{
	UpdateData(TRUE);
	ShowSeps[5] = m_ck6;
	ShowSeps[6] = m_ck6;
	((CViewPortView *)m_pParent)->DrawScene();	
}

void CSepDlg::OnCheck7() 
{
	UpdateData(TRUE);
	ShowSeps[7] = m_ck7;
	((CViewPortView *)m_pParent)->DrawScene();	
}

void CSepDlg::OnCheck8() 
{
	UpdateData(TRUE);
	ShowSeps[8] = m_ck8;
	((CViewPortView *)m_pParent)->DrawScene();	
}

void CSepDlg::OnCheck9() 
{
	UpdateData(TRUE);
	ShowSeps[9] = m_ck9;
	((CViewPortView *)m_pParent)->DrawScene();	
}

void CSepDlg::RefreshView()
{
	ShowSeps[0] = m_ck1;
	ShowSeps[1] = m_ck2;
	ShowSeps[2] = m_ck3;
	ShowSeps[3] = m_ck4;
	ShowSeps[4] = m_ck5;
	ShowSeps[5] = m_ck6;
	ShowSeps[6] = m_ck6;
	ShowSeps[7] = m_ck7;
	ShowSeps[8] = m_ck8;
	ShowSeps[9] = m_ck9;
	((CViewPortView *)m_pParent)->DrawScene();	
}
