// VisDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ViewPort.h"
#include "VisDlg.h"

#include "ViewPortView.h"
#include "DoFap.h"
#include "DoExpVisem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVisDlg dialog


CVisDlg::CVisDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVisDlg::IDD, pParent)
{
	m_pParent=pParent;				//For Modalless
	m_nID=CVisDlg::IDD;				//For Modalless

	//{{AFX_DATA_INIT(CVisDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CVisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVisDlg)
	DDX_Control(pDX, IDC_VISEMS, m_viss);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVisDlg, CDialog)
	//{{AFX_MSG_MAP(CVisDlg)
	ON_BN_CLICKED(IDC_SAVEVIS, OnSavevis)
	ON_LBN_SELCHANGE(IDC_VISEMS, OnSelchangeVisems)
	ON_BN_CLICKED(IDC_SAVEVISTAB, OnSavevistab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisDlg message handlers

void CVisDlg::OnOK() 
{
	// TODO: Add extra validation here
	
//	CDialog::OnOK();
}

void CVisDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	((CViewPortView *)m_pParent)->m_pVisDlg = NULL;
	DestroyWindow();
	
//	CDialog::OnCancel();
}

BOOL CVisDlg::Create()
{
	return(CDialog::Create(m_nID,m_pParent));
}

void CVisDlg::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;	
//	CDialog::PostNcDestroy();
}

BOOL CVisDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_viss.ResetContent();
	m_viss.AddString("-");
	m_viss.AddString("a");
	m_viss.AddString("o");
	m_viss.AddString("e");
	m_viss.AddString("i");
	m_viss.AddString("u");
	m_viss.AddString("v");
	m_viss.AddString("b p m");
	m_viss.AddString("f");
	m_viss.AddString("d t n l");
	m_viss.AddString("g k h");
	m_viss.AddString("j q x");
	m_viss.AddString("zh ch sh r");
	m_viss.AddString("z c s");
	m_viss.AddString("-n");
	m_viss.AddString("-ng");

	m_viss.SetCurSel(0);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVisDlg::OnSelchangeVisems() 
{
	// TODO: Add your control notification handler code here
	cur_visem = m_viss.GetCurSel();
	RefreshDraw();
}

void CVisDlg::RefreshDraw()
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

void CVisDlg::OnSavevis() 
{
	// TODO: Add your control notification handler code here
	int vis, counter;
	vis = m_viss.GetCurSel();
	if(vis == 0)	return;

	vis --;
	for(counter=1;counter<=NO_FAPS;counter++)
	{
		vis_table[vis][counter] = (int)faps[counter];
	}
	
}

void CVisDlg::OnSavevistab() 
{
	// TODO: Add your control notification handler code here
	FILE * fp;
	int vis, counter;
	char vis_name[15][20] = {"a", "o", "e", "i", "u", "v", "b p m", "f", "d t n", "g k h", "j q x", "zh ch sh r", "z c s", "-n", "-ng"};
	
	fp = fopen("IST_visems", "w");
	if(fp == NULL)
	{
		AfxMessageBox("Write Vis Table Error!");
		return;
	}
	
	for(vis=0; vis<15; vis++)
	{
		fprintf(fp, "# %s\n", vis_name[vis]);
		
		for(counter=1; counter<=NO_FAPS; counter++)
		{
			if(vis_table[vis][counter])		fprintf(fp, "%d ", 1);
			else							fprintf(fp, "%d ", 0);
		}
		fprintf(fp, "\n");
		
		for(counter=1; counter<=NO_FAPS; counter++)
		{
			if(vis_table[vis][counter])
				fprintf(fp, "%d ", vis_table[vis][counter]);
		}
		fprintf(fp, "\n");
	}
	
	fclose (fp);
	
}
